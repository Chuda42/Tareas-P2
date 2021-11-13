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

typedef struct _rep_mapping *TMapping;


struct _rep_mapping{
    TColCadenas arr;
    nat cantidad;
    nat cota;
};

static nat funcionHash(nat clave, nat M){
    return clave % M;
}

TMapping crearMap(nat M){
    TMapping res = new _rep_mapping; 
    res->arr = crearColCadenas(M);
    res->cantidad = 0;
    res->cota = M;
    return res;
};


TMapping asociarEnMap(nat clave, double valor, TMapping map){
    nat hash = funcionHash(clave, map->cota);
    map->arr = insertarEnColCadenas(crearInfo(clave, valor), hash, map->arr);
    map->cantidad++;
    return map;
};


TMapping desasociarEnMap(nat clave, TMapping map){
    nat hash = funcionHash(clave, map->cota);
    map->arr = removerDeColCadenas(clave, hash, map->arr);
    map->cantidad--;
    return map;
};


bool existeAsociacionEnMap(nat clave, TMapping map){
    nat hash = funcionHash(clave, map->cota);
    bool res = estaEnColCadenas(clave, hash, map->arr);
    return res;
};


double valorEnMap(nat clave, TMapping map){
    nat hash = funcionHash(clave, map->cota);
    double res = realInfo(infoEnColCadenas(clave, hash, map->arr));
    return res;
};


bool estaLlenoMap(TMapping map){
    return map->cantidad == map->cota;
};


void liberarMap(TMapping map){
    liberarColCadenas(map->arr);
    delete map;
};