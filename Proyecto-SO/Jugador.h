#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "listaMazo.h"

typedef struct Jugador
{
    char* nombre; // Nombre del jugador
    int puntos; // Puntos del jugador
    listaMazo* mazo; // Mazo del jugador
    pthread_mutex_t* next; // Puntero al siguiente mutex en la secuencia
    pthread_mutex_t* current; // Puntero al mutex actual
    pthread_mutex_t myMutex1; // Declaración de 2 variables de tipo mutex
    pthread_mutex_t myMutex2;
} Jugador;

Jugador* newJugador(pthread_mutex_t* next, pthread_mutex_t* current) {
    Jugador* self = (Jugador*)malloc(sizeof(Jugador));
    self->nombre = "Jugador";
    self->puntos = 0;
    self->mazo = crearLista();

    pthread_mutex_init(&self->myMutex1, NULL);
    pthread_mutex_init(&self->myMutex2, NULL);
    self->current = &self->myMutex1;
    self->next = &self->myMutex2;

    return self;
}