#ifndef MainPrueba
#define MainPrueba
#include "listaMazo.h"
#include "listaTablero.h"
#include "JugadorAux.h"
#include "fichero.c"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <math.h>

FILE *registroJuego;
FILE *registroGanador;

unsigned int sleep(unsigned int seconds);

/*
 * Variables globales, solo se pueden editar en el main
 */
void inicializar_jugadores()
{

    // se inicializa el arreglo de jugadores y los mutexes y se les asigna memoria dinamica
    JUGADORES = malloc(MAX_JUGADORES * sizeof(Jugador));
    JUGADORES_TURNO = malloc(MAX_JUGADORES * sizeof(pthread_mutex_t));
}
int const MAX_JUGADORES = 7;

int num_jugadores;
int fichasXJugador = 0;
ListaJugador *listaJugadores;
struct listaMazo *unaLista ;
char **nombres_jugadores;
struct listaTablero *tablero;
JugadorAux* jugador = NULL;


void *solicitudDeDatos()
{
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
    nombres_jugadores = (char **)malloc(num_jugadores * sizeof(char *));
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
        printf("Jugador %d: %s, %d fichas\n", i + 1, nombres_jugadores[i]);
    }
}

void *crearMazo()
{
    int vectorUP[28] = {0, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 2, 3, 4, 5, 6, 3, 4, 5, 6, 4, 5, 6, 5, 6, 6};
    int vectorDown[28] = {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 6};
    unaLista = crearLista();
    for (size_t i = 0; i < 28; i++)
    {
        struct ficha *unaFicha = newFicha(vectorUP[i], vectorDown[i], i);
        struct nodoMazo *unNodo = crearNodo(unaFicha);
        insertarNodo(unNodo, unaLista);
    }

    struct listaTablero *tablero = newListaTablero();
    fichasXJugador = floor(28 / (num_jugadores + 1));
    listaJugadores = newListaJugador();
    JugadorAux *jugador = NULL;
}


void *llenarJugadores()
{
    struct listaTablero *tablero = newListaTablero();
    int primerTurno = 0;
    int cont = 0;
    jugador = NULL;
    while(primerTurno != 1){
        listaJugadores = newListaJugador();
        while( cont < num_jugadores){
        listaMazo * listJugador = crearLista();
            int numFichas = size(unaLista);
            //printf("fichas restantes: %d\n",size(unaLista)); 
            for(size_t j =0; j < fichasXJugador; j++){
                int numFicha = rand() % numFichas;
                struct nodoMazo * nodoAux = encontrarNodo(numFicha,unaLista);
                if(nodoAux != NULL){
                    insertarNodo(crearNodo(nodoAux->unaFicha),listJugador);
                    eliminarNodoMazo(unaLista,crearNodo(nodoAux->unaFicha));
                    numFicha --;
                } 
                //Ingresamos una ficha al mazo jugador
            }
            //Creando Jugadores 
            insertarJugador(newNodoJugador(cont,nombres_jugadores[cont],listJugador),listaJugadores);
            cont ++;
        }
        JugadorAux* jugadorAux = listaJugadores->primero;
        //Metodo que ingresa la primera ficha
        int contPriTurno = 0;
        primerTurno = 1;
        jugador = encontrarFichaAlta(listaJugadores);
        if(jugador != NULL){
            primerTurno = 1;
            printf("Primera Ficha de %s\n",jugador->nombre);
            imprimirLista(jugador->mazo);
            printf("\n------------------------------------------------------\n");
            nodoTablero * nodoAux = newNodoTablero(ingresarPrimeraFicha(jugador)->unaFicha,NULL); 
            tablero->raiz = nodoAux;
            nodoMazo * nodoTemp = crearNodo(nodoAux->unaFicha);
            eliminarNodoMazo(jugador->mazo,nodoTemp);
        }
    }
}
/**Codigo a a acomodar por Gama */
void *Turno(void *ptr)
{

    printf("Jugador %d esperando turno!!\n", jugador->id);
    sleep(1); // simula el tiempo que tarda en jugar
    while (1)
    {
        pthread_mutex_lock(jugador->turno);
        printf("--------------------------\n");
        // aca sacan el mazo y llaman a insertarFicha !!!!!
        printf("Jugador %d jugando!!\n", jugador->id);
        sleep(5); // simula el tiempo que tarda en jugar

        printf("Jugador %d termino su turno!!\n", jugador->id);
        printf("--------------------------\n");
        pthread_mutex_unlock(jugador->siguienteJugadorTurno);
        // poner un condicional cuando el juego termine
        // y llamar a un break
    }
}


void EmpezarJuego()
{   
    crearMazo();
    solicitudDeDatos();
    llenarJugadores();

    // Inicializar los mutexes
    for (int i = 0; i < 7; i++)
    {
        pthread_mutex_init(&JUGADORES_TURNO[i], NULL);
    }

    // Inicializar los jugadores
    for (size_t i = 0; i < num_jugadores; i++)
    {
        // scan para obtener datos
        // se debe de agregar mas atributos al jugador
        // como el nombre, el mazo, etc
        pthread_t thread_tmp;
        JUGADORES[i].id = i;
        JUGADORES[i].turno = &JUGADORES_TURNO[i];
        JUGADORES[i].siguienteJugadorTurno = &JUGADORES_TURNO[(i + 1) % num_jugadores];
        JUGADORES[i].thread = &thread_tmp;
    }

    // Quien iniciara el juego
    for (size_t k = 0; k < num_jugadores; k++)
    {
        if (jugador->id != JUGADORES[k].id)
        {
            // bloquea el mutex del jugador que no inicia
            // solo el jugador que inicia el juego no se le bloquea el mutex
            pthread_mutex_lock(JUGADORES[k].turno);
        }
    }




    // Crear los hilos
    for (size_t l = 0; l < num_jugadores; l++)
    {
        pthread_create(&JUGADORES[l].thread, NULL, Turno, &JUGADORES[l]);
    }

    for (size_t m = 0; m < num_jugadores; m++)
    {
        pthread_join(JUGADORES[m].thread, NULL);
    }
}

int main(void)
{


    printf("Cantidad de jugadores: %d\n", num_jugadores);
    EmpezarJuego();

    return 0;
};
#endif