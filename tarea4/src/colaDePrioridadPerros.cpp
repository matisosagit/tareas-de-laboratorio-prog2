#include "../include/colaDePrioridadPerros.h"

// La cola de prioridad debe implementarse con un HEAP. 

// NOTA IMPORTANTE: Para evitar diferencias con las salidas esperadas de los tests: 
// * El filtrado ascendente debe parar cuando se encuentra un elemento igual o más prioritario que el elemento filtrado. 
// * El filtrado descendente debe parar cuando los hijos del elemento filtrado sean igual o menos prioritarios que el. 
// * Si se dan empates de prioridad entre los hijos durante el filtrado descendente y corresponde continuar filtrando, 
// se debe seguir el filtrado hacia la rama izquierda.

struct Nodo {
    TPerro perro;
    int vitalidad;
};

struct rep_colaDePrioridadPerros {
    Nodo* arrPerros;
    int cantidad;
    int maximo;
    bool* conjuntoPerr;
    int* arrVit;
    bool esMin;
    //la idea es agregar dos conjuntos aca, uno de enteros que almacenen la vitalidad de los perros (y el indice sea el id de cada uno)
    //y otro conjuntoPerros de booleanos para comprobar si existen y asi cumlpir con el tiempo de ejecucion pedido en las funciones.
};

/* El tiempo de ejecución en el peor caso es O(N). */
TColaDePrioridadPerros crearTColaDePrioridadPerros(nat N) {
    TColaDePrioridadPerros nuevaCola = new rep_colaDePrioridadPerros;
    nuevaCola->cantidad = 0;
    nuevaCola->maximo = N;
    nuevaCola->arrPerros = new Nodo[N+1];
    nuevaCola->conjuntoPerr = new bool[N + 1];
    nuevaCola->arrVit = new int[N+1];
    nuevaCola->esMin = true;
    for(nat i = 0; i<=N ; i++){
        nuevaCola->conjuntoPerr[i] = false;
        nuevaCola->arrVit[i] = -1;
        nuevaCola->arrPerros[i].perro = NULL;
        nuevaCola->arrPerros[i].vitalidad = -1;

    }
    return nuevaCola;
}

/* El tiempo de ejecución en el peor caso es O(1). */
bool estaVaciaTColaDePrioridadPerros(TColaDePrioridadPerros cp) {
    return cp->cantidad == 0;
}

/* El tiempo de ejecución en el peor caso es O(log N) siendp 'N' el parámetro pasado en crearCP. */
void insertarTColaDePrioridadPerros(TColaDePrioridadPerros &cp, TPerro perro) {
    if(cp->cantidad < cp->maximo && idTPerro(perro) > 0 && idTPerro(perro) <= cp->maximo ){
        Nodo nuevoNodo;
        nuevoNodo.perro = perro;
        nuevoNodo.vitalidad = vitalidadTPerro(perro);
        cp->cantidad++;
        int contador = cp->cantidad -1;
        
        cp->arrPerros[contador ] = nuevoNodo;
        cp->conjuntoPerr[idTPerro(perro)] = true;
        cp->arrVit[idTPerro(perro)] = nuevoNodo.vitalidad; 

        while(contador > 0){
            int posPadre = (contador -1)/2;
            bool res;
            if(cp->esMin){
                res = (cp->arrPerros[contador].vitalidad < cp->arrPerros[posPadre].vitalidad);
            }else{
                res = (cp->arrPerros[contador].vitalidad > cp->arrPerros[posPadre].vitalidad);
            }
            if(res){
                Nodo aux = cp->arrPerros[contador];
                cp->arrPerros[contador] = cp->arrPerros[posPadre];
                cp->arrPerros[posPadre] = aux;
                contador = posPadre;
            }else {
                break;
            }
        }
    }
}

/* El tiempo de ejecución en el peor caso es O(1). */
bool estaTColaDePrioridadPerros(TColaDePrioridadPerros cp, int id) {
    if((cp->cantidad > 0) && (id>0) && (id<=cp->maximo) && (cp->conjuntoPerr[id] == true)){
        return true;
    }else return false;
}

/* El tiempo de ejecución en el peor caso es O(N), siendo 'N' el parámetro
pasado en crearCP. */
void liberarTColaDePrioridadPerros(TColaDePrioridadPerros &cp) {
    if(cp->cantidad>0){
        for(int i = 0; i<cp->cantidad ; i++){
            if(cp->arrPerros[i].perro != NULL){
                liberarTPerro(cp->arrPerros[i].perro);
            }
        }
    }
    delete[] cp->arrPerros;
    delete[] cp->conjuntoPerr;
    delete[] cp->arrVit;
    delete cp;
    cp = NULL;
}

