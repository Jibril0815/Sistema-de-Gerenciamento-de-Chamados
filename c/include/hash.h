#ifndef HASH_H
#define HASH_H
#include "chamado.h"
#define HASH_CAPACIDADE 1021u

typedef struct NoHash { 
    Chamado *chamado; struct NoHash *proximo; 
} NoHash;

typedef struct { 
    NoHash *baldes[HASH_CAPACIDADE]; size_t tamanho; 
} Hash;

void hash_inicializar(Hash *hash);
bool hash_inserir(Hash *hash, Chamado *chamado);
Chamado *hash_buscar(const Hash *hash, uint64_t id);
void hash_destruir(Hash *hash);
#endif
