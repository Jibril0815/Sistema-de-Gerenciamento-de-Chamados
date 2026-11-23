#include <stdlib.h>
#include "hash.h"
#include "historico.h"

static size_t indice(uint64_t id) {
    // O resto da divisao distribui o ID em um dos baldes da tabela.
    return (size_t) (id % HASH_CAPACIDADE);
}

void hash_inicializar(Hash *h) {
    // Todos os baldes recebem NULL, indicando que ainda nao tem nos.
    for (size_t i = 0; i < HASH_CAPACIDADE; i++) {
        h->baldes[i] = NULL;
    }
    h->tamanho = 0;
}

bool hash_inserir(Hash *h, Chamado *c) {
    // Um mesmo balde pode conter varios IDs; eles formam uma lista ligada.
    size_t i = indice(c->id);

    // Verifica se o ID ja existe para impedir chamados duplicados.
    for (NoHash *n = h->baldes[i]; n; n = n->proximo) {
        if (n->chamado->id == c->id) {
            return false;
        }
    }

    NoHash *n = malloc(sizeof *n);
    if (!n) {
        return false;
    }

    n->chamado = c;

    // Insere o novo no no inicio do balde: a operacao nao exige percorrer o fim.
    n->proximo = h->baldes[i];
    h->baldes[i] = n;
    h->tamanho++;

    return true;
}

Chamado *hash_buscar(const Hash *h, uint64_t id) {
    // Busca somente no balde correspondente ao ID informado.
    for (NoHash *n = h->baldes[indice(id)]; n; n = n->proximo) {
        if (n->chamado->id == id) {
            return n->chamado;
        }
    }

    return NULL;
}

void hash_destruir(Hash *h) {
    for (size_t i = 0; i < HASH_CAPACIDADE; i++) {
        NoHash *n = h->baldes[i];

        // Percorre cada balde e libera o historico, o chamado e o no da tabela.
        while (n) {
            NoHash *p = n->proximo;
            historico_destruir(n->chamado);
            free(n->chamado);
            free(n);
            n = p;
        }

        h->baldes[i] = NULL;
    }

    h->tamanho = 0;
}
