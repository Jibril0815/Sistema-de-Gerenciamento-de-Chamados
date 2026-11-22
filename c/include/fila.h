#ifndef FILA_H
#define FILA_H
#include "chamado.h"

// A fila é uma estrutura de dados que segue o princípio FIFO (First In, First Out), 
// ou seja, o primeiro elemento a ser inserido é o primeiro a ser removido. 
// Neste caso, a fila é utilizada para gerenciar os chamados que estão aguardando triagem.

typedef struct NoFila { 
    Chamado *chamado; // Ponteiro para o chamado armazenado no nó
    struct NoFila *proximo; // Ponteiro para o próximo nó na fila
} NoFila; // Estrutura para representar um nó na fila, contendo um ponteiro para o chamado
// e um ponteiro para o próximo nó

typedef struct { 
    NoFila *inicio, *fim; size_t tamanho; 
} Fila; // Estrutura para representar a fila de chamados

void fila_inicializar(Fila *fila); // Função para inicializar a fila

bool fila_enfileirar(Fila *fila, Chamado *chamado);// Função para adicionar um chamado à fila

Chamado *fila_frente(const Fila *fila); // Função para obter o chamado na frente da fila sem removê-lo

Chamado *fila_desenfileirar(Fila *fila); // Função para remover e retornar o chamado da frente da fila

void fila_destruir(Fila *fila); // Função para destruir a fila

#endif
