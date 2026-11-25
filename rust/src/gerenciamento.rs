use crate::chamado::{Chamado, Status, Prioridade, Categoria};
use std::collections::{BinaryHeap, HashMap, VecDeque};

pub struct Sistema{
    fila_triagem: VecDeque<Chamado>,
    heap_prioridade: BinaryHeap<Chamado>,
    hash_registros: HashMap<u64, Chamado>,
    pilha_historico: Vec<String>,
    proximo_id: u64,
}

impl Sistema {
    pub fn novo() -> Self {
        Sistema {
            fila_triagem: VecDeque::new(),
            heap_prioridade: BinaryHeap::new(),
            hash_registros: HashMap::new(),
            pilha_historico: Vec::new(),
            proximo_id: 1,
        }
    }

    pub fn cadastrar(&mut self, solicitante: &str, titulo: &str, descricao: &str) -> u64 {
        // Validação de entradas vazias
        if solicitante.is_empty() || titulo.is_empty() || descricao.is_empty() {
            return 0; // Retorna 0 para indicar falha
        }

        let id = self.proximo_id;

        let chamado = Chamado::new(
            id,
            id,
            solicitante.to_string(),
            titulo.to_string(),
            descricao.to_string(),
            Status::AguardandoTriagem,
            Prioridade::Baixa, // Definindo prioridade padrão como Baixa
            Categoria::OUTROS, // Definindo categoria padrão como OUTROS
            Vec::new(),
        );

        // Adiciona o chamado à fila de triagem e ao hash de registros
        self.fila_triagem.push_back(chamado.clone());

        // Registra na tabela hash para buscar por ID
        self.hash_registros.insert(id, chamado);

        // 3. Inserir no heap de prioridade (começa com prioridade baixa)
        self.heap_prioridade.push(chamado.clone());

        // 4. Adicionar evento inicial ao histórico/desfazer
        self.pilha_alteracoes.push_format("Chamado cadastrado ID {}", id);

        id // Retorna o ID do chamado recém-criado
    }

    pub fn triar_proximo (&mut self, categoria: Categoria, prioridade: Prioridade) -> Option<u64> {
        // 1. Pegar o primeiro da fila de triagem (FIFO)
        let chamado = self.fila_triagem.pop_front()?;

        // 2. Atualizar dados do chamado com os da triagem
        let mut c = chamado;
        c.status = Status::Pendente;
        c.categoria = categoria;
        c.prioridade = prioridade;

        // 2. Inserir no heap de prioridade (agora com a novaPrioridade)
        self.heap_prioridade.push(c.clone());

        // 3. Registrar na hash (atualiza o registro existente ou insere)
        self.hash_registros.insert(c.id, c.clone());

        // 4. Registrar no histórico de alterações
        self.pilha_alteracoes.push_format("Chamado {} triado (Cat: {}, Pri: {})", c.id, 
            crate::chamado::categoria_nome(c.categoria), 
            crate::chamado::prioridade_nome(c.prioridade));

        Some(c.id)
    }

    pub fn iniciar_atendimento(&mut self) -> Option<u64> {
        // 1. Pega o chamado de maiorPrioridade do heap
        let chamado = self.heap_prioridade.pop()?;

        // 2. Atualiza status para "Em Atendimento"
        let mut c = chamado;
        c.status = Status::EmAtendimento;

        // 3. Registrar no histórico
        self.pilha_alteracoes.push_format("Atendimento iniciado ID {}", c.id);

        // 4. Como retiramos do heap, não o inserimos de volta.
        // O próximo chamado de maiorPrioridade agora ficará no topo.

        Some(c.id)
    }

    pub fn concluir(&mut self, id: u64) -> bool {
        // 1. Buscar o chamado na hash
        let chamado = match self.hash_registros.get(&id) {
            Some(c) => c.clone(),
            None => return false,
        };

        // 2. Verificar se pode ser concluído (apenas se estiver em atendimento)
        if chamado.status != Status::EmAtendimento {
            return false;
        }

        // 2. Criar cópia para modificar
        let mut c = chamado;
        c.status = Status::Concluido;

        // 3. Registrar no histórico
        self.pilha_alteracoes.push_format("Chamado {} concluido", id);

        // 4. Atualizar na hash (sobrescreve o registro antigo)
        self.hash_registros.insert(id, c);

        true
    }

