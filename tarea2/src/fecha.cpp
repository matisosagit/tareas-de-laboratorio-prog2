#include "../include/fecha.h"

struct rep_fecha {
    nat dia, mes, anio;
};

TFecha crearTFecha(nat dia, nat mes, nat anio) {
    TFecha nuevaFecha = new rep_fecha;
    nuevaFecha->dia = dia;
    nuevaFecha->mes = mes;
    nuevaFecha->anio = anio;
    return nuevaFecha;
}

void liberarTFecha(TFecha &fecha) {
    delete fecha;
    fecha = NULL;
}

void imprimirTFecha(TFecha fecha) {
    printf("%d/%d/%d\n",fecha->dia,fecha->mes,fecha->anio);
}

TFecha copiarTFecha(TFecha fecha) {
    TFecha copia = crearTFecha(fecha->dia, fecha->mes, fecha->anio);
    return copia;
}

bool esBisiesto(nat anio){
    return (anio % 4 == 0 && (anio % 400 == 0 || anio % 100 != 0));
}

static nat diasMes(nat mes, nat anio){
    nat febrero;
    nat dias = 0;
    if(esBisiesto(anio) == true){
        febrero = 29;
    }else {febrero = 28;}

    switch(mes){
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: 
            dias = 31;
            break;
        case 2: dias = febrero;
                break;
        case 4: case 6: case 9: case 11: 
            dias = 30;
            break;
    }
    return dias;
}

void aumentarTFecha(TFecha &fecha, nat dias) {
    fecha->dia += dias;
    while (fecha->dia > diasMes(fecha->mes, fecha->anio)) {
        fecha->dia -= diasMes(fecha->mes, fecha->anio);
        fecha->mes++;
        if (fecha->mes > 12) {
            fecha->mes = 1;
            fecha->anio++;
        }
    }
}

int compararTFechas(TFecha fecha1, TFecha fecha2) {
    int res = 0;
    if((fecha1->anio > fecha2->anio) || ((fecha1->anio == fecha2->anio) && (fecha1->mes > fecha2->mes))
        || ((fecha1->anio == fecha2->anio)&&(fecha1->mes == fecha2->mes)&&(fecha1->dia > fecha2->dia))
    ){
        res = 1;
    }else if((fecha1->anio < fecha2->anio) || ((fecha1->anio == fecha2->anio) && (fecha1->mes < fecha2->mes))
    || ((fecha1->anio == fecha2->anio)&&(fecha1->mes == fecha2->mes)&&(fecha1->dia < fecha2->dia))
    ){
        res = -1;
    }
    return res;
}
