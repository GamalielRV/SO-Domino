
#include "listaMazo.h"
#include "listaTablero.h"
#include "Jugador.h"
//#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <math.h>

unsigned int sleep(unsigned int seconds);

/***
 * Variables globales, solo se pueden editar en el main
 */
// se define el numero maximo de jugadores
int const MAX_JUGADORES = 7;
Jugador *JUGADORES;
pthread_mutex_t *JUGADORES_TURNO;
int num_jugadores;

void inicializar_jugadores()
{

    // se inicializa el arreglo de jugadores y los mutexes y se les asigna memoria dinamica
    JUGADORES = malloc(MAX_JUGADORES * sizeof(Jugador));
    JUGADORES_TURNO = malloc(MAX_JUGADORES * sizeof(pthread_mutex_t));
}

void imprimir_nombre_jugador(Jugador *jugador)
{
    printf("El nombre del jugador es: %s\n", jugador->nombre);
}

void liberar_jugadores()
{
    // liberar la memoria apartada para los jugadores y los mutexes
    free(JUGADORES);
    free(JUGADORES_TURNO);
}
/**aqui debemos implementar todo*/
void *Turno(void *ptr)
{
    int vectorUP[28] = {0, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 2, 3, 4, 5, 6, 3, 4, 5, 6, 4, 5, 6, 5, 6, 6};
    int vectorDown[28] = {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 6};
    struct listaMazo *unaLista = crearLista();
    for (size_t i = 0; i < 28; i++)
    {
        struct ficha *unaFicha = newFicha(vectorUP[i], vectorDown[i], i);
        struct nodoMazo *unNodo = crearNodo(unaFicha);
        insertarNodo(unNodo, unaLista);
    }

    Jugador *jugador = (Jugador *)ptr;
    pthread_mutex_lock(jugador->turno);
    //Ingresando fichas a mazo jugadores
    int fichasXJugador = floor(28 /(num_jugadores+1));
    srand(time(NULL));
    int cont = 0;
    while(fichasXJugador > cont){
       listaMazo * listJugador = crearLista();
        int numFichas = size(unaLista);
        printf("fichas restantes: %d\n",size(unaLista)); 
        for(size_t j =0; j < fichasXJugador; j++){
            int numFicha = rand() % numFichas+1;
            struct nodoMazo * nodoAux = encontrarNodo(numFicha,unaLista);
            if(nodoAux != NULL){
                insertarNodo(crearNodo(nodoAux->unaFicha),listJugador);
                eliminarNodoMazo(unaLista,crearNodo(nodoAux->unaFicha));
                numFicha --;
            } 
        }
        int result = pthread_mutex_trylock(jugador->turno);
        if(result == 0){
            pthread_mutex_lock(jugador->turno);
        }      
        sleep(1);
        jugador->mazo = listJugador;
        //imprimirLista(jugador->mazo);
        pthread_mutex_unlock(jugador->siguienteJugadorTurno);
        cont ++;
    }

    struct listaTablero *tablero = newListaTablero(); // se crea el tablero

    
    printf("Jugador %d esperando turno!!", jugador->id);
    printf("fichas por jugador %d \n ", fichasXJugador);
    printf("Nombre %s\n", jugador->nombre);
    // imprimir_nombre_jugador(&jugador);
    sleep(1); // simula el tiempo que tarda en jugar
    //Algoritmo para el primer turno 
    int vecFichas[7] = {27,25,22,18,13,7,0};
    int primerTurno = 0;
    int contPriTurno = 0;
    while(contPriTurno < 7 && primerTurno != 1){
        for(size_t i = 0; i < num_jugadores; i++){
            pthread_mutex_lock(jugador->turno);
            nodoMazo * nodoAux = jugador->mazo->primero;
            while(nodoAux != NULL && primerTurno != 1){
                if(nodoAux->unaFicha->valor == vecFichas[contPriTurno]){
                    primerTurno == 1;
                    nodoTablero * nodoTab = newNodoTablero(nodoAux->unaFicha,NULL);
                    tablero->raiz = nodoTab;
                }
                nodoAux = nodoAux->siguiente;
            }
            pthread_mutex_unlock(jugador->siguienteJugadorTurno);
        }
        contPriTurno ++;
    }
    


    while (1)
    {
        
        // entrada al while se bloquea el jugador que este jugando actualmente
        pthread_mutex_lock(jugador->turno);
        if (jugador->mazo->primero == NULL && unaLista->primero != NULL)
        { // Validando que su mazo no este vacio y el mazo para comer tampoco
            insertarNodo(unaLista->primero,jugador->mazo);
            eliminarNodoMazo(unaLista,unaLista->primero);
        }

        printf("--------------------------\n");
        // aca saca el mazo y se de bebe llamar a insertarFicha !!!!!
        printf("Jugador %d jugando!! ", jugador->id);
        printf("Nombre con %s\n", jugador->nombre);
        // imprimir_nombre_jugador(&jugador);
        sleep(2); // simula el tiempo que tarda en jugar

        printf("Jugador %d termino su turno!! ", jugador->id);
        printf("Nombre  %s\n", jugador->nombre);
        // imprimir_nombre_jugador(&jugador);
        printf("--------------------------\n");
        // se desbloquea el siguiente jugador
        pthread_mutex_unlock(jugador->siguienteJugadorTurno);
        // poner un condicional cuando el juego termine que seria el gane de algun jugador
        // para con un break detener el while
    }
}

