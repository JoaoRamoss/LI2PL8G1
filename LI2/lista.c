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
    LISTA tmp;
    tmp = L;
    L = proximo(L);
    free(tmp);
    return L;
}

int lista_esta_vazia(LISTA L) {
    int r;
    ///> Caso r seja 1, a lista é vazia, caso seja 0, a lista não é vazia.
    if (L==NULL)
        r = 1;
    else
        r = 0;
    return r;
}
