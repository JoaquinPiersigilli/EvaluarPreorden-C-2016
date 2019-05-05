#include <stdio.h>
#include <stdlib.h>
#include "pila.h"
#define PIL_NO_INI 9
#define PIL_VACIA 10

/**
 *Este metodo crea una pila vacía y la retorna.
 *@return puntero a struct pila que apunta al valor NULL.
 *
 */
pila_t pila_crear(){
    pila_t pilaNueva=NULL;

    return pilaNueva;
}

/**
 *Este metodo retorna el elemento que se encuentra en el tope de una pila recibida por parametro y en caso de que ésta esté vacía termina la ejecución con código de error PIL_VACIA.
 *@param pila Puntero a struct pila.
 *@return Retorna el elemento de tipo char* que se encuentra en el tope de la pila.
 *
 */
char* tope(pila_t pila){
   char* toReturn = NULL;

    if(pila!=NULL){
            toReturn = pila->elemento;
    }
    else exit(PIL_VACIA);

    return toReturn;
}

/**
 *Este metodo retorna el elemento que se encuentra en el tope de una pila recibida por parametro liberando la memoria que ocupa el struct pila que contiene al elemento.
 *Luego el elemento que estaba en la segunda posición de la pila pasa a estar en el tope de la misma y el puntero recibido por parametro apunta a este nuevo tope.
 *En caso de que la pila esté vacía termina la ejecución con código de error PIL_VACIA.
 *@param pila Puntero a un puntero a struct pila.
 *@return Retorna el elemento de tipo char* que se encuentra en el tope de la pila.
 *
 */
char* desapilar(pila_t* pila){
    char* toReturn = NULL;
    if((*pila)!=NULL){
            toReturn = (*pila)->elemento;

            pila_t pilaActual = (*pila)->proximo_elemento;

            free(*pila);

            *pila = pilaActual;

    }else exit(PIL_VACIA);

    return toReturn;
}

/**
 *Este método recibe por parámetro un puntero a una pila_t (es decir un puntero a un puntero a un struct pila) y un elemento de tipo char* que se desea insertar como nuevo tope de la pila (apilar).
 *Si la pila no está inicializada termina la ejecución del programa con código de error PIL_NO_INI (9), de lo contrario, se reserva espacio en memoria para un nuevo struct pila "pilaNueva" con primer elemento “elem” y proximo elemento "(*pila)"
 (es decir, ahora el próximo elemento de "pilaNueva" es el tope inicial de la pila).
 *Luego pilaNueva pasa a ser el nuevo tope de la pila haciendo que el puntero a pila_t recibido por parametro apunte ahora a "pilaNueva"
 *@param pila Puntero a un puntero a un struct pila.
 *@param str Elemento que se desea apilar.
 *@return Retorna uno si procede con éxito y cero en caso contrario.
 *
 */
int apilar(pila_t* pila, char* str){

    int toReturn = 0;

    if(pila!=NULL){
        pila_t pilaNueva = (pila_t) malloc(sizeof(struct pila));
        pilaNueva->elemento=str;
        pilaNueva->proximo_elemento=(*pila);
        (*pila) = pilaNueva;
        toReturn=1;
    }else exit(PIL_NO_INI);

    return toReturn;
}

/**
 *Este método recibe por parámetro un puntero a un struct pila y retorna uno si la pila está vacia y cero en caso contrario.
 *@param pila Puntero a un struct pila.
 *@return Retorna uno si la pila "pila" está vacía y cero si tiene al menos un elemento.
 *
 */
int pila_vacia(pila_t pila){

    //como diferencio si la pila esta vacia o no inicializada? si la pila vacia es un puntero a NULL...
    int toReturn = 0;

    if(pila==NULL)
            toReturn = 1;

    return toReturn;
}
