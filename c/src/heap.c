#include <stdlib.h>
#include "heap.h"
static bool maior(const Chamado *a, const Chamado *b) {
    if (a->prioridade != b->prioridade) {
        return a->prioridade > b->prioridade;
    }

    return a->ordem_chegada < b->ordem_chegada;
}

void heap_inicializar(Heap *h) {
    h->itens = NULL;
    h->tamanho = h->capacidade = 0;
}

bool heap_reservar(Heap *h, size_t minimo) {
    if (minimo <= h->capacidade) {
        return true;
    }

    size_t cap = h->capacidade ? h->capacidade : 8;
    while (cap < minimo) {
        if (cap > SIZE_MAX / 2) {
            return false;
        }
        cap *= 2;
    }

    Chamado **p = realloc(h->itens, cap * sizeof *p);
    if (!p) {
        return false;
    }

    h->itens = p;
    h->capacidade = cap;

    return true;
}

static void subir(Heap *h, size_t i) {
    while (i) {
        size_t p = (i - 1) / 2;
        if (!maior(h->itens[i], h->itens[p])) {
            break;
        }

        Chamado *t = h->itens[i];
        h->itens[i] = h->itens[p];
        h->itens[p] = t;
        i = p;
    }
}

static void descer(Heap *h, size_t i) {
    for (;;) {
        size_t e = i * 2 + 1;
        size_t d = e + 1;
        size_t m = i;

        if (e < h->tamanho && maior(h->itens[e], h->itens[m])) {
            m = e;
        }
        if (d < h->tamanho && maior(h->itens[d], h->itens[m])) {
            m = d;
        }
        if (m == i) {
            break;
        }

        Chamado *t = h->itens[i];
        h->itens[i] = h->itens[m];
        h->itens[m] = t;
        i = m;
    }
}

bool heap_inserir(Heap *h, Chamado *c) {
    if (!heap_reservar(h, h->tamanho + 1)) {
        return false;
    }

    h->itens[h->tamanho] = c;
    subir(h, h->tamanho++);

    return true;
}

Chamado *heap_maximo(const Heap *h) {
    return h->tamanho ? h->itens[0] : NULL;
}

Chamado *heap_extrair_maximo(Heap *h) {
    if (!h->tamanho) {
        return NULL;
    }

    Chamado *c = h->itens[0];
    h->tamanho--;

    if (h->tamanho) {
        h->itens[0] = h->itens[h->tamanho];
        descer(h, 0);
    }

    return c;
}

bool heap_reordenar(Heap *h, Chamado *c) {
    for (size_t i = 0; i < h->tamanho; i++) {
        if (h->itens[i] == c) {
            subir(h, i);

            for (size_t j = h->tamanho / 2; j > 0; j--) {
                descer(h, j - 1);
            }

            return true;
        }
    }

    return false;
}

void heap_destruir(Heap *h) {
    free(h->itens);
    h->itens = NULL;
    h->tamanho = h->capacidade = 0;
}
