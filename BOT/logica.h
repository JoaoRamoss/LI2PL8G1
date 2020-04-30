#ifndef UNTITLED_LOGICA_H
#define UNTITLED_LOGICA_H
#include "dados.h"
#include "lista.h"

/**
 * \brief Efetua a jogada.
 * @param e Estado atual do jogo
 * @param c Coordenada oara onde jogar,
 * @return 1 caso seja realizado com sucesso.
 */
int jogar(ESTADO *e, COORDENADA c);

/**
 * \brief verifica se a jogada e possivel.
 * @param e Estado atual do jogo.
 * @param c Coordenada da jogada a avaliar.
 * @return 1 caso seja possivel.
 */
int jogada_possivel (ESTADO *e, COORDENADA c);

/**
 * \brief Função atualiza os dados do jogo ao ler o ficheiro.
 * @param e Estado Estado atual do jogo.
 * @param linha Linha lida pela função "ler_ficheiro".
 */
void ler_tab(ESTADO *e, char *linha);

/**
 * \brief Lê um ficheiro e atualiza o estado do jogo com o estado do jogo definido nesse ficheiro.
 * @param e Estado atual do jogo.
 * @param linha Linha obtida pela função "fgets()" no interpretador.
 * @return 1 caso consiga ler o ficheiro, 0  caso nao consiga.
 */
int ler_ficheiro (ESTADO *e, char linha []);

/**
 * \brief Converte a string no formato de dados do ficheiro criado pelo utilizador para um inteiro correspondente à linha.
 * @param str String de onde vao ser tirados os dados.
 * @return Uma posição para a linha do tabuleiro.
 */
int retira_linha (char str[]);

/**
 * \brief Converte a string no formato de dados do ficheiro criado pelo utilizador para um inteiro correspondente à coluna.
 * @param str String de onde vao ser tirados os dados.
 * @return Uma posição para a coluna do tabuleiro.
 */
int retira_coluna (char str[]);

/**
 *\brief Verifica se a peça está encurralada.
 * @param e Estado atual do jogo.
 * @return 1 caso esteja encurralada, 0 caso nao esteja.
 */
int encurralado(ESTADO *e);

/**
 * \brief Verifica se todas as casas a volta da peça branca estao preenchidas com peças pretas.
 * @param e Estado atual do jogo.
 * @return 1 caso a peca esteja encurralada, 0 caso nao esteja.
 */
int check_around (ESTADO *e);

/**
 * \brief Verifica todas as casas a volta da peca branca caso se encontre em col == 0 ou col == 7.
 * @param e Estado atual do jogo.
 * @return 1 caso a peca esteja encurralada.
 */
int check_lados (ESTADO *e);

/**
 * \brief Verifica todas as casas  a volta da peça branca caso se encontre em lin == 0 ou lin == 7;
 * @param e Estado atual do jogo.
 * @return 1 caso a peça esteja encurralada.
 */
int check_bottom(ESTADO *e);

/**
 * \brief Verifica se o jogo terminou.
 * @param e Estado do jogo.
 * @return 1 caso o jogador 1 ganhe, 2 caso o jogador ganhe, 0 caso ainda ninguem tenha ganho, 3 caso as jogadas acabem, ou 4 caso a peça fique encurralada.
 */
int jogo_terminado (ESTADO *e);

/**
 * \brief Função que invoca o minimax para decidir qual é a melhor jogada a realizar.
 * @param e Estado atual do jogo.
 */
void bestMove (ESTADO *e);

/**
 * \brief Verifica se o jogador se encontra na possibilidade de fazer uma jogada vencedora.
 * @param e Estado atual do jogo.
 * @param L Lista com posições possiveis.
 * @return 1 caso exista uma jogada vencedora.
 */
int check_vencedora (ESTADO *e, LISTA L);

/**
 * \brief
 * @param str
 * @param cords
 */
COORDENADA get_cords(char *str);

/**
 * \brief Variação do algoritmo "minimax".
 * @param e Cópia do estado do jogo.
 * @param depth Profundidade.
 * @param player Varia entre -1 e 1, dependendo de quem e a vez de jogar.
 * @return Score da posição onde a peça se encontra.
 */
int negamax (ESTADO *e, int depth, int player);

/**
 * \brief Caso exista uma jogada vencedora, obtem esta jogada.
 * @param L Lista de jogadas possiveis.
 * @return As coordenadas da jogada vencedora.
 */
COORDENADA get_vencedor(LISTA L);

/**
 * \brief Atribui uma pontuação a cada uma das casas do tabuleiro.
 * @param e Estado atual do jogo.
 * @return A pontuação final.
 */
int scores(ESTADO *e);

/**
 * \brief Coloca o tabuleiro e o estado do jogo num ficheiro
 * @param e Estado do jogo.
 * @param linha Nome do ficheiro onde vai ser guardado o estado.
 */
void tabuleiro_ficheiro(ESTADO *e, char *linha);
#endif
