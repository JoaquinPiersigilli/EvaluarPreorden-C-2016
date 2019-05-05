#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED

typedef struct pila {
char* elemento;
struct pila* proximo_elemento;
} *pila_t;

//Signatures
pila_t pila_crear();

char* tope(pila_t pila);

char* desapilar(pila_t* pila);

int apilar(pila_t* pila, char* str);

int pila_vacia(pila_t pila);

#endif // PILA_H_INCLUDED

