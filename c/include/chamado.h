#ifndef CHAMADO_H
#define CHAMADO_H

#include <stdbool.h> // Para o tipo bool
#include <stddef.h> // Para o tipo size_t
#include <stdint.h> // Para os tipos uint64_t e int64_t

typedef enum { 
    STATUS_TRIAGEM, STATUS_PENDENTE, STATUS_ATENDIMENTO, STATUS_CONCLUIDO 
} Status; // Enumeração para representar o status de um chamado

typedef enum { 
    PRIORIDADE_BAIXA, PRIORIDADE_MEDIA, PRIORIDADE_ALTA, PRIORIDADE_CRITICA 
} Prioridade; // Enumeração para representar a prioridade de um chamado

typedef enum { 
    CAT_HARDWARE, CAT_SOFTWARE, CAT_REDE, CAT_ACESSO, CAT_OUTROS 
} Categoria; // Enumeração para representar a categoria de um chamado

typedef struct Evento {
    char descricao[192];
    struct Evento *proximo; // Ponteiro para o próximo evento na lista
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
    Evento *historico_inicio; // Ponteiro para o início da lista de eventos do chamado
    Evento *historico_fim; // Ponteiro para o fim da lista de eventos do chamado
} Chamado;

const char *status_nome(Status valor); // Função para obter o nome de um status
const char *prioridade_nome(Prioridade valor); // Função para obter o nome de uma prioridade
const char *categoria_nome(Categoria valor); // Função para obter o nome de uma categoria

#endif
