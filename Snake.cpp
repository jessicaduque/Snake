#include "Snake.h"

int main()
{
    inicializa();
    while (!fimDoJogo) {
        desenha();
        entrada();
        logica();
    }
    finaliza();

}
