#include <stdlib.h>
#include "pilha.h"

void pilha_inicializar(Pilha *p) {
    // No inicio nao existe alteracao registrada no topo da pilha.
    p->topo = NULL;
    p->tamanho = 0;
}// Função para inicializar a pilha, definindo o topo como NULL e o tamanho como 0, 
// indicando que a pilha está vazia.

bool pilha_empilhar(Pilha *p, Chamado *c, Categoria cat, Prioridade pr, bool ehcat) {
    // Cada alteracao vira um no que guarda o chamado e os valores anteriores.
    Alteracao *a = malloc(sizeof *a);
    if (!a) {
        return false;
    }

    a->chamado = c;
    a->categoria_anterior = cat;
    a->prioridade_anterior = pr;
    a->alterou_categoria = ehcat;

    // O novo no aponta para a alteracao que estava no topo.
    // Depois ele passa a ser o novo topo da pilha.
    a->proximo = p->topo;
    p->topo = a;
    p->tamanho++;

    return true;
}// Função para adicionar uma alteração à pilha, criando um novo nó que armazena o chamado,
// a categoria e prioridade anteriores, e um indicador se a categoria foi alterada. O novo
// nó é adicionado ao topo da pilha, e o tamanho da pilha é incrementado. Retorna true se a
// operação foi bem-sucedida, ou false se não foi possível alocar memória para o novo nó.

Alteracao *pilha_desempilhar(Pilha *p) {
    // Uma pilha vazia nao possui um topo para remover.
    if (!p->topo) {
        return NULL;
    }

    // Guarda o topo, atualiza o ponteiro e decrementa o tamanho.
    Alteracao *a = p->topo;
    p->topo = a->proximo;
    p->tamanho--;

    // Isola o no removido antes de libera-lo ou devolve-lo ao chamador.
    a->proximo = NULL;
    return a;
}// Função para remover e retornar a alteração do topo da pilha. Se a pilha estiver vazia,
// retorna NULL. Caso contrário, atualiza o ponteiro do topo para o próximo nó, decrementa
// o tamanho da pilha e isola o nó removido antes de retorná-lo ao chamador.

void pilha_destruir(Pilha *p) {
    Alteracao *a;

    // Remove e libera um no por vez ate que a pilha fique vazia.
    while ((a = pilha_desempilhar(p))) {
        free(a);
    }
}// Função para destruir a pilha, removendo e liberando cada nó da pilha até que ela fique
// vazia.
