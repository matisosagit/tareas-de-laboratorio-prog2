#include "../include/perro.h"

struct rep_perro {
    int id;
    char  nombre[MAX_NOMBRE];
    nat edad;
    nat vitalidad;
    char  descripcion[MAX_DESCRIPCION];
    TFecha ingreso;
};

TPerro crearTPerro(int id, const char nombre[MAX_NOMBRE], nat edad, nat vitalidad, const char descripcion[MAX_DESCRIPCION], TFecha fechaIngreso) {
    TPerro perroCopia = new rep_perro;
    perroCopia->id = id;
    strcpy(perroCopia->nombre, nombre);
    perroCopia->edad = edad;
    perroCopia->vitalidad = vitalidad;
    strcpy(perroCopia->descripcion, descripcion);
    perroCopia->ingreso = fechaIngreso;
    return perroCopia;
}

void liberarTPerro(TPerro &perro) {
    liberarTFecha(perro->ingreso);
    delete perro;
    perro = NULL;
}

int idTPerro(TPerro perro) {
    return perro->id;
}

char* nombreTPerro(TPerro perro) {
    return perro->nombre; 
}

nat edadTPerro(TPerro perro) {
    return perro->edad;
}

nat vitalidadTPerro(TPerro perro) {
    return perro->vitalidad; 
}

char* descripcionTPerro(TPerro perro) {
    return perro->descripcion; 
}

TFecha fechaIngresoTPerro(TPerro perro) {
    return perro->ingreso; 
}

void imprimirTPerro(TPerro perro) {
    printf("Perro %d\n", perro->id);
    printf("Nombre: %s\n", perro->nombre);
    printf("Edad: %d\n",perro->edad);
    printf("Descripcion: %s\n", perro->descripcion);
    printf("Fecha de ingreso: "); imprimirTFecha(perro->ingreso);
    printf("Vitalidad: %d\n", perro->vitalidad);
}

TPerro copiarTPerro(TPerro perro) {
    TFecha copiaF =copiarTFecha(perro->ingreso);
    TPerro copia = crearTPerro(perro->id, perro->nombre, perro->edad, perro->vitalidad, perro->descripcion, copiaF);
    return copia;
}

void actualizarEdadTPerro(TPerro &perro, nat nuevaEdad) {
    perro->edad = nuevaEdad;
}

void actualizarVitalidadTPerro(TPerro &perro, nat nuevaVitalidad) {
    perro->vitalidad = nuevaVitalidad;
}