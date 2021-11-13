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

typedef struct _rep_grafo *TGrafo;

struct _rep_grafo{
    nat cantNodos;
    nat cantAristas;
    nat maxAristas;
    TAvl* s1;
    TColCadenas s2;
};

/*funcion de hash*/
static nat funcionHash(nat n1, nat n2, nat N){
    nat res;
    res = (fmin(n1, n2) - 1)*N + (fmax(n1,n2) - 1);
    return res;
};

TGrafo crearGrafo(nat N, nat M){
    TGrafo res = new _rep_grafo;
    res->cantNodos = N;
    res->cantAristas = 0;
    res->maxAristas = M;
    res->s1 = new TAvl[N + 1];
    res->s1[0] = crearAvl();
    for (nat i = 1; i < N + 1; i++){
        res->s1[i] = crearAvl();
    }
    res->s2 = crearColCadenas(M + 1);
    return res;
};


nat cantidadVertices(TGrafo g){
    return g->cantNodos;
};


bool hayMParejas(TGrafo g){
    return g->cantAristas == g->maxAristas;
};


TGrafo hacerVecinos(nat v1, nat v2, double d, TGrafo g){
    g->s1[v1] = insertarEnAvl(v2, g->s1[v1]);
    g->s1[v2] = insertarEnAvl(v1, g->s1[v2]);
    g->cantAristas = g->cantAristas + 1;
    nat hash = funcionHash(v1, v2, g->cantNodos);
    g->s2 = insertarEnColCadenas(crearInfo(hash, d), hash % g->maxAristas,  g->s2);
    return g;
};


bool sonVecinos(nat v1, nat v2, TGrafo g){
    nat hash = funcionHash(v1, v2, g->cantNodos);
    return estaEnColCadenas(hash, hash % g->maxAristas, g->s2);
};


double distancia(nat v1, nat v2, TGrafo g){
    nat hash = funcionHash(v1,v2, g->cantNodos);
    return realInfo(infoEnColCadenas(hash, hash % g->maxAristas, g->s2));
};


TIterador vecinos(nat v, TGrafo g){
    TIterador res = enOrdenAvl(g->s1[v]);
    return res;
};


void liberarGrafo(TGrafo g){
    for (nat i = 0; i < g->cantNodos + 1; i++){
        liberarAvl(g->s1[i]);
    }
    liberarColCadenas(g->s2);
    delete [] g->s1;
    delete g; 
};