#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "pila.h"
#include <string.h>
#include <strings.h>
#define EXITO EXIT_SUCCESS
#define EXP_MALF 2
#define OPND_DEMAS 5
#define OPND_INSUF 6
#define OPND_INV 7
#define OPRD_INV 8
#define LST_POS_INV 4
#define OK       0
#define NO_HUBO_ENTRADA 13
#define LARGO 12

/**
 * Funcion encargada de mostrar la ayuda del sistema.
 *
 */
void ayuda()
{
    printf("\nBienvenido al evaluador de expresiones aritmeticas en preorden.\n");
	printf("Este programa le pedirá que ingrese una expresion aritmetica en preorden para luego evaluarla y mostrarle el resultado\n\t");
	printf("Las operaciones disponibles son: Suma, Resta, Multiplicación y División\n\t");
	printf("Puede separar los operadores, parentesis y operandos por cualquier cantidad de espacios en blanco\n\t");
	printf("No se admiten operandos negativos\n\t");
	printf("Los operadores + (suma) y * (multiplicacion) admiten cualquier numero de operandos\n\t");
	printf("Un ejemplo de una expresion en preorden es: \n\t");
	printf("( * ( + 9 12 3 ) 4 5 ( - 3 2 ) )  que se interpreta como: ( 9 + 12 + 3 ) * 4 * 5 * ( 3 - 2 ) \n\t");
    printf("La sintaxis para utilizar el programa es la siguiente:\n\t");
    printf(" $ evaluar [-h] donde el parametro entre corchetes es opcional y en caso de utilizarse despliega este mismo mensaje de ayuda.\n\t");
    exit(0);
}

/**
 * Funcion encargada de mostrar el mensaje de error en los parametros.
 *
 */
void error_parametros(){
	printf("\n Ha ingresado mal los parametros!\n");
	ayuda();
    exit(0);
}

char* evaluar(char exp[], int size);
int iniciar();

/**
 *Funcion inicial encargada de analizar los parametros con los cuales se llama a la ejecución del programa,
 *de acuerdo a este analisis se ejecuta la funcionalidad del programa, se muestra un mensaje de ayuda, o se muestra un mensaje de error
 *@param argc indica la cantidad de parametros introducidos en la linea de comandos
 *@param argv contiene cada uno de los parametros recibidos de la linea de comandos
 *
 */
int main(int argc, char *argv[]){

    if (argc >= 3)//si tiene más de 2 argumentos (el nombre del programa y -h)
        error_parametros();
    else // si tiene uno o dos argumentos
        if(argc==2){
            if(strcmp(argv[1],"-h") ==0)
                ayuda();
            else error_parametros();
        }else if (argc==1)
                  iniciar();
              else error_parametros();

return 0;
}

/**
 * Funcion encargada de armar un string que indicara que el simulador realizo alguna accion
 * @param mensaje Mensaje que se desplegará en la salida estandar antes de recibir una cadena de entrada.
 * @param buff Arreglo de caracteres donde se almacenará la cadena de entrada al sistema.
 * @param size Tamaño del arreglo de caracteres buff.
 * @return devuelve 0 si termina correctamente, 13 si no hubo entrada, y 12 si la entrada fue demasiado larga.
 *
 */
int getLine (char *mensaje, char *buff, size_t size) {
    int ch, extra;

    if (mensaje != NULL) {
        printf ("\n%s\n", mensaje);
        fflush (stdout);
    }
    if (fgets (buff, size, stdin) == NULL)
        return NO_HUBO_ENTRADA;

    if (buff[strlen(buff)-1] != '\n') {
        extra = 0;
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;
        return (extra == 1) ? LARGO : OK;
    }


    buff[strlen(buff)-1] = '\0';
    return OK;
}
/**
 * Funcion encargada de cortar una cadena de caracteres.
 * @param str Cadena de caracteres que se desea cortar.
 * @param begin Posicion en la cadena de caracteres a partir de la cual se cortará.
 * @param len Cantidad de caracteres a cortar a partir de la posicion begin, si len es negativo se corta desde la posición begin hasta el final.
 * @return Devuelve la cantidad de caracteres cortados.
 *
 */
int str_cut(char *str, int begin, int len)
{
    int l = strlen(str);

    if (len < 0) len = l - begin;
    if (begin + len > l) len = l - begin;
    memmove(str + begin, str + begin + len, l - len + 1);

    return len;
}