// trabajar en esta funcion, para obtener el id del jugador con la ficha mas alta
// es el que nos indica quien inicia el juego
int FichaAlta()
{

    // retorna el ID del jugador con la ficha mas alta

    return 0;
}

void EmpezarJuego(int cantidadJugadores, char *nombreJugadores[])
{

    inicializar_jugadores();
    // Inicializar los mutexes
    for (int i = 0; i < 7; i++)
    {
        pthread_mutex_init(&JUGADORES_TURNO[i], NULL);
    }

    // Inicializar los jugadores
    for (size_t i = 0; i < cantidadJugadores; i++)
    {
        // scan para obtener datos
        // se debe de agregar mas atributos al jugador
        // como el nombre, el mazo, etc
        pthread_t thread_tmp;
        JUGADORES[i].id = i;
        JUGADORES[i].nombre = nombreJugadores[i];
        JUGADORES[i].mazo = crearLista();
        JUGADORES[i].turno = &JUGADORES_TURNO[i];
        JUGADORES[i].siguienteJugadorTurno = &JUGADORES_TURNO[(i + 1) % cantidadJugadores];
        JUGADORES[i].thread = &thread_tmp;
    }

    // Quien iniciara el juego
    for (size_t k = 0; k < cantidadJugadores; k++)
    {
        // se bloquea el mutex del jugador que no inicia
        if (FichaAlta() != JUGADORES[k].id)
        {
            // bloquea el mutex del jugador que no inicia
            // solo el jugador que inicia el juego no se le bloquea el mutex
            pthread_mutex_lock(JUGADORES[k].turno);
        }
    }
    // Crear los hilos
    for (size_t l = 0; l < cantidadJugadores; l++)
    {
        pthread_create(&JUGADORES[l].thread, NULL, Turno, &JUGADORES[l]);
    }

    for (size_t m = 0; m < cantidadJugadores; m++)
    {
        pthread_join(JUGADORES[m].thread, NULL);
    }
}

int main(void)
{

    // solicitud de datos para iniciar el juego
    

    printf("Bienvenido al juego de domino\n");

    // Pedir número de jugadores
    printf("Ingrese el número de jugadores (2-7): ");
    scanf("%d", &num_jugadores);

    // Validar número de jugadores
    while (num_jugadores < 2 || num_jugadores > 7)
    {
        printf("Número de jugadores inválido. Ingrese un número entre 2 y 4: ");
        scanf("%d", &num_jugadores);
    }

    // Pedir nombres de jugadores
    char **nombres_jugadores = (char **)malloc(num_jugadores * sizeof(char *));
    for (int i = 0; i < num_jugadores; i++)
    {
        nombres_jugadores[i] = (char *)malloc(50 * sizeof(char));
        printf("Ingrese el nombre del jugador %d: ", i + 1);
        scanf("%s", nombres_jugadores[i]);
    }



    // Imprimir información de jugadores
    printf("Información de jugadores:\n");
    for (int i = 0; i < num_jugadores; i++)
    {
        printf("Jugador %d: %s, %d fichas\n", i + 1, nombres_jugadores[i] );
    }

    // Iniciar juego
    EmpezarJuego(num_jugadores, nombres_jugadores);

    // al finalizar el juego se libera la memoria apartada previamente
    liberar_jugadores();
    return 0;
};
