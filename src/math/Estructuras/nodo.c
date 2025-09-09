#include "nodo.h"

Nodo* crearNodo(void* dato) {
    Nodo *nuevoNodo = calloc(1, sizeof(Nodo));
    nuevoNodo -> dato = dato;

    return nuevoNodo;
}