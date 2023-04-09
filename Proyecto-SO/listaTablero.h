#include <stdio.h>
#include <stdlib.h>
#include "listaSalida.h"
#include "listaPosibles.h"

typedef struct listaTablero
{
    struct nodoTablero * raiz;
}listaTablero;

listaTablero* newListaTablero(){
    struct listaTablero* self= (struct listaTablero*)malloc(sizeof(struct listaTablero));
    self->raiz = NULL;
    return self;
}

void insertarNodoTablero(struct nodoTablero * raiz, struct nodoTablero * nodo, int pos, int vert){
    if(vert == 0){//Vertical
        switch (pos)
        {
        case 1://derecha
            if(raiz->derecha == NULL && raiz->unaFicha->valUp == nodo->unaFicha->valUp || raiz->unaFicha->valUp == nodo->unaFicha->valDown){
                raiz->derecha = nodo;
                nodo->padre = raiz;
                if(raiz->unaFicha->valUp == nodo->unaFicha->valUp){
                    nodo->arriba = raiz;
                }else{
                    nodo->abajo = raiz;
                }
            }
            break;
        case 2://Izquierda
            if(raiz->izquierda == NULL && raiz->unaFicha->valUp == nodo->unaFicha->valUp || raiz->unaFicha->valUp == nodo->unaFicha->valDown){
                raiz->izquierda = nodo;
                nodo->padre = raiz;
                if(raiz->unaFicha->valUp == nodo->unaFicha->valUp){
                    nodo->arriba = raiz;
                }else{
                    nodo->abajo = raiz;
                }
            }
            break;
        case 3://Arriba
            if(raiz->arriba == NULL && raiz->unaFicha->valUp == nodo->unaFicha->valUp || raiz->unaFicha->valUp == nodo->unaFicha->valDown){
                raiz->arriba = nodo;
                nodo->padre = raiz;
                if(raiz->unaFicha->valUp == nodo->unaFicha->valUp){
                    nodo->arriba = raiz;
                }else if(raiz->unaFicha->valUp == nodo->unaFicha->valDown){
                    nodo->abajo = raiz;
                }
            }
            break;
        case 4://Abajo
            if(raiz->abajo == NULL && raiz->unaFicha->valDown == nodo->unaFicha->valDown || raiz->unaFicha->valDown == nodo->unaFicha->valUp){
                raiz->abajo = nodo;
                nodo->padre = raiz;
                if(raiz->unaFicha->valDown == nodo->unaFicha->valUp){
                    nodo->arriba = raiz;
                }else if(raiz->unaFicha->valDown == nodo->unaFicha->valDown){
                    nodo->abajo = raiz;
                }
            }
            break;
        default:
            break;
        }
    }else{//Horizontal
        switch (pos)
        {
        case 3://Arriba
            if(raiz->arriba == NULL && raiz->unaFicha->valUp == nodo->unaFicha->valUp || raiz->unaFicha->valUp == nodo->unaFicha->valDown){
                raiz->arriba = nodo;
                nodo->padre = raiz;
                nodo->derecha = raiz;
            }
            break;
        case 4://Abajo
            if(raiz->abajo == NULL && raiz->unaFicha->valDown == nodo->unaFicha->valDown || raiz->unaFicha->valDown == nodo->unaFicha->valUp){
                raiz->abajo = nodo;
                nodo->padre = raiz;
                nodo->izquierda = raiz;
            }
            break;
        default:
            break;
        }
    }
}
/*
Este metodo no esta haciendo nada fue una prueba para encontrar todas las puntas del tablero
*/
void encontrarPuntas(struct nodoTablero* actual){
    if(actual != NULL){
        if(actual->unaFicha->valUp == actual->unaFicha->valDown){
            if(actual->derecha != NULL && actual->derecha != actual->padre){
                encontrarPuntas(actual->derecha);
            }
            if(actual->izquierda != NULL && actual->izquierda != actual->padre){
                encontrarPuntas(actual->izquierda);
            }
        }
        if(actual->arriba == NULL){
            printf("Encontramos una punta Superior con valor %d\n",actual->unaFicha->valUp);
        }else if(actual->arriba != actual->padre){
            encontrarPuntas(actual->arriba);
        }
        if(actual->abajo == NULL){
            printf("Encontramos una punta Inferior con valor %d\n",actual->unaFicha->valDown);
        }else if(actual->abajo != actual->padre){
            encontrarPuntas(actual->abajo);
        }
    }else{
        //printf("el nodo no existe");
    }
}
/*
Este metodo encuentra y retorna todas las salidas en la que se puede ingresar una ficha
*/
void encontrarSalidas(struct nodoTablero* actual, struct listaSalida* lista){
    if(actual != NULL){
        if(actual->unaFicha->valUp == actual->unaFicha->valDown){
            if(actual->derecha == NULL){
                struct nodoSalida* self = newNodoSalida(actual,1);
                insertarNodoSalida(lista,self);
            }else if(actual->derecha != NULL && actual->derecha != actual->padre){
                encontrarSalidas(actual->derecha,lista);
            }
            if(actual->izquierda == NULL){
                struct nodoSalida* self = newNodoSalida(actual,2);
                insertarNodoSalida(lista,self);
            }else if(actual->izquierda != NULL && actual->izquierda != actual->padre){
                encontrarSalidas(actual->izquierda,lista);
            }
        }
        if(actual->arriba == NULL){
            struct nodoSalida* self = newNodoSalida(actual,3);
            insertarNodoSalida(lista,self);
        }else if(actual->arriba != actual->padre){
            encontrarSalidas(actual->arriba,lista);
        }
        if(actual->abajo == NULL){
            struct nodoSalida* self = newNodoSalida(actual,4);
            insertarNodoSalida(lista,self);
        }else if(actual->abajo != actual->padre){
            encontrarSalidas(actual->abajo,lista);
        }
    }else{
        //printf("el nodo no existe");
    }
}
/*
Este metodo calcula todos los puntos del tablero
*/
int calcularPuntosTablero(struct nodoTablero* actual , int puntos){
    if(actual != NULL){
        if(actual->unaFicha->valUp == actual->unaFicha->valDown){
            if(actual->derecha != NULL && actual->derecha != actual->padre){
                puntos = calcularPuntosTablero(actual->derecha,puntos);
            }
            if(actual->izquierda != NULL && actual->izquierda != actual->padre){
                puntos = calcularPuntosTablero(actual->izquierda,puntos);
            }
        }
        if(actual->arriba == NULL){
            puntos += actual->unaFicha->valUp;
        }else if(actual->arriba != actual->padre){
            puntos = calcularPuntosTablero(actual->arriba,puntos);
        }
        if(actual->abajo == NULL){
            puntos += actual->unaFicha->valDown;
        }else if(actual->abajo != actual->padre){
            puntos = calcularPuntosTablero(actual->abajo,puntos);
        }
        return puntos;
    }else{
        //printf("el nodo no existe");
    }
}

