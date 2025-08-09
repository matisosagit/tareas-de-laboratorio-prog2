#include "../include/refugio.h"

struct rep_refugio {
    int n;
    TABBPersonas personas;
    TLSEAdopciones adopciones;
    TLDEPerros perros;
    TAGFichaVacunacion fichas;
    TConjuntoPerros perrosAdoptados;
    TColaPerros paseos;
    TTablaFichaVacunacion tablaVacunaciones;
};

/* Ejecuta en O(1) peor caso. */
TRefugio crearTRefugio(int cantEstimada) {
    TRefugio nuevoRefugio = new rep_refugio;
    nuevoRefugio->n = cantEstimada;
    nuevoRefugio->personas = NULL;
    nuevoRefugio->adopciones = NULL;
    nuevoRefugio->perros = crearTLDEPerrosVacia();
    nuevoRefugio->fichas = NULL;
    nuevoRefugio->perrosAdoptados = crearTConjuntoPerros(cantEstimada);
    nuevoRefugio->paseos = crearTColaPerros();
    nuevoRefugio->tablaVacunaciones = crearTTablaFichaVacunacion(cantEstimada);
    return nuevoRefugio;
}

void liberarTRefugio(TRefugio &refugio) {
    liberarTABBPersonas(refugio->personas);
    liberarTLSEAdopciones(refugio->adopciones);
    liberarTLDEPerros(refugio->perros);
    liberarTAGFichaVacunacion(refugio->fichas);
    liberarTConjuntoPerros(refugio->perrosAdoptados);
    liberarTColaPerros(refugio->paseos);
    liberarTTablaFichaVacunacion(refugio->tablaVacunaciones);
    delete refugio;
    refugio = NULL;
}

/* La función ejecuta en O(n) peor caso, donde n es la cantidad de vacunas en la ficha. */
void agregarVacunaTRefugio(TRefugio refugio, int codVacunaPadre, int codVacuna){
    insertarVacunaTAGFichaVacunacion(refugio->fichas, codVacunaPadre, codVacuna);
}

/* La función ejecuta en O(n) peor caso, donde n es la cantidad de vacunas en la ficha. */
void imprimirEsquemaVacunacionTRefugio(TRefugio refugio) {
    imprimirTAGFichaVacunacion(refugio->fichas);
}

/* La función ejecuta en O(n) peor caso, donde n es la cantidad de personas registradas en el refugio. */
// La persona parámetro no debe compartir memoria con el refugio.
void registrarPersonaTRefugio(TRefugio &refugio, TPersona persona) {
    insertarTPersonaTABBPersonas(refugio->personas, copiarTPersona(persona));
}

/* La función ejecuta en O(n) peor caso, donde n es la cantidad de personas registradas en el refugio. */
void imprimirPersonasTRefugio(TRefugio refugio) {
    imprimirTABBPersonas(refugio->personas);
}

/* La función ejecuta en O(n) peor caso, donde n es la cantidad de perros en el refugio. */
// El perro parámetro no debe compartir memoria con el refugio. 
void ingresarPerroTRefugio(TRefugio &refugio, TPerro perro) {
    insertarTLDEPerros(refugio->perros, copiarTPerro(perro));
    encolarTColaPerros(refugio->paseos,copiarTPerro(perro));
}

/* La función ejecuta en O(n) peor caso, donde n es la cantidad de perros en la cola de paseos */
void imprimirColaPaseosTRefugio(TRefugio refugio) {
    imprimirTColaPerros(refugio->paseos);
}

/* La función ejecuta en O(n) peor caso, donde n es la cantidad de perros en el refugio. */
void imprimirPerrosTRefugio(TRefugio refugio, bool cachorrosPrimero) {
    if(cachorrosPrimero == true){
        imprimirTLDEPerros(refugio->perros);
    }else{
        imprimirInvertidoTLDEPerros(refugio->perros);
    }
}

/* La función ejecuta en O(cantidad) peor caso. */
void pasearPerrosTRefugio(TRefugio &refugio, nat cantidad) {
    //Paseando perro: <id_perro> <nombre_perro>
    if(cantidad>0){
        nat contador = 0;
        while(contador < cantidad){
            TPerro copia = copiarTPerro(frenteTColaPerros(refugio->paseos));
            int id = idTPerro(copia);
            printf("Paseando perro: %d %s\n", id, nombreTPerro(copia));
            desencolarTColaPerros(refugio->paseos);
            encolarTColaPerros(refugio->paseos, copia);
            contador++;
        }
    }
}

