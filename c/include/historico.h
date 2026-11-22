#ifndef HISTORICO_H
#define HISTORICO_H
#include "chamado.h"
bool historico_adicionar(Chamado *chamado, const char *descricao);
void historico_destruir(Chamado *chamado);
#endif
