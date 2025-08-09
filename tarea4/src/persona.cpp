#include "../include/persona.h"

struct rep_persona {
    int cedula;
    char nombre[MAX_NOMBRE_PERSONA];
    char apellido[MAX_APELLIDO_PERSONA];
    TFecha nacimiento;
    TPerro coleccion_perros[MAX_PERROS_PERSONA];
    int tope_coleccion;
};

TPersona crearTPersona(int ci, const char nombre[MAX_NOMBRE_PERSONA], const char apellido[MAX_APELLIDO_PERSONA], nat diaNac, nat mesNac, nat anioNac){
    TPersona nueva_persona = new rep_persona;
    nueva_persona->cedula = ci;
    strcpy(nueva_persona->nombre, nombre);
    strcpy(nueva_persona->apellido, apellido);
    nueva_persona->nacimiento = crearTFecha(diaNac, mesNac, anioNac);
    nueva_persona->tope_coleccion = 0;
    return nueva_persona;
}

void imprimirTPersona(TPersona persona){
    printf("Persona %s %s\n", persona->nombre, persona->apellido);
    printf("CI: %d\n", persona->cedula);
    printf("Fecha de Nacimiento: ");
    imprimirTFecha(persona->nacimiento);
    printf("Perros adoptados:\n");
    if(persona->tope_coleccion > 0){
        for(int i = 0; i < persona->tope_coleccion; i++){
            imprimirTPerro(persona->coleccion_perros[i]);
        }
    }
}

void liberarTPersona(TPersona &persona){
    liberarTFecha(persona->nacimiento);
    if(persona->tope_coleccion > 0){
        for(int i = persona->tope_coleccion -1; i>=0; i--){
            liberarTPerro(persona->coleccion_perros[i]);
            persona->tope_coleccion--;
        }
    }
    delete persona;
    persona = NULL;
}

int ciTPersona(TPersona persona){
    return persona->cedula;
}

char* nombreTPersona(TPersona persona){
    return persona->nombre;
}

char* apellidoTPersona(TPersona persona){
    return persona->apellido;
}

TFecha fechaNacimientoTPersona(TPersona persona){
    return persona->nacimiento;
}

void agregarPerroTPersona(TPersona &persona, TPerro perro){
    if((persona != NULL) && (perro != NULL) && (fechaIngresoTPerro(perro) !=NULL) && (persona->tope_coleccion < MAX_PERROS_PERSONA)){
        persona->tope_coleccion++;
        TPerro copia_perro = copiarTPerro(perro);
        persona->coleccion_perros[persona->tope_coleccion - 1] = copia_perro;
    }
}

bool pertenecePerroTPersona(TPersona persona, int idPerro){
    if(persona == NULL){
        return false;
    }
    bool respuesta = false;
    int contador = 0;
    while(contador < persona->tope_coleccion && respuesta == false){
        if(idTPerro(persona->coleccion_perros[contador]) == idPerro){
            respuesta = true;
        }
        contador++;
    }
    return respuesta;
}

int cantidadPerrosTPersona(TPersona persona){
    int contador_perros = 0;
    if(persona != NULL){
        while(contador_perros < persona->tope_coleccion){
            contador_perros++;
        }
    }
    return contador_perros;
}

TPersona copiarTPersona(TPersona persona){
    TPersona copia = crearTPersona(persona->cedula, persona->nombre, persona->apellido, 0, 0, 0);
    liberarTFecha(copia->nacimiento);
    copia->nacimiento = copiarTFecha(persona->nacimiento);
    if(persona->tope_coleccion > 0){
        for(int i = 0; i<persona->tope_coleccion; i++){
            copia->tope_coleccion++;
            copia->coleccion_perros[i] = copiarTPerro(persona->coleccion_perros[i]);
        }
    }
    return copia;
}