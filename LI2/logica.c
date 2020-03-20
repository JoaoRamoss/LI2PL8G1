#include "logica.h"
#include "dados.h"
#include <stdio.h>
#include <stdlib.h>

int jogar(ESTADO *e, COORDENADA c) {
    int lin = c.linha;
    int col = c.coluna;
    int jog = obter_jogador_atual(e);
    int jogadas = obter_numero_de_jogadas(e);

    if (jogada_possivel(e,c) == 1) {
        ///<Coloca a peça na posição pedida pelo utilizador.
        e->tab[lin][col] = BRANCA;
        ///<Coloca uma peça preta na casa anterior da peça branca.
        e->tab[(e->ultima_jogada).linha][(e->ultima_jogada).coluna] = PRETA;
        ///<Coloca a nova posição da peça branca como posição anterior para ser usada futuramente.
        e->ultima_jogada.coluna = col;
        e->ultima_jogada.linha = lin;

        ///<Determinar se foi o jogador 1 ou 2 a jogar, e, consoante isto, coloca na array "jogadas" as informações correspondentes.
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
            ///<Incrementa o numero de jogadas.
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

///Verifica se a jogada pedida pelo utilizador é valida.
int jogada_possivel (ESTADO *e, COORDENADA c) {
    if (obter_estado_casa(e,c) == BRANCA || obter_estado_casa(e,c) == PRETA ||
    abs((e->ultima_jogada.linha) - (c.linha)) > 1 || abs((e->ultima_jogada.coluna) - (c.coluna)) > 1) {
        return 0;
    }
    else return 1;
}

/// Verifica se o jogo terminou.
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