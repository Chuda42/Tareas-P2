/*50977574*/
/*Eber Manuel Rodriguez*/

#include "../include/binario.h"
#include "../include/cadena.h"
#include "../include/utils.h"
#include "../include/info.h"
#include "../include/iterador.h"
#include "../include/usoTads.h"
#include "../include/colaBinarios.h"
#include "../include/pila.h"
#include "../include/avl.h"
#include "../include/colCadenas.h"
#include "../include/conjunto.h"
#include "../include/colaDePrioridad.h"
#include "../include/grafo.h"
#include "../include/mapping.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>


typedef struct _rep_colaDePrioridad *TColaDePrioridad;
typedef TInfo *TpunteroInfo;

struct _rep_colaDePrioridad{
    nat cantMaxN;
    nat topeS1;
    TpunteroInfo *s1;
    TpunteroInfo *s2;
};

TColaDePrioridad crearCP(nat N){
    TColaDePrioridad res = new _rep_colaDePrioridad;
    res->cantMaxN = N;
    res->topeS1 = 0;
    res->s1  = new TInfo*[N + 1];
    res->s2 = new TInfo*[N + 1];
    for (nat i = 0; i < N + 1; i++){
        res->s2[i] = NULL;
    }
    return res;
};


nat rangoCP(TColaDePrioridad cp){
    return cp->cantMaxN;  
};


/*Auxiliar*/
static void swap(TpunteroInfo &i1, TpunteroInfo &i2, TColaDePrioridad &cp){
    
    /*Arreglar la estructura 2*/
    TInfo nuevo1 = crearInfo(natInfo(*(cp->s2[natInfo(*(i2))])), realInfo(*(cp->s2[natInfo(*(i1))])));
    TInfo nuevo2 = crearInfo(natInfo(*(cp->s2[natInfo(*(i1))])), realInfo(*(cp->s2[natInfo(*(i2))])));
    liberarInfo(*(cp->s2[natInfo(*(i1))]));
    liberarInfo(*(cp->s2[natInfo(*(i2))]));
    *(cp->s2[natInfo(*(i1))]) = nuevo1;
    *(cp->s2[natInfo(*(i2))]) = nuevo2;

    /*Hacer el swap en la estructura 1*/
    TpunteroInfo aux;
    aux = i1;
    i1 = i2;
    i2 = aux;
};


/*Auxiliar*/
//pre existe algo en s1[i]
//pre i>1
//i es el indice en el array donde esta el elemento que quiero filtrar
//paso i por referencia porque necesito cambiar i
static TColaDePrioridad filtradoAcendente (nat i, TColaDePrioridad cp){
    nat j = floor(i/2); //padre en el arbol
    double real1 = realInfo(*(cp->s1[i])); //real donde estoy
    while(1 <= j && real1 < realInfo(*(cp->s1[j])) /*real del padre*/){
        swap(cp->s1[i], cp->s1[j], cp);
        i = j;
        j = floor(j/2);
    }//while
   return cp;
};

/*Auxiliar*/
//pre: existe algo en s1[i]
//i indica donde estoy en el array
//i de referencia se tiene que poder cambiar
static TColaDePrioridad filtradoDecendente(nat i, TColaDePrioridad cp){
    nat j = 2*i;
    nat k = 2*i + 1;
    double real = realInfo(*(cp->s1[i]));
    while ((j < cp->topeS1 && k < cp->topeS1 )&& (real > realInfo(*(cp->s1[j]))
    || real > realInfo(*(cp->s1[k])))){
        if (realInfo(*(cp->s1[j])) < realInfo(*(cp->s1[k])) ){
            swap(cp->s1[i], cp->s1[j], cp);
            i = j;
            j = 2*i;
            k = 2*i + 1;
        }else{
            swap(cp->s1[i], cp->s1[k], cp);
            i = k;
            j = 2*i;
            k = 2*i + 1;
        }//else
    }//while
    if (j < cp->topeS1 && k > cp->topeS1 && real > realInfo(*(cp->s1[j])) ){
        swap(cp->s1[i],cp->s1[cp->topeS1], cp);
    }
    return cp;
}


TColaDePrioridad insertarEnCP(nat elem, double valor, TColaDePrioridad cp){
    /*Crear el nuevo elemento*/
    TpunteroInfo nuevo = new TInfo;
    *(nuevo) = crearInfo(elem, valor);
    /*Insertar en la estructura 1 s1*/
    cp->topeS1++;
    cp->s1[cp->topeS1] = nuevo;
    /*Insertar en la estructura 2 s2*/
    cp->s2[elem] = new TInfo;
    *(cp->s2[elem]) = crearInfo(cp->topeS1, valor);
    /*Reacomodo las estructuras*/
    if (cp->topeS1 > 1){
        nat i = floor(cp->topeS1 / 2);
        nat j = cp->topeS1;
        while (1<= i && i<= j && valor < realInfo(*(cp->s1[i]))){
            swap(cp->s1[j], cp->s1[i], cp);
            j = i;
            i = floor(i/2);
        };
    }
    return cp;
};


