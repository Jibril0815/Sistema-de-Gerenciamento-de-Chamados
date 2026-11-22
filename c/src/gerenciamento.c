#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include "gerenciamento.h"
#include "historico.h"

const char *status_nome(Status v) {
    static const char *n[] = {
        "Aguardando triagem",
        "Pendente",
        "Em atendimento",
        "Concluido"
    };

    return v <= STATUS_CONCLUIDO ? n[v] : "Desconhecido";
}

const char *prioridade_nome(Prioridade v) {
    static const char *n[] = {
        "Baixa",
        "Media",
        "Alta",
        "Critica"
    };

    return v <= PRIORIDADE_CRITICA ? n[v] : "Desconhecida";
}

const char *categoria_nome(Categoria v) {
    static const char *n[] = {
        "Hardware",
        "Software",
        "Rede",
        "Acesso",
        "Outros"
    };

    return v <= CAT_OUTROS ? n[v] : "Desconhecida";
}

void sistema_inicializar(Sistema *s) {
    fila_inicializar(&s->triagem);
    heap_inicializar(&s->pendentes);
    hash_inicializar(&s->registros);
    pilha_inicializar(&s->alteracoes);
    s->proximo_id = 1;
    s->proxima_ordem = 1;
}

void sistema_destruir(Sistema *s) {
    fila_destruir(&s->triagem);
    heap_destruir(&s->pendentes);
    pilha_destruir(&s->alteracoes);
    hash_destruir(&s->registros);
}

Chamado *sistema_cadastrar(Sistema *s, const char *sol, const char *tit, const char *desc) {
    if (!sol || !tit || !desc || !*sol || !*tit || !*desc || s->proximo_id == UINT64_MAX) {
        return NULL;
    }

    Chamado *c = calloc(1, sizeof *c);
    if (!c) {
        return NULL;
    }

    c->id = s->proximo_id;
    c->ordem_chegada = s->proxima_ordem;
    (void) snprintf(c->solicitante, sizeof c->solicitante, "%s", sol);
    (void) snprintf(c->titulo, sizeof c->titulo, "%s", tit);
    (void) snprintf(c->descricao, sizeof c->descricao, "%s", desc);
    c->status = STATUS_TRIAGEM;
    c->prioridade = PRIORIDADE_BAIXA;
    c->categoria = CAT_OUTROS;

    if (!historico_adicionar(c, "Chamado cadastrado")
        || !fila_enfileirar(&s->triagem, c)) {
        historico_destruir(c);
        free(c);
        return NULL;
    }

    if (!hash_inserir(&s->registros, c)) {
        (void) fila_desenfileirar(&s->triagem);
        historico_destruir(c);
        free(c);
        return NULL;
    }

    s->proximo_id++;
    s->proxima_ordem++;
    return c;
}

bool sistema_triar_proximo(Sistema *s, Categoria cat, Prioridade pr) {
    if (cat > CAT_OUTROS || pr > PRIORIDADE_CRITICA) {
        return false;
    }

    Chamado *c = fila_frente(&s->triagem);
    if (!c) {
        return false;
    }
    if (!heap_reservar(&s->pendentes, s->pendentes.tamanho + 1)) {
        return false;
    }
    if (!historico_adicionar(c, "Chamado triado e enviado para a fila de prioridade")) {
        return false;
    }

    c->categoria = cat;
    c->prioridade = pr;
    c->status = STATUS_PENDENTE;

    if (!heap_inserir(&s->pendentes, c)) {
        c->status = STATUS_TRIAGEM;
        return false;
    }

    (void) fila_desenfileirar(&s->triagem);
    return true;
}

Chamado *sistema_iniciar_proximo(Sistema *s) {
    Chamado *c = heap_maximo(&s->pendentes);
    if (!c) {
        return NULL;
    }
    if (!historico_adicionar(c, "Atendimento iniciado")) {
        return NULL;
    }

    Chamado *rem = heap_extrair_maximo(&s->pendentes);
    if (rem != c) {
        if (rem) {
            (void) heap_inserir(&s->pendentes, rem);
        }
        return NULL;
    }

    c->status = STATUS_ATENDIMENTO;
    return c;
}

bool sistema_concluir(Sistema *s, uint64_t id) {
    Chamado *c = hash_buscar(&s->registros, id);
    if (!c || c->status != STATUS_ATENDIMENTO) {
        return false;
    }
    if (!historico_adicionar(c, "Chamado concluido")) {
        return false;
    }

    c->status = STATUS_CONCLUIDO;
    return true;
}

