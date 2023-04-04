#ifndef JUGADOR_FILE
#define JUGADOR_FILE

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "listaMazo.h"

typedef struct Jugador
{
    int id; // Id del jugador
    char* nombre; // Nombre del jugador
    int puntos; // Puntos del jugador
    listaMazo* mazo; // Mazo del jugador
    pthread_t thread; // Hilo del jugador 
    pthread_mutex_t* siguienteJugadorTurno; // Puntero al siguiente mutex en la secuencia
    pthread_mutex_t* turno; // Puntero al mutex actual

} Jugador;




#endif
