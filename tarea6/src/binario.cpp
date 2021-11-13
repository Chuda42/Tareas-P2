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
#include "../include/colaBinarios.h"
#include "../include/pila.h"
#include "../include/avl.h"
#include "../include/colCadenas.h"
#include "../include/conjunto.h"



typedef struct _rep_binario *TBinario;


struct _rep_binario{
    TInfo info;
    TBinario izq;
    TBinario der;
};


TBinario crearBinario(){
    return NULL;
};


TBinario insertarEnBinario(TInfo i, TBinario b){
    if (b == NULL){
        b = new _rep_binario;
        b->info = i;
        b->der = NULL;
        b->izq = NULL;
    }else if (natInfo(i) < natInfo(b->info)){
        b->izq = insertarEnBinario(i, b->izq);
    }else if (natInfo(i) > natInfo(b->info)){
        b->der = insertarEnBinario(i, b->der);
    };
    return b;
};


TInfo mayor(TBinario b){
    TBinario aux = b;
    while (!esVacioBinario(derecho(aux))){
        aux = derecho(aux);
    };
    return aux->info;
};


/*Auxiliares para remover mayor*/
/*Retorna el nodo del anterior mayor elemento del arbol. 
Si b es NULL, retorna NULL, si b->der NULL retorna b */
static TBinario PadreMayorB (TBinario b){
    if (b == NULL)
        return NULL;
    else if (b->der == NULL)
        return b;
    else{
        while (!esVacioBinario(derecho(derecho(b)))){
            b = derecho(b);
        };
    return b;
    };
};

TBinario removerMayor(TBinario b){
    if ((b->izq == NULL) && (b->der ==NULL)){
        delete b;
        return NULL;
    }else if ((b->der == NULL) && (b->izq != NULL)){
        TBinario borrar = b;
        b = b->izq; 
        
        delete borrar;
        return b;
    }else{
        b->der = removerMayor(b->der);
        return b;
    };
};

/*Auxiliar para pararme en el nodo anterior al que voy a eliminar.
si no tiene padre retorna NULL*/
static TBinario PadreB(nat elem, TBinario b){
    TBinario aux;
    if (natInfo(b->info) == elem){
        return NULL;
    }else if (natInfo(b->info) < elem){
        aux = PadreB(elem , b->der);
    }else if (natInfo(b->info) > elem){
        aux = PadreB(elem ,b->izq);  
    };
    if (aux == NULL){
            return b;
        }else
            return aux;
};

/*Auxiliar devuelve una referencia al nodo con el mayor elemento*/
/*static TBinario MayorB(TBinario b){
    TBinario aux;
    aux = PadreMayorB(b);
    if (aux->der != NULL)
        aux = aux->der;
    return aux;
};*/


TBinario removerDeBinario(nat elem, TBinario b){
    /*Casos base, son todos sobre eleminar la raiz de b*/
    if ( natInfo(b->info) == elem){
        /*Caso base 1: b es la raiz, el izq y der son NULL*/
        if ((b->izq == NULL) && (b->der == NULL)){
            liberarInfo(b->info);
            delete b;
            return NULL;
        }
        /*Caso base 2: b es la raiz el izq es NULL y el der no*/
        else if ((b->izq == NULL) && (b->der != NULL)){
            TBinario borrar = b;
            b = b->der;
            liberarInfo(borrar->info);
            delete borrar; 
        }
        /*Caso base 3: b es la raiz el der es NULL y el izq no*/
        else if ((b->izq != NULL) && (b->der == NULL)){
            TBinario borrar = b;
            b = b->izq;
            liberarInfo(borrar->info);
            delete borrar;
            }
        /*Caso base 4: b es la raiz ni el der ni el izq son NULL*/
        else if ((b->izq != NULL) && (b->der != NULL)){
            TBinario borrar = b;
            /*Subcaso 1: b->izq es el mayor de b->izq*/
            if(b->izq->der == NULL){
                b = b->izq;
                b->der = borrar->der;
            
            }else 
            {//subcaso 2: b->izq no es el mayor de b->izq
                TBinario aux = PadreMayorB(b->izq);
                b = aux->der;
                aux->der = b->izq;
                b->izq = borrar->izq;
                b->der = borrar->der;
            };
            liberarInfo(borrar->info);
            delete borrar;
        };
    }else{
        /*Los casos recursivos*/
        if (natInfo(b->info) < elem){
            b->der = removerDeBinario(elem, b->der);
        }else if (natInfo(b->info) > elem){
            b->izq = removerDeBinario(elem, b->izq);
        };
    };
    return b;   
};
/*Auxiliar es nodo sin hijos true si no tiene subarboles y false si tiene subarboles*/
static bool esNodoSinHijos (TBinario b){
    if ((b->izq == NULL && b->der ==NULL)){
        return true;
    }else 
        return false;
};