Chamado *sistema_buscar(const Sistema *s, uint64_t id) {
    return hash_buscar(&s->registros, id);
}

static bool alterar(Sistema *s, uint64_t id, bool cat, int valor) {
    Chamado *c = hash_buscar(&s->registros, id);
    if (!c || c->status != STATUS_PENDENTE) {
        return false;
    }

    if (cat) {
        if (valor < 0 || valor > CAT_OUTROS) {
            return false;
        }
        if (c->categoria == (Categoria) valor) {
            return true;
        }
    } else {
        if (valor < 0 || valor > PRIORIDADE_CRITICA) {
            return false;
        }
        if (c->prioridade == (Prioridade) valor) {
            return true;
        }
    }

    if (!pilha_empilhar(&s->alteracoes, c, c->categoria, c->prioridade, cat)) {
        return false;
    }
    if (!historico_adicionar(c, cat ? "Categoria alterada" : "Prioridade alterada")) {
        Alteracao *a = pilha_desempilhar(&s->alteracoes);
        free(a);
        return false;
    }

    if (cat) {
        c->categoria = (Categoria) valor;
    } else {
        c->prioridade = (Prioridade) valor;
        (void) heap_reordenar(&s->pendentes, c);
    }

    return true;
}

bool sistema_alterar_categoria(Sistema *s, uint64_t id, Categoria c) {
    return alterar(s, id, true, (int) c);
}

bool sistema_alterar_prioridade(Sistema *s, uint64_t id, Prioridade p) {
    return alterar(s, id, false, (int) p);
}

bool sistema_desfazer(Sistema *s) {
    while (s->alteracoes.topo) {
        Alteracao *a = pilha_desempilhar(&s->alteracoes);
        Chamado *c = a->chamado;

        if (c->status == STATUS_PENDENTE) {
            if (!historico_adicionar(c, "Ultima alteracao administrativa desfeita")) {
                a->proximo = s->alteracoes.topo;
                s->alteracoes.topo = a;
                s->alteracoes.tamanho++;
                return false;
            }

            if (a->alterou_categoria) {
                c->categoria = a->categoria_anterior;
            } else {
                c->prioridade = a->prioridade_anterior;
                (void) heap_reordenar(&s->pendentes, c);
            }

            free(a);
            return true;
        }

        free(a);
    }

    return false;
}

static void imprimir(const Chamado *c) {
    printf(
        "\n#%" PRIu64 " | %s | %s | %s"
        "\nSolicitante: %s"
        "\nTitulo: %s"
        "\nDescricao: %s\n",
        c->id,
        status_nome(c->status),
        categoria_nome(c->categoria),
        prioridade_nome(c->prioridade),
        c->solicitante,
        c->titulo,
        c->descricao
    );
}

void sistema_listar_status(const Sistema *s, Status st) {
    for (size_t i = 0; i < HASH_CAPACIDADE; i++) {
        for (NoHash *n = s->registros.baldes[i]; n; n = n->proximo) {
            if (n->chamado->status == st) {
                imprimir(n->chamado);
            }
        }
    }
}

void sistema_listar_todos(const Sistema *s) {
    for (size_t i = 0; i < HASH_CAPACIDADE; i++) {
        for (NoHash *n = s->registros.baldes[i]; n; n = n->proximo) {
            imprimir(n->chamado);
        }
    }
}

void sistema_listar_pendentes(const Sistema *s) {
    size_t n = s->pendentes.tamanho;
    if (!n) {
        return;
    }

    Chamado **c = malloc(n * sizeof *c);
    if (!c) {
        puts("Memoria insuficiente para ordenar a listagem.");
        return;
    }

    for (size_t i = 0; i < n; i++) {
        c[i] = s->pendentes.itens[i];
    }

    for (size_t i = 1; i < n; i++) {
        Chamado *v = c[i];
        size_t j = i;

        while (j
            && ((c[j - 1]->prioridade < v->prioridade)
                || (c[j - 1]->prioridade == v->prioridade
                    && c[j - 1]->ordem_chegada > v->ordem_chegada))) {
            c[j] = c[j - 1];
            j--;
        }

        c[j] = v;
    }

    for (size_t i = 0; i < n; i++) {
        imprimir(c[i]);
    }

    free(c);
}

void sistema_listar_historico(const Chamado *c) {
    if (!c) {
        return;
    }

    for (Evento *e = c->historico_inicio; e; e = e->proximo) {
        printf("- %s\n", e->descricao);
    }
}
