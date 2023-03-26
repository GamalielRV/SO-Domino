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
        printf("Ficha %d",nodoAux->unaFicha->valUp);
        printf("/");
        printf("%d\n",nodoAux->unaFicha->valDown);
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
    if(lista->primero != NULL){
        struct nodoMazo * nodoAux = lista->primero;
        int contPos = 0;
        while(nodoAux->siguiente != NULL && contPos != posicion){
            contPos += 1;
            nodoAux = nodoAux->siguiente;
        }
        if(nodoAux == NULL){
            printf("no se encontro el nodo");
        }
        printf("se encontro el nodo %d\n",posicion);
        struct nodoMazo * self = crearNodo(nodoAux->unaFicha);
        return self;
    }else{
        printf("no se encontro el nodo");
    }
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
    if(lista->primero != NULL){
        if(lista->primero == nodo){
            if(lista->primero->siguiente == NULL){
                lista->primero = NULL;
            }else{
                lista->primero = lista->primero->siguiente;
            }
        }else{
            struct nodoMazo * nodoAux = lista->primero;
            int flag = 0;
            while(flag != 1 && nodoAux->siguiente != NULL){
                if(nodoAux->siguiente == nodo){
                    nodoAux->siguiente = nodo->siguiente;
                    flag = 1;
                }
                nodoAux = nodoAux->siguiente;
            }
        }
        //limpiarNodo(nodo);
    }else{
        printf("la lista esta vacia");
    }
}

