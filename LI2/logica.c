#include "logica.h"
#include "dados.h"
#include <stdio.h>
#include <stdlib.h>
#define BUF_SIZE 1024
#include <string.h>

int jogar(ESTADO *e, COORDENADA c) {
    int lin = c.linha;
    int col = c.coluna;
    int jog = obter_jogador_atual(e);
    int jogadas = obter_numero_de_jogadas(e);

    if (jogada_possivel(e,c) == 1) {
        //Coloca a peça na posição pedida pelo utilizador.
        e->tab[lin][col] = BRANCA;
        //Coloca uma peça preta na casa anterior da peça branca.
        e->tab[(e->ultima_jogada).linha][(e->ultima_jogada).coluna] = PRETA;
        //Coloca a nova posição da peça branca como posição anterior para ser usada futuramente.
        e->ultima_jogada.coluna = col;
        e->ultima_jogada.linha = lin;

        //Determinar se foi o jogador 1 ou 2 a jogar, e, consoante isto, coloca na array "jogadas" as informações correspondentes.
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
            //Incrementa o numero de jogadas.
            e->num_jogadas++;
        }
        return 1;
    }
    else {
        while (jogada_possivel(e,c) == 0){
            printf("Jogada Invalida.\n");
            return 0;
        }

    }
    return 0;
}

//Verifica se a jogada pedida pelo utilizador é valida.
int jogada_possivel (ESTADO *e, COORDENADA c) {
    if (obter_estado_casa(e,c) == BRANCA || obter_estado_casa(e,c) == PRETA ||
    abs((e->ultima_jogada.linha) - (c.linha)) > 1 || abs((e->ultima_jogada.coluna) - (c.coluna)) > 1) {
        return 0;
    }
    else return 1;
}

// Verifica se o jogo terminou.
int jogo_terminado (ESTADO *e) {
    int r = 0;
    if (e -> num_jogadas == 32 || (e->ultima_jogada.coluna == 0 && e->ultima_jogada.linha == 7))
        r = 1;
    else
        if ( e-> num_jogadas == 32 || (e ->ultima_jogada.linha == 0 && e->ultima_jogada.coluna == 7))
            r = 2;
    else
        r = 0;

    return r;
}

//Função usada para o comando gr (grava o estado de jogo num ficheiro).
void tabuleiro_ficheiro(ESTADO *e, char linha[]) {
    int j = 0;
    char item;
    char comando[BUF_SIZE];
    for (int i = 2; linha[i] != '\n'; i++) {
        comando[j] = linha[i];
        j++;
    }
    comando[j] = '\0';
    strcat(comando, ".txt");

    FILE *fp;
    fp = fopen(comando, "w");
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            if (i == 0 && j == 7) {
                fprintf(fp, "2");
                break;
            }
            else if (i == 7 && j == 0) {
                fprintf(fp, "1");
                j++;
            }

            else {
                if (obter_casa(e, i, j) == VAZIO)
                    item = '.';
                else if (obter_casa(e, i, j) == BRANCA)
                    item = '*';
                else
                    item = '#';
            }
            fprintf(fp, "%c", item);
        }
        fprintf(fp, "\n");
    }
    //Coloca jogadas anteriores no ficheiro.
    if (e->jogador_atual == 2) {
        for (int i = 0; i <= e->num_jogadas; i++) {
            if(i < 10)
                fprintf(fp, "0%d: ",i+1);
            else
                fprintf(fp, "%d: ",i+1);

            if (i != e->num_jogadas) {
                fprintf(fp, "%c%d %c%d", e->jogadas[i].jogador1.coluna + 'a', e->jogadas[i].jogador1.linha+1, e->jogadas[i].jogador2.coluna + 'a', e->jogadas[i].jogador2.linha+1);
            }
            else
                fprintf(fp,"%c%d", e->jogadas[i].jogador1.coluna + 'a', e->jogadas[i].jogador1.linha+1);
            fprintf(fp,"\n");
        }
    }

    if (e->jogador_atual == 1) {
        for (int i = 0; i < e->num_jogadas; i++) {
            if (i < 10)
                fprintf(fp, "0%d: ", i+1);
            else
                fprintf(fp, "%d: ", i+1);

            fprintf(fp, "%c%d %c%d",  e->jogadas[i].jogador1.coluna + 'a', e->jogadas[i].jogador1.linha+1, e->jogadas[i].jogador2.coluna + 'a', e->jogadas[i].jogador2.linha+1);
            fprintf(fp, "\n");
        }
    }
    fclose(fp);
}