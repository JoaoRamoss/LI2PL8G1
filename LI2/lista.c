#include "lista.h"
#include "lista.h"
#include <stdlib.h>
LISTA criar_lista () {
    LISTA r;
    r = malloc(sizeof(Nodo));
    r = NULL;
    return r;
}

LISTA insere_cabeca(LISTA L, void *valor) {
    LISTA r;
    r = malloc(sizeof(Nodo));
    r->head = valor;
    r->proximo = L;
    return r;
}

void *devolve_cabeca(LISTA L) {
    return L->head;
}

LISTA proximo(LISTA L) {
    return L->proximo;
}

LISTA remove_cabeca(LISTA L) {
    L = L->proximo;
    return L;
}

int lista_esta_vazia(LISTA L) {
    int r;
    if (L==NULL)
        r = 1;
    else
        r = 0;
    return r;
}
