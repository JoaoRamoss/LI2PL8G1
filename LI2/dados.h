/**
 * @file dados.h
 * Defiinição da camada dados.
 */

#ifndef LI2_DADOS_H
#define LI2_DADOS_H
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
} ESTADO;

/**
 * \brief Função para inicializar o estado do jogo, colocando todas as peças do tabuleiro como "VAZIO" menos na posição "e5"
 * que fica definida como "BRANCA".
 * @return O Estado do jogo ja inicializado.
 */
ESTADO *inicializar_estado();

/**
 * \brief Obtem o jogador atual
 * @param estado Estado atual do jogo.
 * @return Jogador atual.
 */
int obter_jogador_atual(ESTADO *estado);

/**
 * \brief Obtem o numero de jogadas.
 * @param estado Estado atual do jogo.
 * @return O número de jogadas efetuadas.
 */
int obter_numero_de_jogadas(ESTADO *estado);

/**
 * \brief Obtem o estado atual da peca numa determinada casa.
 * @param e Estado atual do jogo.
 * @param c Coordenada introduzida pelo utilizador.
 * @return O estado da casa pedida.
 */
CASA obter_estado_casa(ESTADO *e, COORDENADA c);

/**
 * \brief Tem a mesma função que a funcao "obter_estado_casa" mas com input diferente.
 * @param e Estado atual do jogo
 * @param i Coordenada introduzida pelo utilizador
 * @param j Coordenada introduzida pelo utilizador.
 * @return O estado da casa pedida.
 */
CASA obter_casa (ESTADO *e, int i, int j);

/**
 * \brief Obtem os dados da coluna do array jogadas de um determinado jogador.
 * @param e Estado atual do jogo.
 * @param n Especificação de qual jogador se pretende obter informação (1 ou 2).
 * @param i Indice do array jogadas para obter informação.
 * @return O char correspondente à coordenada coluna na jogada "i".
 */
char obtem_dados_jogadas_col (ESTADO *e, int n, int i);

/**
 * \brief Obtem os dados da linha do array jogadas de um determinado jogador.
 * @param e Estado atual do jogo.
 * @param n Especificação de qual jogador se pretende obter informação (1 ou 2).
 * @param i Indice do array jogadas para obter informação.
 * @return O int correspondente à coordenada linha na jogada "i".
 */
int obtem_dados_jogadas_lin (ESTADO *e, int n, int i);

/**
 * \brief Tendo em conta os dados lidos pelo ficheiro, atualiza as casas do tabuleiro.
 * @param e Estado atual do jogo.
 * @param linha Linha obtida na leitura do ficheiro de texto na função "ler_ficheiro".
 * @param k Determina em que linha vao ser colocados os dados.
 */
void set_casa (ESTADO *e, char linha [], int k);

/**
 * \brief Função que coloca todas as jogadas anteriores no devido array na struct.
 * @param e Estado atual do jogo.
 * @param cord String de onde vão ser tiradas as coordenadas para serem colocadas como jogadas anteriores.
 * @param jog Variável que indica qual das partes das funções será utilizada (1 ou 2).
 * @param index Indice a ser usado para colocar os dados no array.
 */
void set_jogadas(ESTADO *e, char cord[], int jog, int index);

/**
 * \brief Função que dá update ao numero de jogadas atual, tendo em conta a informação do ficheiro.
 * @param e Estado atual do jogo.
 * @param k Valor da coordenada correspondente à linha.
 * @param i Valor da coordenada correspondente à coluna.
 * @return 1 caso seja realizado com suceso, 0 caso nao seja possivel realizar a operação.
 */
int update_num_jogadas (ESTADO *e, int k, int i);

/**
 * \brief Função auxiliar para a função "pos" na camada dados, atualiza o estado do jogo para que esta  seja executada com sucesso.
 * @param e Estado atual do jogo.
 * @param r Algarismo que vem a seguir ao comando "pos", ("pos 5", r = 5).
 */
void pos_helper (ESTADO *e, int r);

#endif
