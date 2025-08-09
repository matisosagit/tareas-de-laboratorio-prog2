#include "../include/tablaFichaVacunacion.h"

// Se debe implementar mediante una tabla de dispersión abierta (hash)

struct nodoAux{
    int id;
    TAGFichaVacunacion ficha;
};

struct nodoFicha{
    nodoAux* datos;
    nodoFicha * sig;
};

struct rep_tablaFichaVacunacion {
    nodoFicha** tabla;
    int cantidad;
    int max;
};


/* La función es O(cantEstimada) peor caso. */
TTablaFichaVacunacion crearTTablaFichaVacunacion(int cantEstimada){
    TTablaFichaVacunacion nueva = new rep_tablaFichaVacunacion;
    nueva->cantidad = 0;
    nueva->max = cantEstimada;
    nueva->tabla = new nodoFicha* [cantEstimada];
    for(int i = 0; i < cantEstimada; i++){
        nueva->tabla[i] = NULL;
    }
    return nueva;
}

int hash(TTablaFichaVacunacion t, int id){
    return (id % t->max);
}

/* La función es O(n + max) peor caso, donde n es la cantidad actual de fichas en la tabla 
y max la cantidad esperada de fichas en la tabla. */
void liberarTTablaFichaVacunacion(TTablaFichaVacunacion &tabla){
    if (tabla != NULL){
        int contador = 0;
        while(contador < tabla->max){
            nodoFicha*aux = tabla->tabla[contador];
            while(aux != NULL){
                nodoFicha* siguiente = aux->sig;
                liberarTAGFichaVacunacion(aux->datos->ficha);
                delete aux->datos;
                delete aux;
                aux = siguiente;
            }
            contador++;
        }
        delete[] tabla->tabla;
        delete tabla;
        tabla = NULL;
    }
}

// Para calcular la posición en la que se debe insertar la asociación en
// la tabla de dispersión abierta se debe utilizar la función de dispersión dada por 
// idPerro % tamanio (tamanio es la cantidad estimada de los elementos de la tabla).
// Por convención se deberá insertar la asociación al comienzo de la lista asociada a esa posición.
/* La función es O(1) peor caso. */
void insertarTTablaFichaVacunacion(TTablaFichaVacunacion &tabla, int idPerro, TAGFichaVacunacion ficha){
    int posicion = hash(tabla, idPerro);
    nodoFicha* nuevoNodo = new nodoFicha;
    nuevoNodo->datos = new nodoAux;
    nuevoNodo->datos->id = idPerro;
    nuevoNodo->datos->ficha = ficha;
    nuevoNodo->sig = tabla->tabla[posicion];
    tabla->tabla[posicion] = nuevoNodo;
    tabla->cantidad++;
}

// Imprime cada ficha de vacunación de la tabla (idPerro, ficha), en orden creciente de 
// posiciones asociadas en la tabla, en líneas sucesivas (utilizando la función 'imprimirTAGFichaVacunacion')
// En caso de que haya más de una ficha en la misma posición, se deben imprimir por orden
// de ingreso a la tabla, desde la más reciente a la menos.
// La función es O(n + max) peor caso, donde n es la cantidad de fichas en la tabla 
// y max la cantidad esperada de fichas en la tabla.
void imprimirTTablaFichaVacunacion(TTablaFichaVacunacion tabla){
    if (tabla != NULL){
        int contador = 0;
        while(contador < tabla->max){
            nodoFicha*aux = tabla->tabla[contador];
            while( aux!= NULL){
                printf("Perro ID: %d\n", aux->datos->id);              
                imprimirTAGFichaVacunacion(aux->datos->ficha);
                aux = aux->sig;
            }
            contador++;
        }
    }
}

/* La función es O(1) promedio. */
bool perteneceTTablaFichaVacunacion(TTablaFichaVacunacion tabla, int idPerro){
    bool res1 = false;
    if(tabla != NULL){
        int contador = hash(tabla, idPerro);
        nodoFicha*aux1 = tabla->tabla[contador];
        while( aux1!= NULL && res1==false){
            if(aux1->datos->id == idPerro){
                return true;
            }else{
                aux1 = aux1->sig;
            }
        }
    }
    return res1;
}

/* La función es O(1) promedio. */
TAGFichaVacunacion obtenerFichaTTablaFichaVacunacion(TTablaFichaVacunacion tabla, int idPerro){
    int posicion = hash(tabla, idPerro);
    nodoFicha* aux = tabla->tabla[posicion];
    while( aux != NULL ){
        if(aux->datos->id == idPerro){
            return aux->datos->ficha;
        }
        aux = aux->sig;
    }
    return NULL;
}

/* La función es O(1) promedio. */
void eliminarDeTTablaFichaVacunacion(TTablaFichaVacunacion &tabla, int idPerro){
    int posicion2 = hash(tabla, idPerro);
    nodoFicha* aux2 = tabla->tabla[posicion2];
    nodoFicha* ant = NULL;
    while(aux2!= NULL && idPerro != aux2->datos->id){
        ant = aux2;
        aux2 = aux2->sig;
    }
    if(aux2!=NULL){
        if(ant == NULL){
            tabla->tabla[posicion2] = aux2->sig;
        }else{
            ant->sig = aux2->sig;
        }
        liberarTAGFichaVacunacion(aux2->datos->ficha);
        delete aux2->datos;
        delete aux2;
        tabla->cantidad--;
    }
}




