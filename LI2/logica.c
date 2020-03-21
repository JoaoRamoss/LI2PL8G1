#include "logica.h"
#include <stdio.h>
#include <stdlib.h>
#define BUF_SIZE 1024
#include <string.h>
#include <unistd.h>

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
    int j = 0;
    ///> Copia o nome do ficheiro presente na string "linha" e coloca na string "comando", e concatena ".txt" no final.
    comando = strtok(linha, " ");
    comando = strtok(NULL, "\n");
    strcat(comando, ".txt");

    ///> Cria o ficheiro com o nome pedido pelo utilizador, ou abre-o, caso este ja exista.
    FILE *fp;
    fp = fopen(comando, "w");
    imprime_fileTab(e, fp);
    file_posAnt(e, fp);
    fclose(fp);
}

//Imprime o tabuleiro no ficheiro.
void imprime_fileTab (ESTADO *e, FILE *fp) {
    ///> Imprime o conteudo do tabuleiro, imprimindo '*' no caso de a Peça ser "BRANCA",'#' no caso de a peça ser "PRETA", e '.' no caso de ser "VAZIO".
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            char peca = obter_casa(e, i, j);
            fprintf(fp, "%c", peca);
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "\n");
}

//Imprime todas as jogadas anteriores no ficheiro.
void file_posAnt (ESTADO *e, FILE *fp) {
    int jog = obter_jogador_atual(e);
    int num_jogadas = obter_numero_de_jogadas(e);
    ///> Coloca jogadas anteriores no ficheiro.
    if (jog == 2) {
        for (int i = 0; i <= num_jogadas; i++) {
            if(i < 10)
                fprintf(fp, "0%d: ",i+1);
            else
                fprintf(fp, "%d: ",i+1);

            if (i != num_jogadas) {
                fprintf(fp, "%c%d %c%d", obtem_dados_jogadas_col(e,1,i), obtem_dados_jogadas_lin(e,1,i),
                        obtem_dados_jogadas_col(e,2,i), obtem_dados_jogadas_lin(e,2,i));
            }
            else
                fprintf(fp,"%c%d",obtem_dados_jogadas_col(e,1,i), obtem_dados_jogadas_lin(e,1,i));
            fprintf(fp,"\n");
        }
    }

    if (jog == 1) {
        for (int i = 0; i < num_jogadas; i++) {
            if (i < 10)
                fprintf(fp, "0%d: ", i+1);
            else
                fprintf(fp, "%d: ", i+1);

            fprintf(fp, "%c%d %c%d",  obtem_dados_jogadas_col(e,1,i), obtem_dados_jogadas_lin(e,1,i),
                    obtem_dados_jogadas_col(e,2,i), obtem_dados_jogadas_lin(e,2,i));
            fprintf(fp, "\n");
        }
    }
}

int ler_ficheiro (ESTADO *e, char linha []) {

    FILE *fp;
    char lin_fich [BUF_SIZE], *comando, *cord;
    int k = 0;
    int i = 0;
    ///> Copia o nome do ficheiro presente na string "linha" e coloca na string "comando", e concatena ".txt" no final.
    comando = strtok(linha, " ");
    comando = strtok (NULL, "\n");
    strcat(comando, ".txt");

        fp = fopen(comando, "r");
        while(fgets(lin_fich,BUF_SIZE , fp) != NULL) {
            set_casa(e, lin_fich, k);
            k++;
        }
        set_estado(e, lin_fich);
     printf("%d%d \n", e->ultima_jogada.linha, e->ultima_jogada.coluna);
        fclose(fp);
        return 1;
}


