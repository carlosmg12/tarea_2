#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funciones.h"
#include "Map.h"
#include "lectura.h"
#define LINEA 1024

struct Cancion
{
    char* titulo;
    char* artista;
    char* duracion;
    char* album;
    char* fecha;
};

/*Funcion que muestra las opciones del menu*/

void mostrar()
{
    printf("\n(1)-Importar musica desde un archivo CSV.\n");
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

/*Funcion que crea un dato de tipo cancion*/

Cancion * crearCancion(char* linea)
{
    Cancion* dato=calloc(1,sizeof(Cancion));
    dato->titulo=calloc(100,sizeof(char));
    dato->artista=calloc(100,sizeof(char));
    dato->duracion=calloc(100,sizeof(char));
    dato->album=calloc(100,sizeof(char));
    dato->fecha=calloc(100,sizeof(char));
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

/*Funcion que carga los datos desde un archivo tipo .csv*/

void cargar_datos_csv(char* archivo, Map * mapa_canciones , Map * mapa_artistas, Map * Mapa_album)
{
    FILE* fp=fopen(archivo,"r");
    char linea[LINEA];
    char* ptr;
    Cancion* cancion_nueva=NULL;
    Cancion* cancion=NULL;
    Map* artista=NULL;
    Map* album=NULL;
    fgets(linea,1023,fp);

    while(fgets(linea,1023,fp)!=NULL)
        {
        ptr = strtok(linea,"\r");
        ptr = _strdup(ptr);
        cancion_nueva=crearCancion(ptr);
        cancion=searchMap(mapa_canciones,cancion_nueva->titulo);

        if(cancion==NULL)
        {
            insertMap(mapa_canciones,cancion_nueva->titulo,cancion_nueva);
        }
        artista=searchMap(mapa_artistas,cancion_nueva->artista);

        if(artista==NULL)
        {
            artista=createMap(stringHash, stringEqual);
            insertMap(artista,cancion_nueva->titulo,cancion_nueva);
            insertMap(mapa_artistas,cancion_nueva->artista,artista);
        }

        else
        {
            insertMap(artista,cancion_nueva->titulo,cancion_nueva);
        }

        album=searchMap(Mapa_album,cancion_nueva->album);

        if(album==NULL)
        {
            album=createMap(stringHash, stringEqual);
            insertMap(album,cancion_nueva->titulo,cancion_nueva);
            insertMap(Mapa_album,cancion_nueva->album,album);
        }

        else
        {
            insertMap(album,cancion_nueva->titulo,cancion_nueva);
        }

    }
    fclose(fp);
}

/*Funcion que exporta los datos hacia un archivo*/

void exportar_musica(char* archivo, Map* mapa_canciones)
{
    FILE* fp=fopen(archivo,"a");
    Cancion* cancion=firstMap(mapa_canciones);

    while(cancion!=NULL)
    {
        fputs(cancion->titulo,fp);
        fputc(',',fp);
        fputs(cancion->artista,fp);
        fputc(',',fp);
        fputs(cancion->duracion,fp);
        fputc(',',fp);
        fputs(cancion->album,fp);
        fputc(',',fp);
        fputs(cancion->fecha,fp);
        fputc('\n',fp);
        cancion=nextMap(mapa_canciones);
    }
    fclose(fp);
}

/*Agrega un nuevo album al mapa de albumes en caso de que este no exista previamente*/

void agregar_album(char* nombre_album,Map* Mapa_album)
{
    if(searchMap(Mapa_album,nombre_album)!=NULL)
    {
        printf("El album ya existe\n");
        return;
    }

    Map* nuevo_album=createMap(stringHash, stringEqual);
    insertMap(Mapa_album,nombre_album,nuevo_album);
}

/*Agrega una nueva cancion a la base de datos*/

void agregar_cancion(char *linea, Map * mapa_canciones , Map * mapa_artistas,  Map* Mapa_album)
{
    char* ptr;
    Cancion* cancion_nueva=NULL;
    Cancion* cancion=NULL;
    Map* artista=NULL;
    Map* album=NULL;
    ptr = strtok(linea,"\r");
    ptr = _strdup(ptr);
    cancion_nueva=crearCancion(ptr);
    cancion=searchMap(mapa_canciones,cancion_nueva->titulo);

    if(cancion==NULL)
    {
        insertMap(mapa_canciones,cancion_nueva->titulo,cancion_nueva);
    }

    else
    {
        return;
    }

    artista=searchMap(mapa_artistas,cancion_nueva->artista);

    if(artista==NULL)
    {
        artista=createMap(stringHash, stringEqual);
        insertMap(artista,cancion_nueva->titulo,cancion_nueva);
        insertMap(mapa_artistas,cancion_nueva->artista,artista);
    }

    else
    {
        insertMap(artista,cancion_nueva->titulo,cancion_nueva);
    }

    album=searchMap(Mapa_album,cancion_nueva->album);

    if(album==NULL)
    {
        album=createMap(stringHash, stringEqual);
        insertMap(album,cancion_nueva->titulo,cancion_nueva);
        insertMap(Mapa_album,cancion_nueva->album,album);
    }

    else
    {
        insertMap(album,cancion_nueva->titulo,cancion_nueva);
    }
}

/*Elimina todas las canciones de un artista indicado incluyendo sus albumes, luego elimina al artista*/

void eliminar_canciones_artista(char * nombre_artista,Map * mapa_canciones, Map * mapa_artistas, Map * Mapa_album)
{
    Map* artista=searchMap(mapa_artistas,nombre_artista);

    if(artista==NULL)
    {
        printf("El artista no existe.\n");
        return;
    }

    Cancion* cancion=firstMap(artista);
    Map* album=NULL;

    while(cancion!=NULL)
    {
        eraseKeyMap(mapa_canciones,cancion->titulo);
        album=searchMap(Mapa_album,cancion->album);
        eraseKeyMap(album,cancion->titulo);
        cancion=nextMap(searchMap(mapa_artistas,nombre_artista));
    }

    eraseKeyMap(mapa_artistas,nombre_artista);
}

/*Busca una cancion por su titulo y muestra su informacion*/

void buscar_cancion(char * nombre_cancion, Map * mapa_canciones)
{
    Cancion* cancion_buscada=searchMap(mapa_canciones,nombre_cancion);

    if(cancion_buscada==NULL)
    {
        printf("Cancion no encontrada\n");
        return;
    }

    printf("\n");
    printf("Titulo: %s\nArtista: %s\nDuracion: %s\nAlbum: %s\nFecha: %s\n",
    cancion_buscada->titulo, cancion_buscada->artista, cancion_buscada->duracion, cancion_buscada->album,cancion_buscada->fecha);
}

/*Busca todas las canciones de un artista y muestra la informacion de cada una de ellas*/

void buscar_canciones_artista(char * nombre_artista, Map * mapa_artistas)
{
    Map * mapa_canciones_buscadas = searchMap(mapa_artistas,nombre_artista);

    if(mapa_canciones_buscadas==NULL)
    {
        printf("El artista no existe.\n");
        return;
    }

    Cancion* cancion_buscada=firstMap(mapa_canciones_buscadas);

    while(cancion_buscada!=NULL)
    {
        printf("\nTitulo: %s\nDuracion: %s\nAlbum: %s\nFecha: %s\n",
        cancion_buscada->titulo, cancion_buscada->duracion, cancion_buscada->album,cancion_buscada->fecha);
        cancion_buscada = nextMap(mapa_canciones_buscadas);
    }
}

/*Busca las canciones de un album y muestra la informacion de todas las canciones presentes en este*/

void buscar_canciones_album(char * nombre_album, Map * mapa_album)
{
    Map * mapa_canciones_buscadas = searchMap(mapa_album,nombre_album);

    if(mapa_canciones_buscadas==NULL)
    {
        printf("El album no existe.\n");
        return;
    }

    Cancion* cancion_buscada=firstMap(mapa_canciones_buscadas);
    printf("\n");

    if(cancion_buscada==NULL)
    {
        printf("El album no contiene canciones\n");
    }

    while(cancion_buscada!=NULL)
    {
        printf("Titulo: %s\nArtista: %s\nDuracion: %s\nFecha: %s\n",
        cancion_buscada->titulo, cancion_buscada->artista, cancion_buscada->duracion,cancion_buscada->fecha);
        cancion_buscada = nextMap(mapa_canciones_buscadas);
    }
}
