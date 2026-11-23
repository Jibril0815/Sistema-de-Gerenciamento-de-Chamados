#include <stdlib.h>
#include "pilha.h"

void pilha_inicializar(Pilha *p) {
    // No inicio nao existe alteracao registrada no topo da pilha.
    p->topo = NULL;
    p->tamanho = 0;
}

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
}

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
}

void pilha_destruir(Pilha *p) {
    Alteracao *a;

    // Remove e libera um no por vez ate que a pilha fique vazia.
    while ((a = pilha_desempilhar(p))) {
        free(a);
    }
}
