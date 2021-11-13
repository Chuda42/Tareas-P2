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

struct _rep_avl {
    nat info;
    nat altura;
    nat cantidad;
    TAvl der;
    TAvl izq;
};


TAvl crearAvl(){
    return NULL;
};


bool estaVacioAvl(TAvl avl){
    if (avl == NULL)
        return true;
    else
        return false;
};

/*Auxiliar*/
static TAvl rotacionSimpleIzq(TAvl avl){
    TAvl A, B, C, L, K;
    K = avl;
    L = K->izq;
    A = L->izq;
    B = L->der;
    C = K->der;

    K->izq = B;
    L->der = avl;

    if (B != NULL && C != NULL){
        K->altura = fmax(B->altura, C->altura) + 1;
        K->cantidad = C->cantidad + B->cantidad + 1;
    }
    else if (B != NULL && C == NULL){
        K->altura = B->altura + 1;
        K->cantidad = B->cantidad + 1;
    }
    else if (B == NULL && C!= NULL){
        K->altura = C->altura + 1;
        K->cantidad = C->cantidad + 1;
    }
    else{ 
        K->altura = 1;
        K->cantidad =  1;
    };
    if (A != NULL){
        L->altura = fmax(K->altura, A->altura) + 1;
        L->cantidad = A->cantidad + K->cantidad + 1;
    }
    else{
        L->altura = K->altura + 1;
        L->cantidad = K->cantidad + 1;
    };
    avl = L;
    return avl;

};
/*Auxiliar*/
static TAvl rotacionSimpleDer(TAvl avl){
    TAvl A, B, C, L, K;
    K = avl;
    L = K->der;
    A = K->izq;
    B = L->izq;
    C = L->der;

    K->der = B;
    L->izq = K;

    if (A != NULL && B!= NULL){
        K->altura = fmax(A->altura, B->altura) + 1;
        K->cantidad = A->cantidad + B->cantidad + 1;
    }
    else if (A != NULL && B == NULL){
        K->altura = A->altura + 1;
        K->cantidad = A->cantidad + 1;
    }
    else if (A== NULL && B != NULL){
        K->altura = B->altura + 1;
        K->cantidad = B->cantidad + 1;
    }
    else {
        K->altura = 1;
        K->cantidad = 1;
    };
    if (C != NULL){
        L->altura = fmax(C->altura, K->altura) + 1;
        L->cantidad = C->cantidad + K->cantidad + 1;
    }
    else{
        L->altura = K->altura + 1;
        L->cantidad = K->cantidad + 1;
    }
    avl = L;
    return avl;

};

/*Auxiliar*/
static TAvl rotacionDobleIzq(TAvl avl){
    TAvl L, K, M, A, B, C, D;
    L = avl;
    K = avl->izq;
    M = K->der;
    A = K->izq;
    B = M->izq;
    C = M->der;
    D = L->der;

    M->izq = K;
    M->der = L;
    K->der = B;
    L->izq = C;
    if (A != NULL && B != NULL){
        K->altura = fmax(A->altura, B->altura) + 1;
        K->cantidad = A->cantidad + B->cantidad + 1;
    }
    else if(A != NULL && B == NULL){
        K->altura = A->altura + 1;
        K->cantidad = A->cantidad + 1;
    }
    else if(A == NULL && B != NULL){
        K->altura = B->altura + 1;
        K->cantidad = B->cantidad + 1;
    }    
    else {
        K->altura = 1;
        K->cantidad = 1;
    };
    if (C != NULL && D != NULL){
        L->altura = fmax(C->altura, D->altura) + 1;
        L->cantidad = C->cantidad + D->cantidad + 1;
    }
    else if (C != NULL && D == NULL){
        L->altura = C->altura + 1;
        L->cantidad = C->cantidad + 1;
    }
    else if (C == NULL && D != NULL){
        L->altura = D->altura + 1;
        L->cantidad = D->cantidad + 1;
    }
    else {
        L->altura = 1;
        L->cantidad = 1;
    };
    M->altura = fmax(K->altura, L->altura) + 1;
    M->cantidad = K->cantidad + L->cantidad + 1;    
    avl = M;
    return avl;

};