/**
 * Funcion encargada de transformar una cadena de caracteres cuyos caracteres son digitos decimales al numero entero correspondiente.
 * @param var Cadena de caracteres que se desea transformar a un entero.
 * @param size Tamaño de la cadena de caracteres var.
 * @return Devuelve el valor entero correspondiente a la cadena de caracteres ingresada.
 *
 */
int transformar_a_int(char* var, int size){
    int i=size-1;
    char x;
    int retorno=0;
    int multiplo=1;
    while(i>=0){
        x= *(var+i);
        if(x=='1'){ retorno+=multiplo; }
        if(x=='2'){ retorno+=multiplo*2; }
        if(x=='3'){ retorno+=multiplo*3; }
        if(x=='4'){ retorno+=multiplo*4; }
        if(x=='5'){ retorno+=multiplo*5; }
        if(x=='6'){ retorno+=multiplo*6; }
        if(x=='7'){ retorno+=multiplo*7; }
        if(x=='8'){ retorno+=multiplo*8; }
        if(x=='9'){ retorno+=multiplo*9; }
        multiplo*=10;
        i--;
    }
    return retorno;
}

/**
 * Funcion encargada de pedir una cadena de entrada, analizarla y mostrar su resultado en la salida estandar.
 * @param mensaje Mensaje que se desplegará en la salida estandar antes de recibir una cadena de entrada.
 * @param buff Arreglo de caracteres donde se almacenará la cadena de entrada al sistema.
 * @param size Tamaño del arreglo de caracteres buff.
 * @return devuelve 0 si termina correctamente, 13 si no hubo entrada, y 12 si la entrada fue demasiado larga.
 *
 */
int iniciar(){

    int rc;
    char buff[250];

    rc = getLine ("Ingrese la expresión en notación prefija: ", buff, sizeof(buff));
    if (rc == NO_HUBO_ENTRADA) {
    // Extra NL since my system doesn't output that on EOF.
    printf ("\nDebe ingresar una cadena\n");
    }

    if (rc == LARGO) {
        printf ("Cadena demasiado larga [%s]\n", buff);
    }

    int size= strlen(buff);
    if(size>0){
        int i = 0;
            while(buff[i]==' '){
                i++;
            }

            if(buff[i]!='('){
                int esNumero=1;

                while(buff[i]!='\0' && esNumero){
                    if( buff[i]=='0' || buff[i]=='1' || buff[i]=='2' || buff[i]=='3' || buff[i]=='4' || buff[i]=='5' || buff[i]=='6' || buff[i]=='7' || buff[i]=='8' || buff[i]=='9'){
                        i++;
                    }
                    else esNumero=0;
               }


               if(esNumero==0)
                exit(OPND_INV);


                str_cut(buff,i, strlen(buff)-i);

                int resu = transformar_a_int(buff,strlen(buff));
                printf("\n%s = %i\n",buff, resu);
            }
            else  printf("\n%s = %s\n",buff,evaluar(buff,size));
    }
    printf("\nEjecución terminada\n");
    return 0;
}

/**
 * Esta funcion recibe una cadena de caracteres y evalua si tiene parentesis correctamente balanceados.
 * @param expresion Cadena de caracteres a ser evaluada.
 * @param size Tamaño de la cadena de caracteres expresion.
 * @return devuelve 0 si los parentesis de la expresion no están balanceados y 1 en caso contrario.
 *
 */
int comprobar_parentesis_balanceados(char expresion[], int size){
    int estan_balanceados=1;
    int i;
    pila_t pila=pila_crear();
    for(i=0;(i<size)&&(estan_balanceados);i++){
        if(expresion[i]=='('){

            apilar(&pila,"(");
        }
        else{
            if(expresion[i]==')'){
                if(pila_vacia(pila)){
                    estan_balanceados=0;
                }
                else{

                    desapilar(&pila);
                }
            }
        }
    }

    if(!pila_vacia(pila)){

        estan_balanceados=0;
    }
    return estan_balanceados;
}

/**
 * Funcion encargada de realizar la suma de los operandos contenidos en una lista pasada por parametro.
 * @param operandos Lista de tipo lista_t que contiene elementos enteros.
 * @return Devuelve el resultado de sumar los operandos de la lista.
 *
 */
