#include "interface.h"

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