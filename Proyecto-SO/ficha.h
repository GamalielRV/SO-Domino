#include <stdio.h>
#include <stdlib.h>

typedef struct ficha
{
    int valUp;
    int valDown;
    int valor;
    unsigned char tipo[10];
    int direccion;
}ficha;



ficha * newFicha(int Up, int Down, int val){
   struct ficha * fichaAux = (struct ficha*)malloc(sizeof(struct ficha));
   fichaAux->valUp = Up;
   fichaAux->valDown = Down;
   fichaAux->valor = val;
   fichaAux->direccion = 0;
   return fichaAux;
}

void imprimirFicha(struct ficha* unaficha){
    printf("[%d,%d]",unaficha->valUp,unaficha->valDown);
}
