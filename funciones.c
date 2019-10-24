#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funciones.h"
#include "Map.h"
#include "lectura.h"

struct Cancion{
    char* titulo;
    char* artista;
    char* duracion;
    char* album;
    char* fecha;
};

void mostrar(){
    printf("(1)-Importar musica desde un archivo CSV.\n");
    printf("(2)-Exportar musica CSV.\n");
    printf("(3)-Agregar album.\n");
    printf("(4)-Agregar cancion.\n");
    printf("(5)-Eliminar canciones de un artista.\n");
    printf("(6)-Buscar cancion.\n");
    printf("(7)-Buscar canciones de un artista.\n");
    printf("(8)-Buscar album.\n");
    printf("(0)-Salir\n");
    printf("Seleccione una opcion del menu:\n");
}


/*Cancion *crearCancion(char *linea){
    int largo;
    Cancion *nueva=malloc(sizeof(char));
    largo=strlen(get_csv_field(linea,1))+1;
    nueva->titulo=malloc(sizeof(char)*largo);
    largo=strlen(get_csv_field(linea,2))+1;
    nueva->artista=malloc(sizeof(char)*largo);
    largo=strlen(get_csv_field(linea,3))+1;
    nueva->duracion=malloc(sizeof(char)*largo);
    largo=strlen(get_csv_field(linea,4))+1;
    nueva->album=malloc(sizeof(char)*largo);
    strcpy(nueva->titulo,get_csv_field(linea,1));
    strcpy(nueva->artista,get_csv_field(linea,2));
    strcpy(nueva->duracion,get_csv_field(linea,3));
    strcpy(nueva->album,get_csv_field(linea,4));
    return nueva;
}*/

Cancion * crearCancion(char* linea){
    Cancion* dato=malloc(sizeof(Cancion));
    dato->titulo=malloc(sizeof(char));
    dato->artista=malloc(sizeof(char));
    dato->duracion=malloc(sizeof(char));
    dato->album=malloc(sizeof(char));
    dato->fecha=malloc(sizeof(char));
    const char* titulo=get_csv_field (linea,1);
    const char* artista=get_csv_field (linea,2);
    const char* duracion=get_csv_field (linea,3);
    const char* album=get_csv_field (linea,4);
    const char* fecha=get_csv_field (linea,5);
    strcpy(dato->titulo,titulo);
    strcpy(dato->artista,artista);
    strcpy(dato->duracion,duracion);
    strcpy(dato->album,album);
    strcpy(dato->fecha,fecha);
    return dato;
}

void cargar_datos_csv(char* archivo, Map * mapa_canciones , Map * mapa_artistas, Map * Mapa_album){
    FILE* fp=fopen(archivo,"r");
    long canciones=0;
    char linea[1024];
    char* ptr;
    Cancion* cancion_nueva=NULL;
    Cancion* cancion=NULL;
    Map* artista=NULL;
    Map* album=NULL;
    fgets(linea,1023,fp);
    while(fgets(linea,1023,fp)!=NULL){
        printf("1-");
        ptr = strtok(linea,"\r");
        ptr = _strdup(ptr);
        printf("2-");
        cancion_nueva=crearCancion(ptr);
        printf("3-");
        cancion=searchMap(mapa_canciones,cancion_nueva->titulo);
        printf("4-");
        if(cancion==NULL){
            insertMap(mapa_canciones,cancion_nueva->titulo,cancion_nueva);
        }
        printf("5-");
        artista=searchMap(mapa_artistas,cancion_nueva->artista);
        printf("6-");
        if(artista==NULL){
            artista=createMap(stringHash, stringEqual);
            insertMap(artista,cancion_nueva->titulo,cancion_nueva);
            insertMap(mapa_artistas,cancion_nueva->artista,artista);
        }
        else{
            insertMap(artista,cancion_nueva->titulo,cancion_nueva);
        }
        printf("7-");
        album=searchMap(Mapa_album,cancion_nueva->album);
        printf("8-");
        if(album==NULL){
            album=createMap(stringHash, stringEqual);
            insertMap(album,cancion_nueva->titulo,cancion_nueva);
            insertMap(Mapa_album,cancion_nueva->album,album);
        }
        else{
            insertMap(album,cancion_nueva->titulo,cancion_nueva);
        }
        printf("9\n");
        canciones++;
        printf("cantidad: %ld \nnombre: %s\nalbum: %s\n",canciones,cancion_nueva->titulo,cancion_nueva->album);
    }
    if(linea==NULL){
        printf("NULO\n");
    }
    fclose(fp);
}

void exportar_musica(char* archivo, Map* mapa_canciones){
    FILE* fp=fopen(archivo,"a");
    Cancion* cancion=firstMap(mapa_canciones);
    while(cancion!=NULL){
        fputs(cancion->titulo,fp);
        fputc(',',fp);
        fputs(cancion->artista,fp);
        fputc(',',fp);
        fputs(cancion->duracion,fp);
        fputc(',',fp);
        fputs(cancion->album,fp);
        fputc('\n',fp);
        cancion=nextMap(mapa_canciones);
    }
    fclose(fp);
}

void agregar_album(char* album,Map* Mapa_album){
    Map* mapa=createMap(stringHash, stringEqual);
    insertMap(Mapa_album,album,mapa);
}

