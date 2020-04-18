#include "interface.h"
#include <stdio.h>
#include <string.h>
#include "logica.h"
#define BUF_SIZE 1024

void mostrar_tabuleiro(ESTADO *e) {
    int num = 8;

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
        printf("%d  ", num);
        num--;
        for (int j = 0; j < 8; j++) {
            char peca = obter_casa(e, i, j);
            printf("%c  ", peca);
        }
        printf("\n");
    }
    printf("#(%d) JOG: %d => ", obter_numero_de_jogadas(e) + 1, obter_jogador_atual(e));
}

void mostrar_tabuleiro_final(ESTADO *e) {
    int num = 8;

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
        printf("%d  ", num);
        num--;
        for (int j = 0; j < 8; j++) {
            char peca = obter_casa(e, i, j);
            printf("%c  ", peca);
        }
        printf("\n");
    }
}

int interpretador(ESTADO *e) {
    char linha[BUF_SIZE];
    char col[2], lin[2];

    ///> Usa a funcao "jogo_terminado" para verificar se tem de continuar a pedir comandos.
    while (jogo_terminado(e) == 0) {
        mostrar_tabuleiro(e);
        ///> Verifica qual é o comando do utilizador, tendo ações diferentes para cada um destes comandos.
        if (fgets(linha, BUF_SIZE, stdin) == NULL)
            return 0;
        else
            //Comando "Q", para sair do jogo.
            if (strlen(linha) == 2 && strncmp(linha, "Q", 1) == 0) {
                printf("Saiu do jogo. \n");
                break;
            }
            //Comando "gr", para guardar o estado do jogo.
            else if (strncmp(linha, "gr", 2) == 0) {
                tabuleiro_ficheiro(e, linha);
                printf("\n#=> Estado do jogo gravado.\n");
            }
            //Comando "ler" para ler o estado do jogo num dado ficheiro.
            else if (strncmp(linha, "ler", 3) == 0) {
               if (ler_ficheiro(e,linha) == 1) {
                    printf("\n#=> Estado do jogo atualizado.\n");
                }
               else
                   printf("\n#=> Nao foi possivel encontrar esse ficheiro.\n");
            }
            //Comando "movs" que mostra todas as jogadas efetuadas até ao momento da execução do comando.
            else if (strncmp(linha, "movs", 4) == 0) {
                printf("#=> Movimentos do jogo:\n");
                movs(e);
            }
            //Comando "pos", que permite ao jogador voltar atras para uma jogada à sua escolha.
            else if (strncmp(linha, "pos", 3) == 0) {
                if (pos(e,linha) == 1)
                    printf ("#=> Posição atualizada.\n");
                else
                    printf("A posição escolhida nao e valida!\n");
            }
            else if (strncmp(linha, "jog", 3) == 0) {
                printf("O bot jogou na sua vez.\n");
                jog(e);
            }
            //Caso nao se pretenda efetuar nenhum comando mas sim uma jogada.
        if (strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) {
            COORDENADA coord = {*col - 'a', *lin - '1'};
            //Caso seja feita uma jogada, colocamos o valor máximo do comando pos = ao valor da jogada atual.
            set_max(e);
            if(jogar(e,coord) == 0)
                printf("Jogada Invalida. \n");
        }
    }
    //Verifica qual dos jogadores congratular no final do jogo.
    if (jogo_terminado(e) == 1) {
        mostrar_tabuleiro_final(e);
        printf("Parabens!! O jogador 1 ganha!\n");
    }
    else if (jogo_terminado(e) == 2) {
        mostrar_tabuleiro_final(e);
        printf("Parabens!! O jogador 2 ganha! \n");
    }
    else if (jogo_terminado(e) == 3) {
        mostrar_tabuleiro_final(e);
        printf("Acabaram-se as jogadas! Ninguém ganhou. \n");
    }
    else if (jogo_terminado(e) == 4) {
        mostrar_tabuleiro_final(e);
        printf("A peca ficou encurralada, e um empate!\n");
    }
    return 1;
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
            if(i < 9)
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

void movs(ESTADO *e) {
        int jog = obter_jogador_atual(e);
        int num_jogadas = obter_numero_de_jogadas(e);
        ///> Obtem o numero do jogador atual e, dependedo desse numero, decide se tem de imprimir um ou dois movimentos numa dada jogada.
        if (jog == 2) {
            for (int i = 0; i <= num_jogadas; i++) {
                if(i < 9)
                    printf("0%d: ",i+1);
                else
                    printf("%d: ",i+1);
                if (i != num_jogadas) {
                    printf("%c%d %c%d", obtem_dados_jogadas_col(e,1,i), obtem_dados_jogadas_lin(e,1,i),
                            obtem_dados_jogadas_col(e,2,i), obtem_dados_jogadas_lin(e,2,i));
                }
                else
                    printf("%c%d",obtem_dados_jogadas_col(e,1,i), obtem_dados_jogadas_lin(e,1,i));
                printf("\n");
            }
        }
        if (jog == 1) {
            for (int i = 0; i < num_jogadas; i++) {
                if (i < 10)
                    printf("0%d: ", i+1);
                else
                    printf("%d: ", i+1);
                printf( "%c%d %c%d",  obtem_dados_jogadas_col(e,1,i), obtem_dados_jogadas_lin(e,1,i),
                        obtem_dados_jogadas_col(e,2,i), obtem_dados_jogadas_lin(e,2,i));
                printf("\n");
            }
        }
}
