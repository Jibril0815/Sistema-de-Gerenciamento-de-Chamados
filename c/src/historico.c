#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "historico.h"

bool historico_adicionar(Chamado *c,const char *s) {
    // Aloca memoria para o novo evento do historico.
    Evento *e = malloc(sizeof *e);
    if (!e) {
        return false;
    }

    // Copia a descricao no limite do vetor para evitar escrever fora dele.
    (void) snprintf(e->descricao, sizeof e->descricao, "%s", s);
    e->proximo = NULL;

    // Conecta o evento ao fim da lista. Se a lista estiver vazia,
    // ele passa a ser tambem o primeiro evento.
    if (c->historico_fim) {
        c->historico_fim->proximo = e;
    } else {
        c->historico_inicio = e;
    }

    c->historico_fim = e;

    return true;
}

void historico_destruir(Chamado *c) {
    Evento *e = c->historico_inicio;

    // Percorre a lista guardando o proximo endereco antes de liberar o atual.
    while (e) {
        Evento *p = e->proximo;
        free(e);
        e = p;
    }

    // Limpa os ponteiros do chamado para nao apontarem para memoria liberada.
    c->historico_inicio = c->historico_fim = NULL;
}
