
#include "../include/abbPersonas.h"

struct rep_abbPersonas {
    TPersona persona;
    TABBPersonas izq, der;
};

TABBPersonas crearTABBPersonasVacio(){
    return NULL;
}

void insertarTPersonaTABBPersonas(TABBPersonas &abbPersonas, TPersona persona){
    if(abbPersonas == NULL){
        abbPersonas = new rep_abbPersonas;
        abbPersonas->persona = persona;
        abbPersonas->izq = NULL;
        abbPersonas->der = NULL;
    }else{
        if(ciTPersona(persona) < ciTPersona(abbPersonas->persona)){
            insertarTPersonaTABBPersonas(abbPersonas->izq, persona);
        }else{
            insertarTPersonaTABBPersonas(abbPersonas->der, persona);
        }
    }
}

void imprimirTABBPersonas(TABBPersonas abbPersonas){
    if(abbPersonas != NULL){
        imprimirTABBPersonas(abbPersonas->izq);
        imprimirTPersona(abbPersonas->persona);
        imprimirTABBPersonas(abbPersonas->der);
    }
}


//primero tengo que hacer una funcion auxiliar para liberar solo un nodo y luego usarla en liberarTABBPersonas.
void liberarNodoPersona(TABBPersonas &abbPersonas){
    liberarTPersona(abbPersonas->persona);
    delete abbPersonas;
    abbPersonas = NULL;
}


void liberarTABBPersonas(TABBPersonas &abbPersonas){
    if(abbPersonas != NULL){
        liberarTABBPersonas(abbPersonas->izq);
        liberarTABBPersonas(abbPersonas->der);
        liberarNodoPersona(abbPersonas);
    }
}

bool existeTPersonaTABBPersonas(TABBPersonas abbPersonas, int ciPersona){
    if(abbPersonas != NULL && ciTPersona(abbPersonas->persona) == ciPersona){
        return true;
    }else{
        if(abbPersonas != NULL && ciPersona < ciTPersona(abbPersonas->persona)){
            return existeTPersonaTABBPersonas(abbPersonas->izq, ciPersona);
        }else if(abbPersonas != NULL){
            return existeTPersonaTABBPersonas(abbPersonas->der, ciPersona);
        }else return false;
    }
}

TPersona obtenerTPersonaTABBPersonas(TABBPersonas abbPersonas, int ciPersona){
    if(ciTPersona(abbPersonas->persona) == ciPersona){
        return abbPersonas->persona;
    }else{
        if(ciPersona < ciTPersona(abbPersonas->persona)){
            return obtenerTPersonaTABBPersonas(abbPersonas->izq, ciPersona);
        }else{
            return obtenerTPersonaTABBPersonas(abbPersonas->der, ciPersona);
        }
    }
}

nat alturaTABBPersonas(TABBPersonas abbPersonas){
    if(abbPersonas == NULL){
        return 0;
    }else{
        nat altura_izq = 1 + alturaTABBPersonas(abbPersonas->izq);
        nat altura_der = 1 + alturaTABBPersonas(abbPersonas->der);
        if(altura_izq > altura_der){
            return  altura_izq;
        }else return altura_der;
    }
}

TPersona maxCITPersonaTABBPersonas(TABBPersonas abbPersonas){
    if(abbPersonas->der == NULL){
        return abbPersonas->persona;
    }else{
        return(maxCITPersonaTABBPersonas(abbPersonas->der));
    }
}

void removerTPersonaTABBPersonas(TABBPersonas &abbPersonas, int ciPersona){
    if(ciTPersona(abbPersonas->persona) == ciPersona){
        if(abbPersonas->izq == NULL && abbPersonas->der == NULL){
            liberarNodoPersona(abbPersonas);
        }else{
            if(abbPersonas->izq == NULL){
                TABBPersonas copia = abbPersonas;
                abbPersonas = abbPersonas->der;
                liberarNodoPersona(copia);
            }else {
                if(abbPersonas->der == NULL){
                    TABBPersonas copia = abbPersonas;
                    abbPersonas = abbPersonas->izq;
                    liberarNodoPersona(copia);
                }else{
                    liberarTPersona(abbPersonas->persona);
                    abbPersonas->persona = copiarTPersona(maxCITPersonaTABBPersonas(abbPersonas->izq));
                    removerTPersonaTABBPersonas(abbPersonas->izq, ciTPersona(abbPersonas->persona));
                }
            }
        }
    }else{
        if(ciPersona > ciTPersona(abbPersonas->persona)){
            removerTPersonaTABBPersonas(abbPersonas->der, ciPersona);
        }else{
            removerTPersonaTABBPersonas(abbPersonas->izq, ciPersona);
        }
        }
}

int cantidadTABBPersonas(TABBPersonas abbPersonas){
    if(abbPersonas == NULL){
        return 0;
    } else{
        return (1 + cantidadTABBPersonas(abbPersonas->izq) + cantidadTABBPersonas(abbPersonas->der));
    }
}


TPersona obtenerNesimaPersonaTABBPersonas(TABBPersonas abbPersonas, int n){
    int nodos_izq = cantidadTABBPersonas(abbPersonas->izq);
    if(n == nodos_izq +1){
        return abbPersonas->persona;
    }else if(n < nodos_izq + 1){
        return (obtenerNesimaPersonaTABBPersonas(abbPersonas->izq, n));
    }else {
        return(obtenerNesimaPersonaTABBPersonas(abbPersonas->der, n - nodos_izq - 1));
    }
}

TABBPersonas filtradoPorFechaDeNacimientoTABBPersonas(TABBPersonas abbPersonas, TFecha fecha, int criterio){
    if(abbPersonas == NULL){
        return NULL;
    }else{
        TABBPersonas arbol_izquierdo = filtradoPorFechaDeNacimientoTABBPersonas(abbPersonas->izq, fecha, criterio);
        TABBPersonas arbol_derecho = filtradoPorFechaDeNacimientoTABBPersonas(abbPersonas->der, fecha, criterio);
        int comparacion = compararTFechas(fechaNacimientoTPersona(abbPersonas->persona), fecha);
        if((comparacion < 0 && criterio < 0)
            || (comparacion == 0 && criterio == 0)
            || (comparacion > 0 && criterio > 0))
        {
            TABBPersonas nuevo_arbol = new rep_abbPersonas;
            nuevo_arbol->persona = copiarTPersona(abbPersonas->persona);
            nuevo_arbol->izq = arbol_izquierdo;
            nuevo_arbol->der = arbol_derecho;
            return nuevo_arbol;
        }else if(arbol_izquierdo == NULL){
            return arbol_derecho;
        }else if(arbol_derecho == NULL){
            return arbol_izquierdo;
        }else{
            TABBPersonas nuevo_arbol2 = new rep_abbPersonas;
            nuevo_arbol2->der = arbol_derecho;
            nuevo_arbol2->persona = copiarTPersona(maxCITPersonaTABBPersonas(arbol_izquierdo));
            removerTPersonaTABBPersonas(arbol_izquierdo, ciTPersona(nuevo_arbol2->persona));
            nuevo_arbol2->izq = arbol_izquierdo;
            return nuevo_arbol2;
        }
    }
}