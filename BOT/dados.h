#ifndef UNTITLED_DADOS_H
#define UNTITLED_DADOS_H
/**
 * \brief Tipos diferentes de Casa que o tabuleiro pode ter.
 */
typedef enum {VAZIO = '.', BRANCA = '*', PRETA = '#', UM = '1', DOIS = '2'} CASA;
/**
 * \brief Struct para as coordenadas, sendo estas usadas para fazer jogadas.
 */
typedef struct {
    int coluna;
    int linha;
} COORDENADA;
/**
 * \brief Struct que guarda as coordenadas de um determinado jogador.
 */
typedef struct {
    COORDENADA jogador1;
    COORDENADA jogador2;
} JOGADA;
/**
 * \brief Array de structs do tipo "JOGADA", onde são guardadas as várias jogadas.
 */
typedef JOGADA JOGADAS[32];
/**
 * \brief Struct que guarda o estado atual do jogo (tabuleiro, ultima jogada, todas as jogadas efetuadas, numero total de  jogadas e o jogador atual).
 */
typedef struct {
    CASA tab[8][8];
    COORDENADA ultima_jogada;
    JOGADAS jogadas;
    int num_jogadas;
    int jogador_atual;
    int max_num_jogadas;
} ESTADO;

/**
 * \brief Inicializa o estado.
 * @return Estado inicializado.
 */
ESTADO *inicializar_estado();

/**
 * \brief Obtem um inteiro com o valor do jogador atual
 * @param estado Estado atual do jogo.
 * @return Inteiro com o valor do jogador atual.
 */
int obter_jogador_atual(ESTADO *estado);

/**
 * \brief Obtem o numero de jogadas.
 * @param estado Estado atual do jogo.
 * @return Inteiro com o valor do numero atual de jogadas.
 */
int obter_numero_de_jogadas(ESTADO *estado);

/**
 * \brief coloca max_num_jogadas = 0
 * @param e Estado atual do jogo.
 */
void reset_max_num_jogadas (ESTADO *e);

/**
 * \brief Atualiza o tabuleiro conforme a jogada do utilizador.
 * @param e Estado atual do jogo.
 * @param lin Linha
 * @param col Coluna
 */
void update_tab (ESTADO *e, int lin, int col);

/**
 * \brief Atualiza "ultima_jogada" como a jogada atual do utilizador.
 * @param e Estado atual do jogo.
 * @param lin Linha.
 * @param col Coluna.
 */
void set_ultima_jogada (ESTADO *e, int lin, int col);

/**
 * \brief Atualiza o array "jogadas".
 * @param e Estado atual do jogo.
 * @param col Coluna.
 * @param lin Linha.
 */
void atualiza_jogada (ESTADO *e, int col, int lin);

/**
 * \brief Obtem o estado de uma dada casa do tabuleiro.
 * @param e Estado atual do jogo.
 * @param c Coordenada da casa a avaliar.
 * @return VAZIO, BRANCA, PRETA, dependendo do estado em que a casa se encontre.
 */
CASA obter_estado_casa(ESTADO *e, COORDENADA c);

/**
 * \brief Obtem a coordenada da linha da ultima jogada.
 * @param e Estado atual do jogo.
 * @return Inteiro com o valor da coordenada da linha da ultima jogada.
 */
int ultima_linha (ESTADO *e);

/**
 * \brief Obtem a coordenada da coluna da ultima jogada.
 * @param e Estado atual do jogo.
 * @return Inteiro com o valor da coordenada da coluna da ultima jogada.
 */
int ultima_coluna (ESTADO *e);

/**
 * \brief Copia um struct para outro struct.
 * @param e Estado atual do jogo.
 * @param aux Struct para onde vai ser copiado "e".
 */
void copyStruct (ESTADO *e, ESTADO *aux);

/**
 * \brief Obtem o estado de uma casa do tabuleiro.
 * @param e Estado atual do jogo.
 * @param i Linha.
 * @param j Coluna.
 * @return VAZIO, PRETA, BRANCA, dependendo do estado da casa.
 */
CASA obter_casa (ESTADO *e, int i, int j);

/**
 * \brief obtem dados da coluna do array jogadas.
 * @param e Estado atual do jogo.
 * @param n Numero do jogador atual.
 * @param i Indice onde ir buscar os dados da coluna no array.
 * @return Char com a coordenada da coluna.
 */
char obtem_dados_jogadas_col (ESTADO *e, int n, int i);

/**
 * \brief Obtem dados da linha do array jogadas.
 * @param e Estado atual do jogo.
 * @param n Numero do jogador atual.
 * @param i Indice onde ir buscar os dados da linha no array.
 * @return
 */
int obtem_dados_jogadas_lin (ESTADO *e, int n, int i);
#endif
