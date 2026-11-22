#ifndef PILHA_H
#define PILHA_H
#include "chamado.h"
typedef struct Alteracao { Chamado *chamado; Categoria categoria_anterior; Prioridade prioridade_anterior; bool alterou_categoria; struct Alteracao *proximo; } Alteracao;
typedef struct { Alteracao *topo; size_t tamanho; } Pilha;
void pilha_inicializar(Pilha *pilha);
bool pilha_empilhar(Pilha *pilha, Chamado *chamado, Categoria categoria_anterior, Prioridade prioridade_anterior, bool categoria);
Alteracao *pilha_desempilhar(Pilha *pilha);
void pilha_destruir(Pilha *pilha);
#endif
