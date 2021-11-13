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



bool pertenece(nat elem, TCadena cad){
    if (!esVaciaCadena(cad)){
        TLocalizador aux = inicioCadena(cad);
        while ((aux != NULL) && (natInfo(infoCadena(aux, cad)) != elem)){
            aux = siguiente(aux, cad);
        };
        return aux != NULL;
    }else {
        return false;
    };
};


nat longitud(TCadena cad){
    if (!esVaciaCadena(cad)){
        TLocalizador aux = inicioCadena(cad);
        nat cont = 0;
        while (aux != NULL){
            aux = siguiente(aux, cad);
            cont += 1;
        };
        return cont;
    }else{
        return 0;
    };
};


bool estaOrdenadaPorNaturales(TCadena cad){
    if (!esVaciaCadena(cad)){
        TLocalizador aux = inicioCadena(cad);
        while ( (siguiente(aux, cad) != NULL) && (natInfo(infoCadena(aux,cad))<=natInfo(infoCadena(siguiente(aux, cad), cad))) ){
            aux = siguiente(aux, cad);
        };
        return siguiente(aux, cad) == NULL;
    }else {
        return true;
    };
};


bool hayNatsRepetidos(TCadena cad){
    if (!esVaciaCadena(cad)){
        TLocalizador aux1 = inicioCadena(cad);
        TLocalizador aux2;
        bool aux3 = true;
        while ((aux1 != NULL) && (aux3)){
            aux2 = siguiente(aux1, cad);
            while ((aux2 != NULL) && 
            (natInfo(infoCadena(aux1, cad)) != natInfo(infoCadena(aux2, cad)))){
                aux2 = siguiente(aux2, cad);
            };
            if (aux2 == NULL){
                aux2 = anterior(aux1, cad);
                while ((aux2 != NULL) && 
                (natInfo(infoCadena(aux1, cad)) != natInfo(infoCadena(aux2, cad)))){
                    aux2 = anterior(aux2, cad);
                };
            } else {
                aux3 = false;
            };
            if (aux2 == NULL){
                aux1 = siguiente(aux1, cad);
            };
        };
        return aux1 != NULL;
    } else 
    return false;
};


bool sonIgualesCadena(TCadena c1, TCadena c2){
    if ((esVaciaCadena(c1)) && (esVaciaCadena(c2))){
        return true;
    } else if (((esVaciaCadena(c1)) && !(esVaciaCadena(c2))) ||
    (!(esVaciaCadena(c1)) && (esVaciaCadena(c2)))){
        return false;
    }else {
        bool res = true;
        TLocalizador aux1 = inicioCadena(c1);
        TLocalizador aux2 = inicioCadena(c2);
        while ((aux1 != NULL) && (aux2 != NULL) &&
        (natInfo(infoCadena(aux1,c1))==natInfo(infoCadena(aux2,c2))) && 
        (realInfo(infoCadena(aux1,c1))==realInfo(infoCadena(aux2,c2)))){

            aux1 = siguiente(aux1,c1);
            aux2 = siguiente(aux2,c2);
        };
        if ((aux1 == NULL) && (aux2 == NULL)){
            res = true;
        }else res= false;
        return res;
    };
};


TCadena concatenar(TCadena c1, TCadena c2){
    TCadena res;
    TCadena copia_c1 = copiarSegmento(inicioCadena(c1), finalCadena(c1), c1);
    TCadena copia_c2 = copiarSegmento(inicioCadena(c2), finalCadena(c2), c2);
    TLocalizador aux = finalCadena(copia_c1);
    insertarSegmentoDespues(copia_c2, aux, copia_c1 );
    res = copia_c1;
    return res;
};


TCadena ordenar(TCadena cad){
    if (!esVaciaCadena(cad)){
        TLocalizador aux = inicioCadena(cad);;
        while (aux != NULL){
            intercambiar(aux, menorEnCadena(aux,cad), cad);
            aux = siguiente(aux,cad);
        };
        return cad;
    }else
    return cad;
};


