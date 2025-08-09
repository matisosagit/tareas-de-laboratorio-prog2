#include "../include/ldePerros.h"


struct rep_nodoPLDE {
    TPerro perro;
    rep_nodoPLDE * sig, * ant;
};

typedef rep_nodoPLDE *TNODOPerros;

struct rep_tldeperros {
    nat cantidad;
    TNODOPerros inicio, fin;
};



/* ********** FUNCIONES NUEVAS TAREA 3 ********** */ 

TPerro removerPrimeroTLDEPerros(TLDEPerros &ldePerros){
    if(ldePerros != NULL &&  ldePerros->inicio != NULL){
        TPerro res = copiarTPerro(ldePerros->inicio->perro);
        TNODOPerros aux = ldePerros->inicio;
        aux->ant = NULL;
        ldePerros->inicio = aux->sig;
        liberarTPerro(aux->perro);
        ldePerros->cantidad--;
        if(ldePerros->cantidad == 0){
            ldePerros->inicio = ldePerros->fin = NULL;
        }
        delete aux;
        return res;
    }else return NULL;
}

TPerro removerUltimoTLDEPerros(TLDEPerros &ldePerros) {
    if(ldePerros != NULL && ldePerros->fin != NULL){
        TPerro res = copiarTPerro(ldePerros->fin->perro);
        TNODOPerros aux = ldePerros->fin;
        aux->sig = NULL;
        ldePerros->fin = aux->ant;
        liberarTPerro(aux->perro);
        ldePerros->cantidad--;
        if(ldePerros->cantidad == 0){
            ldePerros->inicio = ldePerros->fin = NULL;
        }
        delete aux;
        return res;
    }else return NULL;
}

/* ********** FUNCIONES TAREA 2 ********** */ 

TLDEPerros crearTLDEPerrosVacia(){
    TLDEPerros nueva_lista = new rep_tldeperros;
    nueva_lista->cantidad = 0;
    nueva_lista->inicio = nueva_lista->fin = NULL;
    return nueva_lista;
}

void insertarTLDEPerros(TLDEPerros &ldePerros, TPerro perro){
    TNODOPerros nuevo_nodo = new rep_nodoPLDE;
    nuevo_nodo->perro = perro;
    nuevo_nodo->sig = NULL;
    nuevo_nodo->ant = NULL;
    TNODOPerros busqueda = ldePerros->inicio;
    if(busqueda == NULL){
        ldePerros->inicio = nuevo_nodo;
        ldePerros->fin = nuevo_nodo;
    }else {
        while(busqueda->sig !=NULL && edadTPerro(perro) > edadTPerro(busqueda->perro)){
            busqueda = busqueda->sig;
        }
        if(busqueda->sig == NULL && edadTPerro(perro) > edadTPerro(busqueda->perro)){
            busqueda->sig = nuevo_nodo;
            nuevo_nodo->ant = busqueda;
            ldePerros->fin = nuevo_nodo;
        }else if(busqueda->ant == NULL){
            nuevo_nodo->sig = busqueda;
            busqueda->ant = nuevo_nodo;
            ldePerros->inicio = nuevo_nodo;
        } else{
            nuevo_nodo->sig = busqueda;
            nuevo_nodo->ant = busqueda->ant;
            busqueda->ant->sig = nuevo_nodo;
            busqueda->ant = nuevo_nodo;
        }
    }
    ldePerros->cantidad++;
}

void liberarTLDEPerros(TLDEPerros &ldePerros){
    while(ldePerros->inicio != NULL){
        TNODOPerros copia = ldePerros->inicio;
        ldePerros->inicio = copia->sig;
        liberarTPerro(copia->perro);
        delete copia;
        copia =  NULL;
    }
    delete ldePerros;
    ldePerros = NULL;
}

void imprimirTLDEPerros(TLDEPerros ldePerros){
    TNODOPerros copia = ldePerros->inicio;
    printf("LDE Perros:\n");
    while(copia != NULL){
        imprimirTPerro(copia->perro);
        copia = copia->sig;
    }
}

void imprimirInvertidoTLDEPerros(TLDEPerros ldePerros){
    TNODOPerros copia = ldePerros->fin;
    printf("LDE Perros:\n");
    while(copia != NULL){
        imprimirTPerro(copia->perro);
        copia = copia->ant;
    }
}

nat cantidadTLDEPerros(TLDEPerros ldePerros){
    return ldePerros->cantidad;
}

TPerro removerPerroTLDEPerros(TLDEPerros &ldePerros, int id){
    TNODOPerros busqueda = ldePerros->inicio;
    while(busqueda != NULL && id != idTPerro(busqueda->perro)){
        busqueda = busqueda->sig;
    }
    if(busqueda == NULL) return NULL;
    TPerro  res = copiarTPerro(busqueda->perro);
    if(busqueda->ant == NULL){
        ldePerros->inicio = busqueda->sig;
        liberarTPerro(busqueda->perro);
        delete busqueda;
        ldePerros->cantidad--;
        if(ldePerros->cantidad == 0){
            ldePerros->fin = NULL;
        }else{
            ldePerros->inicio->ant = NULL;
        }
    }else if(busqueda->sig == NULL){
        ldePerros->fin = busqueda->ant;
        liberarTPerro(busqueda->perro);
        delete busqueda;
        ldePerros->cantidad--;
        if(ldePerros->cantidad == 0){
            ldePerros->inicio = NULL;
        }else{
            ldePerros->fin->sig = NULL;
        }
    }else{
        busqueda->ant->sig = busqueda->sig;
        busqueda->sig->ant = busqueda->ant;
        liberarTPerro(busqueda->perro);
        delete busqueda;
        ldePerros->cantidad--;
    }
    return res;

}

TPerro obtenerPrimeroTLDEPerros(TLDEPerros ldePerros){
    return ldePerros->inicio->perro;
}

TPerro obtenerUltimoTLDEPerros(TLDEPerros ldePerros){
    return ldePerros->fin->perro;
}

TPerro obtenerNesimoTLDEPerros(TLDEPerros ldePerros, int n){
    nat h = n;
    if(h <1 || h > ldePerros->cantidad) return NULL;
    int contador = 1;
    TNODOPerros copia = ldePerros->inicio;
    while(copia != NULL &&  contador <= n){
        copia = copia->sig;
        contador++;
    }
    return copia->perro;
}

bool existePerroTLDEPerros(TLDEPerros ldePerros, int id){
    TNODOPerros copia = ldePerros->inicio;
    while(copia != NULL && id != idTPerro(copia->perro)){
        copia = copia->sig;
    }
    return copia != NULL;
}
