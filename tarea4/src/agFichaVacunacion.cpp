#include "../include/agFichaVacunacion.h"

struct rep_agFichaVacunacion {
    int codigo;
    TAGFichaVacunacion primerHijo, segundoHermano;
};
 
/* Debe ejecutar en O(1) peor caso. */
TAGFichaVacunacion crearTAGFichaVacunacion(){
    return NULL;
}

/* Debe ejecutar en O(n) peor caso, siendo n la cantidad de vacunas en el árbol. */
void insertarVacunaTAGFichaVacunacion(TAGFichaVacunacion &fichaVacunacion, int codVacunaPadre, int codVacuna){  
    if(fichaVacunacion != NULL && codVacunaPadre != -1 ){
        if(fichaVacunacion->codigo == codVacunaPadre){
            TAGFichaVacunacion nuevaFicha = new rep_agFichaVacunacion;
            nuevaFicha->codigo = codVacuna;
            nuevaFicha->primerHijo = nuevaFicha->segundoHermano = NULL;
            nuevaFicha->segundoHermano = fichaVacunacion->primerHijo;
            fichaVacunacion->primerHijo = nuevaFicha;
            return;
        }else{
            insertarVacunaTAGFichaVacunacion(fichaVacunacion->primerHijo, codVacunaPadre, codVacuna);
            insertarVacunaTAGFichaVacunacion(fichaVacunacion->segundoHermano, codVacunaPadre, codVacuna);
            return;
        }       
    }else if(fichaVacunacion == NULL && codVacunaPadre == -1) {
        TAGFichaVacunacion nuevaFicha = new rep_agFichaVacunacion;
        nuevaFicha->codigo = codVacuna;
        nuevaFicha->primerHijo = nuevaFicha->segundoHermano = NULL;
        fichaVacunacion = nuevaFicha;
        return;
    }
}

void auxEspacios(int n){
    if(n > 0){
        printf("    ");
        auxEspacios(n - 1);
    }
}

void imprimirAuxiliar(TAGFichaVacunacion fichaVacunacion, int n){
    if(fichaVacunacion != NULL){
        auxEspacios(n);
        printf("%d\n", fichaVacunacion->codigo);
        imprimirAuxiliar(fichaVacunacion->primerHijo, n + 1);
        imprimirAuxiliar(fichaVacunacion->segundoHermano, n);
    }
}

/*Debe ejecutar en O(n) peor caso, donde n es la cantidad de vacunas en el árbol. */
void imprimirTAGFichaVacunacion(TAGFichaVacunacion fichaVacunacion){
        printf("Ficha Vacunacion:\n");
        imprimirAuxiliar(fichaVacunacion, 0);
}

/* Debe ejecutar en O(n) peor caso, donde n es la cantidad de vacunas en el árbol. */
// Luego de la función, el puntero fichaVacunacion debe apuntar a NULL.
void liberarTAGFichaVacunacion(TAGFichaVacunacion &fichaVacunacion){
    if(fichaVacunacion != NULL){
        liberarTAGFichaVacunacion(fichaVacunacion->primerHijo);
        liberarTAGFichaVacunacion(fichaVacunacion->segundoHermano);
        delete fichaVacunacion;
        fichaVacunacion = NULL;
    }
}

/* Debe ejecutar en O(n) peor caso, siendo n la cantidad de vacunas en el árbol. */
bool existeVacunaTAGFichaVacunacion(TAGFichaVacunacion fichaVacunacion, int codVacuna){
    if(fichaVacunacion == NULL) return false;
    if(codVacuna == fichaVacunacion->codigo) return true; 
    if(existeVacunaTAGFichaVacunacion(fichaVacunacion->primerHijo, codVacuna))return true;
    return  existeVacunaTAGFichaVacunacion(fichaVacunacion->segundoHermano, codVacuna); 
}

/* Debe ejecutar en O(n) peor caso, siendo n la cantidad de vacunas en el árbol. */
nat alturaTAGFichaVacunacion(TAGFichaVacunacion fichaVacunacion){
    if(fichaVacunacion == NULL){
        return 0;
    }
    nat altPrimerHijo = 1 + alturaTAGFichaVacunacion(fichaVacunacion->primerHijo);
    nat altSegundoHermano = alturaTAGFichaVacunacion(fichaVacunacion->segundoHermano);
    if(altPrimerHijo >= altSegundoHermano){
        return altPrimerHijo;
    }else return altSegundoHermano;
}

/* Debe ejecutar en O(n) peor caso, siendo n la cantidad de vacunas en el árbol general. */
nat cantidadTAGFichaVacunacion(TAGFichaVacunacion fichaVacunacion){
    if(fichaVacunacion == NULL){
        return 0;
    }
    return(1 + cantidadTAGFichaVacunacion(fichaVacunacion->primerHijo) + cantidadTAGFichaVacunacion(fichaVacunacion->segundoHermano)); 
}

/* Debe ejecutar en O(n) peor caso, donde n es la cantidad de vacunas en el árbol. */
void removerVacunaTAGFichaVacunacion(TAGFichaVacunacion &fichaVacunacion, int codVacuna){
    if(fichaVacunacion == NULL) return;
    if(codVacuna == fichaVacunacion->codigo && fichaVacunacion->segundoHermano == NULL){
        liberarTAGFichaVacunacion(fichaVacunacion);
        return;
    }else if(codVacuna == fichaVacunacion->codigo){
        TAGFichaVacunacion aux = fichaVacunacion;
        fichaVacunacion = fichaVacunacion->segundoHermano;
        liberarTAGFichaVacunacion(aux);
        return;
    }
    if(fichaVacunacion->primerHijo != NULL && fichaVacunacion->primerHijo->codigo == codVacuna){
        TAGFichaVacunacion aBorrar = fichaVacunacion->primerHijo;
        fichaVacunacion->primerHijo = aBorrar->segundoHermano;
        liberarTAGFichaVacunacion(aBorrar->primerHijo);
        delete aBorrar;
        aBorrar = NULL;
    }else{
        removerVacunaTAGFichaVacunacion(fichaVacunacion->primerHijo, codVacuna);
    }
    if(fichaVacunacion->segundoHermano != NULL && fichaVacunacion->segundoHermano->codigo == codVacuna){
        TAGFichaVacunacion aBorrar = fichaVacunacion->segundoHermano;
        fichaVacunacion->segundoHermano = aBorrar->segundoHermano;
        liberarTAGFichaVacunacion(aBorrar->primerHijo);
        delete aBorrar;
        aBorrar = NULL;      
    }else{
        removerVacunaTAGFichaVacunacion(fichaVacunacion->segundoHermano, codVacuna);
    }
}
        


/* Debe ejecutar en O(n1 * n2) peor caso, donde n1 es el número de vacunas de fv1 
y n2 es el número de vacunas de fv2. */
bool igualesTAGFichaVacunacion(TAGFichaVacunacion fv1, TAGFichaVacunacion fv2){
    if(fv1 == NULL && fv2 == NULL) return true;
    if(fv1 == NULL || fv2 == NULL) return false;
    if(fv1->codigo != fv2->codigo)return false;
    
    return (igualesTAGFichaVacunacion(fv1->primerHijo,fv2->primerHijo) && 
    igualesTAGFichaVacunacion(fv1->segundoHermano, fv2->segundoHermano));
}

 
 