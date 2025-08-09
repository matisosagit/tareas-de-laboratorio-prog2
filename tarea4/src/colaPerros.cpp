#include "../include/colaPerros.h"

struct nodoCola{
    TPerro perro;
    nodoCola* sig;
};

struct rep_colaPerros {
    nodoCola* cola;
    nat cantidad;
};

/* Debe ejecutar en O(1) peor caso. */
TColaPerros crearTColaPerros(){
    TColaPerros nuevaCola = new rep_colaPerros;
    nuevaCola->cola = NULL;
    nuevaCola->cantidad = 0;
    return nuevaCola;
}

/* Debe ejecutar en O(n) peor caso, donde n es la cantidad de perros 
en la cola.*/
// Debe liberar toda la memoria asociada a la cola, incluidos sus perros.
// Luego de la función, el puntero colaPerros debe apuntar a NULL.
void liberarTColaPerros(TColaPerros &colaPerros){
    while(cantidadTColaPerros(colaPerros) > 0){
        desencolarTColaPerros(colaPerros);
    }
    delete colaPerros;
    colaPerros = NULL;
}

/* Debe ejecutar en O(1) peor caso. */
// El resultado comparte memoria con el perro pasado por parámetro. 
void encolarTColaPerros(TColaPerros &colaPerros, TPerro perro){
    nodoCola* nuevaCola = new nodoCola;
    nuevaCola->perro = perro;
    nuevaCola->sig = NULL;
    if(cantidadTColaPerros(colaPerros)>0){
        nodoCola* aux = colaPerros->cola;
        while(aux->sig != NULL){
            aux = aux->sig;
        }
        aux->sig = nuevaCola;
    }else{
        colaPerros->cola = nuevaCola;
    }
    colaPerros->cantidad ++;
}

/* Debe ejecutar en O(n) peor caso, donde n es el número de perros en la cola */
void imprimirTColaPerros(TColaPerros colaPerros){
    printf("Cola de Perros:\n");
    nodoCola* aux = colaPerros->cola;
    while(aux != NULL){
        imprimirTPerro(aux->perro);
        aux = aux->sig;
    }
}

/* Debe ejecutar en O(1) peor caso. */
nat cantidadTColaPerros(TColaPerros colaPerros){
    return colaPerros->cantidad;
}

/* Debe ejecutar en O(1) peor caso. */
TPerro frenteTColaPerros(TColaPerros colaPerros) {
    return colaPerros->cola->perro;
}

/* Debe ejecutar en O(1) peor caso. */
void desencolarTColaPerros(TColaPerros &colaPerros) {
    if(cantidadTColaPerros(colaPerros) > 0){
        nodoCola*aux = colaPerros->cola;
        colaPerros->cola = colaPerros->cola->sig;
        liberarTPerro(aux->perro);
        delete aux;
        colaPerros->cantidad--;
    }
}