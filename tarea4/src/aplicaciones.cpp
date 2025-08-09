#include "../include/aplicaciones.h"

bool mismosElementos(TPila p, TColaPerros c) {
    bool res = true;
    if(cantidadTPila(p) != cantidadTColaPerros(c)){
        for(nat i = 0; i< cantidadTPila(p); i++){
            desapilarTPila(p);
        }
        for(nat j = 0; j < cantidadTColaPerros(c); j++){
            desencolarTColaPerros(c);
        }
        return false;
    }
    TPila pilaAux = crearTPila();
    while(cantidadTPila(p) > 0){
        apilarTPila(pilaAux, cimaTPila(p));
        desapilarTPila(p);
    }
    while(cantidadTPila(pilaAux)>0 && cantidadTColaPerros(c)>0){
        if(cimaTPila(pilaAux) != idTPerro(frenteTColaPerros(c))){
            res = false;
        }
        desapilarTPila(pilaAux);
        desencolarTColaPerros(c);
    }
    liberarTPila(pilaAux);
    return res;
}

TPila menoresQueElResto(TLDEPerros lista) {
    TPila res = crearTPila();
    while(cantidadTLDEPerros(lista)>0){
        bool esMenor = true;
        TPerro perro = removerPrimeroTLDEPerros(lista);
        nat vitalidad = vitalidadTPerro(perro);
        int n = vitalidad;
        nat cont = 1;
        while((cont <= cantidadTLDEPerros(lista)) && esMenor){
            if(vitalidad < vitalidadTPerro(obtenerNesimoTLDEPerros(lista, cont))){
                cont+=1;
            }else esMenor = false;
        }
        if(esMenor && cont > cantidadTLDEPerros(lista)){
            apilarTPila(res, n);
        }
        liberarTPerro(perro);
    }
    return res;
}
 
bool sumaPares(nat k, TConjuntoPerros c) {
    for(int i=0; i < cantMaxTConjuntoPerros(c); i++){
        for(int j = i; j < cantMaxTConjuntoPerros(c); j++){
            nat suma = i + j;
            if(perteneceTConjuntoPerros(c,i) && perteneceTConjuntoPerros(c,j) && (suma == k)){
                return true;
            }
        }
    }
    return false;
}