void liberarBinario(TBinario b){
    if (b != NULL){
        liberarBinario(b->izq);
        liberarBinario(b->der);
        liberarInfo(b->info);
    };
    delete b;
};


bool esVacioBinario(TBinario b){
    if (b == NULL){
        return true;
    }else
        return false;
};
static nat absoluto(int nat1){
    if (nat1 < 0){
        return -1*nat1;
    }else
        return nat1;
}

static bool esAvlRec(TBinario b, nat &cont){
    if (b == NULL){
        return true;
    }else{
        bool res1, res2;
        nat cont1, cont2;
        cont1 = 0;
        cont2 = 0;
        res1 = esAvlRec(b->izq, cont1);
        res2 = esAvlRec(b->der, cont2);
        cont = fmax(cont1, cont2) + 1;
        if ((res1 == true) && (res2 == true) && (absoluto(cont1 - cont2) <= 1)){
            return true;
        }else 
            return false;
    };
};


bool esAvl(TBinario b){
    nat cont = 0;
    return  esAvlRec(b, cont);  
};


TInfo raiz(TBinario b){
    return b->info;
};


TBinario izquierdo(TBinario b){
    return b->izq;
};


TBinario derecho(TBinario b){
    return b->der;
};


TBinario buscarSubarbol(nat elem, TBinario b){
    TBinario res;
    if (esVacioBinario(b))
        res = NULL;
    else if (natInfo(b->info) == elem)
        res = b;
    else if (natInfo(b->info) < elem){
        res = buscarSubarbol(elem, b->der);
    }else if (natInfo(b->info) > elem){
        res = buscarSubarbol(elem, b->izq);
    };
    return res;
};


nat alturaBinario(TBinario b){
    if(b != NULL){
        return 1 + fmax(alturaBinario(b->izq), alturaBinario(b->der));
    }else
        return 0;
};


nat cantidadBinario(TBinario b){
    if (b == NULL){
        return 0;
    }else if ((b->izq == NULL) && (b->der == NULL)){
        return 1;
    }else {
        nat res = cantidadBinario(b->izq) + cantidadBinario(b->der) + 1;
        return res;
    };
};

/*Auxiliar*/
static void sumaUltimosPositivosRec(nat i, nat &cont, double &res, TBinario b){
    if ((b != NULL) && (i != 0) && (cont != i)){
        sumaUltimosPositivosRec(i, cont, res, b->der);
        if ((realInfo(b->info) > 0) && (cont != i)){
            res = res + realInfo(b->info);
            cont++;
        };
        sumaUltimosPositivosRec(i, cont, res, b->izq);
    };
};

double sumaUltimosPositivos(nat i, TBinario b){
    double res = 0;
    nat cont = 0;
    sumaUltimosPositivosRec(i, cont, res, b);
    return res;
};

/*Auxiliar*/
static TCadena linealizacionRec (TBinario b, TCadena cad){
    if (b != NULL){
        if (esNodoSinHijos(b)){
            if (esVaciaCadena(cad)){
                cad = insertarAlFinal(copiaInfo(b->info), cad);
            }else if (natInfo(b->info) < natInfo(infoCadena(finalCadena(cad), cad))){
                cad = insertarAntes(copiaInfo(b->info), finalCadena(cad), cad);
            }else if (natInfo(b->info) > natInfo(infoCadena(finalCadena(cad), cad))){
                cad =insertarAlFinal(copiaInfo(b->info), cad);
            };
        }else{
            cad = linealizacionRec(b->izq, cad);
            cad = insertarAlFinal(copiaInfo(b->info), cad);
            cad = linealizacionRec(b->der, cad);
        };
    };
    return cad;
};

