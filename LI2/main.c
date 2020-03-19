#include <stdio.h>
#include "dados.h"
#include "logica.h"
#include "interface.h"

int main () {
    ESTADO *e = inicializar_estado();
   while (jogo_terminado(e) == 0) {
        interpretador(e);
    }
   if (jogo_terminado(e) == 1)
       printf("Parabens! O jogador 1 ganha!!\n");
   else
       printf("Parabens!! O jogador 2 ganha!!\n");
    return 0;
}
