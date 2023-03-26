#include <stdio.h>
#include <stdlib.h>
#include "ficha.h"

typedef struct nodoMazo
{
    ficha *unaFicha;
    struct nodoMazo * siguiente;
}nodoMazo;

nodoMazo * crearNodo(ficha *laFicha){
    struct nodoMazo * self = (struct nodoMazo*)malloc(sizeof(struct nodoMazo));
    self->unaFicha = laFicha;
    self->siguiente = NULL;
    return self;
}