/*Auxiliar*/
static TAvl rotacionDobleDer(TAvl avl){
TAvl L, K, M, A, B, C, D;
    L = avl;
    K = avl->der;
    M = K->izq;
    A = L->izq;
    B = M->izq;
    C = M->der;
    D = K->der;

    M->izq = L;
    M->der = K;
    K->izq = C;
    L->der = B;
    
    if (C != NULL && D != NULL){
        K->altura = fmax(C->altura, D->altura) + 1;
        K->cantidad = C->cantidad + D->cantidad + 1;
    }
    else if (C != NULL && D == NULL){
        K->altura = C->altura + 1;
        K->cantidad = C->cantidad + 1;
    }
    else if (C == NULL && D != NULL){
        K->altura = D->altura + 1;
        K->cantidad = D->cantidad + 1;
    }
    else {
        K->altura = 1;
        K->cantidad = 1;
    };
    if (A != NULL && B != NULL){
        L->altura = fmax(A->altura, B->altura) + 1;
        L->cantidad = A->cantidad + B->cantidad + 1;
    }
    else if(A != NULL && B == NULL){
        L->altura = A->altura + 1;
        L->cantidad = A->cantidad + 1;
    }
    else if(A == NULL && B != NULL){
        L->altura = B->altura + 1;
        L->cantidad = B->cantidad + 1;
    }
    else {
        L->altura = 1;
        L->cantidad = 1;
    }
    M->altura = fmax(K->altura, L->altura) + 1;
    M->cantidad = K->cantidad + L->cantidad + 1;
    avl = M;
    return avl;
};

static nat absoluto(int nat1){
    if (nat1 < 0){
        return -1*nat1;
    }else
        return nat1;
}

TAvl insertarEnAvl(nat elem, TAvl avl){
    //inserto el elemento en el arbol de manera recursiva
    if (estaVacioAvl(avl)){
        avl = new _rep_avl;
        avl->info = elem;
        avl->altura = 1;
        avl->cantidad = 1;
        avl->izq = NULL;
        avl->der = NULL;
    }else{
        if (elem > avl->info){
            //inserto el elemento
            avl->der = insertarEnAvl(elem, avl->der);
            avl->cantidad++;
        }else if (elem < avl->info){
            //inserto el elemento
            avl->izq = insertarEnAvl(elem, avl->izq);
            avl->cantidad++;
        };
        if (!estaVacioAvl(avl->der) && !estaVacioAvl(avl->izq))
            avl->altura = fmax(avl->der->altura, avl->izq->altura) + 1;
        else if (!estaVacioAvl(avl->der) && estaVacioAvl(avl->izq))
            avl->altura = avl->der->altura + 1;
        else if (estaVacioAvl(avl->der) && !estaVacioAvl(avl->izq))
            avl->altura = avl->izq->altura + 1;
        else 
            avl->altura = 1;

        //reacomodo el arbol
        if (avl->izq != NULL && avl->der != NULL){
            if (absoluto(avl->izq->altura - avl->der->altura) > 1 ){
                
                //Vengo de insertar a la derecha
                if (avl->der->altura > avl->izq->altura){

                    //puede que tenga que insertar doble o simple
                    if (elem > avl->info && elem < avl->der->info ){
                        avl = rotacionDobleDer(avl);
                    }else{
                        avl = rotacionSimpleDer(avl);
                    }
                
                //Vengo de insertar a la izquierda
                }else if (avl->der->altura < avl->izq->altura){
                    
                    //Puede que tenga que insertar doble o simple
                    if (elem < avl->info && elem > avl->izq->info){
                        avl = rotacionDobleIzq(avl);
                        
                    }else{
                        avl = rotacionSimpleIzq(avl);
                    };
                };
            };
        }else if (avl->izq == NULL && avl->der != NULL){
            if (avl->der->altura >= 2){
                if (elem > avl->info && elem < avl->der->info ){
                    avl = rotacionDobleDer(avl);
                }else{
                    avl = rotacionSimpleDer(avl);
                };
            };
        }else if (avl->izq != NULL && avl->der == NULL){
            if (avl->izq->altura >= 2){
                if (elem < avl->info && elem > avl->izq->info){
                        avl = rotacionDobleIzq(avl);
                        
                    }else{
                        avl = rotacionSimpleIzq(avl);
                    };
            };
        };
    };
    return avl;
};


