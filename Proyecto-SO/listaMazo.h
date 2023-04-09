#ifndef LISTAMAZO_FILE
#define LISTAMAZO_FILE

#include <stdio.h>
#include <stdlib.h>
#include "nodoMazo.h"

typedef struct listaMazo
{
    struct nodoMazo * primero;
    struct nodoMazo * ultimo;
}listaMazo;

listaMazo * crearLista(){
    struct listaMazo * self = (struct listaMazo*)malloc(sizeof(listaMazo));
    self->primero = NULL;
    self->ultimo = NULL;
    return self;
}

void insertarNodo(struct nodoMazo* nodo, struct listaMazo* lista){
    if(lista->primero == NULL){
        lista->primero = nodo;
    }else{
        struct nodoMazo* nodoAux = lista->primero;
        while(nodoAux->siguiente != NULL){
            nodoAux = nodoAux->siguiente;
        }
        nodoAux->siguiente = nodo;
    }
};

void imprimirLista(struct listaMazo* lista){
    struct nodoMazo* nodoAux = lista->primero;
    while(nodoAux != NULL){
        imprimirFicha(nodoAux->unaFicha);
        nodoAux = nodoAux->siguiente;
    }
};

void ordenarLista(struct listaMazo* lista){
    if(lista->primero != NULL){

        struct nodoMazo* nodoAux = lista->primero;
        struct nodoMazo* nodoCont = lista->primero;
        while(nodoCont != NULL){
            while(nodoAux->siguiente != NULL){
                if(nodoAux->siguiente->unaFicha->valor < nodoAux->unaFicha->valor){
                    struct ficha * nod = nodoAux->unaFicha;
                    nodoAux->unaFicha = nodoAux->siguiente->unaFicha;
                    nodoAux->siguiente->unaFicha = nod;
                }else{
                    nodoAux = nodoAux->siguiente;
                }
            }
            nodoAux = lista->primero;
            nodoCont = nodoCont->siguiente;
        }  
    }
};

struct nodoMazo* encontrarNodo(int posicion, struct listaMazo* lista){
    // puntero auxiliar para recorrer la lista
    struct nodoMazo * nodoActual = lista->primero;
    int cont = 0;
    // recorrer la lista enlazada
    while (nodoActual != NULL) {
        // si se encuentra el nodo buscado, devolver un puntero al nodo
        if (cont == posicion) {
            return nodoActual;
        }else{
            cont ++;
        }
        // avanzar al siguiente nodo de la lista
        nodoActual = nodoActual->siguiente;
    }

    // si el nodo no está en la lista, devolver NULL
    return lista->primero;
}

int size(struct listaMazo * lista){
    if(lista->primero != NULL){
        struct nodoMazo * nodoAux = lista->primero;
        int cont = 1;
        while(nodoAux->siguiente != NULL){
            cont += 1;
            nodoAux = nodoAux->siguiente;
        }
        return cont;
    }else{
        printf("la lista esta vacia");
    }
}

void limpiarNodo(struct nodoMazo * nodo){
    free(nodo);
}

void eliminarNodoMazo(struct listaMazo * lista, struct nodoMazo * nodo){

    if(nodo != NULL){
        struct nodoMazo * nodoActual = lista->primero;

        // si el nodo a eliminar es el primer nodo de la lista
        if (nodoActual != NULL && nodoActual->unaFicha == nodo->unaFicha) {
            // actualizar el puntero del primer nodo para que apunte al siguiente nodo
            lista->primero = nodoActual->siguiente;
            // liberar la memoria del nodo eliminado
            free(nodoActual);
            return;
        }
        struct nodoMazo * nodoAnterior = NULL;
        while (nodoActual != NULL && nodoActual->unaFicha != nodo->unaFicha) {
            nodoAnterior = nodoActual;
            nodoActual = nodoActual->siguiente;
        }
        if (nodoActual != NULL) {
            // actualizar el puntero del nodo anterior para que apunte al siguiente nodo
            nodoAnterior->siguiente = nodoActual->siguiente;
            // liberar la memoria del nodo eliminado
            free(nodoActual);
        }
    }
    
}

#endif
