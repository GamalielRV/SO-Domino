#include <stdio.h>
#include <stdlib.h>

//YEILAN trabajen sobre esta lista 
//Metodo para ingresar las jugables y borrar las fichas de lista mazo
typedef struct nodoPosible{
    struct nodoPosible * siguiente;
    struct nodoTablero * padre;
    struct ficha * unaficha;
    int puntos;
    int dirrecion;
    int rotacion;
}nodoPosible;

typedef struct listaPosible{
    struct nodoPosible * primero;
}listaPosible;

nodoPosible * newNodoPosible(){
    nodoPosible * self = (struct nodoPosible*)malloc(sizeof(struct nodoPosible));
    self->siguiente = NULL;
    self->padre = NULL;
    self->unaficha = NULL;
    self->puntos = 0;
    self->dirrecion = 0;
    self->rotacion = 0;
    return self;
}

listaPosible * newListaPosible(){
    listaPosible * self = (struct listaPosible*)malloc(sizeof(struct listaPosible));
    self->primero = NULL;
    return self;
}

void insertarNodoPosible(struct nodoPosible * nodo,struct listaPosible* lista){
    if(lista->primero == NULL){
        lista->primero = nodo;
    }else{
        struct nodoPosible * nodoAux = lista->primero;
        while(nodoAux->siguiente != NULL){
            nodoAux = nodoAux->siguiente;
        }
        nodoAux->siguiente = nodo;
    }
}
/*
Este metodo mueve todas las fichas que se pueden jugar a lista posible
*/
void agregarFichasPosibles(struct listaSalida* listaSal, struct listaPosible * listaPos, struct listaMazo* listaMaz){
    if(listaMaz->primero != NULL){
        struct nodoMazo * nodoMaz = listaMaz->primero;
        while(nodoMaz != NULL){
            struct nodoSalida * nodoSal = listaSal->primero;
            struct nodoMazo * siguiente = NULL;
            int flag = 0;
            while(nodoSal != NULL && flag != 1){
                if(nodoMaz->unaFicha->valUp == nodoSal->raiz->unaFicha->valUp || nodoMaz->unaFicha->valDown == nodoSal->raiz->unaFicha->valUp || nodoMaz->unaFicha->valUp == nodoSal->raiz->unaFicha->valDown || nodoMaz->unaFicha->valDown == nodoSal->raiz->unaFicha->valDown){
                    struct nodoPosible * nodoPos = newNodoPosible();
                    nodoPos->unaficha = nodoMaz->unaFicha;
                    insertarNodoPosible(nodoPos,listaPos);
                    siguiente = nodoMaz->siguiente;
                    eliminarNodoMazo(listaMaz,nodoMaz);
                    flag = 1;
                }
                nodoSal = nodoSal->siguiente;
            }
            if(flag == 1){
                nodoMaz = siguiente;
            }else{
                nodoMaz = nodoMaz->siguiente;
            }
        }
    }else{
        printf("la lista esta vacia");
    }
}

void imprimirListaPosibles(struct listaPosible * listaPos){
    if(listaPos->primero != NULL){
        struct nodoPosible * nodoPos = listaPos->primero;
        while(nodoPos != NULL){
            printf("Ficha %d",nodoPos->unaficha->valUp);
            printf("/");
            printf("%d",nodoPos->unaficha->valDown);
            printf(" Valor de la ficha: %d\n",nodoPos->puntos);
            nodoPos = nodoPos->siguiente;
        }
    }else{
        printf("la lista esta vacia \n");
    }  
}

int sizePosible(struct listaPosible * lista){
    if(lista->primero != NULL){
        struct nodoPosible * nodoAux = lista->primero;
        int cont = 1;
        while(nodoAux->siguiente != NULL){
            cont += 1;
            nodoAux = nodoAux->siguiente;
        }
        return cont;
    }else{
       // printf("la lista esta vacia");
    }
}

void eliminarNodoPosible(struct nodoPosible * nodo, struct listaPosible * lista){
    if(lista->primero != NULL){
        if(lista->primero == nodo){
            lista->primero = nodo->siguiente;
        }else{
            struct nodoPosible * nodoAux = lista->primero;
            int flag = 0;
            while(nodoAux->siguiente != NULL && flag != 1){
                if(nodoAux->siguiente == nodo){
                    nodoAux->siguiente = nodoAux->siguiente->siguiente;
                    flag = 1;
                }else{
                    nodoAux = nodoAux->siguiente;
                }
            }
        }
    }else{
        //printf("la Lista esta vacia");
    }
}
/*
Este metodo mueve todas las fichas que son multiplos de 5 a una nueva lista posible llamada lista
jugables
*/
void moverFichasJugables(struct listaPosible * posibles, struct listaPosible * jugadables){
    if(posibles->primero != NULL){
        struct nodoPosible * nodoPos = posibles->primero;
        while(nodoPos != NULL){
            struct nodoPosible * nodoAux = NULL;
            if(nodoPos->puntos % 5 == 0 && nodoPos->puntos != 0){
                struct nodoPosible * nodoTemp = newNodoPosible();
                nodoTemp->unaficha = nodoPos->unaficha;
                nodoTemp->puntos = nodoPos->puntos;
                nodoTemp->padre = nodoPos->padre;
                nodoTemp->dirrecion = nodoPos->dirrecion;
                nodoTemp->rotacion = nodoPos->rotacion;
                insertarNodoPosible(nodoTemp,jugadables);
                nodoAux = nodoPos;
            }
            nodoPos = nodoPos->siguiente;
            eliminarNodoPosible(nodoAux,posibles);
        }
    }else{
       // printf("la Lista esta vacia");
    }
    
}

void ordenarListaPosibles(struct listaPosible * list){
    if(list->primero != NULL){
        struct nodoPosible * nodo = list->primero;
        struct nodoPosible * nodoTemp = list->primero;
        while(nodoTemp->siguiente != NULL){
            while(nodo->siguiente != NULL){
                if(nodo->puntos < nodo->siguiente->puntos){
                    int puntosAux = nodo->puntos;
                    struct nodoTablero * nodoAux = nodo->padre;
                    struct ficha * fichaAux = nodo->unaficha;
                    nodo->padre = nodo->siguiente->padre;
                    nodo->puntos = nodo->siguiente->puntos;
                    nodo->unaficha = nodo->siguiente->unaficha;
                    nodo->siguiente->puntos = puntosAux;
                    nodo->siguiente->padre = nodoAux;
                    nodo->siguiente->unaficha = fichaAux;
                }
                nodo = nodo->siguiente;
            }
            nodo = list->primero;
            nodoTemp = nodoTemp->siguiente;
        }
    }else{
       // printf("lista vacia");
    }
}

