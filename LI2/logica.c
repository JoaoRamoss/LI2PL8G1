#include "logica.h"
#include "dados.h"
#include <stdio.h>

int jogar(ESTADO *e, COORDENADA c) {
    int lin = c.linha;
    int col = c.coluna;
    int jog = obter_jogador_atual(e);
    int jogadas = obter_numero_de_jogadas(e);

    // Coloca a peça na posição pedida pelo utilizador.
    e -> tab[lin][col] = BRANCA;
    //Coloca uma peça preta na casa anterior da peça branca.
    e -> tab[(e->ultima_jogada).linha][(e->ultima_jogada).coluna] = PRETA;
    //Coloca a nova posição da peça branca como posição anterior para ser usada futuramente.
    e -> ultima_jogada.coluna = col;
    e -> ultima_jogada.linha = lin;

    //Incrementa o numero de jogadas.
    e -> num_jogadas++;

    //Determinar se foi o jogador 1 ou 2 a jogar, e, consoante isto, coloca na array "jogadas" as informações correspondentes.
    if (jog == 1) {
        e->jogadas[jogadas].jogador1.linha = lin;
        e->jogadas[jogadas].jogador1.coluna = col;
    }
    else {
        e->jogadas[jogadas].jogador2.linha = lin;
        e->jogadas[jogadas].jogador2.coluna = col;
    }
    if (jog == 1)
        e -> jogador_atual = 2;
    else
        e -> jogador_atual = 1;

    printf("jogar %d %d\n", c.coluna, c.linha);
    return 1;
    
}