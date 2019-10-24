#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Map.h"
#include "funciones.h"
#include "mainmap.h"


int main(){
    Map * mapa_canciones=createMap(stringHash, stringEqual);
    Map * mapa_artistas=createMap(stringHash, stringEqual);
    Map * Mapa_album=createMap(stringHash, stringEqual);
    char archivo_importacion[256];
    char datos_cancion[1024];
    char artista[256];
    char nombre_cancion[256];
    char album[256];
    char fecha[256];
    char archivo_exportacion[256];
    int opcion;
    int opcion_album;
    mostrar();
    scanf("%d", &opcion);
    while(opcion!=0){
        if(opcion==1){
            printf("Ingrese el nombre del archivo(con su extension, ej:canciones.csv):\n");
            scanf("%s",archivo_importacion);
            cargar_datos_csv(archivo_importacion, mapa_canciones, mapa_artistas, Mapa_album);
            mostrar();
            scanf("%d", &opcion);
        }
        else if(opcion==2){
            printf("Ingrese el nombre del archivo(con su extension, ej:canciones.csv):\n");
            scanf("%s",archivo_exportacion);
            exportar_musica(archivo_exportacion, mapa_canciones);
            mostrar();
            scanf("%d", &opcion);
        }
        else if(opcion==3){
            printf("Ingrese el nombre del album:\n");
            scanf("%s",album);
            printf("Ingrese la fecha:\n");
            scanf("%s",fecha);
            agregar_album(album,Mapa_album);
            printf("Desea agregar una cancion? No:0, Si:1\n");
            scanf("%d",&opcion_album);
            while(opcion_album==1){
                printf("Ingrese los datos de la cancion separados por una coma(,):\n");
                scanf("%s",datos_cancion);
                strcat(datos_cancion,",");
                strcat(datos_cancion,album);
                strcat(datos_cancion,",");
                strcat(datos_cancion,fecha);
                agregar_cancion_album(datos_cancion, mapa_canciones , mapa_artistas, Mapa_album);
                printf("Desea seguir agregando canciones? No:0, Si:1\n");
                scanf("%d",&opcion_album);
            }
            mostrar();
            scanf("%d", &opcion);
        }
        else if(opcion==4){
            printf("Ingrese los datos de la cancion separados por una coma(,):\n");
            scanf("%s",datos_cancion);
            strcat(datos_cancion,",");
            strcat(datos_cancion,"-");
            agregar_cancion(datos_cancion,mapa_canciones ,mapa_artistas, Mapa_album);
            mostrar();
            scanf("%d", &opcion);
        }
        else if(opcion==5){
            printf("Ingrese el nombre del artista:\n");
            scanf("%s",artista);
            eliminar_canciones_artista(artista,mapa_canciones,mapa_artistas,Mapa_album);
            mostrar();
            scanf("%d", &opcion);
        }
        else if(opcion==6){
            printf("Ingrese el titulo de la cancion:\n");
            scanf("%s",nombre_cancion);
            buscar_cancion(nombre_cancion,mapa_canciones);
            mostrar();
            scanf("%d", &opcion);
        }
        else if(opcion==7){
            printf("Ingrese el nombre del artista:\n");
            scanf("%s",artista);
            buscar_canciones_artista(artista,mapa_artistas);
            mostrar();
            scanf("%d", &opcion);
        }
        else if(opcion==8){
            printf("Ingrese el nombre del album:\n");
            scanf("%s",album);
            buscar_canciones_album(album,Mapa_album);
            mostrar();
            scanf("%d", &opcion);
        }
    }

    return 0;
}
