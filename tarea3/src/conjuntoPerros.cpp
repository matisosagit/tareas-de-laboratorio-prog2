#include "../include/conjuntoPerros.h"

struct rep_conjuntoperros{
  int cantidad;
  int cota;
  bool* arreglo;
};

/* Debe ejectuar en O(n) peor caso, siendo n la cantidad máxima de elementos del conjunto. */
TConjuntoPerros crearTConjuntoPerros(int cantMax){
  TConjuntoPerros nuevoConjunto = new rep_conjuntoperros;
  nuevoConjunto->cantidad = 0;
  nuevoConjunto->cota = cantMax;
  nuevoConjunto->arreglo = new bool[cantMax];
  for(int i = 0; i<cantMax; i++){
    nuevoConjunto->arreglo[i] = false;
  }
  return nuevoConjunto;
}

/* Debe ejecutar en O(1) peor caso. */
void insertarTConjuntoPerros(TConjuntoPerros &c, int id){
  if((c!= NULL) && (id >= 0) && (id < c->cota) && !perteneceTConjuntoPerros(c, id)){
    c->arreglo[id] = true;
    c->cantidad++;
  }
}

/* Debe ejecutar en O(n) peor caso, siendo "n" la cantidad máxima de elementos de "c". */
void imprimirTConjuntoPerros(TConjuntoPerros c){
  int cont = 0;
    for(int i = 0; i<c->cota; i++){
      if(perteneceTConjuntoPerros(c, i)){
        cont++;
        printf("%d",i);
        if(cont < c->cantidad){
          printf(" ");
        }else{
          break;
        }
      }
    }
    printf("\n");
}

/* Debe ejecutar en O(1) peor caso. */
// Luego de la función, el puntero c debe apuntar a NULL.
void liberarTConjuntoPerros(TConjuntoPerros &c){
  if(c!= NULL){
      c->cantidad = 0;
    delete[] c->arreglo;
    c->arreglo = NULL;
    delete c;
    c = NULL;
  }
}

/* Debe ejecutar en O(1) peor caso. */
bool esVacioTConjuntoPerros(TConjuntoPerros c){
  return (c== NULL || c->cantidad == 0);
}

/* Debe ejecutar en O(1) peor caso. */
int cardinalTConjuntoPerros(TConjuntoPerros c){
  return c->cantidad;
}

/* Debe ejecutar en O(1) peor caso. */
int cantMaxTConjuntoPerros(TConjuntoPerros c){
  return c->cota;
}

/* Debe ejecutar en O(1) peor caso. */
bool perteneceTConjuntoPerros(TConjuntoPerros c, int id){
  if(c != NULL && id>=0 && id<c->cota && c->arreglo[id]==true){
    return true;
  }else return false;
}

/* Debe ejecutar en O(1) peor caso. */
void borrarDeTConjuntoPerros(TConjuntoPerros &c, int id){
  if(id >= 0 && id < c->cota && perteneceTConjuntoPerros(c, id)){
    c->arreglo[id] = false;
    c->cantidad--;
  }
}

/* Debe ejecutar en O(n) peor caso, siendo n la cantidad máxima de elementos permitidos en el conjunto */
TConjuntoPerros unionTConjuntoPerros(TConjuntoPerros c1, TConjuntoPerros c2){
  TConjuntoPerros unionP = crearTConjuntoPerros(c1->cota);
  for(int i = 0; i < unionP->cota; i++){
    if(perteneceTConjuntoPerros(c1,i) || perteneceTConjuntoPerros(c2,i)){
      insertarTConjuntoPerros(unionP,i);
    }
  }
  return unionP;
}

/* Debe ejecutar en O(n) peor caso, siendo n la cantidad máxima de elementos permitidos en el conjunto */
TConjuntoPerros interseccionTConjuntoPerros(TConjuntoPerros c1, TConjuntoPerros c2){
  TConjuntoPerros interseccionP = crearTConjuntoPerros(cantMaxTConjuntoPerros(c1));
  for(int i = 0; i < interseccionP->cota; i++){
    if(perteneceTConjuntoPerros(c1,i) && perteneceTConjuntoPerros(c2,i)){
      insertarTConjuntoPerros(interseccionP,i);
    }
  }
  return interseccionP;
}

/* Debe ejecutar en O(n) peor caso, siendo n la cantidad máxima de elementos permitidos en el conjunto */
TConjuntoPerros diferenciaTConjuntoPerros(TConjuntoPerros c1, TConjuntoPerros c2){
  TConjuntoPerros diferenciaP = crearTConjuntoPerros(cantMaxTConjuntoPerros(c1));
  for(int i = 0; i < diferenciaP->cota; i++){
    if(perteneceTConjuntoPerros(c1,i) && !perteneceTConjuntoPerros(c2,i)){
      insertarTConjuntoPerros(diferenciaP,i);
    }
  }
  return diferenciaP;
}
