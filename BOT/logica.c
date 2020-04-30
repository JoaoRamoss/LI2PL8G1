#include "logica.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define BUF_SIZE 1024
#include <ctype.h>
#include "lista.h"
#include <limits.h>
#include "interface.h"

int jogar(ESTADO *e, COORDENADA c) {
    int lin = abs(c.linha - 8) - 1;
    int col = c.coluna;
    if (jogada_possivel(e, c) == 1) {
        update_tab(e, lin, col);
        ///> Coloca a nova posição da peça branca como posição anterior para ser usada futuramente.
        set_ultima_jogada(e, lin, col);
        atualiza_jogada(e, col, lin);
        return 1;
    } else
        return 0;
}

// Verifica se a jogada pedida pelo utilizador é valida.
int jogada_possivel (ESTADO *e, COORDENADA c) {
    int lin = abs(c.linha - 8) - 1;
    if (obter_estado_casa(e,c) == BRANCA || obter_estado_casa(e,c) == PRETA ||
        abs((ultima_linha(e)) - lin) > 1 || abs((ultima_coluna(e)) - (c.coluna)) > 1
        || lin > 7  || lin < 0 || c.coluna >  7 || c.coluna < 0)
        return 0;
    else
        return 1;
}



void ler_tab(ESTADO *e, char *linha) {
    int col, lin, col2, lin2;
    char *linha2, *cords;
    int i;
    strtok(linha, " ");
    linha2 = strtok  (NULL, "\n");
    for (i = 0; linha2[i] != '\0'; i++);
    strtok(linha2, " ");
    cords = strtok(NULL, "\n");
    if (i > 2) {
        col = retira_coluna(linha2);
        lin = abs(retira_linha(linha2)-8) - 1;
        col2 = retira_coluna(cords);
        lin2 = abs(retira_linha(cords)-8) - 1;
        COORDENADA coord = {col,lin};
        jogar(e,coord);
        COORDENADA coord2 = {col2, lin2};
        jogar(e, coord2);
    }
    else {
        col = retira_coluna(linha2);
        lin = abs(retira_linha(linha2)-8) - 1;
        COORDENADA coord = {col,lin};
        jogar(e,coord);
    }
}

int ler_ficheiro (ESTADO *e, char linha []) {
    FILE *fp;
    char lin_fich [BUF_SIZE];
    int k = 0;
    int r = 0;
    ///> Copia o nome do ficheiro presente na string "linha" e coloca na string "comando", e concatena ".txt" no final.
    ///> Abre o ficheiro pedido pelo utilizador e lê o seu conteúdo.
    //A função "access" retorna -1 caso nao encontre o ficheiro.
    if (access(linha, F_OK) != -1) {
        reset_max_num_jogadas(e);
        fp = fopen(linha, "r");
        while (fgets(lin_fich, BUF_SIZE, fp) != NULL) {
            ///> Ao ler o ficheiro, quando chega ao local onde se encontram as jogadas anteriores, chama a função "update_array_jogadas()".
            if (k >= 9) {
                ler_tab(e, lin_fich);
            }
            k++;
        }
        fclose(fp);
        r = 1;
    }
    else
        r = 0;
    return r;
}

int retira_linha (char str[]) {
    int r = 0;
    char *end;
    //Quando enconrtar algum elemento da string para a qual a funcao isdigit() devolva algum valor diferente de 0, converte-o num int e devolve-o.
    for (int i = 0; str[i] != '\0'; i++) {
        if (isdigit(str[i]) != 0) {
            r = strtol(&str[i], &end, 10);
            r = abs(r-8);
            return r;
        }
    }
    return 0;
}


int retira_coluna (char str[]) {
    int cord;
    //Quando a função isalpha() retornar algum valor diferente de 0, converte-o num int e devolve-o.f
    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha(str[i]) != 0) {
            cord = str[i] - 'a';
            return cord;
        }
    }
    return 0;
}


