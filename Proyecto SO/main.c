
#include "listaMazo.h"
#include "listaTablero.h"
#include <stdio.h>
#include <stdlib.h>

int main(void){
    
    int vectorUP[28] = {0,1,2,3,4,5,6,1,2,3,4,5,6,2,3,4,5,6,3,4,5,6,4,5,6,5,6,6};
    int vectorDown[28] = {0,0,0,0,0,0,0,1,1,1,1,1,1,2,2,2,2,2,3,3,3,3,4,4,4,5,5,6};
    struct listaMazo * unaLista = crearLista();
    for (size_t i = 0; i < 27; i++)
    {
        struct ficha * unaFicha = newFicha(vectorUP[i],vectorDown[i],i); 
        struct nodoMazo * unNodo = crearNodo(unaFicha);
        insertarNodo(unNodo,unaLista);

    }
    struct listaMazo * listaMazoJugador = crearLista();
    int numero = rand() % 27;
    insertarNodo(encontrarNodo(numero,unaLista),listaMazoJugador);
    numero = rand() % 27;
    insertarNodo(encontrarNodo(numero,unaLista),listaMazoJugador);
    numero = rand() % 27;
    insertarNodo(encontrarNodo(numero,unaLista),listaMazoJugador);
    imprimirLista(listaMazoJugador);
    ordenarLista(listaMazoJugador);
    imprimirLista(listaMazoJugador);
    printf("%d\n",size(listaMazoJugador));
    printf("webadas");
    /*
    struct ficha * ficha1 = newFicha(6,6,27);
    struct nodoTablero * nodo1 = newNodoTablero(ficha1,NULL);
    struct ficha * ficha2 = newFicha(6,5,26);
    struct nodoTablero * nodo2 = newNodoTablero(ficha2,nodo1);
    struct ficha * ficha3 = newFicha(6,4,25);
    struct nodoMazo * nodo3 = crearNodo(ficha3);
    struct ficha * ficha4 = newFicha(3,5,12);
    struct nodoMazo * nodo4 = crearNodo(ficha4);
    struct ficha * ficha5 = newFicha(5,5,20);
    struct nodoMazo * nodo5 = crearNodo(ficha5);
    struct ficha * ficha6 = newFicha(1,1,20);
    */
    struct nodoMazo * nodo6 = crearNodo(ficha6);
    struct listaTablero * tablero = newListaTablero();
    struct listaMazo * mazo1 = crearLista();
    insertarNodo(nodo3,mazo1);
    insertarNodo(nodo4,mazo1);
    insertarNodo(nodo5,mazo1);
    insertarNodo(nodo6,mazo1);
    tablero->raiz = nodo1;
    tablero->raiz->izquierda = nodo2;
    nodo2->arriba = tablero->raiz;
    nodo2->padre = tablero->raiz;

    imprimirLista(mazo1);
    insertarFichaAJugar(mazo1,tablero);//Aqui sucede la magia XD
};