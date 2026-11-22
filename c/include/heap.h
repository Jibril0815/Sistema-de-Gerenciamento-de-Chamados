#ifndef HEAP_H
#define HEAP_H
#include "chamado.h"

typedef struct { 
    Chamado **itens; 
    size_t tamanho, capacidade; 
} Heap;

void heap_inicializar(Heap *heap);
bool heap_reservar(Heap *heap, size_t minimo);
bool heap_inserir(Heap *heap, Chamado *chamado);
Chamado *heap_maximo(const Heap *heap);
Chamado *heap_extrair_maximo(Heap *heap);
bool heap_reordenar(Heap *heap, Chamado *chamado);
void heap_destruir(Heap *heap);
#endif
