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

typedef struct _rep_colaBinarios *TColaBinarios;
typedef struct repNodoCadBinarios *TNodoCadBin;

struct _rep_colaBinarios{
    TNodoCadBin ultimo;  //es el ultimo en ingresar a la cola, el que esta atras
    TNodoCadBin primero; //es el que esta primero en la cola, el de adelante
    
};

struct repNodoCadBinarios{
    TBinario info;
    TNodoCadBin sig;
    TNodoCadBin ant;
};

TColaBinarios crearColaBinarios(){
    TColaBinarios res = new _rep_colaBinarios;
    res->ultimo  = NULL;
    res->primero = NULL;
    return res;
};

TColaBinarios encolar(TBinario b, TColaBinarios c){
    TNodoCadBin nuevo = new repNodoCadBinarios;
    nuevo->info = b;
    if (estaVaciaColaBinarios(c)){
        nuevo->sig = NULL;
        nuevo->ant = NULL;
        c->ultimo  = nuevo;
        c->primero = nuevo;
    }else{
        c->ultimo->ant = nuevo;
        nuevo->sig     = c->ultimo;
        nuevo->ant     = NULL;
        c->ultimo      = nuevo;
    }
    return c;
};

TColaBinarios desencolar(TColaBinarios c){
    if (!estaVaciaColaBinarios(c)){
        TNodoCadBin borrar;
        borrar = c->primero;
        c->primero = borrar->ant;
        if (c->ultimo == borrar)
            c->ultimo = NULL;
        delete borrar;
    }
    return c;
};

void liberarColaBinarios(TColaBinarios c){
    while (!estaVaciaColaBinarios(c)){
        c = desencolar(c);  
    };
    delete c;
};

bool estaVaciaColaBinarios(TColaBinarios c){
    return (c->primero == NULL && c->ultimo == NULL);
};

TBinario frente(TColaBinarios c){
    return c->primero->info;
};