TCadena cambiarTodos(nat original, nat nuevo, TCadena cad){
    if (!esVaciaCadena(cad)){
        TLocalizador aux = siguienteClave(original, inicioCadena(cad), cad);
        while (aux != NULL){
            aux = siguienteClave(original, aux, cad);
            if (aux != NULL){
                TInfo aux_info = crearInfo(nuevo, realInfo(infoCadena(aux, cad)));
                liberarInfo(infoCadena(aux, cad));
                cambiarEnCadena(aux_info, aux, cad);
                aux = siguiente(aux, cad);
            };
        };
        return cad;
    }else
    return cad;
};


TCadena subCadena(nat menor, nat mayor, TCadena cad){
    TCadena res = crearCadena();
    if (!esVaciaCadena(cad)){
        TLocalizador aux = siguienteClave(menor, inicioCadena(cad), cad);
        TInfo auxi = NULL;
        while ((aux != NULL) && (natInfo(infoCadena(aux,cad)) <= mayor) ){
            auxi = copiaInfo(infoCadena(aux, cad));
            insertarAlFinal(auxi, res);
            aux = siguiente(aux, cad);
        };
        return res;
    }else
    return res;
};

/*Auxiliar*/
static TCadena nivelEnBinarioRec(nat l, TBinario b, nat cont, TCadena cad){
    if (!esVacioBinario(b)){
        if (cont == l){
            cad = insertarAlFinal(copiaInfo(raiz(b)), cad);
        }
        cad = nivelEnBinarioRec(l, izquierdo(b), cont + 1, cad);
        cad = nivelEnBinarioRec(l, derecho(b), cont + 1, cad);
    }
    return cad;
};

TCadena nivelEnBinario(nat l, TBinario b){
    TCadena cad = crearCadena();
    cad = nivelEnBinarioRec(l, b, 1, cad);
    return cad;
};

/*Auxiliar*/
static bool esCaminoRec(TCadena c, TBinario b, TLocalizador loc){
    if (((loc == NULL)&&(esVacioBinario(b)))){
        return true;
    }else if ((esVacioBinario(b) && !esVaciaCadena(c)) || (!esVacioBinario(b) && esVaciaCadena(c)) ||
    (loc == NULL && (!esVacioBinario(b)))){
        
        return false;

    }else{;
        if ( (natInfo(infoCadena(loc,c)) == natInfo(raiz(b)))){
            loc = siguiente(loc, c);
            if (loc == NULL && (esVacioBinario(izquierdo(b))&& esVacioBinario(derecho(b)))){
                return true;
            }else if (loc == NULL && ((!esVacioBinario(izquierdo(b))&& esVacioBinario(derecho(b))) || 
            (esVacioBinario(izquierdo(b))&& !esVacioBinario(derecho(b)))))
                return false;
            return (esCaminoRec(c, izquierdo(b), loc) || esCaminoRec(c, derecho(b), loc));
        };
        return false;
    };
};

bool esCamino(TCadena c, TBinario b){
    TLocalizador loc = inicioCadena(c);
    return esCaminoRec(c, b, loc);
};


nat cantidadEnIterador(TIterador it){
    nat cont = 0;
    it = reiniciarIterador(it);
    while (estaDefinidaActual(it)){
        it = avanzarIterador(it);
        cont++;
    }
    return cont;
};


TIterador enAlguno(TIterador a, TIterador b){
    TIterador res = crearIterador();
    a = reiniciarIterador(a);
    b = reiniciarIterador(b);
    while (estaDefinidaActual(a) && estaDefinidaActual(b)){
        if (actualEnIterador(a) < actualEnIterador(b)){
            res = agregarAIterador(actualEnIterador(a), res);
            a = avanzarIterador(a);
        }else if ( actualEnIterador(a) > actualEnIterador(b)){
            res = agregarAIterador(actualEnIterador(b), res);
            b = avanzarIterador(b);
        }else if (actualEnIterador(a) == actualEnIterador(b)){
            res = agregarAIterador(actualEnIterador(a), res);
            a = avanzarIterador(a);
            b = avanzarIterador(b);
        };
    };
    while (estaDefinidaActual(b)){
        res = agregarAIterador(actualEnIterador(b), res);
        b = avanzarIterador(b);
    };
    while (estaDefinidaActual(a)){
        res = agregarAIterador(actualEnIterador(a), res);
        a = avanzarIterador(a);
    };
    res = reiniciarIterador(res);
    return res;
};


