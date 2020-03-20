/**
 * @file interface.h
 * Definicao da camada interface.
 */

#ifndef LI2_INTERFACE_H
#define LI2_INTERFACE_H
#include "dados.h"
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
 * \brief Coloca o tabuleiro e o estado do jogo num ficheiro
 * @param e Estado do jogo.
 * @param linha Nome do ficheiro onde vai ser guardado o estado.
 */
void tabuleiro_ficheiro(ESTADO *e, char linha[]);

#endif
