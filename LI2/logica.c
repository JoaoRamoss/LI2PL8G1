#include "logica.h"
#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#define BUF_SIZE 1024
#include <string.h>
#include <unistd.h>
#include <ctype.h>

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
        e->num_jogadas++;
    }
}

// Verifica se a jogada pedida pelo utilizador é valida.
int jogada_possivel (ESTADO *e, COORDENADA c) {
    int lin = abs(c.linha - 8) - 1;
    if (obter_estado_casa(e,c) == BRANCA || obter_estado_casa(e,c) == PRETA ||
    abs((e->ultima_jogada.linha) - lin) > 1 || abs((e->ultima_jogada.coluna) - (c.coluna)) > 1) {

        return 0;
    }
    else return 1;
}

//Verifica se o jogo terminou.
int jogo_terminado (ESTADO *e) {
    int r = 0;
    if ((e->ultima_jogada.coluna == 0 && e->ultima_jogada.linha == 7))
        r = 1;
    else if ((e ->ultima_jogada.linha == 0 && e->ultima_jogada.coluna == 7))
            r = 2;
    else if (e->num_jogadas == 32)
                r = 3;
    else
        r = 0;
    return r;
}

//Função usada para o comando gr (grava o estado de jogo num ficheiro).
void tabuleiro_ficheiro(ESTADO *e, char *linha) {
    char *comando;
    ///> Copia o nome do ficheiro presente na string "linha" e coloca na string "comando", e concatena ".txt" no final.
    strtok(linha, " ");
    comando = strtok(NULL, "\n");
    strcat(comando, ".txt");

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
    strcat(comando, ".txt");
    ///> Abre o ficheiro pedido pelo utilizador e lê o seu conteúdo.
    //A função "access" retorna -1 caso nao encontre o ficheiro.
    if (access(comando, F_OK) != -1) {
        reinit(e);
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
    int r, max = obter_numero_de_jogadas(e);
    strtok (linha, " ");
    comando = strtok(NULL, "\n");
    ///> Extrai o algarismo que é introduzido após o comando "pos" ("pos 5", extrai o "5").
    r = strtol (comando, &end, 10);
    ///> Verifica  que o comando "pos" apenas está a ser introduzido a uma jogada anterior e não à jogada anterior.
    if (r < max + 1) {
        pos_helper(e, r);
        return 1;
    }
    else
        return 0;
}


