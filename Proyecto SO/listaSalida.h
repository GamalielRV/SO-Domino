#include "nodoTablero.h"


typedef struct nodoSalida{
    struct nodoSalida * siguiente;
    struct nodoTablero * raiz;
    int direc;
}nodoSalida;

nodoSalida * newNodoSalida(struct nodoTablero * padre, int direccion){
    struct nodoSalida * self = (struct nodoSalida*)malloc(sizeof(struct nodoSalida));
    self->raiz = padre;
    self->siguiente = NULL;
    self->direc = direccion;
    return self;
}

typedef struct listaSalida{
    nodoSalida * primero;
}listaSalida;

listaSalida * newListaSalida(){
    struct listaSalida * self = (struct listaSalida*)malloc(sizeof(struct listaSalida));
    self->primero = NULL;
    return self;
}

void insertarNodoSalida(struct listaSalida * lista, struct nodoSalida * nodo){
    if(lista->primero == NULL){
        lista->primero = nodo;
    }else{
        struct nodoSalida * nodoAux = lista->primero;
        while(nodoAux->siguiente != NULL){
            nodoAux = nodoAux->siguiente;
        }
        nodoAux->siguiente = nodo;
    }
}

void imprimirListaSalida(struct listaSalida * lista){
    struct nodoSalida * nodoAux = lista->primero;
    while(nodoAux != NULL){
        switch (nodoAux->direc)
        {
        case 1:
            printf("Se encontro una salida derecha con valor: %d\n",nodoAux->raiz->unaFicha->valUp);
            break;
        case 2:
            printf("Se encontro una salida izquierda con valor: %d\n",nodoAux->raiz->unaFicha->valUp);
            break;
        case 3:
            printf("Se encontro una salida superior con valor: %d\n",nodoAux->raiz->unaFicha->valUp);
            break;
        case 4:
            printf("Se encontro una salida inferior con valor: %d\n",nodoAux->raiz->unaFicha->valDown);
            break;
        default:
            break;
        }
        nodoAux = nodoAux->siguiente;
    }
    printf("Fin de impresion \n ");
}