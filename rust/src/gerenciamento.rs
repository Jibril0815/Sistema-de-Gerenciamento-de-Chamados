use crate::chamado::{Chamado, Status, Prioridade, Categoria};
use crate::pilha::Pilha;
use crate::historico;
use std::collections::{BinaryHeap, HashMap, VecDeque};

pub struct Sistema {
    fila_triagem: VecDeque<Chamado>,
    heap_prioridade: BinaryHeap<Chamado>,
    hash_registros: HashMap<u64, Chamado>,
    pilha_alteracoes: Pilha,
    proximo_id: u64,
}

impl Sistema {
    pub fn novo() -> Self {
        Sistema {
            fila_triagem: VecDeque::new(),
            heap_prioridade: BinaryHeap::new(),
            hash_registros: HashMap::new(),
            pilha_alteracoes: Pilha::novo(),
            proximo_id: 1,
        }
    }

    pub fn cadastrar(&mut self, solicitante: &str, titulo: &str, descricao: &str) -> u64 {
        if solicitante.is_empty() || titulo.is_empty() || descricao.is_empty() {
            return 0;
        }

        let id = self.proximo_id;

        let chamado = Chamado::new(
            id,
            id,
            solicitante.to_string(),
            titulo.to_string(),
            descricao.to_string(),
            Status::AguardandoTriagem,
            Prioridade::Baixa,
            Categoria::Outros,
        );

        self.fila_triagem.push_back(chamado.clone());

        self.hash_registros.insert(id, chamado.clone());

        self.heap_prioridade.push(chamado.clone());

        self.pilha_alteracoes.empilhar(chamado.clone());
        historico::adicionar(&mut self.hash_registros.get_mut(&id).unwrap(), "Chamado cadastrado");

        id
    }

    pub fn triar_proximo(&mut self, categoria: Categoria, prioridade: Prioridade) -> Option<u64> {
        let chamado = self.fila_triagem.pop_front()?;

        let mut c = chamado;
        c.status = Status::Pendente;
        c.categoria = categoria;
        c.prioridade = prioridade;

        self.heap_prioridade.push(c.clone());

        self.hash_registros.insert(c.id, c.clone());

        self.pilha_alteracoes.empilhar(c.clone());
        historico::adicionar(&mut c, &format!(
            "Chamado {} triado (Cat: {}, Pri: {})",
            c.id,
            crate::chamado::categoria_nome(c.categoria),
            crate::chamado::prioridade_nome(c.prioridade)
        ));
        self.hash_registros.insert(c.id, c);

        Some(c.id)
    }

    pub fn iniciar_atendimento(&mut self) -> Option<u64> {
        let chamado = self.heap_prioridade.pop()?;

        let mut c = chamado;
        c.status = Status::EmAtendimento;

        self.pilha_alteracoes.empilhar(c.clone());
        historico::adicionar(&mut c, &format!("Atendimento iniciado ID {}", c.id));

        Some(c.id)
    }

    pub fn concluir(&mut self, id: u64) -> bool {
        let chamado = match self.hash_registros.get(&id) {
            Some(c) => c.clone(),
            None => return false,
        };

        if chamado.status != Status::EmAtendimento {
            return false;
        }

        let mut c = chamado;
        c.status = Status::Concluido;

        self.pilha_alteracoes.empilhar(c.clone());
        historico::adicionar(&mut c, &format!("Chamado {} concluido", id));

        self.hash_registros.insert(id, c);

        true
    }

    pub fn alterar_categoria(&mut self, id: u64, nova_categoria: Categoria) -> bool {
        let chamado = match self.hash_registros.get(&id) {
            Some(c) => c.clone(),
            None => return false,
        };

        if chamado.status != Status::Pendente {
            return false;
        }

        self.pilha_alteracoes.empilhar(chamado.clone());

        let mut c = chamado;
        historico::adicionar(&mut c, &format!(
            "Categoria alterada de {} para {}",
            crate::chamado::categoria_nome(c.categoria),
            crate::chamado::categoria_nome(nova_categoria)
        ));
        c.categoria = nova_categoria;

        self.hash_registros.insert(id, c);

        true
    }

    pub fn alterar_prioridade(&mut self, id: u64, nova_prioridade: Prioridade) -> bool {
        let chamado = match self.hash_registros.get(&id) {
            Some(c) => c.clone(),
            None => return false,
        };

        if chamado.status != Status::Pendente {
            return false;
        }

        self.pilha_alteracoes.empilhar(chamado.clone());

        let mut temp_vec = Vec::new();

        while let Some(mut c) = self.heap_prioridade.pop() {
            if c.id != id {
                temp_vec.push(c);
            } else {
                historico::adicionar(&mut c, &format!(
                    "Prioridade alterada de {} para {}",
                    crate::chamado::prioridade_nome(c.prioridade),
                    crate::chamado::prioridade_nome(nova_prioridade)
                ));
                c.prioridade = nova_prioridade;
                temp_vec.push(c);
            }
        }

        for c in temp_vec {
            self.heap_prioridade.push(c);
        }

        let mut c_hash = self.hash_registros.get(&id).unwrap().clone();
        c_hash.prioridade = nova_prioridade;
        self.hash_registros.insert(id, c_hash);

        true
    }

    pub fn desfazer(&mut self) -> bool {
        if self.pilha_alteracoes.vazia() {
            return false;
        }

        let acao = self.pilha_alteracoes.desempilhar();
        match acao {
            Some(_) => {
                println!("Ultima alteracao desfeita.");
                true
            }
            None => false,
        }
    }

    pub fn buscar(&self, id: u64) -> Option<&Chamado> {
        self.hash_registros.get(&id)
    }

    pub fn listar_todos(&self) {
        println!("\n--- Lista Completa de Chamados ---");
        for (id, chamado) in &self.hash_registros {
            println!(
                "#{} | {} | {} | {} | {} | Solicitante: {}",
                id,
                chamado.status_nome(),
                chamado.categoria_nome(),
                chamado.prioridade_nome(),
                chamado.titulo,
                chamado.solicitante
            );
        }
        println!("-----------------------------\n");
    }
}
