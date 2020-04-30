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
    int max_num_jogadas;
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
 *\brief Obtem o número máximo de jogadas que o jogador pode introduzir no comando "pos".
 * @param e Estado atual do jogo.
 * @return O valor do máximo numero permitido no comando "pos".
 */
int obter_max_num_jog(ESTADO *e);

/**
 * \brief Coloca o "max_num_jogadas" igual ao valor de "num_jogadas".
 * @param e Estado atual do jogo.
 */
void set_max(ESTADO *e);

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

void set_ultima_jogada (ESTADO *e, int lin, int col);

void update_tab (ESTADO *e, int lin, int col);

/**
 * \brief Função (auxiliar) que atualiza os dados de forma a que a jogada fique realizada.
 * @param e Estado atual do jogo.
 * @param col posição da coluna.
 * @param lin posição da linha.
 */
void atualiza_jogada (ESTADO *e, int col, int lin);

int ultima_linha (ESTADO *e);

int ultima_coluna (ESTADO *e);

void reset_max_num_jogadas (ESTADO *e);

/**
 * \brief Função auxiliar para a função "pos" na camada dados, atualiza o estado do jogo para que esta  seja executada com sucesso.
 * @param e Estado atual do jogo.
 * @param r Algarismo que vem a seguir ao comando "pos", ("pos 5", r = 5).
 */
void pos_helper (ESTADO *e, int r);
/**
 * \brief Reinicializa o tabuleiro, colocando peças vazias em todas as casas exceto na casa  "e5".
 * @param e Estado atual do jogo.
 */
void reinit(ESTADO *e);

/**
 * \brief Função que atualiza os dados do jogo ao ler o ficheiro.
 * @param e Estado atual do jogo.
 * @param linha Linha obtida na função "ler_ficheiro()".
 */
void ler_tab(ESTADO *e, char *linha);

/**
 * \brief Copia um struct para um outro struct.
 * @param e Estado atual do jogo.
 * @param aux Struct auxiliar para onde vao ser copiadas as informações.
 */
void copyStruct (ESTADO *e, ESTADO *aux);
#endif
