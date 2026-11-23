#include <stdlib.h>
#include "heap.h"
static bool maior(const Chamado *a, const Chamado *b) {
    // Primeiro compara a prioridade numerica dos chamados.
    if (a->prioridade != b->prioridade) {
        return a->prioridade > b->prioridade;
    }

    // Em caso de empate, chega primeiro quem tem menor ordem de chegada.
    return a->ordem_chegada < b->ordem_chegada;
}

void heap_inicializar(Heap *h) {
    // O heap comeca sem vetor de itens e sem memoria reservada.
    h->itens = NULL;
    h->tamanho = h->capacidade = 0;
}

bool heap_reservar(Heap *h, size_t minimo) {
    // Nao reallocar quando a capacidade ja atende a quantidade necessaria.
    if (minimo <= h->capacidade) {
        return true;
    }

    // Comeca com capacidade oito e dobra ate atender ao minimo.
    size_t cap = h->capacidade ? h->capacidade : 8;
    while (cap < minimo) {
        if (cap > SIZE_MAX / 2) {
            return false;
        }
        cap *= 2;
    }

    // Realloca o vetor de ponteiros para os chamados, aumentando a capacidade.
    Chamado **p = realloc(h->itens, cap * sizeof *p);
    if (!p) {
        return false;
    }

    h->itens = p; // Atualiza o ponteiro do vetor de itens para o novo 
    //  endereço retornado pelo realloc
    h->capacidade = cap; // Atualiza a capacidade do heap para o novo valor

    return true;
}

static void subir(Heap *h, size_t i) {
    // Move o elemento para cima enquanto ele tiver prioridade maior
    // que o pai. Essa operacao mantem o maior elemento no indice zero.
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
        // Calcula os indices dos filhos esquerdo e direito.
        size_t e = i * 2 + 1;
        size_t d = e + 1;
        size_t m = i;

        // Escolhe o filho com maior prioridade para substituir o atual.
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
    // Garante que existe posicao no vetor antes de inserir.
    if (!heap_reservar(h, h->tamanho + 1)) {
        return false;
    }

    // Adiciona no final e faz o elemento subir ate sua posicao correta.
    h->itens[h->tamanho] = c;
    subir(h, h->tamanho++);

    return true;
}

Chamado *heap_maximo(const Heap *h) {
    return h->tamanho ? h->itens[0] : NULL;
}

Chamado *heap_extrair_maximo(Heap *h) {
    // O heap vazio nao possui elemento maximo.
    if (!h->tamanho) {
        return NULL;
    }

    // Guarda o primeiro elemento, que tem maior prioridade.
    Chamado *c = h->itens[0];
    h->tamanho--;

    // Move o ultimo elemento para a raiz e faz ele descer quando necessario.
    if (h->tamanho) {
        h->itens[0] = h->itens[h->tamanho];
        descer(h, 0);
    }

    return c;
}

bool heap_reordenar(Heap *h, Chamado *c) {
    // Procura o ponteiro do chamado dentro do vetor.
    for (size_t i = 0; i < h->tamanho; i++) {
        if (h->itens[i] == c) {
            subir(h, i);

            // Corrige todos os outros elementos que possam ter mudado de ordem.
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
