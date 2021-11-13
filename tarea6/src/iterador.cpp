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



typedef struct _rep_iterador *TIterador;


/*Lo modelo como un struct que tiene un estado de reinicio esto marca si se puede agregar elementos (false) o
no se puede (true), el elemento nat que guarda (elem), la posicion donde se encuentra en la colección (pos),
información sobre el siguiente en la colección (sig) e información sobre el primero de todos de la colección*/
struct _rep_iterador{
    bool reinicio;
    nat *elem;
    TIterador sig;
    TIterador inicio;
    nat pos;
};



TIterador crearIterador(){
    TIterador iter = new _rep_iterador;
    iter->reinicio = false;
    iter->elem     = NULL;
    iter->sig      = NULL;
    iter->inicio   = NULL;
    iter->pos      = 0;
    return iter;
};


TIterador agregarAIterador(nat elem, TIterador iter){
    if (iter->reinicio == false){
        if (iter->pos == 0){
            iter->reinicio = false;
            iter->elem     = new nat;
            *(iter->elem)  = elem;
            iter->sig      = NULL;
            iter->inicio   = iter;
            iter->pos      = 1;
        }else{
            iter->reinicio = true;
            iter->sig = crearIterador();

            iter->sig->reinicio    = false;
            iter->sig->elem        = new nat;
            *(iter->sig->elem)     = elem;
            iter->sig->sig         = NULL;
            iter->sig->inicio      = iter->inicio;
            iter->sig->pos         = iter->pos + 1;

            iter = iter->sig; 
        };
        return iter;
    }else
        return iter;
};


TIterador reiniciarIterador(TIterador iter){
    if ((iter->pos == 0) && (iter->reinicio == false)){
        iter->reinicio = true;  //No se le puede agregar mas nada
    }else if ((iter->pos == 0) && (iter->reinicio == true)){
        if (iter->inicio != NULL)
            iter = iter->inicio;
    }else if ((iter->pos != 0) && (iter->reinicio == true)){
        iter = iter->inicio;
    }else if ((iter->pos != 0) && (iter->reinicio== false)){
        iter->reinicio = true;  //NO se le peude agregar mas nada
        
        /*Creo un elemento despues del ultimo que no esta definido pero tenga un puntero a inicio, cuando 
        se intente acceder al siguiete del ultimo va a decir indefinido pero se podra volver al inicio*/
        iter->sig           = crearIterador();
        iter->sig->reinicio = true;
        iter->sig->inicio   = iter->inicio;
        iter->sig->pos      = 0;
        iter                = iter->inicio;

    }; 
    return iter;
};


TIterador avanzarIterador(TIterador iter){
    if (estaDefinidaActual(iter)){
        iter = iter->sig;
    };
    return iter;
};


nat actualEnIterador(TIterador iter){
    return *(iter->elem);
};


bool estaDefinidaActual(TIterador iter){
   return !((iter->reinicio == false) || (iter->pos == 0));
};
/*Solucion de la anterior diferente
if ((iter->reinicio== fasle) || (iter->pos == 0)){
    return false;
} else if ((iter->reinicio == true) && (iter->pos != 0)){
    return true;0
}
*/


void liberarIterador(TIterador iter){
    TIterador borrar;
    if (iter->inicio == NULL){
        borrar = iter;
        delete borrar;
    }else{
        if (estaDefinidaActual(iter) == false)
            iter = reiniciarIterador(iter);
        else 
            iter = iter->inicio;
        while (iter->pos != 0){
            borrar = iter;
            iter = iter->sig;
            delete borrar->elem;
            delete borrar;
        };
        borrar = iter;
        delete borrar;
    };
};







