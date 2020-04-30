#include "dados.h"
#include <stdlib.h>

ESTADO *inicializar_estado() {
    ESTADO *e = (ESTADO *) malloc(sizeof(ESTADO));
    for (int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            e -> tab[i][j] = VAZIO;
        }
    }
    ///> Atribui uma peca "BRANCA" na posição "e5".
    e -> tab[3][4] = BRANCA;
    e-> tab[7][0] = UM;
    e->tab[0][7] = DOIS;
    ///> Define como ultima jogada a peça inicial, para ser utilizado futuramente na funçao "jogar".
    (e -> ultima_jogada).coluna = 4;
    (e -> ultima_jogada).linha = 3;
    ///> Inicializa o numero de jogadas, atribuindo-lhe o valor '0'.
    e -> num_jogadas = 0;
    ///> Coloca como jogador atual o jogador 1, visto que o jogo começa sempre por ele.
    e -> jogador_atual = 1;
    e->max_num_jogadas = 0;
    return e;
}

int obter_jogador_atual(ESTADO *estado) {
    return estado -> jogador_atual;
}

int obter_numero_de_jogadas(ESTADO *estado) {
    return estado -> num_jogadas;
}

void reset_max_num_jogadas (ESTADO *e) {
    e->max_num_jogadas = 0;
}

void update_tab (ESTADO *e, int lin, int col) {
    ///> Coloca a peça na posição pedida pelo utilizador.
    e->tab[lin][col] = BRANCA;
    ///> Coloca uma peça preta na casa anterior da peça branca.
    e->tab[(e->ultima_jogada).linha][(e->ultima_jogada).coluna] = PRETA;
}

void set_ultima_jogada (ESTADO *e, int lin, int col) {
    e->ultima_jogada.coluna = col;
    e->ultima_jogada.linha = lin;
}

void atualiza_jogada (ESTADO *e, int col, int lin) {
    int jog = obter_jogador_atual(e);
    int jogadas = obter_numero_de_jogadas(e);
    ///> Determina se foi o jogador 1 ou 2 a jogar, e, consoante isto, coloca na array "jogadas" as informações correspondentes.
    if (jog == 1) {
        e->jogadas[jogadas].jogador1.linha = lin;
        e->jogadas[jogadas].jogador1.coluna = col;
    } else {
        e->jogadas[jogadas].jogador2.linha = lin;
        e->jogadas[jogadas].jogador2.coluna = col;
    }
    if (jog == 1)
        e->jogador_atual = 2;
    else {
        e->jogador_atual = 1;
        ///> Incrementa o numero de jogadas.
        if (e->num_jogadas >= e->max_num_jogadas) {
            e->num_jogadas++;
            e->max_num_jogadas++;
        }
        else
            e->num_jogadas++;
    }
}

CASA obter_estado_casa(ESTADO *e, COORDENADA c) {
    CASA r;
    int lin = abs(c.linha -8) - 1;
    r = e -> tab[lin][c.coluna];
    return r;
}

int ultima_linha (ESTADO *e) {
    return e->ultima_jogada.linha;
}

int ultima_coluna (ESTADO *e) {
    return e->ultima_jogada.coluna;
}

void copyStruct (ESTADO *e, ESTADO *aux) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            aux->tab[i][j] = e->tab[i][j];
        }
    }
    aux->ultima_jogada = e->ultima_jogada;
    aux->jogador_atual = e->jogador_atual;
    aux->num_jogadas = e->num_jogadas;
}

CASA obter_casa (ESTADO *e, int i, int j) {
    CASA r = e -> tab[i][j];
    return r;
}

char obtem_dados_jogadas_col (ESTADO *e, int n, int i) {
    if (n == 1) {
        return e->jogadas[i].jogador1.coluna + 'a';
    }
    else
        return e->jogadas[i].jogador2.coluna + 'a';
}

int obtem_dados_jogadas_lin (ESTADO *e, int n, int i) {
    int lin;
    if (n == 1) {
        lin = abs((e->jogadas[i].jogador1.linha + 1) - 8) + 1;
        return lin;
    }
    else
        lin = abs((e -> jogadas[i].jogador2.linha + 1) - 8) + 1;
    return lin;
}