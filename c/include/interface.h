#ifndef INTERFACE_H
#define INTERFACE_H
#include "gerenciamento.h"

// A interface é responsável por interagir com o usuário, apresentando opções de gerenciamento de 
// chamados e recebendo entradas para realizar ações no sistema. Ela utiliza as funções do sistema de
// gerenciamento para cadastrar, listar, triar, iniciar atendimento, concluir, alterar categoria e
// prioridade dos chamados.

void interface_executar(Sistema *sistema);

#endif