TAvl buscarEnAvl(nat elem, TAvl avl){
    if (!estaVacioAvl(avl)){
        if (avl->info == elem){
            return avl;
        }else if (avl->info < elem){
            return buscarEnAvl(elem, avl->der);
        }else if (avl->info > elem){
            return buscarEnAvl(elem, avl->izq);
        }else
            return NULL;
    }else
        return NULL;
};


nat raizAvl(TAvl avl){
    return avl->info;
};


TAvl izqAvl(TAvl avl){
    return avl->izq;
};


TAvl derAvl(TAvl avl){
    return avl->der;
};


nat cantidadEnAvl(TAvl avl){
    if (avl == NULL)
        return 0;
    else
        return avl->cantidad;
};


nat alturaDeAvl(TAvl avl){
    if (estaVacioAvl(avl))
        return 0;
    else 
        return avl->altura;
};

/*Auxiliar*/
static TIterador enOrdenAvlREC(TAvl avl, TIterador iter){
    if (avl != NULL){
        iter = enOrdenAvlREC(avl->izq, iter);
        iter = agregarAIterador(raizAvl(avl), iter);
        iter = enOrdenAvlREC(avl->der, iter);
        return iter;
    };
    return iter;
}

TIterador enOrdenAvl(TAvl avl){
    TIterador res = crearIterador();
    res = enOrdenAvlREC(avl, res);
    res = reiniciarIterador(res);
    return res;
};


/*Auxiliar*/
static TAvl arregloAAvlRec (ArregloNats elems, nat n1, nat n2, nat &h){
    if (n2 > n1){
        TAvl res = crearAvl();
        nat auxN = floor((n2 + n1)/2);
        if (auxN == n1){
            res = insertarEnAvl(elems[n1], res);
            res = insertarEnAvl(elems[n2], res);
            return res;
        }else{
            res = insertarEnAvl(elems[auxN], res);
            res->der = arregloAAvlRec(elems, auxN+1, n2, h);
            res->izq = arregloAAvlRec(elems, n1, auxN-1, h);
            res->altura = fmax(alturaDeAvl(res->der), alturaDeAvl(res->izq)) + 1;
            res->cantidad = cantidadEnAvl(res->der) + cantidadEnAvl(res->izq) + 1;
            return res;
            };
            return res;
    }else if (n2 == n1){
        TAvl res = crearAvl();
        res = insertarEnAvl(elems[n1], res);
        return res;
    }else
        return NULL;
    
}; 

TAvl arregloAAvl(ArregloNats elems, nat n){
    nat h = 1;
    TAvl res = arregloAAvlRec(elems, 0, n-1, h);
    return res;
};

/*Auxiliar*/
static TAvl avlMinREC(nat h, TAvl avl, nat &i){
    if (h == 1){
        avl = insertarEnAvl(i, avl);
        i++;
    }else if (h == 2){
        avl = insertarEnAvl(i, avl);
        i++;
        avl = insertarEnAvl(i, avl);
        i++;
        avl = rotacionSimpleDer(avl);
        return avl;
    }else{
        TAvl izq, der;
        izq = crearAvl();
        der = crearAvl();
        izq = avlMinREC(h - 1 ,izq, i);
        avl = insertarEnAvl(i, avl);
        i++;
        der = avlMinREC(h - 2, der, i);
        avl->izq = izq;
        avl->der = der;
        return avl;
    }
    return avl;
};

TAvl avlMin(nat h){
    nat i = 1;
    TAvl res =crearAvl();
    res = avlMinREC(h, res, i);
    return res;
};


void liberarAvl(TAvl avl){
    if (avl != NULL){
        liberarAvl(avl->izq);
        liberarAvl(avl->der);
    };
    delete avl;
};