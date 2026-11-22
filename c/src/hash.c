#include <stdlib.h>
#include "hash.h"
#include "historico.h"
static size_t indice(uint64_t id) { return (size_t)(id % HASH_CAPACIDADE); }
void hash_inicializar(Hash *h) { for (size_t i=0;i<HASH_CAPACIDADE;i++) h->baldes[i]=NULL; h->tamanho=0; }
bool hash_inserir(Hash *h, Chamado *c) {
    size_t i=indice(c->id); for (NoHash *n=h->baldes[i];n;n=n->proximo) if(n->chamado->id==c->id) return false;
    NoHash *n=malloc(sizeof *n); if(!n) return false; n->chamado=c; n->proximo=h->baldes[i]; h->baldes[i]=n; h->tamanho++; return true;
}
Chamado *hash_buscar(const Hash *h,uint64_t id) { for(NoHash *n=h->baldes[indice(id)];n;n=n->proximo) if(n->chamado->id==id) return n->chamado; return NULL; }
void hash_destruir(Hash *h) { for(size_t i=0;i<HASH_CAPACIDADE;i++){ NoHash *n=h->baldes[i]; while(n){NoHash *p=n->proximo;historico_destruir(n->chamado);free(n->chamado);free(n);n=p;}h->baldes[i]=NULL;}h->tamanho=0; }
