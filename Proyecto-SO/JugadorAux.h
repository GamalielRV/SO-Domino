#ifndef JUGADOR_FILE
#define JUGADOR_FILE
//importante para que no se auto importen las librerias

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "listaMazo.h"


typedef struct JugadorAux
{
    int id; // Id del jugador
    char* nombre; // Nombre del jugador
    int puntos; // Puntos del jugador
    listaMazo* mazo; // Mazo del jugador
    struct JugadorAux * siguiente; //

    //gama agrego esto
    pthread_t thread; // Hilo del jugador 
    pthread_mutex_t* siguienteJugadorTurno; // Puntero al siguiente mutex en la secuencia
    pthread_mutex_t* turno; // Puntero al mutex actual

} JugadorAux;

JugadorAux* newNodoJugador(int id,char* nombre, listaMazo* mazo){
    struct JugadorAux* self= (struct JugadorAux*)malloc(sizeof(struct JugadorAux));
    self->id = id;
    self->nombre = nombre;
    self->mazo = mazo;
    self->puntos = 0;
    self->siguiente = NULL;
    return self;
}

typedef struct ListaJugador{
    JugadorAux* primero;
    JugadorAux* ultimo;
}ListaJugador;

ListaJugador* newListaJugador(){
    struct ListaJugador* self= (struct ListaJugador*)malloc(sizeof(struct ListaJugador));
    self->primero = NULL;
    self->ultimo = NULL;
    return self;
}

void insertarJugador(JugadorAux* jugador, ListaJugador* lista){
    if(lista->primero == NULL){
        lista->primero = jugador;
        lista->ultimo = jugador;
    }else{
        lista->ultimo->siguiente = jugador;
        lista->ultimo = jugador;
    }
}

JugadorAux* encontrarFichaAlta(ListaJugador* lista){
    int vecFichas[7] = {27,25,22,18,13,7,0};
    for(size_t i = 0; i < 7; i++){
        JugadorAux* jugAux = lista->primero;
        while(jugAux != NULL){
            nodoMazo* nodoAux = jugAux->mazo->primero;
            while(nodoAux != NULL){
                if(nodoAux->unaFicha->valor == vecFichas[i]){
                    return jugAux;
                }
                nodoAux = nodoAux->siguiente;
            }
            jugAux = jugAux->siguiente;
        }
    }
    
    return NULL;
};

nodoMazo* ingresarPrimeraFicha(JugadorAux* jugAux){
    if(jugAux != NULL){
        int vecFichas[7] = {27,25,22,18,13,7,0};
        for(size_t i = 0; i < 7; i++){
            nodoMazo* nodoAux = jugAux->mazo->primero;
            while(nodoAux != NULL){
                if(nodoAux->unaFicha->valor == vecFichas[i]){
                    return nodoAux;
                }
                nodoAux = nodoAux->siguiente;
            }
        }
    }
    return NULL;
}




#endif
