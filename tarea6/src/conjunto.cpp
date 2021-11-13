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
#include <math.h>

struct _rep_conjunto{
    nat * arr;
    nat tope;
};


TConjunto crearConjunto(){
    return NULL;
};


TConjunto singleton(nat elem){
    TConjunto res = new _rep_conjunto;
    res->arr = new nat[2];
    res->arr[0] = 1;
    res->arr[1] = elem;
    res->tope = 1;
    return res;
};


TConjunto unionDeConjuntos(TConjunto c1, TConjunto c2){
    TConjunto res;
    if (c1 != NULL  && c2 != NULL){
        res = new _rep_conjunto;
        res->arr = new nat[c1->arr[0] + c2->arr[0] + 1];
        res->tope = 0;
        res->arr[0] = 0;
        nat i = 1;
        nat j = 1;
        nat k = 1;
        while (i != c1->tope + 1 && j != c2->tope + 1){
            if (c1->arr[i] < c2->arr[j]){
                res->arr[k]= c1->arr[i];
                res->arr[0]++;
                res->tope++;
                k++;
                i++;
            }else if (c1->arr[i] > c2->arr[j]){
                res->arr[k] = c2->arr[j];
                res->arr[0]++;
                res->tope++;
                k++;
                j++;
            }else if (c1->arr[i] == c2->arr[j]){
                res->arr[k] = c1->arr[i];
                res->arr[0]++;
                res->tope++;
                k++;
                i++;
                j++;
            }
        }//while
        while (i != c1->tope + 1 && j == c2->tope + 1){
            res->arr[k] = c1->arr[i];
            res->arr[0]++;
            res->tope++;
            k++;
            i++;
        }
        while (i == c1->tope + 1 && j != c2->tope + 1){
            res->arr[k] = c2->arr[j];
            res->arr[0]++;
            res->tope++;
            k++;
            j++;
        }
    }else if (c1 == NULL && c2 != NULL){
        res = new _rep_conjunto;
        res->arr = new nat[c2->arr[0] + 1];
        res->tope = c2->tope;
        res->arr[0] = c2->arr[0];
        nat j = 1;
        nat k = 1;
        while (j != c2->tope + 1){
            res->arr[k] = c2->arr[j];
            k++;
            j++;
        }
    }else if (c1 != NULL && c2 == NULL){
        res = new _rep_conjunto;
        res->arr = new nat[c1->arr[0] + 1];
        res->tope = c1->tope;
        res->arr[0] = c1->arr[0];
        nat i = 1;
        nat k = 1;
        while (i != c1->tope + 1){
            res->arr[k] = c1->arr[i];
            k++;
            i++;
        }
    }else
        res =crearConjunto();
    return res;
};


TConjunto diferenciaDeConjuntos(TConjunto c1, TConjunto c2){
    TConjunto res;
    if (!estaVacioConjunto(c1)){
        res = new _rep_conjunto;
        res->arr = new nat[c1->arr[0] + 1];
        res->arr[0] = 0;
        res->tope = 0;
        if (!estaVacioConjunto(c2)){
            nat i = 1;
            nat j = 1;
            nat k = 1;
            while (i != c1->tope + 1 && j != c2->tope + 1){
                if (c1->arr[i] == c2->arr[j]){
                    i++;
                    j++;
                }else if (c1->arr[i] < c2->arr[j]){
                    res->arr[k] = c1->arr[i];
                    res->arr[0]++;
                    res->tope++;
                    i++;
                    k++;
                }else if (c1->arr[i] > c2->arr[j]){
                    j++;
                }
            }
            while (i!= c1->tope + 1 && j == c2->tope + 1){
                res->arr[k] = c1->arr[i];
                res->arr[0]++;
                res->tope++;
                k++;
                i++;
            }
            if (res->arr[0] == 0){
                liberarConjunto(res);
                return NULL;
            }
        }else if (c2 == NULL){
            res->arr[0] = c1->arr[0];
            res->tope = c1->tope;
            nat i = 1;
            nat k = 1;
            while (i != c1->tope + 1){
                res->arr[k] = c1->arr[i];
                i++;
                k++;
            }
        }
    }else
        res = crearConjunto();
    return res;
};


/*Auxiliar*/
//Prcondicion n1 <= n2
static bool perteneceAConjuntoREC(nat elem, nat n1, nat n2, TConjunto c){
    if (n1 == n2)
        return (c->arr[n1] == elem);
    else{
        nat mid = floor((n1 + n2)/2);
        if (c->arr[mid] == elem){
            return true;
        }else if (c->arr[mid] < elem){
            return perteneceAConjuntoREC(elem, mid+1, n2, c);
        }else if (c->arr[mid] > elem){
            if (mid == n1)
                return (c->arr[n1] == elem);
            else
                return perteneceAConjuntoREC(elem, n1, mid-1, c);
        }
    }
    return false;
};


bool perteneceAConjunto(nat elem, TConjunto c){
    if (estaVacioConjunto(c))
        return false;
    else
        return perteneceAConjuntoREC(elem, 1, c->tope, c);
};


bool estaVacioConjunto(TConjunto c){
    if (c == NULL)
        return true;
    else 
        return false;
};


nat cardinalidad(TConjunto c){
    if (c == NULL){
        return 0;
    }else
        return c->arr[0];
};


nat minimo(TConjunto c){
    return c->arr[1];
};


nat maximo(TConjunto c){
    return c->arr[c->tope];
};


TConjunto arregloAConjunto(ArregloNats elems, nat n){
    TConjunto res = new _rep_conjunto;
    res->arr = new nat[n + 1];
    res->arr[0] = n;
    res->tope = n;
    nat i = 0;
    nat j = 1;
    while (i != n  && j != n + 1){
        res->arr[j] = elems[i];
        i++;
        j++;
    }
    return res;
};

TIterador iteradorDeConjunto(TConjunto c){
    if(c == NULL)
        return reiniciarIterador(crearIterador());
    else{
        TIterador res = crearIterador();
        for(nat i = 1; i < c->tope + 1; i++){
            res = agregarAIterador(c->arr[i], res);
        }
        res = reiniciarIterador(res);
        return res;
    }
    
};


void liberarConjunto(TConjunto c){
    if(c != NULL){
        delete [] c->arr;
    }
    delete c;
};