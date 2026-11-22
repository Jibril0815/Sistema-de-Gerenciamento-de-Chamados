#ifndef HISTORICO_H
#define HISTORICO_H
#include "chamado.h"

 //O histórico é uma lista encadeada de eventos que registra todas as ações realizadas em um chamado,
 //como alterações de categoria, prioridade, status e conclusão. Cada evento contém uma descrição da 
 //ação

bool historico_adicionar(Chamado *chamado, const char *descricao); // Função para adicionar um evento 
// ao histórico de um chamado, adicionando uma descrição da ação realizada no final da lista de eventos

void historico_destruir(Chamado *chamado); // Função para destruir o histórico de um chamado, 
// liberando a memória alocada para os eventos

#endif
