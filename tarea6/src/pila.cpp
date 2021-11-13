/*50977574*/
/*Eber Manuel Rodriguez*/




#include <stdio.h>
#include <math.h>
#include <stdlib.h>


#include "../include/binario.h"
#include "../include/cadena.h"
#include "../include/utils.h"
#include "../include/info.h"
#include "../include/iterador.h"
#include "../include/usoTads.h"
#include "../include/pila.h"
#include "../include/colaBinarios.h"


typedef struct _rep_pila *TPila;

struct _rep_pila{
    nat tope;
    nat *dato;
    TPila sig;
};

TPila crearPila(nat tamanio){
    TPila res = new _rep_pila;
    res->tope = tamanio;
    res->sig = NULL;
    res->dato = NULL;
    return res;
};


TPila apilar(nat num, TPila p){
    TPila res;
    if (estaLlenaPila(p) == false){
        if (p->dato == NULL){
            p->dato = new nat;
            *(p->dato) = num;
            p->tope = p->tope - 1;
            res = p;
        }else{
            TPila nuevo = new _rep_pila;
            nuevo->dato = new nat;
            *(nuevo->dato) = num;
            nuevo->sig = p;
            nuevo->tope = p->tope - 1;
            p = nuevo;
            res = p;
        }
    }else 
        res = p;
    return res;
};


TPila desapilar(TPila p){
    if (estaVaciaPila(p) == false){
        if (p->sig == NULL){
            delete p->dato;
            p->dato = NULL;
            p->tope = p->tope + 1;
        }else{
            TPila borrar = p;
            p = p->sig;
            delete borrar->dato;
            delete borrar;
        };
        return p;
    }else
        return p;
};


void liberarPila(TPila p){
    while (estaVaciaPila(p)== false){
        p = desapilar(p);
    };
    delete p;
};


bool estaVaciaPila(TPila p){
    if (p == NULL || p->dato == NULL)
        return true;
    else
        return false;
};


bool estaLlenaPila(TPila p){
    if  ((p != NULL) &&(p->tope == 0))
        return true;
    else 
        return false;
};


nat cima(TPila p){
    return *(p->dato);
};