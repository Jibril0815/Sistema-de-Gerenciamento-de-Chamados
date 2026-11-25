use std::collections::VecDeque;
use crate::chamado::Chamado; 

struct Fila {
    dados: VecDeque<Chamado>,
}

impl Fila {
    fn novo() -> Self {
        Fila { dados: VecDeque::new() }
    }// Construtor: cria uma fila vazia

    fn enfileirar(&mut self, chamado: Chamado) {
        self.dados.push_back(chamado);
    }// Insere um chamado no final da fila 

    fn desenfileirar(&mut self) -> Option<Chamado> {
        self.dados.pop_front()
    }// Remove e retorna o chamado no início da fila, se houver algum

    fn frente (&self) -> Option<&Chamado> {
        self.dados.front()
    }// Retorna uma referência ao chamado no início da fila, sem removê-lo

    fn tamanho(&self) -> usize {
        self.dados.len()
    }// Retorna o número de chamados na fila

    fn verificar_fila (&self) -> bool {
        self.dados.is_empty()
    }// Verifica se a fila está vazia
}