int suma(lista_t operandos){
    int resultado=0;
    int i;
    for(i=0;i<lista_cantidad(operandos);i++){
        resultado+=lista_obtener(operandos,i);
    }
    return resultado;
}

/**
 * Funcion encargada de realizar la resta de dos operandos contenidos en una lista pasada por parametro.
 * @param operandos Lista de tipo lista_t que contiene dos elementos enteros.
 * @return Devuelve el resultado de restar el valor del primer operando de la lista del valor del segundo operando de la misma.
 *
 */
int resta(lista_t operandos){
    return lista_obtener(operandos,1)-lista_obtener(operandos,0);
}

/**
 * Funcion encargada de realizar la division de dos operandos contenidos en una lista pasada por parametro.
 * @param operandos Lista de tipo lista_t que contiene dos elementos enteros.
 * @return Devuelve el resultado de dividir el valor del segundo de la lista por valor del primer operando de la misma.
 *
 */
int division(lista_t operandos){
    int x=lista_obtener(operandos,0);
    if(x==0){
            printf("No se puede dividir por 0!");
            exit(OPND_INV);
    }
    else{
         return lista_obtener(operandos,1)/x;
    }
}

/**
 * Funcion encargada de realizar la multiplicacion de los operandos contenidos en una lista pasada por parametro.
 * @param operandos Lista de tipo lista_t que contiene elementos enteros.
 * @return Devuelve el resultado de multiplicar los operandos de la lista.
 *
 */
int multiplicacion(lista_t operandos){
    int resultado=1;
    int i;
    for(i=0;i<lista_cantidad(operandos);i++){
        resultado*=lista_obtener(operandos,i);
    }
    return resultado;
}


/**
 * Funcion encargada de decidir qué operacion aritmetica entre las cuatro disponibles se debe realizar.
 * @param lista Lista de tipo lista_t que contiene elementos enteros.
 * @param operador Caracter que determina si se realizara una suma, una resta, una multiplicacion, o una division.
 * @return Devuelve el resultado de la operacion determinada por el operador sobre los elementos de la lista.
 *
 */
int operar(lista_t lista, char* operador){
    int resultado=0;
    if(lista_cantidad(lista)<2){
        exit(OPND_INSUF);
    }
    else{
        if(strcmp(operador,"+")==0){
            resultado=suma(lista);
        }
        else{
            if(strcmp(operador,"*")==0){
                resultado=multiplicacion(lista);
            }
            else{
                if(lista_cantidad(lista)==2){
                    if(strcmp(operador,"/")==0){
                        resultado=division(lista);
                    }
                    else{
                        if(strcmp(operador,"-")==0){
                            resultado=resta(lista);
                        }
                    }
                }
                else{
                    //Se intenta evaluar una resta o una división con más de dos operandos
                    exit(OPND_DEMAS);
                }
            }
        }
    }
    return resultado;
}

/**
 * Funcion encargada de concatenar los caracteres contenidos en una pila en una sola cadena de caracteres.
 * @param pila Pila de tipo pila_t* que contiene los caracteres que se desean concatenar.
 * @return Devuelve el resultado de concatenar todos los caracteres de la pila como una única cadena de caracteres.
 *
 */
char* concatenar_pila(pila_t* pila){
    char* retorno= (char*)malloc(200*sizeof(char*));
    *retorno='\0';
    while(!pila_vacia(*(pila))){
        char* desapilado= desapilar(pila);
        strcat(retorno,desapilado);
    }
    return retorno;
}

/**
 * Funcion encargada de evaluar una cadena de caracteres apilada caracter a caracter y que representa una expresión arimetica expresada en notación prefija en su forma mas simple, es decir, sólo una operacion básica.
 * @param pila Pila de tipo pila_t* que contiene los caracteres de la expresión aritmetica que se desea evaluar.
 * @return Devuelve el resultado producido luego de evaluar aritmeticamente la expresión contenida en la pila.
 */
