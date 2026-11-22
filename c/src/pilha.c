#include <stdlib.h>
#include "pilha.h"

void pilha_inicializar(Pilha *p) {
    p->topo = NULL;
    p->tamanho = 0;
}

bool pilha_empilhar(Pilha *p, Chamado *c, Categoria cat, Prioridade pr, bool ehcat) {
    Alteracao *a = malloc(sizeof *a);
    if (!a) {
        return false;
    }

    a->chamado = c;
    a->categoria_anterior = cat;
    a->prioridade_anterior = pr;
    a->alterou_categoria = ehcat;
    a->proximo = p->topo;
    p->topo = a;
    p->tamanho++;

    return true;
}

Alteracao *pilha_desempilhar(Pilha *p) {
    if (!p->topo) {
        return NULL;
    }

    Alteracao *a = p->topo;
    p->topo = a->proximo;
    p->tamanho--;
    a->proximo = NULL;

    return a;
}

void pilha_destruir(Pilha *p) {
    Alteracao *a;

    while ((a = pilha_desempilhar(p))) {
        free(a);
    }
}
