use crate::chamado::Chamado;

/// Estrutura da Pilha (LIFO - Last In, First Out)
/// Usada para gerenciar alterações administrativas reversíveis (desfazer).
pub struct Pilha {
    dados: Vec<Chamado>,
}

impl Pilha {
    /// Cria uma nova pilha vazia
    pub fn novo() -> Self {
        Pilha { dados: Vec::new() }
    }

    /// Empilha um chamado no topo da pilha
    pub fn empilhar(&mut self, chamado: Chamado) {
        self.dados.push(chamado);
    }

    /// Remove e retorna o chamado do topo da pilha
    pub fn desempilhar(&mut self) -> Option<Chamado> {
        self.dados.pop()
    }

    /// Retorna uma referência ao chamado do topo sem removê-lo
    pub fn topo(&self) -> Option<&Chamado> {
        self.dados.last()
    }

    /// Verifica se a pilha está vazia
    pub fn vazia(&self) -> bool {
        self.dados.is_empty()
    }

    /// Retorna o número de elementos na pilha
    pub fn tamanho(&self) -> usize {
        self.dados.len()
    }
}
