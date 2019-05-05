#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#define LST_NO_INI 3
#define LST_POS_INV 4
#define tamanio_arreglo 4 //tamaño del arreglo "elementos" perteneciente a una celda


/**
 *Este metodo crea una lista vacía y la retorna.
 *Se reserva espacio en memoria para una estructura de tipo lista_eficiente y se inicializa con los atributos “cantidad_elementos” y “primera_celda” con valores 0 y NULL respectivamente.
 *Luego se retorna el puntero al struct lista_eficiente.
 *@return puntero al struct lista_eficiente.
 *
 */
lista_t lista_crear(){
     lista_t miLista;

     miLista=(lista_t)malloc(sizeof (struct lista_eficiente));
     miLista->cantidad_elementos = 0;
     miLista->primera_celda = NULL;

     return miLista;
}

/**
 *Este metodo inserta el elemento “elem” en la posición “pos” de la lista “lista”.
 *Si la lista está vacía se reserva espacio en memoria para una nueva celda de tipo “struct celda”, se inicializa y se asigna como primera celda de la lista.
 *Si la lista no está vacía, al insertar en una posición intermedia, se busca dicha posición y se sobrescribe su valor con el elemento nuevo sin modificar la cantidad de elementos totales, y al insertar al final de la lista,
 *se analiza si es necesario o no reservar espacio en memoria para una nueva celda, en caso de serlo se inicializa la misma con el elemento y se agrega como última celda de la lista, de lo contrario simplemente se agrega el elemento al arreglo de la última celda.
 *En los últimos dos casos se incrementa en uno la cantidad de elementos totales.
 *
 *@param lista Puntero a la lista_eficiente.
 *@param pos Posición de la lista donde se desea insertar.
 *@param elem Elemento que se desea insertar.
 *@return retorna 1 si procede exitosamente y 0 en caso contrario.
 *
 */
int lista_insertar(lista_t lista, unsigned int pos, int elem){

    int toReturn = 0;
    int cantidad = lista->cantidad_elementos;

    if (lista!= NULL){
        if(pos > cantidad){
            toReturn = 0;
        }else if(pos == 0 && cantidad == 0){
                celda_t* nuevaCelda;
                nuevaCelda = (celda_t*) malloc(sizeof(struct celda));
                nuevaCelda->elementos[0]=elem;
                nuevaCelda->proxima_celda=NULL;
                lista->primera_celda=nuevaCelda;
                lista->cantidad_elementos=cantidad+1;
              } else if(pos==cantidad){     //si la cantidad de elementos es igual a la posición, agrego una celda con el elemento elem.
                               //voy hasta la ultima celda de la lista ya que lo tendre que hacer tenga o no que agregar una nueva celda.
                        celda_t* indice = lista->primera_celda;
                        while(indice->proxima_celda!=NULL){
                            indice = indice->proxima_celda;
                        }

                        if((cantidad % tamanio_arreglo)==0){
                            //creo una nueva celda con el elemento.
                        celda_t* nuevaCelda;
                        nuevaCelda = (celda_t*)malloc(sizeof(struct celda));
                        nuevaCelda->elementos[0] = elem;
                        nuevaCelda->proxima_celda = NULL;

                        //enlazo la ultima celda con la nueva celda, por lo que ésta es la última ahora.
                        indice->proxima_celda = nuevaCelda;
                        } else{ //cant mod 4 distinto de 0 entonces solo tengo que agregar el elemento al arreglo de la ultima celda
                                int i = pos % tamanio_arreglo;
                                indice->elementos[i] = elem;
                            }
                        lista->cantidad_elementos = cantidad + 1;
                        toReturn = 1;
                    }
                    else{ //pos < cantidad
                        celda_t* celda1 = lista->primera_celda;
                        int cont = 1;
                        int pos2 = pos+1;
                        while(cont<pos2){ //me posiciono en la celda que contenga el arreglo que debo modificar
                            if((cont % tamanio_arreglo)==0)
                                celda1=celda1->proxima_celda;

                            cont++;
                        }
                        celda1->elementos[pos%tamanio_arreglo]=elem;
                        toReturn = 1;
                    }
    }
    return toReturn;
}