int encurralado(ESTADO *e) {
    int col = ultima_coluna(e), lin = ultima_linha(e);
    ///> Verifica primeiro se a peça está num dos cantos do tabuleiro, e, caso esteja, verifica se está encurralada.
    if (col == 0 && lin == 0) {
        if (obter_casa(e, lin, col + 1) == PRETA && obter_casa(e, lin+1, col+1) == PRETA && obter_casa(e, lin+1, col) == PRETA)
            return 1;
    }
    else if (col == 7 && lin == 7) {
        if (obter_casa(e, lin, col-1) == PRETA && obter_casa(e, lin-1, col-1) == PRETA && obter_casa(e, lin-1, col) == PRETA)
            return 1;
    }
    else if (col == 0 || col == 7) {
        if (check_lados(e) == 1)
            return 1;
    }
    else if (lin == 0 || lin == 7){
        if (check_bottom(e) == 1)
            return 1;
    }
        ///> Caso nao esteja em um dos cantos, chama a função "check_around()" para verificar se está ou nao encurralada.
    else if (check_around(e) == 1)
        return 1;

    return 0;
}

int check_around (ESTADO *e) {
    int col = ultima_coluna(e), lin = ultima_linha(e);
    if (obter_casa(e, lin, col + 1) == PRETA && obter_casa(e, lin+1, col+1) == PRETA && obter_casa(e, lin+1, col) == PRETA &&
        obter_casa(e, lin, col-1) == PRETA && obter_casa(e, lin-1, col-1) == PRETA && obter_casa(e, lin-1, col) == PRETA && obter_casa(e, lin-1, col+1) == PRETA
        && obter_casa(e, lin+1, col-1) == PRETA)
        return 1;
    else
        return 0;
}

int check_lados (ESTADO *e) {
    int col = ultima_coluna(e), lin = ultima_linha(e);
    if (col == 0) {
        if (obter_casa(e, lin-1, col) == PRETA && obter_casa(e, lin - 1, col + 1) == PRETA &&
            obter_casa(e, lin, col + 1) == PRETA &&
            obter_casa(e, lin + 1, col + 1) == PRETA && obter_casa(e, lin + 1, col) == PRETA)
            return 1;
    } else {
        if (obter_casa(e, lin-1, col) == PRETA && obter_casa(e, lin-1, col-1) == PRETA && obter_casa(e, lin, col-1) == PRETA &&
            obter_casa(e, lin+1,col-1) == PRETA && obter_casa(e, lin+1,col) == PRETA)
            return 1;
    }
    return 0;
}

int check_bottom(ESTADO *e) {
    int col = ultima_coluna(e), lin = ultima_linha(e);
    if (lin == 0) {
        if (obter_casa(e, lin, col+1) == PRETA && obter_casa(e, lin+1, col+1) == PRETA && obter_casa(e, lin+1, col) == PRETA
            && obter_casa(e, lin+1,col-1) == PRETA && obter_casa(e, lin, col-1) == PRETA)
            return 1;
    } else {
        if (obter_casa(e, lin, col-1) == PRETA && obter_casa(e, lin-1,col-1) == PRETA && obter_casa(e, lin-1, col) == PRETA &&
            obter_casa(e, lin-1, col+1) == PRETA && obter_casa(e, lin, col+1) == PRETA)
            return 1;
    }
    return 0;
}

//Verifica se o jogo terminou.
int jogo_terminado (ESTADO *e) {
    int r = 0;
    if ((ultima_coluna(e) == 0 && ultima_linha(e) == 7))
        r = 1;
    else if ((ultima_linha(e) == 0 && ultima_coluna(e) == 7))
        r = 2;
    else if (obter_numero_de_jogadas(e) == 31)
        r = 3;
    else if (encurralado(e) == 1)
        r = 4;
    else
        r = 0;
    return r;
}

