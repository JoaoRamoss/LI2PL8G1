#include "dados.h"
#include "logica.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc == 3) {
        ESTADO *e = inicializar_estado();
        ler_ficheiro(e, argv[1]);
        bestMove(e);
        tabuleiro_ficheiro(e, argv[2]);
        free(e);
        return 1;
    }
    return 0;
}
