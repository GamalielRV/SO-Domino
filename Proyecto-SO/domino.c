#include "listaMazo.h"
#include "listaTablero.h"
#include "JugadorAux.h"
#include "fichero.c"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <math.h>

FILE *registroJuego;
FILE *registroGanador;


/**
 * Thread section
*/
int const MAX_JUGADORES = 7;
pthread_mutex_t JUGADORES_TURNO[MAX_JUGADORES];
struct listaMazo *unaLista;
struct listaTablero *tablero;
    
/**Codigo a a acomodar por Gama */
void *Turno(void *ptr)
{
    // aca sacan el mazo y llaman a insertarFicha !!!!!

    JugadorAux *jugador = (JugadorAux*)ptr;
    printf("Jugador %d esperando turno, %d!!\n", jugador->id, jugador->turno);
    while (1)
    {   
        pthread_mutex_lock(jugador->turno);
        printf("--------------------------\n");
        // aca sacan el mazo y llaman a insertarFicha !!!!!
        printf("Jugador %d jugando!!\n", jugador->id);
        sleep(2); //simula el tiempo que tarda en jugar
        /**
         * REvisen esto jajajaj
        */
        while( jugador->mazo->primero != NULL || unaLista->primero != NULL){
            printf("Jugando el turno de %s\n",jugador->nombre);
            printf("Fichas de %s\n",jugador->nombre);
            imprimirLista(jugador->mazo);
            if(jugador->mazo->primero == NULL){
                printf("\n");
                printf("%s Comio una ficha \n",jugador->nombre);
                printf("comio la ficha ");
                printf("\n");
                imprimirFicha(unaLista->primero->unaFicha);
                insertarNodo(crearNodo(unaLista->primero->unaFicha),jugador->mazo);
                eliminarNodoMazo(unaLista,crearNodo(unaLista->primero->unaFicha));
                ordenarLista(jugador->mazo);
            }else{
                printf("\n");
                int puntos = insertarFichaAJugar(jugador->mazo, tablero);
                if(puntos == -1){
                    printf("\n");
                    printf("%s Comio una ficha \n",jugador->nombre);
                    printf("comio la ficha ");
                    imprimirFicha(unaLista->primero->unaFicha);
                    printf("\n");
                    insertarNodo(crearNodo(unaLista->primero->unaFicha),jugador->mazo);
                    eliminarNodoMazo(unaLista,crearNodo(unaLista->primero->unaFicha));
                    ordenarLista(jugador->mazo);
                }else{
                    printf("%s Jugo una ficha \n",jugador->nombre);
                    printf("%s Gano %d Puntos \n",jugador->nombre,puntos);
                    //Llamar al metodo de aciertaPuntos
                    //aciertaPuntos(registroJuego, jugador->nombre, puntos);
                   
                }

            }
            printf("Fin del turno de %s\n",jugador->nombre);
            printf("-------------------------------------------------------\n");
            printf("\nFichas restantes para comer \n");
            imprimirLista(unaLista);
            printf("\n-------------------------------------------------------\n");
        }
        //Aqui seguiria mostrar al ganador y el registro del ganador

        printf("Jugador %d termino su turno!!\n", jugador->id);
        printf("--------------------------\n");
        pthread_mutex_unlock(jugador->siguienteJugadorTurno);
        // poner un condicional cuando el juego termine
        // y llamar a un break
    }

    printf("Jugador %d termino su turno!!\n", jugador->id);

}


void EmpezarJuego(int cantidadJugadores, ListaJugador *listaJugadores, JugadorAux *jugadorInicial)
{   
    printf("Iniciando juego...\n");
    // Inicializar los mutexes
    for (int i = 0; i < 7; i++) {
        pthread_mutex_init(&JUGADORES_TURNO[i], NULL);
    }

    // Inicializar los jugadores
    JugadorAux *jugador = listaJugadores->primero;
    for (size_t i = 0; i < cantidadJugadores; i++)
    {   
        // scan para obtener datos
        // se debe de agregar mas atributos al jugador
        // como el nombre, el mazo, etc
        //primera se bloquea el mutex y luego se crea el hilo
        pthread_t thread_tmp;
        jugador ->id = i;
        jugador ->thread = thread_tmp;
        jugador ->turno = &JUGADORES_TURNO[i];
        jugador ->siguienteJugadorTurno = &JUGADORES_TURNO[(i+1)%cantidadJugadores];
        pthread_mutex_lock(jugador ->turno);
        printf("Jugador %d creado, %d!!\n", jugador->id, jugador->turno);

        jugador = jugador->siguiente;

    }

    jugador = listaJugadores->primero;
    for (size_t i = 0; i < cantidadJugadores; i++)
    {   
        // scan para obtener datos
        // se debe de agregar mas atributos al jugador
        // como el nombre, el mazo, etc
        //primera se bloquea el mutex y luego se crea el hilo
        pthread_create(&jugador ->thread, NULL, Turno, jugador);
        jugador = jugador->siguiente;

    }

    jugador = listaJugadores->primero;
    for (size_t i = 0; i < cantidadJugadores; i++)
    {   
        // scan para obtener datos
        // se debe de agregar mas atributos al jugador
        // como el nombre, el mazo, etc
        //primera se bloquea el mutex y luego se crea el hilo
        pthread_mutex_unlock(jugadorInicial ->turno);
        pthread_join(jugador->thread, NULL);
        jugador = jugador->siguiente;

    }
    printf("Cantidad de jugadores: %d\n", cantidadJugadores);

}




/*
* Thread section
*/

int main(void){
    int num_jugadores;
    int const MAX_JUGADORES = 7;
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
        printf("Jugador %d: %s, %d fichas\n", i + 1, nombres_jugadores[i], 0);
    }

    // Iniciar juego
    //EmpezarJuego(num_jugadores, nombres_jugadores);

    int vectorUP[28] = {0, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 2, 3, 4, 5, 6, 3, 4, 5, 6, 4, 5, 6, 5, 6, 6};
    int vectorDown[28] = {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 6};
    unaLista = crearLista(); // tiene que ser global 
    for (size_t i = 0; i < 28; i++)
    {
        struct ficha *unaFicha = newFicha(vectorUP[i], vectorDown[i], i);
        struct nodoMazo *unNodo = crearNodo(unaFicha);
        insertarNodo(unNodo, unaLista);
    }
    int cont = 0;
    int primerTurno = 0;
    tablero = newListaTablero();
    int fichasXJugador = floor(28 /(num_jugadores+1));
    ListaJugador* listaJugadores = newListaJugador();
    JugadorAux* jugador = NULL;
    //repoarte las fichas que le tocan a cada jugador
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

    /*
    *  Esto es lo que hay que paralelizar
    */
    printf("num_jugadores: %d\n",num_jugadores);
    EmpezarJuego(num_jugadores, listaJugadores, jugador);
            
    //finJuego(registroJuego, registroGanador);
    //printf("El ganador del juego es: %s\n", getNombreGanador(registroGanador));


    printf("Fin del juego\n");
    return 0;
};
