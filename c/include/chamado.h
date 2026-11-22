#ifndef CHAMADO_H
#define CHAMADO_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef enum { STATUS_TRIAGEM, STATUS_PENDENTE, STATUS_ATENDIMENTO, STATUS_CONCLUIDO } Status;
typedef enum { PRIORIDADE_BAIXA, PRIORIDADE_MEDIA, PRIORIDADE_ALTA, PRIORIDADE_CRITICA } Prioridade;
typedef enum { CAT_HARDWARE, CAT_SOFTWARE, CAT_REDE, CAT_ACESSO, CAT_OUTROS } Categoria;

typedef struct Evento {
    char descricao[192];
    struct Evento *proximo;
} Evento;

typedef struct Chamado {
    uint64_t id;
    uint64_t ordem_chegada;
    char solicitante[96];
    char titulo[128];
    char descricao[512];
    Status status;
    Prioridade prioridade;
    Categoria categoria;
    Evento *historico_inicio;
    Evento *historico_fim;
} Chamado;

const char *status_nome(Status valor);
const char *prioridade_nome(Prioridade valor);
const char *categoria_nome(Categoria valor);

#endif
