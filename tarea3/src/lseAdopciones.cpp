#include "../include/lseAdopciones.h"

struct rep_lseadopciones {
	TPersona adoptante;
	TPerro adoptado;
	TFecha fecha_adopcion;
	rep_lseadopciones * sig;
};

TLSEAdopciones crearTLSEAdopcionesVacia(){
	return NULL;
}


bool esVaciaTLSEAdopciones(TLSEAdopciones lseAdopciones){
	return lseAdopciones == NULL;
}

void imprimirTLSEAdopciones(TLSEAdopciones lseAdopciones){
	while(lseAdopciones != NULL){
		printf("---------------------------\n");
		printf("Adopcion en fecha ");
		imprimirTFecha(lseAdopciones->fecha_adopcion);
		printf("Adoptante:\n");
		printf("Persona %s %s\n", nombreTPersona(lseAdopciones->adoptante), apellidoTPersona(lseAdopciones->adoptante));
		printf("CI: %d\n", ciTPersona(lseAdopciones->adoptante));
		printf("Adoptado:\n");
		printf("Perro %d\n", idTPerro(lseAdopciones->adoptado));
		printf("Nombre: %s\n", nombreTPerro(lseAdopciones->adoptado));
		printf("Fecha de ingreso: "); imprimirTFecha(fechaIngresoTPerro(lseAdopciones->adoptado));
		printf("---------------------------\n");
		lseAdopciones = lseAdopciones->sig;
	}
}

void liberarTLSEAdopciones(TLSEAdopciones &lseAdopciones){
	TLSEAdopciones copia = lseAdopciones;
	while(copia!=NULL){
		liberarTFecha(copia->fecha_adopcion);
		liberarTPerro(copia->adoptado);
		liberarTPersona(copia->adoptante);
		TLSEAdopciones siguiente = copia->sig;
		delete copia;
		copia = siguiente;

	}
	lseAdopciones = NULL;
	
}

void insertarTLSEAdopciones(TLSEAdopciones &lseAdopciones, TFecha fecha, TPersona persona, TPerro perro){
	TLSEAdopciones nueva_adopcion = new rep_lseadopciones;
	nueva_adopcion->adoptante = persona;
	nueva_adopcion->adoptado = perro;
	nueva_adopcion->fecha_adopcion = fecha;
	nueva_adopcion->sig = NULL;
	if(lseAdopciones == NULL || compararTFechas(fecha, lseAdopciones->fecha_adopcion) == -1){
		nueva_adopcion->sig = lseAdopciones;
		lseAdopciones = nueva_adopcion;
	}else{
		TLSEAdopciones copia = lseAdopciones;
		while(copia->sig != NULL && compararTFechas(fecha, copia->sig->fecha_adopcion)!= -1){
			copia = copia->sig;
		}
		nueva_adopcion->sig = copia->sig;
		copia->sig = nueva_adopcion;
	}
}

bool existeAdopcionTLSEAdopciones(TLSEAdopciones lseAdopciones, int ciPersona, int idPerro){
	while(lseAdopciones != NULL && (ciPersona != ciTPersona(lseAdopciones->adoptante) || idPerro!= idTPerro(lseAdopciones->adoptado))){
		lseAdopciones = lseAdopciones->sig;
	}
	return lseAdopciones != NULL;
}

void removerAdopcionTLSEAdopciones(TLSEAdopciones &lseAdopciones, int ciPersona, int idPerro){
	if(lseAdopciones!= NULL){
		TLSEAdopciones copia = lseAdopciones;
		TLSEAdopciones copia2 = NULL;
		while(ciPersona != ciTPersona(copia->adoptante) || idPerro != idTPerro(copia->adoptado)){
			copia2 = copia;
			copia = copia->sig;
		}
		if(copia2 != NULL){
			TLSEAdopciones copia3 = copia->sig;
			liberarTFecha(copia->fecha_adopcion);
			liberarTPerro(copia->adoptado);
			liberarTPersona(copia->adoptante);
			copia2->sig = copia3;
			delete copia;
			copia = NULL;
		}else{
			TLSEAdopciones copia3 = copia->sig;
			liberarTFecha(copia->fecha_adopcion);
			liberarTPerro(copia->adoptado);
			liberarTPersona(copia->adoptante);
			lseAdopciones = copia3;
			delete copia;
			copia = NULL;
		}
		
	}
}