bool estaVaciaCP(TColaDePrioridad cp){
    return cp->topeS1 == 0;
};


nat prioritario(TColaDePrioridad cp){
    return natInfo(*(cp->s1[1]));
};


TColaDePrioridad eliminarPrioritario(TColaDePrioridad cp){
    /*Caso 1 elemento*/
    if (cp->topeS1 == 1){
        TInfo borrar1 = *(cp->s1[1]);
        TInfo borrar2 = *(cp->s2[natInfo(borrar1)]);
        /*Borro de estructura 2*/
        liberarInfo(borrar2);
        delete cp->s2[natInfo(borrar1)];
        cp->s2[natInfo(borrar1)] = NULL;
        /*Borro de estructura 1*/
        liberarInfo(borrar1);
        delete cp->s1[1];
        cp->topeS1--;
    }else{
        swap(cp->s1[1], cp->s1[cp->topeS1], cp);  //cambio el primero por el utlimo
        TInfo borrar1 = *(cp->s1[cp->topeS1]);
        TInfo borrar2 = *(cp->s2[natInfo(borrar1)]);
         /*Borro el ultimo estructura 2*/
        liberarInfo(borrar2);
        delete cp->s2[natInfo(borrar1)];
        cp->s2[natInfo(borrar1)] = NULL;
        cp = filtradoDecendente(1, cp);
        /*Borro el ultimo estructura 1*/
        liberarInfo(borrar1);
        delete cp->s1[cp->topeS1];
        cp->topeS1--;
    }
    return cp;
};


bool estaEnCP(nat elem, TColaDePrioridad cp){
    return cp->s2[elem] != NULL;
};


double prioridad(nat elem, TColaDePrioridad cp){
    return realInfo(*(cp->s2[elem]));
};


TColaDePrioridad actualizarEnCP(nat elem, double valor, TColaDePrioridad cp){
    /*Creo indices*/
    nat i = natInfo(*(cp->s2[elem]));
    TpunteroInfo borrar = cp->s1[i];
    double comparar = realInfo(*(borrar));
    nat datoNat = natInfo(*(borrar));

    /*Creo el nuevo tinfo para actualizar*/
    TpunteroInfo nuevo = new TInfo;
    *(nuevo) = crearInfo(datoNat, valor);
    cp->s1[i] = nuevo;

    TInfo nuevo2 = crearInfo(elem, valor);
    liberarInfo(*(cp->s2[elem]));
    *(cp->s2[elem]) = nuevo2;

    /*Reacomodo la estructura*/
    if (i == 1){
        if (valor <= comparar){
            liberarInfo(*(borrar));
            delete borrar;
            return cp;
        }else{
            if (2 <= cp->topeS1 && 3 <= cp->topeS1 && realInfo(*(cp->s1[2])) < realInfo(*(cp->s1[3]))){
                swap(cp->s1[1], cp->s1[2], cp);
                i = 2;
            }
            else if (2 <= cp->topeS1 && 3 <= cp->topeS1 && realInfo(*(cp->s1[2])) > realInfo(*(cp->s1[3]))){
                swap(cp->s1[1], cp->s1[3], cp);
                i = 3;
            }
            else if (2 <= cp->topeS1){
                swap(cp->s1[1], cp->s1[2], cp);
                i = 2;
            }
            cp = filtradoDecendente(i, cp);
        }
    }else if(valor < comparar){
        cp = filtradoAcendente(i, cp);
    }else if (valor > comparar){
        cp = filtradoDecendente(i, cp);
    }
    liberarInfo(*(borrar));
    delete borrar;
    return cp;
};


void liberarCP(TColaDePrioridad cp){
    if (!estaVaciaCP(cp)){
        nat j = cp->topeS1;
        for (nat i = 1; i < j + 1; i++){
            cp = eliminarPrioritario(cp);
        };
        for (nat i = 0; i < cp->cantMaxN + 1; i++){
            if (cp->s2[i] != NULL)
                liberarInfo(*(cp->s2[i]));
            delete cp->s2[i];
        }
        
    }
    delete [] cp->s1;
    delete [] cp->s2;
    delete cp;    
};