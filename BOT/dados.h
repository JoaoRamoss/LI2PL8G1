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

ESTADO *inicializar_estado();

int obter_jogador_atual(ESTADO *estado);

int obter_numero_de_jogadas(ESTADO *estado);

void reset_max_num_jogadas (ESTADO *e);

void update_tab (ESTADO *e, int lin, int col);

void set_ultima_jogada (ESTADO *e, int lin, int col);

void atualiza_jogada (ESTADO *e, int col, int lin);

CASA obter_estado_casa(ESTADO *e, COORDENADA c);

int ultima_linha (ESTADO *e);

int ultima_coluna (ESTADO *e);

void copyStruct (ESTADO *e, ESTADO *aux);

CASA obter_casa (ESTADO *e, int i, int j);

char obtem_dados_jogadas_col (ESTADO *e, int n, int i);

int obtem_dados_jogadas_lin (ESTADO *e, int n, int i);
#endif
