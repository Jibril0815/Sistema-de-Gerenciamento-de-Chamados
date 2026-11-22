#ifndef FILA_H
#define FILA_H
#include "chamado.h"

typedef struct NoFila { 
    Chamado *chamado;
    struct NoFila *proximo; 
} NoFila;

typedef struct { 
    NoFila *inicio, *fim; size_t tamanho; 
} Fila;

void fila_inicializar(Fila *fila);
bool fila_enfileirar(Fila *fila, Chamado *chamado);
Chamado *fila_frente(const Fila *fila);
Chamado *fila_desenfileirar(Fila *fila);
void fila_destruir(Fila *fila);

#endif
