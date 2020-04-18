#include <stdlib.h>
#include "dados.h"
#include "interface.h"
#include <time.h>
int main () {
    srand(time(NULL));
    ESTADO *e = inicializar_estado();
    interpretador(e);
    free(e);
    return 0;
}
