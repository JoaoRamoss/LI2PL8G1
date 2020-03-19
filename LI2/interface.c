#include "interface.h"
#include <stdio.h>
#include <string.h>
#include "logica.h"
#include <string.h>
#define BUF_SIZE 1024

void mostrar_tabuleiro(ESTADO *e) {
    char item;


    //Imprime as letras no topo do tabuleiro.
    printf("   ");
    for (char c = 'a'; c < 'i'; c++)
        printf("%c  ", c);
    printf("\n");

    /*
    Imprime o conteudo do tabuleiro, imprimindo '*' no caso de a Peça ser "BRANCA",
    '#' no caso de a peça ser "PRETA", e '.' no caso de ser "VAZIO".
    */

    for (int i = 0; i < 8; i++) {
        printf("%d  ", i+1);
        for (int j = 0; j < 8; j++) {

            if (i == 0 && j == 7) {
                printf("2");
                break;
            }
            else if (i == 7 && j == 0) {
                printf("1  ");
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
            printf("%c  ", item);
        }
        printf("\n");
    }
    printf("#(%d) JOG: %d => ", e->num_jogadas, e->jogador_atual);
}

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
    fprintf(fp, "   ");
    for (char c = 'a'; c < 'i'; c ++) {
        fprintf(fp, "%c  ", c);
    }
    fprintf(fp, "\n");
    for (int i = 0; i < 8; i++) {
        fprintf(fp, "%d  ", i+1);
        for (int j = 0; j < 8; j++) {

            if (i == 0 && j == 7) {
                fprintf(fp, "2");
                break;
            }
            else if (i == 7 && j == 0) {
                fprintf(fp, "1  ");
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
            fprintf(fp, "%c  ", item);
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "#(%d) JOG: %d => ", e->num_jogadas, e->jogador_atual);
    fclose(fp);
}




int interpretador(ESTADO *e) {
    char linha[BUF_SIZE];
    char col[2], lin[2];

    while (jogo_terminado(e) == 0) {
        printf("\n");
        mostrar_tabuleiro(e);
        if (fgets(linha, BUF_SIZE, stdin) == NULL)
            return 0;
        else
            if (strlen(linha) == 2 && strncmp(linha, "Q", 1) == 0) {
                printf("Saiu do jogo. \n");
                break;
            }
            else if (strncmp(linha, "gr", 2) == 0) {
                tabuleiro_ficheiro(e, linha);
                printf("Gravado.\n");
            }


        if (strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) {
            COORDENADA coord = {*col - 'a', *lin - '1'};
            jogar(e, coord);
        }
    }
    if (jogo_terminado(e) == 1)
        printf("Parabens!! O jogador 1 ganha!\n");
    else if (jogo_terminado(e) == 2)
        printf("Parabens!! O jogador 2 ganha! \n");
    return 1;
}
