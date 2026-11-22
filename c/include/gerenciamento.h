#ifndef GERENCIAMENTO_H
#define GERENCIAMENTO_H
#include "fila.h"
#include "hash.h"
#include "heap.h"
#include "pilha.h"

typedef struct { 
    Fila triagem; 
    Heap pendentes; 
    Hash registros; 
    Pilha alteracoes; 
    uint64_t proximo_id, proxima_ordem; 
} Sistema; // Estrutura para representar o sistema de gerenciamento de chamados

void sistema_inicializar(Sistema *sistema);
void sistema_destruir(Sistema *sistema);
Chamado *sistema_cadastrar(Sistema *sistema, const char *solicitante, const char *titulo, const char *descricao);
bool sistema_triar_proximo(Sistema *sistema, Categoria categoria, Prioridade prioridade);
Chamado *sistema_iniciar_proximo(Sistema *sistema);
bool sistema_concluir(Sistema *sistema, uint64_t id);
bool sistema_alterar_categoria(Sistema *sistema, uint64_t id, Categoria categoria);
bool sistema_alterar_prioridade(Sistema *sistema, uint64_t id, Prioridade prioridade);
bool sistema_desfazer(Sistema *sistema);
Chamado *sistema_buscar(const Sistema *sistema, uint64_t id);
void sistema_listar_status(const Sistema *sistema, Status status);
void sistema_listar_todos(const Sistema *sistema);
void sistema_listar_pendentes(const Sistema *sistema);
void sistema_listar_historico(const Chamado *chamado);
#endif
