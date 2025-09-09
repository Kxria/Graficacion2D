#ifndef NODO_H
#define NODO_H

#include <stdlib.h>

typedef struct Nodo{
    void *dato;
    struct Nodo *sig;
}Nodo;

Nodo* crearNodo(void* dato);  

#endif