/**
 *Este metodo elimina la posicion "pos" de la lista “lista”.
 *Si la posición es inválida termina la ejecución con código de error LST_POS_INV (4).
 *Si se desea eliminar el último elemento, se analiza si éste es el único elemento de la última celda, en caso de serlo, se elimina liberando la memoria de la celda, en caso de no serlo, simplemente se decrementa en uno la cantidad total de elementos, de manera tal que el último elemento no será tomado en cuenta.
 *Si se desea eliminar el elemento “x” de una posición intermedia, se realiza un corrimiento de un lugar de todos los elementos que le siguen a “x” sobrescribiéndolo y en caso de que en la última celda hubiese habido sólo un elemento, se libera la memoria de la misma.
 *
 *@param lista Puntero a la lista_eficiente.
 *@param pos Posición de la lista que se desea eliminar.
 *@return retorna 1 si procede exitosamente y 0 en caso contrario.
 *
 */
int lista_eliminar(lista_t lista, unsigned int pos){
   int toReturn = 0;
   if(lista!=NULL){
       if(pos>=lista->cantidad_elementos)
            exit(LST_POS_INV);
       if(lista->cantidad_elementos==0){
            toReturn=0;
       }else //pos menor a cantidad de elementos
            if(pos == (lista->cantidad_elementos-1)){
                if((pos%tamanio_arreglo)==0){
                    celda_t* ultima = lista->primera_celda;
                    celda_t* anterior = lista->primera_celda;
                    while(ultima->proxima_celda!=NULL){
                        anterior = ultima;
                        ultima = ultima->proxima_celda;
                    }
                    free(ultima);
                    anterior->proxima_celda=NULL;
                    lista->cantidad_elementos=lista->cantidad_elementos-1;
                }else{
                    //si quiero borrar el ultimo elemento y no es el unico que está en la celda,
                    //simplemente considero al último valor como basura restandole 1 a la cantidad total.
                    lista->cantidad_elementos = lista->cantidad_elementos-1;
                }
            }else{
                celda_t* actual = lista->primera_celda;
                celda_t* siguiente = NULL;
                int cont = 1;
                int pos2 = pos +1;

                //me posiciono en la celda que contiene el arreglo con el elemento a eliminar
                while(cont<pos2){
                    if((cont % tamanio_arreglo)==0)
                        actual = actual->proxima_celda;

                    cont++;
                }
                //obtengo la ultima celda, que es la que puedo llegar a liberar.
                celda_t* ultima = lista->primera_celda;
                int cant_celdas = 1;
                while(ultima->proxima_celda!=NULL){
                    ultima = ultima->proxima_celda;
                    cant_celdas++;
                }

                int iguales = actual==ultima;

                int elementos_ultima_celda = (lista->cantidad_elementos - ((cant_celdas-1)*tamanio_arreglo));

                int indice_arreglo = pos % tamanio_arreglo;

                if(iguales){
                    while(indice_arreglo < elementos_ultima_celda-1){
                        actual->elementos[indice_arreglo]=actual->elementos[indice_arreglo+1];
                        indice_arreglo++;
                    }
                    lista->cantidad_elementos = lista->cantidad_elementos -1;

                }else{
                    while(actual!=ultima){

                        while(indice_arreglo < tamanio_arreglo-1){
                            actual->elementos[indice_arreglo]=actual->elementos[indice_arreglo+1];
                            indice_arreglo++;
                        }
                        //termino el while y falta sobreescribir el ultimo elemento de la celda actual.
                        siguiente = actual->proxima_celda;
                        int indice_arreglo2 = indice_arreglo;
                        indice_arreglo = 0;
                        actual->elementos[indice_arreglo2]=siguiente->elementos[indice_arreglo];
                        actual = actual->proxima_celda;
                    }
                    //termina el while y falta correr los elementos de la ultima celda.
                    if(elementos_ultima_celda==1){
                        free(actual);
                    }else{
                     while(indice_arreglo < elementos_ultima_celda-1){
                        actual->elementos[indice_arreglo]=actual->elementos[indice_arreglo+1];
                        indice_arreglo++;
                    }
                    }
                    lista->cantidad_elementos = lista->cantidad_elementos -1;
               }
           }
        }


   return toReturn;
}

/**
 *Este metodo retorna la cantidad de elementos de una lista y en caso de que ésta no esté inicializada termina la ejecución con código de error LST_NO_INI.
 *@param lista Puntero a la lista_eficiente.
 *@return cantidad de elementos de la lista "lista".
 *
 */