void agregar_cancion_album(char *linea, Map * mapa_canciones , Map * mapa_artistas, Map* Mapa_album){
    char* ptr;
    Cancion* cancion_nueva=NULL;
    Cancion* cancion=NULL;
    Map* artista=NULL;
    Map* album=NULL;
    ptr = strtok(linea,"\r");
    ptr = _strdup(ptr);
    cancion_nueva=crearCancion(ptr);
    cancion=searchMap(mapa_canciones,cancion_nueva->titulo);
    if(cancion==NULL){
        insertMap(mapa_canciones,cancion_nueva->titulo,cancion_nueva);
    }
    else{
        return;
    }
    artista=searchMap(mapa_artistas,cancion_nueva->artista);
    if(artista==NULL){
        artista=createMap(stringHash, stringEqual);
        insertMap(artista,cancion_nueva->titulo,cancion_nueva);
        insertMap(mapa_artistas,cancion_nueva->artista,artista);
    }
    else{
        insertMap(artista,cancion_nueva->titulo,cancion_nueva);
    }
    album=searchMap(Mapa_album,cancion_nueva->album);
    if(album==NULL){
        album=createMap(stringHash, stringEqual);
        insertMap(album,cancion_nueva->titulo,cancion_nueva);
        insertMap(Mapa_album,cancion_nueva->album,album);
    }
    else{
        insertMap(album,cancion_nueva->titulo,cancion_nueva);
    }
}

void agregar_cancion(char *linea, Map * mapa_canciones , Map * mapa_artistas,  Map* Mapa_album){
    char* ptr;
    Cancion* cancion_nueva=NULL;
    Cancion* cancion=NULL;
    Map* artista=NULL;
    Map* album=NULL;
    ptr = strtok(linea,"\r");
    ptr = _strdup(ptr);
    cancion_nueva=crearCancion(ptr);
    cancion=searchMap(mapa_canciones,cancion_nueva->titulo);
    if(cancion==NULL){
        insertMap(mapa_canciones,cancion_nueva->titulo,cancion_nueva);
    }
    else{
        return;
    }
    artista=searchMap(mapa_artistas,cancion_nueva->artista);
    if(artista==NULL){
        artista=createMap(stringHash, stringEqual);
        insertMap(artista,cancion_nueva->titulo,cancion_nueva);
        insertMap(mapa_artistas,cancion_nueva->artista,artista);
    }
    else{
        insertMap(artista,cancion_nueva->titulo,cancion_nueva);
    }
    album=searchMap(Mapa_album,cancion_nueva->album);
    if(album==NULL){
        album=createMap(stringHash, stringEqual);
        insertMap(album,cancion_nueva->titulo,cancion_nueva);
        insertMap(Mapa_album,cancion_nueva->album,album);
    }
    else{
        insertMap(album,cancion_nueva->titulo,cancion_nueva);
    }
}

void eliminar_canciones_artista(char * nombre_artista,Map * mapa_canciones, Map * mapa_artistas, Map * Mapa_album){
    Map* artista=searchMap(mapa_artistas,nombre_artista);
    if(artista==NULL){
        printf("El artista no existe.\n");
        return;
    }
    Cancion* cancion=firstMap(artista);
    Map* album=NULL;
    while(cancion!=NULL){
        eraseKeyMap(mapa_canciones,cancion->titulo);
        album=searchMap(Mapa_album,cancion->album);
        eraseKeyMap(album,cancion->titulo);
        cancion=nextMap(searchMap(mapa_artistas,nombre_artista));
    }
    eraseKeyMap(mapa_artistas,nombre_artista);
}

void buscar_cancion(char * nombre_cancion, Map * mapa_canciones){
    Cancion* cancion_buscada=NULL;
    cancion_buscada=searchMap(mapa_canciones,nombre_cancion);
    printf("Titulo: %s\nArtista: %s\nDuracion: %s\nAlbum: %s",cancion_buscada->titulo, cancion_buscada->artista, cancion_buscada->duracion, cancion_buscada->album);
}

void buscar_canciones_artista(char * nombre_artista, Map * mapa_artistas){
    Map * mapa_canciones_buscadas = searchMap(mapa_artistas,nombre_artista);
    if(mapa_canciones_buscadas==NULL){
        printf("El artista no existe.\n");
        return;
    }
    Cancion* cancion=firstMap(mapa_canciones_buscadas);
    while(cancion!=NULL){
        printf("%s %s %s %s\n", cancion->titulo, cancion->artista, cancion->duracion, cancion->album);
        cancion = nextMap(mapa_canciones_buscadas);
    }
}

void buscar_canciones_album(char * nombre_album, Map * mapa_album){
    Map * mapa_canciones_buscadas = searchMap(mapa_album,nombre_album);
    if(mapa_canciones_buscadas==NULL){
        printf("El album no existe.\n");
        return;
    }
    Cancion* cancion=firstMap(mapa_canciones_buscadas);
    while(cancion!=NULL){
        printf("%s %s %s %s\n", cancion->titulo, cancion->artista, cancion->duracion, cancion->album);
        cancion = nextMap(mapa_canciones_buscadas);
    }
}
