#include "dados.h"
#include <stdlib.h>
#include <string.h>
#include "logica.h"

ESTADO *inicializar_estado() {
    ESTADO *e = (ESTADO *) malloc(sizeof(ESTADO));
    for (int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            e -> tab[i][j] = VAZIO;
        }
    }
    ///> Atribui uma peca "BRANCA" na posição "e5".
    e -> tab[3][4] = BRANCA;
    e-> tab[7][0] = UM;
    e->tab[0][7] = DOIS;
    ///> Define como ultima jogada a peça inicial, para ser utilizado futuramente na funçao "jogar".
    (e -> ultima_jogada).coluna = 4;
    (e -> ultima_jogada).linha = 3;
    ///> Inicializa o numero de jogadas, atribuindo-lhe o valor '0'.
    e -> num_jogadas = 0;
    ///> Coloca como jogador atual o jogador 1, visto que o jogo começa sempre por ele.
    e -> jogador_atual = 1;

    return e;
}

int obter_jogador_atual(ESTADO *estado) {
    return estado -> jogador_atual;
}

int obter_numero_de_jogadas(ESTADO *estado) {
    return estado -> num_jogadas;
}

CASA obter_estado_casa(ESTADO *e, COORDENADA c) {
    CASA r;
    int lin = abs(c.linha -8) - 1;
    r = e -> tab[lin][c.coluna];
    return r;
}

CASA obter_casa (ESTADO *e, int i, int j) {
    CASA r = e -> tab[i][j];
    return r;
}

char obtem_dados_jogadas_col (ESTADO *e, int n, int i) {
    if (n == 1) {
        return e->jogadas[i].jogador1.coluna + 'a';
    }
    else
        return e->jogadas[i].jogador2.coluna + 'a';
}

int obtem_dados_jogadas_lin (ESTADO *e, int n, int i) {
    int lin;
    if (n == 1) {
        lin = abs((e->jogadas[i].jogador1.linha + 1) - 8) + 1;
        return lin;
    }
    else
        lin = abs((e -> jogadas[i].jogador2.linha + 1) - 8) + 1;
    return lin;
}

void set_casa (ESTADO *e, char linha [], int k) {
    int i;
    for ( i = 0; i < 9; i++) {
        switch (linha[i]) {
            case ('.'):
                e->tab[k][i] = VAZIO;
                //set_jogadas(e,k,i);
                break;
                ///> Ao encontrar a posição onde coloca a peça BRANCA, define também essa posição como última jogada.
            case ('*'):
                e->tab[k][i] = BRANCA;
                e->ultima_jogada.coluna = i;
                e->ultima_jogada.linha = k ;
                update_num_jogadas(e,k,i);
                break;
            case('#'):
                e->tab[k][i] = PRETA;
                update_num_jogadas(e,k,i);
                break;
            case('2'):
                e->tab[k][i] = DOIS;
                break;
            case('1'):
                e->tab[k][i] = UM;
            default:
                break;
        }
    }
}

void set_jogadas(ESTADO *e, char cord[], int jog, int index) {
    int lin, col;
    char *cord1;
    //cord corresponde à primeira coordenada do ficheiro, cord1 corresponde à segunda. (e5 d5) "cord" vai ser: e5; "cord1" vai ser: d5.
    strtok(cord, " ");
    cord1 = strtok(NULL, "\n");
    ///> No caso de a jogada ainda ser do jogador 2, nao ha registo da jogada deste, pois ainda nao foi feita, logo, apenas atualiza a jogada do jogador 1 no array jogadas.
    switch (jog) {
        case (1):
            col = retira_coluna(cord);
            lin = retira_linha(cord);
            e->jogadas[index].jogador1.linha = lin;
            e->jogadas[index].jogador1.coluna = col;
            break;

            ///> No caso de a jogada ser do jogador 1, entao tem de haver registo de ambos os jogadores, logo, coloca-se as jogadas de ambos os jogadores no array jogadas.
        case(2):
            col = retira_coluna(cord);
            lin = retira_linha(cord);
            e->jogadas[index].jogador1.linha = lin;
            e->jogadas[index].jogador1.coluna = col;
            col = retira_coluna(cord1);
            lin = retira_linha(cord1);
            e->jogadas[index].jogador2.linha = lin;
            e->jogadas[index].jogador2.coluna = col;
            break;
        default:
            break;
    }
}


///> Apenas aumenta ao numero de jogadas caso o jogador atual seja 2.
int update_num_jogadas (ESTADO *e, int k, int i) {
    if (k == 3 && i == 4)
        return 0;
    else if (e->jogador_atual == 2)  {
        e->jogador_atual = 1;
        e->num_jogadas++;
    }
    else if (e->jogador_atual == 1) {
        e->jogador_atual = 2;
    }
 return 1;
}