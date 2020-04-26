#include "logica.h"
#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#define BUF_SIZE 1024
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <limits.h>
#include <time.h>

int jogar(ESTADO *e, COORDENADA c) {
    int lin = abs(c.linha - 8) - 1;
    int col = c.coluna;
    if (jogada_possivel(e,c) == 1) {
        ///> Coloca a peça na posição pedida pelo utilizador.
        e->tab[lin][col] = BRANCA;
        ///> Coloca uma peça preta na casa anterior da peça branca.
        e->tab[(e->ultima_jogada).linha][(e->ultima_jogada).coluna] = PRETA;
        ///> Coloca a nova posição da peça branca como posição anterior para ser usada futuramente.
        e->ultima_jogada.coluna = col;
        e->ultima_jogada.linha = lin;
        atualiza_jogada(e, col, lin);
        return 1;
    }
    else
    return 0;
}


void atualiza_jogada (ESTADO *e, int col, int lin) {
    int jog = obter_jogador_atual(e);
    int jogadas = obter_numero_de_jogadas(e);
    ///> Determina se foi o jogador 1 ou 2 a jogar, e, consoante isto, coloca na array "jogadas" as informações correspondentes.
    if (jog == 1) {
        e->jogadas[jogadas].jogador1.linha = lin;
        e->jogadas[jogadas].jogador1.coluna = col;
    } else {
        e->jogadas[jogadas].jogador2.linha = lin;
        e->jogadas[jogadas].jogador2.coluna = col;
    }
    if (jog == 1)
        e->jogador_atual = 2;
    else {
        e->jogador_atual = 1;
        ///> Incrementa o numero de jogadas.
        if (e->num_jogadas >= e->max_num_jogadas) {
            e->num_jogadas++;
            e->max_num_jogadas++;
        }
        else
            e->num_jogadas++;
    }
}

// Verifica se a jogada pedida pelo utilizador é valida.
int jogada_possivel (ESTADO *e, COORDENADA c) {
    int lin = abs(c.linha - 8) - 1;
    if (obter_estado_casa(e,c) == BRANCA || obter_estado_casa(e,c) == PRETA ||
    abs((e->ultima_jogada.linha) - lin) > 1 || abs((e->ultima_jogada.coluna) - (c.coluna)) > 1
    || lin > 7  || lin < 0 || c.coluna >  7 || c.coluna < 0)
        return 0;
    else
        return 1;
}

//Verifica se o jogo terminou.
int jogo_terminado (ESTADO *e) {
    int r = 0;
    if ((e->ultima_jogada.coluna == 0 && e->ultima_jogada.linha == 7))
        r = 1;
    else if ((e ->ultima_jogada.linha == 0 && e->ultima_jogada.coluna == 7))
            r = 2;
    else if (e->num_jogadas == 31)
                r = 3;
    else if (encurralado(e) == 1)
        r = 4;
    else
        r = 0;
    return r;
}

int encurralado(ESTADO *e) {
    int col = e->ultima_jogada.coluna, lin = e->ultima_jogada.linha;
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
    int col = e->ultima_jogada.coluna, lin = e->ultima_jogada.linha;
    if (obter_casa(e, lin, col + 1) == PRETA && obter_casa(e, lin+1, col+1) == PRETA && obter_casa(e, lin+1, col) == PRETA &&
    obter_casa(e, lin, col-1) == PRETA && obter_casa(e, lin-1, col-1) == PRETA && obter_casa(e, lin-1, col) == PRETA && obter_casa(e, lin-1, col+1) == PRETA
    && obter_casa(e, lin+1, col-1) == PRETA)
        return 1;
    else
        return 0;
}

