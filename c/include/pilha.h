#ifndef PILHA_H
#define PILHA_H
#include "chamado.h"

// A pilha é uma estrutura de dados que segue o princípio LIFO (Last In, First Out),
// ou seja, o último elemento a ser inserido é o primeiro a ser removido.
// Neste caso, a pilha é utilizada para gerenciar as alterações feitas nos chamados,
// permitindo desfazer alterações recentes, como mudanças de categoria ou prioridade.

typedef struct Alteracao { 
    Chamado *chamado; // Ponteiro para o chamado que sofreu a alteração
    Categoria categoria_anterior; // Categoria anterior do chamado antes da alteração
    Prioridade prioridade_anterior; // Prioridade anterior do chamado antes da alteração
    bool alterou_categoria; // Indicador se a categoria foi alterada
    struct Alteracao *proximo; 
} Alteracao;// Estrutura para representar uma alteração feita em um chamado.

typedef struct { 
    Alteracao *topo; 
    size_t tamanho; 
} Pilha;

void pilha_inicializar(Pilha *pilha); // Função para inicializar a pilha

bool pilha_empilhar(Pilha *pilha, Chamado *chamado, Categoria categoria_anterior, Prioridade prioridade_anterior, bool categoria);
// Função para adicionar uma alteração à pilha, armazenando o chamado e suas informações anteriores

Alteracao *pilha_desempilhar(Pilha *pilha); // Função para remover e retornar a alteração do topo da 
// pilha, permitindo desfazer a alteração

void pilha_destruir(Pilha *pilha);// Função para destruir a pilha, liberando a memória alocada para 
// as alterações

#endif
