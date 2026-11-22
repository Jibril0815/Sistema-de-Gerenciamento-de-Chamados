#ifndef HASH_H
#define HASH_H
#include "chamado.h"
#define HASH_CAPACIDADE 1021u

// A tabela hash é uma estrutura de dados que permite armazenar e buscar elementos de forma eficiente,
// utilizando uma função de hash para mapear chaves (neste caso, o ID do chamado) para índices
// em um array.

typedef struct NoHash { 
    Chamado *chamado; struct NoHash *proximo; 
} NoHash; // Estrutura para representar um nó na tabela hash, 
// contendo um ponteiro para o chamado e um ponteiro para o próximo nó na lista encadeada

typedef struct { 
    NoHash *baldes[HASH_CAPACIDADE]; size_t tamanho; 
} Hash; // Estrutura para representar a tabela hash,
// contendo um array de ponteiros para os baldes (listas encadeadas) e o
// tamanho atual da tabela hash

void hash_inicializar(Hash *hash); // Função para inicializar a tabela hash

bool hash_inserir(Hash *hash, Chamado *chamado); // Função para inserir um chamado na tabela hash

Chamado *hash_buscar(const Hash *hash, uint64_t id); // Função para buscar um chamado na tabela hash 
//pelo ID

void hash_destruir(Hash *hash); // Função para destruir a tabela hash
#endif
