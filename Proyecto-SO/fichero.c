#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *registroJuego;
FILE *registroGanador;

void aciertaPuntos(FILE *archivo, char *nomJugador, int cantPuntos)
{

    archivo = fopen("log.txt", "a+");
    char linea[33], parte1[20];
    int contPuntos = 0;
    char *token;

    if (archivo == NULL)
    {
        printf("No fue posible abrir el archivo\n");
    }
    else
    {
        fprintf(archivo, "%s,%d\n", nomJugador, cantPuntos);
        rewind(archivo);
        int puntos_linea = 0, lineaLeida = 1;

        while (fgets(linea, 33, archivo) != NULL) // Leo el archivo por lineas
        {
            puntos_linea = 0;

            // printf("Linea %d es: %s", lineaLeida, linea);
            if (sscanf(linea, "%*[^0-9]%d", &puntos_linea) == 1) // Obtengo el puntaje de una linea.
            {
                int puntaje = puntos_linea;
                parte1[20];
                puntos_linea = 0;
                token = strtok(linea, ",");
                strcpy(parte1, token);
                if (strcmp(parte1, nomJugador) == 0)
                {
                    contPuntos += puntaje;
                }
            }
        }
        fprintf(archivo, "TotalPuntos%s %d\n", nomJugador, (contPuntos / 5));
        rewind(archivo);

        fclose(archivo);
    }
}

void finJuego(FILE *arch1, FILE *arch2)
{
    char ganador[15];
    arch1 = fopen("log.txt", "r");
    if (arch1 == NULL)
    {
        printf("No fue posible abrir el archivo\n");
    }
    else
    {

        char linea[30], primerasLetras[12];
        int puntajeMayor = 0, puntajeLinea;

        while (fgets(linea, sizeof(linea), arch1) != NULL)
        {
            // printf("%s",linea);

            char cadena[] = "TotalPuntos";
            if (strncmp(linea, cadena, strlen(cadena)) == 0) // Comparo las lineas que contienen el valor del array 'cadena' al principio de la linea
            {

                if (sscanf(linea, "%*[^0-9]%d", &puntajeLinea) == 1) // Guardo en la variable puntajeLinea el valor del puntaje de la linea
                {
                    if (puntajeLinea >= puntajeMayor)
                    {
                        puntajeMayor = puntajeLinea;
                        char palabra[30];
                        // printf("%s\n",palabra);
                        // char *palabra = strtok(linea, " "); // Guardo en la variable palabra la primer frase hasta la coma de una linea
                        sscanf(linea, "%s", palabra); // Guardo el valor de la primer palabra de la linea
                        // printf("%s\n", palabra);
                        // printf("%s\n", cadena);

                        // printf("%s\n", ganador);
                        int j = 0;
                        for (int i = 0; i < strlen(palabra); i++)
                        {
                            // printf("%c",cadena[i]);
                            if (palabra[i] != cadena[i])
                            {
                                ganador[j] = palabra[i];
                                // printf("%c",ganador[j]);
                                j++;
                            }
                        }
                        ganador[j] = '\0'; // Añado el caracter nulo al final del arreglo ganador para establecer el final del array
                        //printf("%s\n", ganador);
                    }
                }
            }
        }
        fclose(arch1);
        rewind(arch1);
    }

    arch2 = fopen("totalJuegoGanados.txt", "a+");

    if (arch2 == NULL)
    {
        printf("Error al crear el archivo temporal.\n");
        exit(1);
    }
    else
    {
        char linea[20], ganadorTxt[20];
        int flag = 0, acumuladorPuntos = 0, puntaje, longitudLineaAnterior;
        long int posicion;

        fseek(arch2, 0, SEEK_END); // Ubico el cursor al final fichero
        if (ftell(arch2) == 0)     // Compruebo la posicion actual para corroborar si el archivo esta vacío
        {
            fprintf(arch2, "%s %d\n", ganador, 1);
        }
        else
        {
            fseek (arch2, 0, SEEK_SET);// Ubico el cursor al principio del fichero
            FILE *temporal = fopen("temporal.txt", "w");

            if (temporal == NULL)
            {
                printf("Error al crear el archivo temporal.\n");
                exit(1);
            }

            while (fgets(linea, sizeof(linea), arch2) != NULL)
            {
                sscanf(linea, "%*[^0123456789]%d", &puntaje); // Guardo en la variable puntaje los puntos de cada jugador por linea
                sscanf(linea, "%s", ganadorTxt);              // Guardo en la variable ganadorTxt el nombre del ganador en dicha linea
                
                if (strncmp(ganadorTxt, ganador, strlen(ganador)) == 0)
                {
                    
                    puntaje++;
                    //printf("Entro");
                    
                }
                else
                {
                    printf("Entro2");
                    fputs(linea, temporal);
                    puntaje = 1;
                    // printf("%s\n",linea);
                }
            }
            fclose(arch2);
            fclose(temporal);
            remove("totalJuegoGanados.txt");
            rename("temporal.txt", "totalJuegoGanados.txt");

            arch2 = fopen("totalJuegoGanados.txt", "r+");
            if (arch2 == NULL)
            {
                printf("Error al abrir el archivo.\n");
                exit(1);
            }
            fseek(arch2, 0, SEEK_END); // Ubico el cursor al final del fichero

            // printf("%d", puntaje);
            fprintf(arch2, "%s %d\n", ganador, puntaje);
        }

        fclose(arch2);
    }
}

int main()
{

    int cantidadPuntos = 5;
    char *nomJugador = "Leo";
     aciertaPuntos(registroJuego, nomJugador, cantidadPuntos);
    //finJuego(registroJuego, registroGanador);

    return 0;
}