int check_lados (ESTADO *e) {
    int col = e->ultima_jogada.coluna, lin = e->ultima_jogada.linha;
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
    int col = e->ultima_jogada.coluna, lin = e->ultima_jogada.linha;
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

//Função usada para o comando gr (grava o estado de jogo num ficheiro).
void tabuleiro_ficheiro(ESTADO *e, char *linha) {
    char *comando;
    ///> Copia o nome do ficheiro presente na string "linha" e coloca na string "comando", e concatena ".txt" no final.
    strtok(linha, " ");
    comando = strtok(NULL, "\n");


    ///> Cria o ficheiro com o nome pedido pelo utilizador, ou abre-o, caso este ja exista.
    FILE *fp;
    fp = fopen(comando, "w");
    imprime_fileTab(e, fp);
    file_posAnt(e, fp);
    fclose(fp);
}


int ler_ficheiro (ESTADO *e, char linha []) {

    FILE *fp;
    char lin_fich [BUF_SIZE], *comando;
    int k = 0;
    int r = 0;
    ///> Copia o nome do ficheiro presente na string "linha" e coloca na string "comando", e concatena ".txt" no final.
    strtok(linha, " ");
    comando = strtok (NULL, "\n");
    ///> Abre o ficheiro pedido pelo utilizador e lê o seu conteúdo.
    //A função "access" retorna -1 caso nao encontre o ficheiro.
    if (access(comando, F_OK) != -1) {
        reinit(e);
        e->max_num_jogadas = 0;
        fp = fopen(comando, "r");
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

int pos (ESTADO *e, char *linha) {
    char *comando, *end;
    int r, max = obter_max_num_jog(e);
    strtok (linha, " ");
    comando = strtok(NULL, "\n");
    ///> Extrai o algarismo que é introduzido após o comando "pos" ("pos 5", extrai o "5").
    r = strtol (comando, &end, 10);
    ///> Verifica  que o comando "pos" apenas está a ser introduzido a uma jogada anterior e não à jogada atual.
    if (r < max + 1) {
        pos_helper(e, r);
        return 1;
    }
    else
        return 0;
}

//=====================//
//======= BOT ========//
//====================//

COORDENADA get_cords(char *str) {
    char *end;
    int col, lin;
    lin = strtol(str, &end,  10);
    col = strtol(end,  &end,10);
    COORDENADA cord = {col, abs(lin-8)-1};
    return cord;
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

void copyStruct (ESTADO *e, ESTADO *aux) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            aux->tab[i][j] = e->tab[i][j];
        }
    }
    aux->ultima_jogada = e->ultima_jogada;
    aux->jogador_atual = e->jogador_atual;
    aux->num_jogadas = e->num_jogadas;
}

//comando jog.
void jog (ESTADO *e) {
    ///> Adiciona na lista ligada todas as casas para onde é possivel jogar.
    LISTA L = criar_lista();
    L = add_livres(e, L);
    for(LISTA K = L; lista_esta_vazia(K) != 1; K = proximo(K)) {
        char *str = (char*)devolve_cabeca(K);
        printf("%s\n", str);
    }
    LISTA T = L;
    ///> Calcula a length da lista e gera um numero aleatorio  entre 0 e o length-1.
    int length = lengthLista(L);
    int random = rand() % length;
    char *str;
    ///> Tendo em conta o numero aleatorio gerado pela função rand(), joga com as coordenadas na posição  aleatoria da lista.
    for (int i = 0; i < random; i++)
        T = proximo(T);
    str = (char*) devolve_cabeca(T);
    COORDENADA jog = get_cords(str);
    jogar(e, jog);
    freeLista(L);
}

void jog2 (ESTADO *e) {
    int atual = obter_jogador_atual(e), bestScore = INT_MIN, score;
    COORDENADA melhorJogada;
    LISTA L = criar_lista();
    ///> Adiciona na lista ligada todas as posições para onde pode jogar.
    L = add_livres(e, L);
    ///> Analisa todas as posições presentes na lista e escolbe aquela que tiver o maior score.
    while (lista_esta_vazia(L) != 1) {
        ESTADO *aux = inicializar_estado();
        copyStruct(e, aux);
        char *str = (char*)devolve_cabeca(L);
        COORDENADA jogada = get_cords(str);
        jogar(aux,jogada);
        if (atual == 1)
            score = scores(aux);
        else
            score = scores(aux) * (-1);
        free(aux);
        if (score > bestScore) {
            bestScore = score;
            melhorJogada = jogada;
        }
        L = remove_cabeca(L);
    }
    jogar(e,melhorJogada);
}