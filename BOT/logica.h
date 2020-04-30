#ifndef UNTITLED_LOGICA_H
#define UNTITLED_LOGICA_H
#include "dados.h"
#include "lista.h"

int jogar(ESTADO *e, COORDENADA c);

int jogada_possivel (ESTADO *e, COORDENADA c);

void ler_tab(ESTADO *e, char *linha);

int ler_ficheiro (ESTADO *e, char linha []);

int retira_linha (char str[]);

int retira_coluna (char str[]);

int encurralado(ESTADO *e);

int check_around (ESTADO *e);

int check_lados (ESTADO *e);

int check_bottom(ESTADO *e);

int jogo_terminado (ESTADO *e);

void bestMove (ESTADO *e);

int check_vencedora (ESTADO *e, LISTA L);

COORDENADA get_cords(char *str);

int negamax (ESTADO *e, int depth, int player);

COORDENADA get_vencedor(LISTA L);

int scores(ESTADO *e);

void tabuleiro_ficheiro(ESTADO *e, char *linha);
#endif
