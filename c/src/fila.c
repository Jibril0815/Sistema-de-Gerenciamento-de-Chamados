#include <stdlib.h>
#include "fila.h"
void fila_inicializar(Fila *f) { f->inicio = f->fim = NULL; f->tamanho = 0; }
bool fila_enfileirar(Fila *f, Chamado *c) {
    NoFila *n = malloc(sizeof *n); if (!n) return false;
    n->chamado = c; n->proximo = NULL;
    if (f->fim) f->fim->proximo = n; else f->inicio = n;
    f->fim = n; f->tamanho++; return true;
}
Chamado *fila_frente(const Fila *f) { return f->inicio ? f->inicio->chamado : NULL; }
Chamado *fila_desenfileirar(Fila *f) {
    if (!f->inicio) return NULL;
    NoFila *n = f->inicio; Chamado *c = n->chamado; f->inicio = n->proximo;
    if (!f->inicio) f->fim = NULL; free(n); f->tamanho--; return c;
}
void fila_destruir(Fila *f) { while (fila_desenfileirar(f)) {} }
