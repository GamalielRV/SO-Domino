
#include "listaMazo.h"
#include "listaTablero.h"
#include "Jugador.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

unsigned int sleep(unsigned int seconds);

/***
 * Variables globales, solo se pueden editar en el main
*/
int const MAX_JUGADORES = 7;
Jugador JUGADORES[MAX_JUGADORES];
pthread_mutex_t JUGADORES_TURNO[MAX_JUGADORES];

    
/**Codigo a a acomodar por Gama */
void *Turno(void *ptr)
{
    // aca sacan el mazo y llaman a insertarFicha !!!!!

    Jugador *jugador = (Jugador*)ptr;
    printf("Jugador %d esperando turno!!\n", jugador->id);
    sleep(1); //simula el tiempo que tarda en jugar
    while (1)
    {   
        pthread_mutex_lock(jugador->turno);
        printf("--------------------------\n");
        // aca sacan el mazo y llaman a insertarFicha !!!!!
        printf("Jugador %d jugando!!\n",jugador->id);
        sleep(5); //simula el tiempo que tarda en jugar

        printf("Jugador %d termino su turno!!\n", jugador->id);
        printf("--------------------------\n");
        pthread_mutex_unlock(jugador->siguienteJugadorTurno);
        // poner un condicional cuando el juego termine
        // y llamar a un break
    }


}

int FichaAlta(){

    // retorna el ID del jugador con la ficha mas alta

    return 3;
}

void EmpezarJuego(int cantidadJugadores)
{   

    // Inicializar los mutexes
    for (int i = 0; i < 7; i++) {
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
        JUGADORES[i].turno = &JUGADORES_TURNO[i];
        JUGADORES[i].siguienteJugadorTurno = &JUGADORES_TURNO[( i + 1 ) % cantidadJugadores];
        JUGADORES[i].thread = &thread_tmp;
    }

    // Quien iniciara el juego
    for (size_t k = 0; k < cantidadJugadores; k++)
    {
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


//
int main(void){
    
    // int vectorUP[28] = {0,1,2,3,4,5,6,1,2,3,4,5,6,2,3,4,5,6,3,4,5,6,4,5,6,5,6,6};
    // int vectorDown[28] = {0,0,0,0,0,0,0,1,1,1,1,1,1,2,2,2,2,2,3,3,3,3,4,4,4,5,5,6};
    // struct listaMazo * unaLista = crearLista();
    // for (size_t i = 0; i < 27; i++)
    // {
    //     struct ficha * unaFicha = newFicha(vectorUP[i],vectorDown[i],i); 
    //     struct nodoMazo * unNodo = crearNodo(unaFicha);
    //     insertarNodo(unNodo,unaLista);

    // }
    // struct listaMazo * listaMazoJugador = crearLista();
    // int numero = rand() % 27;
    // insertarNodo(encontrarNodo(numero,unaLista),listaMazoJugador);
    // numero = rand() % 27;
    // insertarNodo(encontrarNodo(numero,unaLista),listaMazoJugador);
    // numero = rand() % 27;
    // insertarNodo(encontrarNodo(numero,unaLista),listaMazoJugador);
    // imprimirLista(listaMazoJugador);
    // ordenarLista(listaMazoJugador);
    // imprimirLista(listaMazoJugador);
    // printf("%d\n",size(listaMazoJugador));
    // printf("webadas");

    // struct ficha * ficha1 = newFicha(6,6,27);
    // struct nodoTablero * nodo1 = newNodoTablero(ficha1,NULL);
    // struct ficha * ficha2 = newFicha(6,5,26);
    // struct nodoTablero * nodo2 = newNodoTablero(ficha2,nodo1);
    // struct ficha * ficha3 = newFicha(6,4,25);
    // struct nodoMazo * nodo3 = crearNodo(ficha3);
    // struct ficha * ficha4 = newFicha(3,5,12);
    // struct nodoMazo * nodo4 = crearNodo(ficha4);
    // struct ficha * ficha5 = newFicha(5,5,20);
    // struct nodoMazo * nodo5 = crearNodo(ficha5);
    // struct ficha * ficha6 = newFicha(1,1,20);

    // struct nodoMazo * nodo6 = crearNodo(ficha6);
    // struct listaTablero * tablero = newListaTablero();
    // struct listaMazo * mazo1 = crearLista();
    // insertarNodo(nodo3,mazo1);
    // insertarNodo(nodo4,mazo1);
    // insertarNodo(nodo5,mazo1);
    // insertarNodo(nodo6,mazo1);
    // tablero->raiz = nodo1;
    // tablero->raiz->izquierda = nodo2;
    // nodo2->arriba = tablero->raiz;
    // nodo2->padre = tablero->raiz;

    // imprimirLista(mazo1);
    // insertarFichaAJugar(mazo1,tablero);//Aqui sucede la magia XD
    
    int cantidadJugadores = 6;
    // scanf("%d",&numero);
    printf("Cantidad de jugadores: %d\n", cantidadJugadores);
    EmpezarJuego(cantidadJugadores);

    return 0;



};
