#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include "Map.h"
#include "funciones.h"
#include "mainmap.h"


int main(){
    Map * mapa_canciones=createMap(stringHash, stringEqual);
    Map * mapa_artistas=createMap(stringHash, stringEqual);
    Map * Mapa_album=createMap(stringHash, stringEqual);
    int opcion;
    char archivo_importacion[256];
    char archivo_exportacion[256];
    char album_agregar[256];
    char fecha_album[256];
    char cancion_agregar[1024];
    char cancion_agregar_nombre[256];
    char cancion_agregar_artista[256];
    char cancion_agregar_duracion[256];
    char cancion_agregar_fecha[256];
    char eliminar_artista[256];
    char cancion_buscada[256];
    char buscar_artista[256];
    char buscar_album[256];
    int opcion_album;
    mostrar();
    scanf("%d", &opcion);
    while(opcion!=0){
        if(opcion==1){
            printf("Ingrese el nombre del archivo(con su extension, ej:canciones.csv):\n");
            fflush(stdin);
            scanf("%[^\n]s",archivo_importacion);
            cargar_datos_csv(archivo_importacion, mapa_canciones, mapa_artistas, Mapa_album);
            mostrar();
            scanf("%d", &opcion);
        }
        else if(opcion==2){

            printf("Ingrese el nombre del archivo(con su extension, ej:canciones.csv):\n");
            fflush(stdin);
            scanf("%[^\n]s",archivo_exportacion);
            exportar_musica(archivo_exportacion, mapa_canciones);
            mostrar();
            scanf("%d", &opcion);
        }
        else if(opcion==3){

            printf("Ingrese el nombre del album:\n");
            fflush(stdin);
            scanf("%[^\n]s",album_agregar);
            printf("Ingrese la fecha:\n");
            fflush(stdin);
            scanf("%[^\n]s",fecha_album);
            agregar_album(album_agregar,Mapa_album);
            printf("Desea agregar una cancion? No:0, Si:1\n");
            scanf("%d",&opcion_album);
            while(opcion_album==1){
                printf("Ingrese los datos de la cancion:\n");
                fflush(stdin);
                printf("Titulo:\n");
                fflush(stdin);
                scanf("%[^\n]s",cancion_agregar_nombre);
                strcpy(cancion_agregar,cancion_agregar_nombre);
                strcat(cancion_agregar,",");
                printf("Artista:\n");
                fflush(stdin);
                scanf("%[^\n]s",cancion_agregar_artista);
                strcat(cancion_agregar,cancion_agregar_artista);
                strcat(cancion_agregar,",");
                printf("Duracion:\n");
                fflush(stdin);
                scanf("%[^\n]s",cancion_agregar_duracion);
                strcat(cancion_agregar,cancion_agregar_duracion);
                strcat(cancion_agregar,",");
                strcat(cancion_agregar,",");
                strcat(cancion_agregar,album_agregar);
                strcat(cancion_agregar,",");
                strcat(cancion_agregar,fecha_album);
                agregar_cancion_album(cancion_agregar, mapa_canciones , mapa_artistas, Mapa_album);
                printf("Desea seguir agregando canciones? No:0, Si:1\n");
                scanf("%d",&opcion_album);
            }
            mostrar();
            scanf("%d", &opcion);
        }
        else if(opcion==4){

            printf("Ingrese los datos de la cancion:\n");
            printf("Titulo:\n");
            fflush(stdin);
            fflush(stdin);
            scanf("%[^\n]s",cancion_agregar_nombre);
            strcpy(cancion_agregar,cancion_agregar_nombre);
            strcat(cancion_agregar,",");
            printf("Artista:\n");
            fflush(stdin);
            scanf("%[^\n]s",cancion_agregar_artista);
            strcat(cancion_agregar,cancion_agregar_artista);
            strcat(cancion_agregar,",");
            printf("Duracion:\n");
            fflush(stdin);
            scanf("%[^\n]s",cancion_agregar_duracion);
            strcat(cancion_agregar,cancion_agregar_duracion);
            strcat(cancion_agregar,",");
            strcat(cancion_agregar,"-");
            strcat(cancion_agregar,",");
            printf("Fecha:\n");
            fflush(stdin);
            scanf("%[^\n]s",cancion_agregar_fecha);
            strcat(cancion_agregar,cancion_agregar_fecha);
            printf("%s\n",cancion_agregar);
            agregar_cancion(cancion_agregar,mapa_canciones ,mapa_artistas, Mapa_album);
            mostrar();
            scanf("%d", &opcion);
        }
        else if(opcion==5){

            printf("Ingrese el nombre del artista:\n");
            fflush(stdin);
            scanf("%[^\n]s",eliminar_artista);
            eliminar_canciones_artista(eliminar_artista,mapa_canciones,mapa_artistas,Mapa_album);
            mostrar();
            scanf("%d", &opcion);
        }
        else if(opcion==6){

            printf("Ingrese el titulo de la cancion(respete mayusculas):\n");
            fflush(stdin);
            scanf("%[^\n]s",cancion_buscada);
            buscar_cancion(cancion_buscada,mapa_canciones);
            mostrar();
            scanf("%d", &opcion);
        }
        else if(opcion==7){

            printf("Ingrese el nombre del artista:\n");
            fflush(stdin);
            scanf("%[^\n]s",buscar_artista);
            buscar_canciones_artista(buscar_artista,mapa_artistas);
            mostrar();
            scanf("%d", &opcion);
        }
        else if(opcion==8){

            printf("Ingrese el nombre del album:\n");
            fflush(stdin);
            scanf("%[^\n]s",buscar_album);
            buscar_canciones_album(buscar_album,Mapa_album);
            mostrar();
            scanf("%d", &opcion);
        }
    }

    return 0;
}
