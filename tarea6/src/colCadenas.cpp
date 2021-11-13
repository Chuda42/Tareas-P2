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


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct _rep_colCadenas {
    TCadena *arr;
    nat tope;
};


TColCadenas crearColCadenas(nat M){
    TColCadenas res = new _rep_colCadenas;
    res->arr = new TCadena[M];
    for (nat i = 0; i < M; i++)
        res->arr[i]= crearCadena();
    res->tope = M;
    return res;
};


TColCadenas insertarEnColCadenas(TInfo info, nat pos, TColCadenas col){
    if (pos < col->tope){
        if (!esVaciaCadena(col->arr[pos])){
            col->arr[pos] = insertarAntes(info, inicioCadena(col->arr[pos]), col->arr[pos]);
        }else
            col->arr[pos] = insertarAlFinal(info, col->arr[pos]);
        return col;
    }else 
        return col;
};


bool estaEnColCadenas(nat dato, nat pos, TColCadenas col){
    if (!esVaciaCadena(col->arr[pos])){
        TLocalizador loc = inicioCadena(col->arr[pos]);
        while (esLocalizador(loc) && dato != natInfo(infoCadena(loc, col->arr[pos])))
            loc = siguiente(loc, col->arr[pos]);
        if (esLocalizador(loc))
            return true;
        else
            return false;
    }else
        return false;
};


TInfo infoEnColCadenas(nat dato, nat pos, TColCadenas col){
    TLocalizador loc = inicioCadena(col->arr[pos]);
    while (natInfo(infoCadena(loc, col->arr[pos])) != dato)
        loc = siguiente(loc, col->arr[pos]);
    return infoCadena(loc, col->arr[pos]);
};


TColCadenas removerDeColCadenas(nat dato, nat pos, TColCadenas col){
    TLocalizador loc = inicioCadena(col->arr[pos]);
    while (natInfo(infoCadena(loc, col->arr[pos])) != dato)
        loc = siguiente(loc, col->arr[pos]);
    col->arr[pos] = removerDeCadena(loc, col->arr[pos]);
    return col;
};


void liberarColCadenas(TColCadenas col){
    for (nat i = 0; i < col->tope; i++){
        liberarCadena(col->arr[i]);
    };
    delete [] col->arr;
    delete col;
};