char* evaluar_aux(pila_t* pila){
    pila_t pila_aux=pila_crear();
    int cant_operadores=0;
    char* ultimo_caracter= (char*)malloc(200*sizeof(char*));
    lista_t lista=lista_crear();
    char* operador= (char*)malloc(sizeof(char*));
    while(strcmp(tope(*(pila)),"(")){
        char* aux=desapilar(pila);
        if(strlen(aux)>1){   //La variable entera ya ha sido formada en alguna evaluación previa de otra subexpresión
            ultimo_caracter=aux;
            lista_adjuntar(lista,transformar_a_int(aux,strlen(aux)));
        }
        else{
            //Apilo en una pila auxiliar los números encontrados para formar la verdadera variable luego
            if((strcmp(aux,"0")==0)||(strcmp(aux,"1")==0)||(strcmp(aux,"2")==0)||(strcmp(aux,"3")==0)||(strcmp(aux,"4")==0)||(strcmp(aux,"5")==0)||(strcmp(aux,"6")==0)||(strcmp(aux,"7")==0)||(strcmp(aux,"8")==0)||(strcmp(aux,"9")==0)){
                apilar(&pila_aux,aux);
                ultimo_caracter=aux;
            }
            else{
                if((strcmp(aux,"+")==0)||(strcmp(aux,"-")==0)||(strcmp(aux,"/")==0)||(strcmp(aux,"*")==0)){
                    if(cant_operadores==0){
                        ultimo_caracter=aux;
                        operador=aux;
                        cant_operadores=1;
                        if(!pila_vacia(pila_aux)){   //Verifico si hay una variable a insertar en la lista
                            char* variable= concatenar_pila(&pila_aux);
                            lista_adjuntar(lista,transformar_a_int(variable,strlen(variable)));

                        }
                    }
                    else{
                        //Hay más de un operador con el cual evaluar la subexpresión
                        exit(EXP_MALF);
                    }
                }
                else{
                    if(strcmp(aux," ")==0){
                        //Si encuentro un espacio verifico si hay una variable contenida en la pila a ser formada
                        if(!pila_vacia(pila_aux)){
                            char* variable= concatenar_pila(&pila_aux);
                            lista_adjuntar(lista,transformar_a_int(variable,strlen(variable)));

                        }
                    }
                    else{
                        exit(OPND_INV); //Caracter inválido
                    }
                }
            }
        }
    }
    desapilar(pila);  // Desapilo el "("
    int retorno;
    if(ultimo_caracter==operador){
        if(cant_operadores==0){
                if(lista_cantidad(lista)==0){
                    exit(OPND_INV);   //La expresion está vacia o se inserto un variable que no es un entero
                }
                else{
                    exit(OPND_INV);  //La expresion no contiene operador y hay mas de un operando
            }
        }
        else{
            retorno= operar(lista, operador);
        }
    }
    else{
        exit(EXP_MALF);  //La expresión no se introdujo en notación prefija
    }

    lista_destruir(&lista);
    char* toReturn= (char*)malloc(sizeof(char*));
    sprintf(toReturn,"%d",retorno);
    return toReturn;
}

/**
 * Funcion encargada de evaluar una cadena de caracteres que representa una expresión arimetica expresada en notación prefija.
 * @param exp Cadena de caracteres que se desea evaluar.
 * @param size Tamaño de la cadena de caracteres exp.
 * @return Devuelve el resultado producido luego de evaluar aritmeticamente toda la cadena de caracteres ingresada, siempre y cuando ésta sea correcta.
 *
 */
char* evaluar(char exp[], int size){
    pila_t pila= pila_crear();
    if(!comprobar_parentesis_balanceados(exp,strlen(exp))){
        exit(EXP_MALF);
    }
    else{
        int i=0;
        char* insertar;
        char* res= (char*)malloc(200*sizeof(char*));
        while(i<size){
            if(exp[i]!=')'){
                insertar= (char*)malloc(200*sizeof(char*));
                *(insertar)=exp[i];
                apilar(&pila,insertar);
            }
            else{
                res= evaluar_aux(&pila);  //Evaluo la subexpresión denotada entre el primer paréntesis que abre ubicado en la pila y el paréntesis que cierra actual
                apilar(&pila," ");  //Separo de caracter anterior
                apilar(&pila,res);   //Apilo el resultado de la subexpresón
                apilar(&pila," ");  //Separo del caracter siguiente
                res=(char*) malloc (200*sizeof(char*));
            }
            i++;
        }
    }
    while((!pila_vacia(pila))&&(strcmp(tope(pila)," ")==0)){
        desapilar(&pila);
    }
    return tope(pila);
}
