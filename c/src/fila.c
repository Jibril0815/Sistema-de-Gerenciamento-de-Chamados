#include <stdlib.h>
#include "fila.h"

void fila_inicializar(Fila *f) {
    // Uma fila vazia nao possui primeiro nem ultimo elemento.
    // NULL indica que o ponteiro nao aponta para nenhum no da memoria.
    f->inicio = f->fim = NULL;

    // O contador acompanha a quantidade de nos armazenados na fila.
    f->tamanho = 0;
}

bool fila_enfileirar(Fila *f, Chamado *c) {
    // Aloca dinamicamente memoria para um novo no da fila.
    // sizeof *n calcula o tamanho necessario para armazenar um NoFila.
    NoFila *n = malloc(sizeof *n);

    // malloc retorna NULL quando nao consegue reservar memoria.
    if (!n) {
        return false;
    }

    // Cada no guarda o endereco de um Chamado e o endereco do proximo no.
    n->chamado = c;
    n->proximo = NULL;

    // Quando a fila nao esta vazia, o antigo ultimo no passa a apontar
    // para o novo no. O operador -> acessa um campo atraves do ponteiro.
    if (f->fim) {
        f->fim->proximo = n;
    } else {
        // Quando a fila esta vazia, o novo no sera tambem o primeiro no.
        f->inicio = n;
    }

    // Agora o novo no passa a ser o fim da fila.
    f->fim = n;
    f->tamanho++;

    return true;
}

Chamado *fila_frente(const Fila *f) {
    // Retorna o chamado armazenado no primeiro no, sem remove-lo da fila.
    // Se inicio for NULL, a fila esta vazia e a funcao retorna NULL.
    return f->inicio ? f->inicio->chamado : NULL;
}

Chamado *fila_desenfileirar(Fila *f) {
    // Nao existe elemento para remover quando o ponteiro inicio e NULL.
    if (!f->inicio) {
        return NULL;
    }

    // n aponta para o no que sera removido.
    // c guarda o endereco do Chamado para poder retorna-lo apos remover o no.
    NoFila *n = f->inicio;
    Chamado *c = n->chamado;

    // Inicio passa a apontar para o proximo no da fila.
    f->inicio = n->proximo;

    // Se nao restaram elementos, o ponteiro fim tambem precisa ficar vazio.
    if (!f->inicio) {
        f->fim = NULL;
    }

    // free libera a memoria reservada por malloc para o no removido.
    // O objeto Chamado apontado por c nao e liberado por esta funcao.
    free(n);
    f->tamanho--;

    // Retorna o chamado removido; a memoria dele continua existente.
    return c;
}

void fila_destruir(Fila *f) {
    // Enquanto houver chamados, fila_desenfileirar remove o primeiro no.
    // Ela libera a memoria dos nos, mas nao libera os objetos Chamado.
    while (fila_desenfileirar(f)) {
    }
}
