#include <stdio.h>
#include "pila.h"

void inicializarPila(Pila* pila) {
    pila->tope = NULL;
    pila->cantidad = 0;
}

int pilaVacia(Pila* pila) {
    return pila->tope == NULL;
}

void push(Pila *pila, void* dato) {
    Nodo* nuevoNodo = crearNodo(dato);
    nuevoNodo -> sig = pila -> tope;
    pila -> tope = nuevoNodo;
    pila -> cantidad++;
}

void* pop(Pila *pila) {
    Nodo *aux = pila->tope;		
    pila->tope = aux->sig;
    aux->sig = NULL;

    void *dato = aux->dato;
    free(aux);
    pila->cantidad--;
    return dato;
}

void freePila(Pila* pila) {
    Nodo* aux = pila -> tope;
    while (aux != NULL) {
        Nodo* temp = aux;
        aux = aux->sig;
        free(temp->dato);
        free(temp);
        pila->cantidad--;
    }
    pila->tope = NULL;
}
