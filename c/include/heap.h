#ifndef HEAP_H
#define HEAP_H
#include "chamado.h"

// O heap é uma estrutura de dados que permite armazenar elementos de forma ordenada,
// de modo que o maior elemento (ou o menor, dependendo da implementação) esteja sempre no topo. 
// Neste caso, o heap é utilizado para gerenciar os chamados que estão aguardando atendimento,
// garantindo que o chamado com maior prioridade seja atendido primeiro.

typedef struct { 
    Chamado **itens; 
    size_t tamanho, capacidade; 
} Heap; // Estrutura para representar o heap de chamados,
// contendo um array de ponteiros para os chamados, o tamanho atual do heap e a capacidade

void heap_inicializar(Heap *heap); // Função para inicializar o heap

bool heap_reservar(Heap *heap, size_t minimo); // Função para reservar espaço no heap, 
// garantindo que ele tenha pelo menos a capacidade mínima especificada

bool heap_inserir(Heap *heap, Chamado *chamado);// Função para inserir um chamado no heap, 
//mantendo a ordem de prioridade

Chamado *heap_maximo(const Heap *heap);// Função para obter o chamado com maior prioridade no heap 
//sem removê-lo

Chamado *heap_extrair_maximo(Heap *heap);// Função para remover e retornar o chamado com maior 
//prioridade no heap

bool heap_reordenar(Heap *heap, Chamado *chamado); // Função para reordenar o heap após uma alteração
// na prioridade de um chamado, garantindo que a ordem de prioridade seja mantida

void heap_destruir(Heap *heap); // Função para destruir o heap, liberando a memória alocada para os 
//chamados e para o próprio heap

#endif
