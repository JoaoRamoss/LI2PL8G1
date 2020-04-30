#ifndef UNTITLED_INTERFACE_H
#define UNTITLED_INTERFACE_H
#include "dados.h"
#include <stdio.h>

/**
 * \brief Imprime o tabuleiro no ficheiro.
 * @param e Estado atual do jogo.
 * @param fp File pointer.
 */
void imprime_fileTab (ESTADO *e, FILE *fp);

/**
 * \brief Imprime as jogadas anteriores no ficheiro.
 * @param e Estado atual do jogo.
 * @param fp File pointer.
 */
void file_posAnt (ESTADO *e, FILE *fp);
#endif
