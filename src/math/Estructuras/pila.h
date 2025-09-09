#include "nodo.h"
#include <stdlib.h>

typedef struct {
    Nodo *tope;
    int cantidad;
}Pila;

void inicializarPila(Pila* pila);
int pilaVacia(Pila* pila);
void push(Pila *pila, void* dato);
void* pop(Pila *pila);
void freePila(Pila* pila);