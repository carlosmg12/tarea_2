#ifndef funciones_h
#define funciones_h

#include "Map.h"

typedef struct Cancion Cancion;

void mostrar();

char * _strdup (const char *s);

const char *get_csv_field (char * tmp, int i);

long long stringHash(const void * key);

int stringEqual(const void * key1, const void * key2);

Cancion * crearCancion(char* linea);

void cargar_datos_csv(char* archivo, Map * mapa_canciones , Map * mapa_artistas, Map * Mapa_album);

void exportar_musica(char* archivo, Map* mapa_canciones);

void agregar_album(char* album,Map* Mapa_album);

void agregar_cancion_album(char *linea, Map * mapa_canciones , Map * mapa_artistas, Map* Mapa_album);

void agregar_cancion(char *linea, Map * mapa_canciones , Map * mapa_artistas, Map* Mapa_album);

void eliminar_canciones_artista(char * nombre_artista,Map * mapa_canciones, Map * mapa_artistas, Map * Mapa_album);

void buscar_cancion(char * nombre_cancion, Map * mapa_canciones);

void buscar_canciones_artista(char * nombre_artista, Map * mapa_artistas);

void buscar_canciones_album(char * nombre_album, Map * mapa_album);

#endif // funciones_h

