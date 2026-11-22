#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "historico.h"

bool historico_adicionar(Chamado *c,const char *s) {
    Evento *e = malloc(sizeof *e);
    if (!e) {
        return false;
    }

    (void) snprintf(e->descricao, sizeof e->descricao, "%s", s);
    e->proximo = NULL;

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

    while (e) {
        Evento *p = e->proximo;
        free(e);
        e = p;
    }

    c->historico_inicio = c->historico_fim = NULL;
}
