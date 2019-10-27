#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Map.h"
#include "mainmap.h"

long long stringHash(const void * key)
{
    long long hash = 5381;
    const char * ptr;

    for (ptr = key; *ptr != '\0'; ptr++)
    {
        hash = ((hash << 5) + hash) + tolower(*ptr); /* hash * 33 + c */
    }

    return hash;
}

int stringEqual(const void * key1, const void * key2)
{
    const char * A = key1;
    const char * B = key2;

    return strcmp(A, B) == 0;
}
