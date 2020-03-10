#include <stdio.h>
#include "dados.h"
#include "logica.h"
#include "interface.h"

int main () {

    ESTADO *e = inicializar_estado();
    interpretador(e);

    return 0;
}
