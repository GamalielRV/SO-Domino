
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
    // solicitud de datos para iniciar el juego
    int num_jugadores, num_fichas;

    printf("Bienvenido al juego de domino\n");

    // Pedir número de jugadores
    printf("Ingrese el número de jugadores (2-7): ");
    scanf("%d", &num_jugadores);

    // Validar número de jugadores
    while (num_jugadores < 2 || num_jugadores > 7) {
        printf("Número de jugadores inválido. Ingrese un número entre 2 y 4: ");
        scanf("%d", &num_jugadores);
    }

    // Pedir nombres de jugadores
    char** nombres_jugadores = (char**) malloc(num_jugadores * sizeof(char*));
    for (int i = 0; i < num_jugadores; i++) {
        nombres_jugadores[i] = (char*) malloc(50 * sizeof(char));
        printf("Ingrese el nombre del jugador %d: ", i + 1);
        scanf("%s", nombres_jugadores[i]);
    }

    // Pedir número de fichas
    printf("Ingrese el número de fichas por jugador (hasta 7): ");
    scanf("%d", &num_fichas);

    // Validar número de fichas
    while (num_fichas < 1 || num_fichas > 7) {
        printf("Número de fichas inválido. Ingrese un número entre 1 y 7: ");
        scanf("%d", &num_fichas);
    }

    // Imprimir información de jugadores
    printf("Información de jugadores:\n");
    for (int i = 0; i < num_jugadores; i++) {
        printf("Jugador %d: %s, %d fichas\n", i + 1, nombres_jugadores[i], num_fichas);
    }

    // Liberar memoria por si se ocupa aqui esta esto mae
    for (int i = 0; i < num_jugadores; i++) {
        free(nombres_jugadores[i]);
    }
    free(nombres_jugadores);
    // solicitud de juego para iniciar 
   
    struct listaTablero * tablero = newListaTablero();// se crea el tablero


    // Convertimos el puntero void *ptr de entrada en un puntero de tipo MutexNode
    MutexNode *node = (MutexNode *) ptr;

    // El hilo entra en un loop infinito
    
        // Se adquiere el mutex actual para poder ejecutar el código en la sección crítica
        pthread_mutex_lock(node->current);
        
        // Se itera 4 veces para imprimir un mensaje cada segundo
        while (/* condition */)
        {
                  sleep(1);
              int puntos =   insertarFichaAJugar(mazo1,tablero);//Aqui sucede la magia XD
              // parte de Juan llevar registro de puntos
              pthread_mutex_unlock(node->next);
        }
        // leer txt de ganadores
        
     

        
        
        // Se libera el mutex siguiente para que otro hilo pueda adquirirlo y entrar a su sección crítica
        


    
};