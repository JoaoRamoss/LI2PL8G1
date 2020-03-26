#include "logica.h"
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
        fp = fopen(comando, "r");
        while (fgets(lin_fich, BUF_SIZE, fp) != NULL) {
            set_casa(e, lin_fich, k);
            ///> Ao ler o ficheiro, quando chega ao local onde se encontram as jogadas anteriores, chama a função "update_array_jogadas()".
            if (k >= 9) {
                update_array_jogadas(e, lin_fich);
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

void update_array_jogadas (ESTADO *e, char lin_fich[]) {
    int i, index;
    char *nome;
    // A partir do ficheiro, obtem o numero da jogada e guarda-a na variável index.
    index = atoi(lin_fich) - 1;

    /* Retira os primeiros 4 elementos da string (uma string que fosse: "01: e5 d5" passa a ser "e5 d5".
     */
    strtok(lin_fich, " ");
    nome = strtok(NULL, "\n");
    ///> Determina qual das partes da função usar (parte 1 caso i seja menor que 2, e parte 2 caso i seja maior que dois.)
    for (i = 0; nome[i] != '\0' ; i++);
    if (i > 2)
        set_jogadas(e, nome, 2, index);

    else
        set_jogadas(e, nome, 1, index);
}


int retira_linha (char str[]) {
    int r = 0;
    char *end;
    //Quando enconrtar algum elemento da string para a qual a funcao isdigit() devolva algum valor diferente de 0, converte-0 num int e devolve-o.
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

