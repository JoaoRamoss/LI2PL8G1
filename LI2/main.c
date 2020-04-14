#include <stdlib.h>
#include "dados.h"
#include "interface.h"
#include "lista.h"
#include <string.h>

int main () {
    ESTADO *e = inicializar_estado();
    interpretador(e);
    free(e);
    return 0;
}
