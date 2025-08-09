#include "../include/refugio.h"

struct rep_refugio {
    /************ Parte 5.1 ************/
    /*Escriba el código a continuación */
    TPerro refugioPerros[MAX_PERROS];
    int tope;
    /****** Fin de parte Parte 5.1 *****/
};

TRefugio crearTRefugio() {
    TRefugio nuevoRefugio = new rep_refugio;
    nuevoRefugio->tope = 0; 
    return nuevoRefugio;
}

void liberarTRefugio(TRefugio& refugio) {
    while(refugio->tope > 0){
        liberarTPerro(refugio->refugioPerros[refugio->tope - 1]);
        refugio->tope --;
    }
    delete refugio;
    refugio = NULL;
}

void agregarEnTRefugio(TRefugio& refugio, TPerro perro) {
    if(refugio != NULL && refugio->tope  < MAX_PERROS && perro != NULL){
        if(refugio->tope == 0){
            refugio->tope ++;
            refugio->refugioPerros[0] = perro;
        }else{
            refugio->tope ++;
            int i = refugio->tope - 1;
            refugio->refugioPerros[i] = perro;
            TPerro copia = NULL;
            while(i > 0 && compararTFechas(fechaIngresoTPerro(refugio->refugioPerros[i]), fechaIngresoTPerro(refugio->refugioPerros[i - 1])) == -1){
                copia = refugio->refugioPerros[i - 1];
                refugio->refugioPerros[i - 1] = refugio->refugioPerros[i];
                refugio->refugioPerros[i] = copia;
                i--;
                
            }
            copia = NULL;
        }
    }
}

void imprimirTRefugio(TRefugio refugio) {
    if(refugio != NULL){
        int contador = 0;
        while(contador < refugio->tope){
            imprimirTPerro(refugio->refugioPerros[contador]);
            contador++;
        }
    }

}

bool estaEnTRefugio(TRefugio refugio, int id) {
    bool respuesta = false;
    if(refugio != NULL && refugio->tope > 0){
        int contador = 0;
        while(contador < refugio->tope && idTPerro(refugio->refugioPerros[contador])!= id){
            contador++;
        }
        respuesta = contador < refugio->tope;
    }
    return respuesta;
}

TPerro obtenerDeTRefugio(TRefugio refugio, int id) {
    bool buscador = estaEnTRefugio(refugio, id);
    TPerro res = NULL;
    if(buscador){
        int contador = 0;
        while(contador < refugio->tope && idTPerro(refugio->refugioPerros[contador])!= id){
            contador++;
        }
        res = refugio->refugioPerros[contador];
    }
    return res;
}

bool ingresaronPerrosFechaTRefugio(TRefugio refugio, TFecha fecha) {
    if(refugio == NULL || refugio->tope == 0 || fecha == NULL){
        return false;
    }

    int izq = 0;
    int der = refugio ->tope - 1;
    bool perroEsta = false;
    while((izq <= der) && (!perroEsta)){
        int mit = (der + izq)/2;
        if(compararTFechas(fechaIngresoTPerro(refugio->refugioPerros[mit]), fecha) == 0){
            perroEsta = true;
        }
        else if (compararTFechas(fechaIngresoTPerro(refugio->refugioPerros[mit]), fecha) == -1){
            izq = mit + 1;
            
        }
        else{
            der = mit - 1;
        }
    }
    return perroEsta;
}

void imprimirPerrosFechaTRefugio(TRefugio refugio, TFecha fecha) {
    bool busqueda = ingresaronPerrosFechaTRefugio(refugio, fecha);
    if(busqueda){
        for (int contador = 0; contador < refugio->tope; contador++) {
            if (compararTFechas(fechaIngresoTPerro(refugio->refugioPerros[contador]), fecha) == 0) {
                imprimirTPerro(refugio->refugioPerros[contador]);
            }
        }
    }
}

void removerDeTRefugio(TRefugio& refugio, int id) {

    bool buscador = estaEnTRefugio(refugio, id);
    int contador = 0;
    if(buscador){
        while(contador < refugio->tope && idTPerro(refugio->refugioPerros[contador])!= id){
            contador++;
        }
        TPerro copia = NULL;
        while(contador < refugio->tope - 1){
            copia = refugio->refugioPerros[contador + 1];
            refugio->refugioPerros[contador + 1] = refugio->refugioPerros[contador];
            refugio->refugioPerros[contador] = copia;
            contador++;
        }
        liberarTPerro(refugio->refugioPerros[contador]);
        refugio->tope --;
    }
}