void bestMove (ESTADO *e) {
    int bestScore = INT_MIN, score, atual = obter_jogador_atual(e);
    COORDENADA best_jogada;
    LISTA L =  criar_lista();
    L = add_livres(e, L);
    ///> Invoca o minimax com player = 1 caso seja o jogador 1 a jogar, e player = -1 caso seja o jogador 2.
    if (check_vencedora(e, L) != 1) {
        while (lista_esta_vazia(L) != 1) {
            char *str = (char *) devolve_cabeca(L);
            if (strncmp(str, "7 0", 3) != 0) {
                ESTADO *aux = inicializar_estado();
                copyStruct(e, aux);
                COORDENADA jog = get_cords(str);
                jogar(aux, jog);
                if (atual == 1)
                    score = negamax(aux, 5, 1);
                else
                    score = negamax(aux, 5, -1);
                free(aux);
                if (score > bestScore) {
                    bestScore = score;
                    best_jogada = jog;
                }
            }
            L = remove_cabeca(L);
        }
    }
    else
        best_jogada = get_vencedor(L);

    jogar(e, best_jogada);
}

int check_vencedora (ESTADO *e, LISTA L) {
    LISTA T;
    int atual = obter_jogador_atual(e);
    for (T = L; !lista_esta_vazia(T); T = proximo(T)) {
        char *str = (char *) devolve_cabeca(T);
        if (strncmp (str,"7 0", 3) == 0 && atual == 1)
            return 1;
    }
    return 0;
}

COORDENADA get_cords(char *str) {
    char *end;
    int col, lin;
    lin = strtol(str, &end,  10);
    col = strtol(end,  &end,10);
    COORDENADA cord = {col, abs(lin-8)-1};
    return cord;
}

int negamax (ESTADO *e, int depth, int player) {
    int bestScore = INT_MIN, score;
    LISTA L = criar_lista();
    L = add_livres(e, L);
    ///> Caso a depth seja = 0 ou esteja em posição terminal do jogo, da return do score (caso de paragem da função recursiva).
    if (depth == 0 || jogo_terminado(e)) {
        return (scores(e)*player);
    }
    ///> Analisa todas as peças possíveis e escolhe aquela que levar o jogador ao melhor score.
    while (lista_esta_vazia(L) != 1) {
        ESTADO *aux = inicializar_estado();
        copyStruct(e, aux);
        char *str = (char *) devolve_cabeca(L);
        COORDENADA jogada = get_cords(str);
        if (strncmp(str, "0 7", 3) == 0 || strncmp (str, "7 0", 3) == 0)
            return (scores(e)*(player));

        jogar(aux, jogada);
        score = -negamax(aux, depth - 1, player * (-1));
        free(aux);
        if (score > bestScore)
            bestScore = score;
        L = remove_cabeca(L);
    }
    return bestScore;
}

COORDENADA get_vencedor(LISTA L) {
    COORDENADA jogada = {0,0};
    while (lista_esta_vazia(L) != 1) {
        char *str = (char *) devolve_cabeca(L);
        if (strncmp(str, "7 0", 3) == 0) {
            jogada = get_cords(str);
            break;
        }
        L = remove_cabeca(L);
    }
    return jogada;
}

//funcao auxiliar do minimax
int scores(ESTADO *e) {
    ///> Cria uma tabela com os scores.
    ///> O score de uma dada casa é atribuido ao valor de (linha - coluna) de cada uma das casas.
    int tabela[8][8], score = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            tabela[i][j] = i-j;
        }
    }
    ///> Ao detetar em que posição do tabuleiro está a peça branca, dá return do score atribuido a essa posiçao.
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (obter_casa(e, i, j) == BRANCA)
                score = tabela[i][j];
        }
    }
    return score;
}

//Função usada para o comando gr (grava o estado de jogo num ficheiro).
void tabuleiro_ficheiro(ESTADO *e, char *linha) {
    ///> Cria o ficheiro com o nome pedido pelo utilizador, ou abre-o, caso este ja exista.
    FILE *fp;
    fp = fopen(linha, "w");
    imprime_fileTab(e, fp);
    file_posAnt(e, fp);
    fclose(fp);
}