void eliminarNodoTablero(struct nodoTablero * nodo, struct nodoTablero * actual){
    if(actual != NULL){
        if(actual->unaFicha->valUp == actual->unaFicha->valDown){
            if(actual->derecha != NULL && actual->derecha != actual->padre){
                if(actual->derecha->unaFicha == nodo->unaFicha){
                    actual->derecha = NULL;
                    //liberarNodoTablero(nodo);
                }else{
                    eliminarNodoTablero(nodo,actual->derecha); 
                }
            } 
            if(actual->izquierda != NULL && actual->izquierda != actual->padre){
                if(actual->izquierda->unaFicha == nodo->unaFicha){
                    actual->izquierda = NULL;
                    //liberarNodoTablero(nodo);
                }else{
                    eliminarNodoTablero(nodo,actual->izquierda); 
                }            
            }
        }
        if(actual->arriba != NULL && actual->arriba != actual->padre){
            if(actual->arriba->unaFicha == nodo->unaFicha){
                actual->arriba = NULL;
                //liberarNodoTablero(nodo);
            }else{
                eliminarNodoTablero(nodo,actual->arriba);
            }
        }
        if(actual->abajo != NULL && actual->abajo != actual->padre){
            if(actual->abajo->unaFicha == nodo->unaFicha){
                actual->abajo = NULL;
                //liberarNodoTablero(nodo);
            }else{
                eliminarNodoTablero(nodo,actual->abajo);
            }
        }
    }else{
        //printf("la raiz esta vacia");
    }
}
/*
Este metodo calcula todos los puntos de las fichas en la lista de posibles
*/
void calcularPuntos(struct listaSalida* lista, struct listaPosible * lista2, struct listaTablero* lista3){
    struct nodoPosible * nodoAux = lista2->primero;
    while(nodoAux != NULL){
        struct nodoSalida * nodoTemp = lista->primero;
        while(nodoTemp != NULL){
            int giro = 0;
            do{
                struct nodoTablero * nodo = newNodoTablero(nodoAux->unaficha,NULL);
                    int vali = 0;
                    switch (nodoTemp->direc)
                    {
                    case 1://Derecha
                        if(nodoTemp->raiz->unaFicha->valUp == nodoAux->unaficha->valUp || nodoTemp->raiz->unaFicha->valUp == nodoAux->unaficha->valDown){
                            vali = 1;
                        }
                        break;
                    case 2://izquierda
                        if(nodoTemp->raiz->unaFicha->valUp == nodoAux->unaficha->valUp || nodoTemp->raiz->unaFicha->valUp == nodoAux->unaficha->valDown){
                            vali = 1;
                        }
                        break;
                    case 3://Arriba
                        if(nodoTemp->raiz->unaFicha->valUp == nodoAux->unaficha->valUp || nodoTemp->raiz->unaFicha->valUp == nodoAux->unaficha->valDown){
                            vali = 1;
                        }
                        break;
                    case 4://Abajo
                        if(nodoTemp->raiz->unaFicha->valDown == nodoAux->unaficha->valUp || nodoTemp->raiz->unaFicha->valDown == nodoAux->unaficha->valDown){
                            vali = 1;
                        }
                        break;
                    default:
                        break;
                    }
                    if(vali == 1){
                        insertarNodoTablero(nodoTemp->raiz,nodo,nodoTemp->direc,giro);
                        int puntosTablero = calcularPuntosTablero(lista3->raiz,0);
                        //printf("  Puntos del tablero: %d\n", puntosTablero);
                        if(puntosTablero % 5 == 0){
                            if(nodoAux->puntos % 5 != 0){
                                nodoAux->puntos = puntosTablero;
                                nodoAux->padre = nodoTemp->raiz;
                                nodoAux->dirrecion = nodoTemp->direc;
                                nodoAux->rotacion = giro;
                            }else{
                                if(nodoAux->puntos < puntosTablero){
                                    nodoAux->puntos = puntosTablero;
                                    nodoAux->padre = nodoTemp->raiz;
                                    nodoAux->dirrecion = nodoTemp->direc;
                                    nodoAux->rotacion = giro;
                                }
                            }       
                        }else{
                            if(nodoAux->puntos == 0){
                                nodoAux->puntos = puntosTablero;
                                nodoAux->padre = nodoTemp->raiz;
                                nodoAux->dirrecion = nodoTemp->direc;
                                nodoAux->rotacion = giro;
                            }
                            if(nodoAux->puntos % 5 != 0){
                                if(nodoAux->puntos < puntosTablero){
                                    nodoAux->puntos = puntosTablero;
                                    nodoAux->padre = nodoTemp->raiz;
                                    nodoAux->dirrecion = nodoTemp->direc;
                                    nodoAux->rotacion = giro;
                                }
                            }
                        }
                        if(nodo->unaFicha->valUp == nodo->unaFicha->valDown && giro == 0){
                            giro = 1;
                            puntosTablero = 0;
                        }else{
                            puntosTablero = 0;
                            giro = 0;
                        }
                        eliminarNodoTablero(nodo,lista3->raiz); 
                    }  
            }while(giro != 0);
            nodoTemp = nodoTemp->siguiente;
        }
        //printf("El mayor valor agregado fue: %d\n",nodoAux->puntos);
        nodoAux = nodoAux->siguiente;
    }
}
/*
El siguiente metodo realiza todos los llamados para que el algoritmo que el juego tire una ficha
El el metodo al que hay que llamar cuando se necesita jugar una ficha
Adicionalmente este metodo tambien retorna las fichas que no fueron jugadas al mazo
*/
int insertarFichaAJugar(struct listaMazo * listMazo, struct listaTablero * listTablero){
    int puntos=0;
    struct listaSalida * listSalida = newListaSalida();
    struct listaPosible * listPosible = newListaPosible();
    struct listaPosible * listaJugables = newListaPosible();
    encontrarSalidas(listTablero->raiz,listSalida);//Encontramos las salidas
    agregarFichasPosibles(listSalida,listPosible,listMazo);//Movemos las ficha que se pueden jugar a lista posible
    calcularPuntos(listSalida,listPosible,listTablero);//calculamos los puntos de cada ficha en lista posible
    ordenarListaPosibles(listPosible);//ordenamos lista posible
    moverFichasJugables(listPosible,listaJugables);//las fichas con puntos multiplos de 5 las movemos a una nueva lista posbile llamada lista jugable
    ordenarListaPosibles(listaJugables);//ordenamos la lista jugable
    /*
    //printf("Inicio \n");
    imprimirListaPosibles(listPosible);
    printf("Lista Jugables \n");
    imprimirListaPosibles(listaJugables);
    printf("Lista Mazo \n");
    //imprimirLista(listMazo);
    //printf("Fin \n");
    */
    
    //Verificamos si la lista jugables no esta vacias y tomamos la primera posicion de la lista y la insertamos en el tablero
    if(listaJugables->primero != NULL){
        struct nodoTablero * nodoAux = newNodoTablero(listaJugables->primero->unaficha,listaJugables->primero->padre);
        insertarNodoTablero(listaJugables->primero->padre,nodoAux,listaJugables->primero->dirrecion,listaJugables->primero->rotacion);
        printf("Ficha Jugada: ");
        imprimirFicha(nodoAux->unaFicha);
        printf("\n");
        puntos = (listaJugables->primero->puntos)/5;
    }else if(listPosible->primero != NULL){
        struct nodoTablero * nodoAux = newNodoTablero(listPosible->primero->unaficha,listPosible->primero->padre);
        insertarNodoTablero(listPosible->primero->padre,nodoAux,listPosible->primero->dirrecion,listPosible->primero->rotacion);
        printf("Ficha Jugada: ");
        imprimirFicha(nodoAux->unaFicha);
        printf("\n");
        puntos = 0;
    }else{
        return -1;
    }
    
    //Regresando las fichas al mazo
    if(listaJugables->primero != NULL){
        struct nodoPosible * nodoAux = listaJugables->primero;
        while(nodoAux != NULL){
            if(nodoAux->unaficha != listaJugables->primero->unaficha){
                insertarNodoPosible(nodoAux,listPosible);
            }
            nodoAux = nodoAux->siguiente;
        }
    }
    if(listPosible->primero != NULL){
        struct ficha * unaFicha = listPosible->primero->unaficha;
        if(listaJugables->primero != NULL){
            unaFicha = listaJugables->primero->unaficha;
        }
        struct nodoPosible * nodoAux = listPosible->primero;
        while(nodoAux != NULL){
            if(nodoAux->unaficha != unaFicha){
                struct nodoMazo * nodoMaz = crearNodo(nodoAux->unaficha);
                insertarNodo(nodoMaz,listMazo);
            }
            nodoAux = nodoAux->siguiente;
        }
    }
    ordenarLista(listMazo);
    /*
        imprimirListaPosibles(listPosible);
        printf("Lista Jugables \n");
        imprimirListaPosibles(listaJugables);
        printf("Lista Mazo \n");
        imprimirLista(listMazo);
        printf("Fin \n");
    */
    free(listPosible);
    free(listaJugables);
    free(listSalida);
    return puntos;
}