int lista_cantidad(lista_t lista){
    if(lista==NULL)
        exit(LST_NO_INI);

return lista->cantidad_elementos;
}

/**
 *Este metodo retorna el elemento que se encuentre en dicha posición en dicha lista o finaliza la ejecución del programa con código de error LST_POS_INV en caso de que la posición pasada por parámetro sea invalida.
 *Se recorre la lista desde la posición 0 hasta alcanzar la posición “pos”, se accede al elemento y se retorna el mismo.
 *@param lista Puntero a una lista_eficiente
 *@param pos Posición de la lista.
 *@return Retorna el elemento que se encuentra en la posición "pos" de la lista "lista".
 *
 */
int lista_obtener(lista_t lista, unsigned int pos){
    int toReturn=0;
    if(pos<=(lista->cantidad_elementos-1)){
        int cont=0;
        celda_t* actual = lista->primera_celda;
        int indice = 0;
        int encontre = 0;
        while(!encontre){
            while(indice<tamanio_arreglo-1 && cont < pos){
                indice++;
                cont++;
            }
            if(cont!=pos){
                actual=actual->proxima_celda;
                indice = (-1);
            }else encontre = 1;
        }

        toReturn = actual->elementos[indice];
    } else exit(LST_POS_INV);
return toReturn;
}


/**
 *Este método recibe por parámetro un puntero a una lista_eficiente y un elemento entero que se desea agregar al final de la misma.
 *Si la lista no está inicializada termina la ejecución del programa con código de error LST_NO_INI (3).
 *Si la lista está vacía se reserva espacio en memoria para una nueva celda con primer elemento “elem” y se agrega como primera celda, caso contrario se avanza hasta la última celda.
 *Si la última celda está completa se reserva espacio en memoria para una nueva celda con primer elemento “elem” y se agrega como ultima celda, si la última celda no estaba completa simplemente se agrega “elem” en la primera posición libre de ésta.
 *En todos los casos se incrementa en uno la cantidad total de elementos de la lista.

 *@param lista Puntero a una lista_eficiente
 *@param elem Elemento que se desea agregar al final de la lista.
 *@return Retorna uno si procede con éxito y cero en caso contrario.
 *
 */
int lista_adjuntar(lista_t lista, int elem){
    int toReturn = 0;
    if(lista!=NULL){

        if(lista->cantidad_elementos==0){
            celda_t* nueva;
            nueva = (celda_t*)malloc(sizeof(struct celda));
            nueva->elementos[0]=elem;
            nueva->proxima_celda=NULL;
            lista->primera_celda=nueva;
            lista->cantidad_elementos=lista->cantidad_elementos+1;
        }else{

        //voy hasta la ultima celda.
        celda_t* actual = lista->primera_celda;
        int cant_celdas = 1;
        while(actual->proxima_celda!=NULL){
              actual = actual->proxima_celda;
              cant_celdas++;
        }

        int elementos_ultima_celda = (lista->cantidad_elementos - ((cant_celdas-1)*tamanio_arreglo));

        if(elementos_ultima_celda == tamanio_arreglo){ //la ultima celda esta llena.
            celda_t* nueva;
            nueva = (celda_t*)malloc(sizeof(struct celda));
            nueva->elementos[0]=elem;
            nueva->proxima_celda=NULL;
            actual->proxima_celda=nueva;
        }else{ //ultima celda no esta llena
            actual->elementos[elementos_ultima_celda]=elem;
        }

        lista->cantidad_elementos=lista->cantidad_elementos+1;
        }
    }else exit(LST_NO_INI);

    return toReturn;
}
/**
 *El método recorre todas las celdas de una lista liberándolas una por una y al finalizar le asigna NULL a la lista.
 *Si la lista no está inicializada finaliza la ejecución del programa con código de error LST_NO_INI (3).
 *@param lista Puntero a una lista_eficiente
 *@return Retorna uno si procede con éxito y cero en caso contrario.
 *
 */
int lista_destruir(lista_t* lista){

    int toReturn = 0;

    if((*lista)!=NULL){
    celda_t* actual = (*lista)->primera_celda;
    celda_t* anterior = NULL;

    while(actual!=NULL){
            anterior = actual;
            actual = actual->proxima_celda;
            free(anterior);
    }

    free((*lista));
    *lista=NULL;


    toReturn = 1;

    }else exit(LST_NO_INI);

    return toReturn;
}