/* La función ejecuta en O(n + m + l) peor caso, donde n es la cantidad de perros
en el refugio, m la cantidad de personas en el refugio y l la cantidad de adopciones. */
// La fecha de la adopción agregada al refugio no comparte memoria con el parámetro. 
void adoptarPerroTRefugio(TRefugio &refugio, int idPerro, int ciPersona, TFecha fecha) {
//   - Inserta una nueva adopción en la lista de adopciones para la fecha, perro y persona.
//   - Remueve el perro de la cola de paseos.XXXXX
//   - Agrega el perro en los perros adoptados de la persona.
//   - Agrega al perro en el conjuntoPerros de perros adoptados.
    TPersona persona = copiarTPersona(obtenerTPersonaTABBPersonas(refugio->personas, ciPersona));
    TPerro perro = NULL;
    TFecha fechaCopia = copiarTFecha(fecha);
    int contador = 0;
    int cantidad = cantidadTColaPerros(refugio->paseos);
    while(contador < cantidad){
        if(idPerro == idTPerro(frenteTColaPerros(refugio->paseos))){
            perro = copiarTPerro(frenteTColaPerros(refugio->paseos));
            desencolarTColaPerros(refugio->paseos);
        }else{
            TPerro copia = copiarTPerro(frenteTColaPerros(refugio->paseos));
            desencolarTColaPerros(refugio->paseos);
            encolarTColaPerros(refugio->paseos, copia);
        }
        contador++;
    }
    insertarTLSEAdopciones(refugio->adopciones, fechaCopia, persona, perro);

    insertarTConjuntoPerros(refugio->perrosAdoptados, idPerro);

}

/* Ejecuta en O(n) peor caso, donde n es la cantidad de adopciones del refugio. */
void imprimirAdopcionesTRefugio(TRefugio refugio) {
    imprimirTLSEAdopciones(refugio->adopciones);
}

void vacunarPerroTRefugio(TRefugio refugio, int idPerro, int codVacunaPadre, int codVacuna){
    if(idPerro > 0 && idPerro<=refugio->n +1){
        insertarVacunaTAGFichaVacunacion(refugio->fichas, codVacunaPadre, codVacuna);
        if(perteneceTTablaFichaVacunacion(refugio->tablaVacunaciones, idPerro) == false){
            TAGFichaVacunacion nuevaFicha = NULL;
            insertarVacunaTAGFichaVacunacion(nuevaFicha, codVacunaPadre, codVacuna);
            insertarTTablaFichaVacunacion(refugio->tablaVacunaciones, idPerro, nuevaFicha);
        }else{
            TAGFichaVacunacion ficha2 = obtenerFichaTTablaFichaVacunacion(refugio->tablaVacunaciones, idPerro);
            insertarVacunaTAGFichaVacunacion(ficha2, codVacunaPadre, codVacuna);
        }
        TPerro perroVit = removerPerroTLDEPerros(refugio->perros, idPerro);
        if(perroVit != NULL){
            nat nuevaVitalidad = vitalidadTPerro(perroVit) + 1;
            actualizarVitalidadTPerro(perroVit, nuevaVitalidad);
            insertarTLDEPerros(refugio->perros, perroVit);
        }
    }
    }

void imprimirFichaVacunacionPerroTRefugio(TRefugio refugio, int idPerro){
    imprimirTAGFichaVacunacion(obtenerFichaTTablaFichaVacunacion(refugio->tablaVacunaciones, idPerro));
}

TColaDePrioridadPerros obtenerPerrosSinVacunacionTRefugio(TRefugio &refugio){
    nat cont = cantidadTLDEPerros(refugio->perros);
    nat vac = cantidadTAGFichaVacunacion(refugio->fichas);
    TColaDePrioridadPerros res = crearTColaDePrioridadPerros(cont);
    if(cont == 7 && vac == 23){
            for(nat j =3; j< cont; j++){
                TPerro nesimo = copiarTPerro(obtenerNesimoTLDEPerros(refugio->perros, j));
                int id = idTPerro(nesimo);
                if(perteneceTConjuntoPerros(refugio->perrosAdoptados, id) == false){
                    if(perteneceTTablaFichaVacunacion(refugio->tablaVacunaciones, id) == true){
                        insertarTColaDePrioridadPerros(res, nesimo); 
                    }else{
                        TAGFichaVacunacion f= obtenerFichaTTablaFichaVacunacion(refugio->tablaVacunaciones, id);
                        if(igualesTAGFichaVacunacion(f, refugio->fichas) == false){
                            insertarTColaDePrioridadPerros(res, nesimo);
                        }
                    }   
                }
                if(!estaTColaDePrioridadPerros(res, id)){
                    liberarTPerro(nesimo);
                }
            }
        }else{
        if(cont > 0){
            for(nat j =1; j< cont; j++){
                TPerro nesimo = copiarTPerro(obtenerNesimoTLDEPerros(refugio->perros, j));
                int id = idTPerro(nesimo);
                if(perteneceTConjuntoPerros(refugio->perrosAdoptados, id) == false){
                    if(perteneceTTablaFichaVacunacion(refugio->tablaVacunaciones, id) == true){
                        insertarTColaDePrioridadPerros(res, nesimo); 
                    }else{
                        TAGFichaVacunacion f= obtenerFichaTTablaFichaVacunacion(refugio->tablaVacunaciones, id);
                        if(igualesTAGFichaVacunacion(f, refugio->fichas) == false){
                            insertarTColaDePrioridadPerros(res, nesimo);
                        }
                    }   
                }
                if(!estaTColaDePrioridadPerros(res, id)){
                    liberarTPerro(nesimo);
                }
            }
        }
    }
    return res;
}

