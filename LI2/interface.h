/**
 * @file interface.h
 * Definicao da camada interface.
 */
#ifndef LI2_INTERFACE_H
#define LI2_INTERFACE_H
#include "dados.h"
#include <stdio.h>
/**
 * \brief Imprime o tabuleiro.
 * @param e Estado do jogo.
 */
void mostrar_tabuleiro(ESTADO *e);

/**
 * \brief Interpretador do jogo, todos os comandos sao efetuados nesta função.
 * @param e Estado do jogo.
 * @return 1 caso a operação seja efetuada com sucesso.
 */
int interpretador(ESTADO *e);

/**
 * \brief Função que imprime o tabuleiro no ficheiro criado pelo utilizador com o comando "gr".
 * @param e Estado atual do jogo.
 * @param fp apontador do ficheiro, usado para escrever no documento de texto.
 */
void imprime_fileTab (ESTADO *e, FILE *fp);

/**
 * \brief Função que imprime as jogadas anteriores no ficheiro criado pelo utilizador com o comando "gr".
 * @param e Estado atual do jogo.
 * @param fp apontador do ficheiro, usado para escrever no documento de texto.
 */
void file_posAnt (ESTADO *e, FILE *fp);

void movs(ESTADO *e);
#endif