TIterador soloEnA(TIterador a, TIterador b){
    TIterador res = crearIterador();
    a = reiniciarIterador(a);
    b = reiniciarIterador(b);
    while (estaDefinidaActual(a) && estaDefinidaActual(b)){
        if (actualEnIterador(a) < actualEnIterador(b)){
            res = agregarAIterador(actualEnIterador(a), res);
            a = avanzarIterador(a);
        }else if (actualEnIterador(a) > actualEnIterador(b)){
            b = avanzarIterador(b);
        }else if (actualEnIterador(a) == actualEnIterador(b)){
            b = avanzarIterador(b);
            a = avanzarIterador(a);
        };
    };
    while (estaDefinidaActual(a)){
        res = agregarAIterador(actualEnIterador(a), res);
        a = avanzarIterador(a);
    };
    res = reiniciarIterador(res);
    return res;
};

/*Auxiliar*/
/*static TColaBinarios ColaPorNiveles (TBinario b, TColaBinarios cola){
    if (!esVacioBinario(b)){
        cola = encolar(b, cola);
        return cola;
    }else 
        return cola;
};*/

/*Auxiliar, precondicion cola no vacia y al principio tiene que entrar con un binario y separador despues*/
static TCadena recorridaPorNivelesREC(TColaBinarios cola,TCadena cad, TBinario separador){
    if (!estaVaciaColaBinarios(cola)){
        if (!(separador == frente(cola))){
            while (frente(cola) != separador){
                TBinario b = frente(cola);
                TBinario izq = izquierdo(frente(cola));
                TBinario der = derecho(frente(cola));
                cad = insertarAlFinal (copiaInfo(raiz(b)), cad);
                cola = desencolar(cola);
                if (!esVacioBinario(der))
                    cola = encolar(der, cola);
                if (!esVacioBinario(izq))
                    cola = encolar(izq, cola);
            }
            cad = recorridaPorNivelesREC(cola, cad, separador);
            return cad;
        }else{
            cola = desencolar(cola);
            if (!estaVaciaColaBinarios(cola)){
                cola = encolar(separador, cola);
                cad = insertarAlFinal(copiaInfo(raiz(separador)), cad);
                cad = recorridaPorNivelesREC(cola, cad, separador);
            };
            return cad;
        };
    }else
        return cad;
};

TIterador recorridaPorNiveles(TBinario b){
    if (!esVacioBinario(b)){
        TColaBinarios cola = crearColaBinarios();
        TBinario separador = crearBinario();
        TCadena cad = crearCadena();
        TIterador res = crearIterador();
        TLocalizador aux;


        separador = insertarEnBinario(crearInfo(UINT_MAX, 0), separador);
        cola = encolar(b, cola);
        cola = encolar(separador, cola);
        cad = recorridaPorNivelesREC(cola, cad, separador);
        aux = finalCadena(cad);
        while (esLocalizador(aux)){
            res = agregarAIterador(natInfo(infoCadena(aux, cad)), res);
            aux = anterior(aux, cad);
        };

        liberarCadena(cad);
        liberarBinario(separador);
        liberarColaBinarios(cola);
        return res;
    }else 
        return crearIterador();
};

// nueva
TConjunto interseccionDeConjuntos(TConjunto c1, TConjunto c2){
    if ((!estaVacioConjunto(c1) && estaVacioConjunto(c2)) ||
    (estaVacioConjunto(c1) && !estaVacioConjunto(c2)) ||
    (estaVacioConjunto(c1) && estaVacioConjunto(c2)))
        return crearConjunto();
    else{
        TConjunto u = unionDeConjuntos(c1, c2);
        TConjunto soloC1 = diferenciaDeConjuntos(c1, c2);
        TConjunto soloC2 = diferenciaDeConjuntos(c2, c1);
        TConjunto NoUnion = unionDeConjuntos(soloC1, soloC2);
        TConjunto res = diferenciaDeConjuntos(u, NoUnion);
        liberarConjunto(u);
        liberarConjunto(soloC1);
        liberarConjunto(soloC2);
        liberarConjunto(NoUnion);
        return res;
    }
};