/* El tiempo de ejecución en el peor caso es O(1). */
nat prioridadTColaDePrioridadPerros(TColaDePrioridadPerros cp, int id) {
    return cp->arrVit[id];
}

/* El tiempo de ejecución en el peor caso es O(1). */
TPerro prioritarioTColaDePrioridadPerros(TColaDePrioridadPerros cp) {
    return cp->arrPerros[0].perro;
}

void ordenarMenor(TColaDePrioridadPerros &cp, int j){
    int padre = j;
    while(true){
        int menor = padre;
        int hijoIzq = 2*padre + 1;
        int hijoDer = 2*padre + 2;
        if(hijoIzq < cp->cantidad){
            if(cp->arrPerros[hijoIzq].vitalidad < cp->arrPerros[menor].vitalidad ||
            (cp->arrPerros[hijoIzq].vitalidad == cp->arrPerros[menor].vitalidad &&
                idTPerro(cp->arrPerros[hijoIzq].perro) < idTPerro(cp->arrPerros[menor].perro))){
                menor = hijoIzq;
            }
        } 
        if(hijoDer < cp->cantidad){
            if(cp->arrPerros[hijoDer].vitalidad < cp->arrPerros[menor].vitalidad ||
            (cp->arrPerros[hijoDer].vitalidad == cp->arrPerros[menor].vitalidad &&
                idTPerro(cp->arrPerros[hijoDer].perro) < idTPerro(cp->arrPerros[menor].perro))){
            menor = hijoDer;
            }
        } 
        if(menor == padre) break;
        Nodo aux = cp->arrPerros[padre];
        cp->arrPerros[padre] = cp->arrPerros[menor];
        cp->arrPerros[menor] = aux;
        padre = menor;
    }
}

void ordenarMayor(TColaDePrioridadPerros &cp, int j){
    int padre = j;
    while(true){
        int mayor = padre;
        int hijoIzq = 2*padre + 1;
        int hijoDer = 2*padre + 2;
        if(hijoIzq < cp->cantidad){
            if(cp->arrPerros[hijoIzq].vitalidad > cp->arrPerros[mayor].vitalidad ||
            (cp->arrPerros[hijoIzq].vitalidad == cp->arrPerros[mayor].vitalidad &&
                idTPerro(cp->arrPerros[hijoIzq].perro) < idTPerro(cp->arrPerros[mayor].perro))){
            mayor = hijoIzq;
            }
        } 
        if(hijoDer < cp->cantidad){
            if(cp->arrPerros[hijoDer].vitalidad > cp->arrPerros[mayor].vitalidad ||
            (cp->arrPerros[hijoDer].vitalidad == cp->arrPerros[mayor].vitalidad &&
                idTPerro(cp->arrPerros[hijoDer].perro) < idTPerro(cp->arrPerros[mayor].perro))){
            mayor = hijoDer;
            }
        } 
        if(mayor == padre) break;
        Nodo aux = cp->arrPerros[padre];
        cp->arrPerros[padre] = cp->arrPerros[mayor];
        cp->arrPerros[mayor] = aux;
        padre = mayor;
    }
}


/* El tiempo de ejecución en el peor caso es O(log N), siendo 'N' el parámetro
pasado en crearCP. */
void eliminarPrioritarioTColaDePrioridadPerros(TColaDePrioridadPerros &cp) {
    if(cp->cantidad > 0){
        cp->conjuntoPerr[idTPerro(cp->arrPerros[0].perro) ] = false;
        cp->arrVit[idTPerro(cp->arrPerros[0].perro) ] = -1;
        liberarTPerro(cp->arrPerros[0].perro);
        
        if(cp->cantidad > 1){
            cp->arrPerros[0] = cp->arrPerros[cp->cantidad - 1];
            cp->arrPerros[cp->cantidad -1].perro = NULL;
            cp->arrPerros[cp->cantidad -1].vitalidad = -1;
        }
        cp->cantidad--;
        
        if(cp->cantidad > 0){
            if(cp->esMin){
                ordenarMenor(cp, 0);
            }else{
                ordenarMayor(cp, 0);
            }
        }

    }
}

/* Se pide que el tiempo de ejecución en el peor caso sea O(n*log n), siendo 'n' la cantidad de
elementos de 'cp'. Sin embargo, existe una solución que lo hace en O(n). */
void invertirPrioridadTColaDePrioridadPerros(TColaDePrioridadPerros &cp) {
    cp->esMin = !cp->esMin;
    if(cp->cantidad > 0){
        for(int i = (cp->cantidad/2) -1; i>=0; i--){
            if(cp->esMin){
                ordenarMenor(cp, i);
            }else{
                ordenarMayor(cp, i);
            }
        }
    }
}
