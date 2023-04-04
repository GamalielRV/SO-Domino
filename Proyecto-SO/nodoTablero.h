#include <stdio.h>
#include <stdlib.h>


typedef struct nodoTablero
{
    struct nodoTablero * padre;
    struct nodoTablero * arriba;
    struct nodoTablero * abajo;
    struct nodoTablero * derecha;
    struct nodoTablero * izquierda;
    struct ficha * unaFicha;
}nodoTablero;

nodoTablero * newNodoTablero(struct ficha * laFicha,struct nodoTablero * padreAux){
    nodoTablero * self=(struct nodoTablero*)malloc(sizeof(struct nodoTablero));
    self->padre = padreAux;
    self->arriba = NULL;
    self->abajo = NULL;
    self->derecha = NULL;
    self->izquierda = NULL;
    self->unaFicha = laFicha;
    return self;
}

void liberarNodoTablero(struct nodoTablero * nodo){
    nodo->unaFicha = NULL;
    nodo->arriba = NULL;
    nodo->abajo = NULL;
    nodo->derecha = NULL;
    nodo->izquierda = NULL;
    nodo->padre = NULL;
    free(nodo);
}
