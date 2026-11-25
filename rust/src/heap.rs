use std::collections::BinaryHeap;
use crate::chamado::{Chamado, Prioridade};

// Estrutura que envolve o BinaryHeap
struct HeapPrioridade {
    heap: BinaryHeap<Chamado>,
}

impl HeapPrioridade {
    /// Cria um novo heap vazio
    fn novo() -> Self {
        // O BinaryHeap já começa vazio
        HeapPrioridade { heap: BinaryHeap::new() }
    }

    /// Insere um chamado no heap (mantendo a ordem dePrioridade)
    fn inserir(&mut self, chamado: Chamado) {
        // O BinaryHeap usa a trait Ord do Chamado para ordenar.
        // Como implementamos o Ord inversamente (maiorPrioridade primeiro), 
        // ele já coloca no lugar correto.
        self.heap.push(chamado);
    }

    /// Retorna o chamado de maiorPrioridade SEM remover
    fn maximo(&self) -> Option<&Chamado> {
        self.heap.peek()
    }

    /// Remove e retorna o chamado de maiorPrioridade
    fn extrair_maximo(&mut self) -> Option<Chamado> {
        self.heap.pop()
    }

    /// Verifica se o heap está vazio
    fn vazia(&self) -> bool {
        self.heap.is_empty()
    }

    /// Tamanho do heap
    fn tamanho(&self) -> usize {
        self.heap.len()
    }
}