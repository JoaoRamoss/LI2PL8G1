#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
LISTA criar_lista () {
    LISTA r;
    r = malloc(sizeof(Nodo));
    r->proximo = NULL;
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

int lengthLista (LISTA L) {
    LISTA T;
    int i = 0;
    for (T = L; T->proximo != NULL; T = T->proximo)
        i++;

    return i;
}


LISTA add_livres (ESTADO *e, LISTA L) {
    int col = e->ultima_jogada.coluna, lin = e->ultima_jogada.linha;
    ///> Verifica se a peca branca esta em um dos cantos e dependendo disto, decide qual das duas funcoes chamar (add_cantos() ou add_around()).
    if ((col == 7 && lin == 7) || (col == 0 && lin == 0))
       L =  add_cantos(e, L);
    else if (lin == 7 || lin == 0)
        L = add_bottom(e, L);
    else if (col == 7 || col ==  0)
        L = add_lados(e, L);
    else
        L = add_arround(e, L);
    return L;
}


LISTA add_cantos(ESTADO *e, LISTA L) {
    int col = e->ultima_jogada.coluna, lin = e->ultima_jogada.linha;
    char cord[4];
    if (col == 0 && lin == 0) {
        if (obter_casa(e, lin, col + 1) == VAZIO) {
            sprintf(cord, "%d %d", lin, col+1);
            L = insere_cabeca(L, strdup(cord));
        }
        if (obter_casa(e, lin+1, col+1) == VAZIO) {
            sprintf(cord, "%d %d", lin+1, col+1);
            L = insere_cabeca(L, strdup(cord));
        }
        if (obter_casa(e, lin+1, col) == VAZIO) {
            sprintf(cord, "%d %d", lin+1, col);
            L = insere_cabeca(L, strdup(cord));
        }
    }
    else if (col == 7 && lin == 7) {
        if (obter_casa(e, lin, col-1) == VAZIO) {
            sprintf(cord, "%d %d", lin, col-1);
            L = insere_cabeca(L, strdup(cord));
        }
        if (obter_casa(e, lin-1, col-1) == VAZIO) {
            sprintf(cord, "%d %d", lin-1, col-1);
            L = insere_cabeca(L, strdup(cord));
        }
        if(obter_casa(e, lin-1, col) == VAZIO) {
            sprintf(cord, "%d %d", lin-1, col);
            L = insere_cabeca(L, strdup(cord));
        }
    }
    return L;
}

LISTA add_arround (ESTADO *e, LISTA L) {
    int col = e->ultima_jogada.coluna, lin = e->ultima_jogada.linha;
    char cord[4];
    ///> Passa as coordenadas como strings para a lista.
    if (obter_casa(e, lin, col + 1) == VAZIO || obter_casa(e, lin, col + 1) == UM || obter_casa(e, lin, col + 1) == DOIS) {
        sprintf(cord, "%d %d", lin, col+1); //Usa-se sprintf para passar as coordenadas como strings ("transforma" int em char).
        L = insere_cabeca(L, strdup(cord));
    }
    if (obter_casa(e, lin+1, col+1) == VAZIO || obter_casa(e, lin+1, col+1) == UM || obter_casa(e, lin+1, col+1) == DOIS) {
        sprintf(cord, "%d %d", lin+1, col+1);
        L = insere_cabeca(L, strdup(cord));
    }
    if (obter_casa(e, lin+1, col) == VAZIO || obter_casa(e, lin+1, col) == UM || obter_casa(e, lin+1, col) == DOIS) {
        sprintf(cord, "%d %d", lin+1, col);
        L = insere_cabeca(L, strdup(cord));
    }
    if (obter_casa(e, lin, col-1) == VAZIO || obter_casa(e, lin, col-1) == UM || obter_casa(e, lin, col-1) == DOIS) {
        sprintf(cord, "%d %d", lin, col-1);
        L = insere_cabeca(L, strdup(cord));
    }
    if (obter_casa(e, lin-1, col-1) == VAZIO || obter_casa(e, lin-1, col-1) == UM || obter_casa(e, lin-1, col-1) == DOIS) {
        sprintf(cord, "%d %d", lin-1, col-1);
        L = insere_cabeca(L, strdup(cord));
    }
    if(obter_casa(e, lin-1, col) == VAZIO || obter_casa(e, lin-1, col) == UM || obter_casa(e, lin-1, col) == DOIS) {
        sprintf(cord, "%d %d", lin-1, col);
        L = insere_cabeca(L, strdup(cord));
    }
    if (obter_casa(e, lin-1, col+1) == VAZIO || obter_casa(e, lin-1, col+1) == UM || obter_casa(e, lin-1, col+1) == DOIS) {
        sprintf(cord, "%d %d", lin-1, col+1);
        L = insere_cabeca(L, strdup(cord));
    }
    if(obter_casa(e, lin+1, col-1) == VAZIO || obter_casa(e, lin+1, col-1) == UM || obter_casa(e, lin+1, col-1) == DOIS) {
        sprintf(cord, "%d %d", lin+1,col-1);
        L = insere_cabeca(L, strdup(cord));
    }
return L;
}

LISTA add_lados (ESTADO *e, LISTA L) {
    int col = e->ultima_jogada.coluna, lin = e->ultima_jogada.linha;
    char cord[4];
    if (col == 0) {
        if (obter_casa(e, lin, col - 1) == VAZIO || obter_casa(e, lin, col - 1) == UM || obter_casa(e, lin, col - 1) == DOIS){
            sprintf(cord, "%d %d", lin, col-1);
            L = insere_cabeca(L, strdup(cord));
        }
        if (obter_casa(e, lin - 1, col + 1) == VAZIO || obter_casa(e, lin - 1, col + 1) == UM || obter_casa(e, lin - 1, col + 1) == DOIS) {
            sprintf(cord, "%d %d", lin-1,col+1);
            L = insere_cabeca(L, strdup(cord));
        }
        if (obter_casa(e, lin, col + 1) == VAZIO || obter_casa(e, lin, col + 1) == UM || obter_casa(e, lin, col + 1) == DOIS) {
            sprintf(cord, "%d %d", lin, col+1);
            L = insere_cabeca(L, strdup(cord));
        }
        if (obter_casa(e, lin + 1, col + 1) == VAZIO || obter_casa(e, lin + 1, col + 1) == UM || obter_casa(e, lin + 1, col + 1) == DOIS) {
            sprintf(cord, "%d %d", lin+1, col+1);
            L = insere_cabeca(L, strdup(cord));
        }
        if (obter_casa(e, lin - 1, col) == VAZIO || obter_casa(e, lin + 1, col + 1) == UM || obter_casa(e, lin + 1, col + 1) == DOIS) {
            sprintf(cord, "%d %d", lin-1, col);
            L = insere_cabeca(L, strdup(cord));
        }
            return L;
    } else {
        if (obter_casa(e, lin-1 , col) == VAZIO || obter_casa(e, lin-1 , col) == UM || obter_casa(e, lin-1 , col) == DOIS){
            sprintf(cord, "%d %d", lin-1, col);
            L = insere_cabeca(L, strdup(cord));
        }
        if (obter_casa(e, lin - 1, col - 1) == VAZIO || obter_casa(e, lin - 1, col - 1) == UM || obter_casa(e, lin - 1, col - 1) == DOIS) {
            sprintf(cord, "%d %d", lin-1,col-1);
            L = insere_cabeca(L, strdup(cord));
        }
        if (obter_casa(e, lin, col - 1) == VAZIO || obter_casa(e, lin, col - 1) == UM || obter_casa(e, lin, col - 1) == DOIS) {
            sprintf(cord, "%d %d", lin, col-1);
            L = insere_cabeca(L, strdup(cord));
        }
        if (obter_casa(e, lin + 1, col - 1) == VAZIO || obter_casa(e, lin + 1, col - 1) == UM || obter_casa(e, lin + 1, col - 1) == DOIS) {
            sprintf(cord, "%d %d", lin+1, col-1);
            L = insere_cabeca(L, strdup(cord));
        }
        if (obter_casa(e, lin + 1, col) == VAZIO || obter_casa(e, lin + 1, col) == UM || obter_casa(e, lin + 1, col) == DOIS) {
            sprintf(cord, "%d %d", lin+1, col);
            L = insere_cabeca(L, strdup(cord));
        }
        return L;
    }
}


LISTA add_bottom (ESTADO  *e, LISTA L) {
    int lin = e->ultima_jogada.linha, col = e->ultima_jogada.coluna;
    char cord[4];
    if (lin == 0) {
        if (obter_casa(e, lin, col + 1) == VAZIO || obter_casa(e, lin, col + 1) == UM || obter_casa(e, lin, col + 1) == DOIS) {
            sprintf(cord, "%d %d", lin, col + 1);
            L = insere_cabeca(L, strdup(cord));
        } if (obter_casa(e, lin + 1, col + 1) == VAZIO || obter_casa(e, lin + 1, col + 1) == UM || obter_casa(e, lin + 1, col + 1) == DOIS) {
            sprintf(cord, "%d %d", lin + 1, col + 1);
            L = insere_cabeca(L, strdup(cord));
        } if (obter_casa(e, lin + 1, col) == VAZIO || obter_casa(e, lin + 1, col) == UM || obter_casa(e, lin + 1, col) == DOIS) {
            sprintf(cord, "%d %d", lin + 1, col);
            L = insere_cabeca(L, strdup(cord));
        } if (obter_casa(e, lin + 1, col - 1) == VAZIO || obter_casa(e, lin + 1, col - 1) == UM || obter_casa(e, lin + 1, col - 1) == DOIS) {
            sprintf(cord, "%d %d", lin + 1, col - 1);
            L = insere_cabeca(L, strdup(cord));
        } if (obter_casa(e, lin, col - 1) == VAZIO || obter_casa(e, lin, col - 1) == UM || obter_casa(e, lin, col - 1) == DOIS) {
            sprintf(cord, "%d %d", lin, col - 1);
            L = insere_cabeca(L, strdup(cord));
        }
        return L;
    } else {
        if (obter_casa(e, lin, col - 1) == VAZIO) {
            sprintf(cord, "%d %d", lin, col - 1);
            L = insere_cabeca(L, strdup(cord));
        }if (obter_casa(e, lin - 1, col - 1) == VAZIO) {
            sprintf(cord, "%d %d", lin - 1, col - 1);
            L = insere_cabeca(L, strdup(cord));
        } if (obter_casa(e, lin - 1, col) == VAZIO) {
            sprintf(cord, "%d %d", lin - 1, col);
            L = insere_cabeca(L, strdup(cord));
        } if (obter_casa(e, lin - 1, col + 1) == VAZIO) {
            sprintf(cord, "%d %d", lin - 1, col + 1);
            L = insere_cabeca(L, strdup(cord));
        } if (obter_casa(e, lin, col + 1) == VAZIO) {
            sprintf(cord, "%d %d", lin, col + 1);
            L = insere_cabeca(L, strdup(cord));
        }
        return L;
    }
}

void freeLista (LISTA L) {
    while (!lista_esta_vazia(L)) {
        void *str = devolve_cabeca(L);
        L = remove_cabeca(L);
        free(str);
    }
}