    pub fn alterar_categoria(&mut self, id: u64, nova_categoria: Categoria) -> bool {
        // 1. Buscar o chamado
        let chamado = match self.hash_registros.get(&id) {
            Some(c) => c.clone(),
            None => return false,
        };

        // 2. Só permite alterar se estiver Pendente
        if chamado.status != Status::Pendente {
            return false;
        }

        // 2. Registrar na pilha de Desfazer ANTES de alterar
        self.pilha_alteracoes.push_format("Alteração de categoria ID {} (de {} para {})", 
            id, 
            crate::chamado::categoria_nome(chamado.categoria), 
            crate::chamado::categoria_nome(nova_categoria));

        // 3. Atualizar a categoria no objeto
        let mut c = chamado;
        c.categoria = nova_categoria;

        // 4. Atualizar na hash
        self.hash_registros.insert(id, c);

        true
    }

    pub fn alterar_prioridade(&mut self, id: u64, nova_prioridade: Prioridade) -> bool {
        // 1. Buscar o chamado na hash
        let chamado = match self.hash_registros.get(&id) {
            Some(c) => c.clone(),
            None => return false,
        };

        // 2. Só permite alterar se estiver Pendente
        if chamado.status != Status::Pendente {
            return false;
        }

        // 3. Registrar na pilha de Desfazer
        self.pilha_alteracoes.push_format("Alteração dePrioridade ID {} (de {} para {})", 
            id, 
            crate::chamado::prioridade_nome(chamado.prioridade), 
            crate::chamado::prioridade_nome(nova_prioridade));

        // 4. Lógica para reordenar o Heap:
        // O BinaryHeap do Rust não tem "alterarPrioridade" embutido.
        // A estratégia aqui é: retirar o elemento, modificar e re-insere.
        // Como não temos um "remove by value" direto no BinaryHeap,
        // faremos o seguinte processo:
        
        let mut temp_vec = Vec::new();
        
        // Esvazia o heap atual temporariamente
        while let Some(c) = self.heap_prioridade.pop() {
            if c.id != id {
                // Mantém os outros no temp
                temp_vec.push(c);
            } else {
                // Encontramos o elemento. Vamos modificá-lo aqui.
                let mut c_mod = chamado; // Usa o chamado modificado
                c_mod.prioridade = nova_prioridade;
                temp_vec.push(c_mod); // Empilha o modificado
            }
        }

        // Agora re-empilha todos os elementos de volta no heap na ordem correta
        for c in temp_vec {
            self.heap_prioridade.push(c);
        }

        // 5. Atualizar a struct 'chamado' na hash (já fizemos isso logicamente acima, 
        // mas precisamos garantir que o objeto na hash tenha a novaPrioridade para consistência)
        let mut c_hash = self.hash_registros.get(&id).unwrap().clone();
        c_hash.prioridade = nova_prioridade;
        self.hash_registros.insert(id, c_hash);

        true
    }

    pub fn desfazer(&mut self) -> bool {
        let Some(acao) = self.pilha_alteracoes.pop() else {
            return false; // Pilha vazia
        };
        
        println!("Desfazendo ação: {}", acao);

        true
    }// faz a ação de desfazer a última alteração feita no sistema, retornando 
    //true se houver uma ação para desfazer e false caso contrário 

    pub fn buscar(&self, id: u64) -> Option<&Chamado> {
        self.hash_registros.get(&id)
    }

    pub fn listar_todos(&self) {
        println!("\n--- Lista Completa de Chamados ---");
        for (id, chamado) in &self.hash_registros {
            println!(
                "#{} | {} | {} | {} | {} | Solicitante: {}",
                id,
                crate::chamado::status_nome(chamando.status),
                crate::chamado::categoria_nome(chamando.categoria),
                crate::chamado::prioridade_nome(chamando.prioridade),
                chamando.titulo,
                chamando.solicitante
            );
        }
        println!("-----------------------------\n");
    }
}