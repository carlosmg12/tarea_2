Cancion * crearCancion(char* linea){
    Cancion* dato=malloc(sizeof(Cancion));
    dato->titulo=malloc(sizeof(char));
    dato->artista=malloc(sizeof(char));
    dato->duracion=malloc(sizeof(char));
    dato->album=malloc(sizeof(char));
    const char* titulo=get_csv_field (linea,1);
    const char* artista=get_csv_field (linea,2);
    const char* duracion=get_csv_field (linea,3);
    const char* album=get_csv_field (linea,4);
    strcpy(dato->titulo,titulo);
    strcpy(dato->artista,artista);
    strcpy(dato->duracion,duracion);
    strcpy(dato->album,album);
    return dato;
}

void cargar_datos_csv(FILE * fp, Map * mapa_canciones , Map * mapa_artistas, Map * Mapa_album){
    char linea[1024];
    char* ptr;
    Cancion* cancion_nueva=NULL;
    Cancion* cancion=NULL;
    Map* artista=NULL;
    Map* album=NULL;
    while(fgets(linea,1023,fp)!=NULL){
        ptr = strtok(linea,"\r");
        ptr = _strdup(ptr);
        cancion_nueva=crearCancion(ptr);
        cancion=searchMap(mapa_canciones,cancion_nueva->titulo);
        if(cancion==NULL){
            insertMap(mapa_canciones,cancion_nueva->titulo,cancion_nueva);
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
}

void eliminar_canciones_artista(char * nombre_artista,Map * mapa_canciones, Map * mapa_artistas, Map * Mapa_album){
    Cancion* cancion=firstMap(searchMap(mapa_artistas,nombre_artista));
    Map* album=NULL;
    while(cancion!=NULL){eraseKeyMap(mapa_canciones,cancion->titulo);
        album=searchMap(Mapa_album,cancion->album);
        eraseKeyMap(album,cancion->titulo);
        cancion=nextMap(searchMap(mapa_artistas,nombre_artista));
    }eraseKeyMap(mapa_artistas,nombre_artista);
}
