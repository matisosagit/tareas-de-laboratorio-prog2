#include "../include/pila.h"

struct nodoAux{
    int elemento;
    nodoAux*sig;
};

struct rep_pila{
    nodoAux* pila;
    nat cantidad;
};

/* Debe ejecutar en O(1) peor caso. */
TPila crearTPila(){
    TPila nuevaPila = new rep_pila;
    nuevaPila->pila = NULL;
    nuevaPila->cantidad = 0;
    return nuevaPila;
}

/* Debe ejecutar en O(n) peor caso, donde n es la cantidad de elementos en la pila. */
// Luego de la función, el puntero pila debe apuntar a NULL.
void liberarTPila(TPila &pila){
    while(cantidadTPila(pila) > 0){
        desapilarTPila(pila);
    }
    delete pila;
    pila = NULL;
}

/* Debe ejecutar en O(1) peor caso. */
void apilarTPila(TPila &pila, int elem){
    nodoAux* nueva = new nodoAux;
    nueva->elemento = elem;
    nueva->sig = pila->pila;
    pila->pila = nueva;
    pila->cantidad++;
}

/* Debe ejecutar en O(n) peor caso, donde n es la cantidad de elementos en la pila */
void imprimirTPila(TPila pila){
    if(pila != NULL){
        TPila pilaAux = crearTPila();
        nodoAux* actual = pila->pila;
        while(actual != NULL){
            apilarTPila(pilaAux, actual->elemento);
            actual = actual->sig;
        }
        printf("Pila:");
        while(cantidadTPila(pilaAux)>0){
            printf(" %d",cimaTPila(pilaAux));
            desapilarTPila(pilaAux);
        }
        liberarTPila(pilaAux);
        printf("\n");
    }
} 

/* Debe ejecutar en O(1) peor caso. */
nat cantidadTPila(TPila pila){
    return pila->cantidad;
}

/* Debe ejecutar en O(1) peor caso. */
int cimaTPila(TPila pila) {
    return pila->pila->elemento;
}

/* Debe ejecutar en O(1) peor caso. */
void desapilarTPila(TPila &pila){
    nodoAux* aBorrar = pila->pila;
    pila->pila  = pila->pila->sig;
    delete aBorrar;
    pila->cantidad--;
}







 
 