TCadena linealizacion(TBinario b){
    if (b == NULL){
        return crearCadena();
    }else{
        TCadena cad = crearCadena();
        cad = linealizacionRec(b, cad);
        return cad;
    };
};
/*Auxiliar*/
static TBinario reOrg(TBinario b){
    if (b != NULL){
        TBinario aux = crearBinario(); 
        aux = insertarEnBinario(mayor(b), aux);
        b = removerMayor(b);
        aux->izq = b;
        b = aux;
    };
    return b;
};

/*Auxiliar*/
static TBinario menoresRec(double cota, TBinario b, TBinario copia){
    if (b == NULL){
        return NULL;
    }else{
        if (realInfo(b->info) < cota){
            copia = insertarEnBinario(copiaInfo(b->info), copia);
            copia->izq = menoresRec(cota, b->izq, copia->izq);
            copia->der = menoresRec(cota, b->der, copia->der);
        }else {
            copia = menoresRec(cota, b->izq, copia);
            TBinario aux = crearBinario(); 
            aux = menoresRec(cota, b->der, aux);
            if ((copia != NULL) && (aux!= NULL)){
                copia = reOrg(copia);
                copia->der = aux;
            }else if (copia == NULL){
                copia = aux;
            };
        };
        return copia;
    };
};

TBinario menores(double cota, TBinario b){
    TBinario res = crearBinario();
    res = menoresRec(cota, b, res);
    return res;
};

/*Auxiliar*/
/*La variable cont te dice en que nivel esta y cuantos guiones hay que imprimir*/
/*Cuando no es raiz se le suma uno a cont, cuando es raiz se resta 1,
esto es porque mis casos base son 1 cuando es hoja y el otro cuando es NULL*/
static void imprimirBinarioRec(TBinario b, nat cont){
    if (!esVacioBinario(b)){
        if (esVacioBinario(b->der) && esVacioBinario(b->izq)){
            for (nat i = 0; i < cont ; i++)
                printf("-");
            char * imp1 = infoATexto(raiz(b));
            printf("%s\n", imp1);
            delete [] imp1;
        }else {
            cont = cont + 1; 
            imprimirBinarioRec(derecho(b), cont);
            cont = cont - 1;  
            for (nat i = 0; i < cont; i++)
                printf("-");
            char * imp2 = infoATexto(raiz(b));
            printf("%s\n", imp2);
            delete [] imp2;
            cont = cont + 1;
            imprimirBinarioRec(izquierdo(b), cont);
        };
    };
};

void imprimirBinario(TBinario b){
    if (!esVacioBinario(b)){
        printf("\n");
        imprimirBinarioRec(b, 0);
    }else
        printf("\n");
};

/*Auxiliar*/
static TBinario binarioBalanceadoREC(ArregloNats elems, nat n1, nat n2){
    if (n2 > n1){
        TBinario res = crearBinario();
        nat auxN = floor((n2 + n1)/2);
        if (auxN == n1){
            res = insertarEnBinario(crearInfo(elems[n1], 0), res);
            res = insertarEnBinario(crearInfo(elems[n2], 0), res);
            return res;
        }else{
            res = insertarEnBinario(crearInfo(elems[auxN], 0), res);
            res->der = binarioBalanceadoREC(elems, auxN+1, n2);
            res->izq = binarioBalanceadoREC(elems, n1, auxN-1);
            return res;
            };
            return res;
    }else if (n2 == n1){
        TBinario res = crearBinario();
        res = insertarEnBinario(crearInfo(elems[n1], 0), res);
        return res;
    }else
        return NULL;
    
};


TBinario binarioBalanceado(ArregloNats elems, nat n){
    TBinario res = binarioBalanceadoREC(elems, 0, n-1);
    return res;
};


// nueva
TBinario avlABinario(TAvl a){
    if (!estaVacioAvl(a)){
        TBinario res = crearBinario();
        res = insertarEnBinario(crearInfo(raizAvl(a), 0), res);
        res->der = avlABinario(derAvl(a));
        res->izq = avlABinario(izqAvl(a));
        return res;
    }else
        return NULL;
};












