/*50977574*/
/*Eber Manuel Rodriguez*/

#include "../include/binario.h"
#include "../include/cadena.h"
#include "../include/utils.h"
#include "../include/info.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct nodoCadena {
  TInfo dato;
  TLocalizador anterior;
  TLocalizador siguiente;
};

struct _rep_cadena {
  TLocalizador inicio;
  TLocalizador final;
};

bool esLocalizador(TLocalizador loc) {
  return loc != NULL; 
};

TCadena crearCadena() {
  TCadena res = new _rep_cadena;
  res->inicio = res->final = NULL;
  return res;
};

void liberarCadena(TCadena cad) {
  TLocalizador borrar;        //nodo auxiliar para ir eleminando
  while (cad->inicio != NULL){
    borrar = cad->inicio;
    cad->inicio = cad->inicio->siguiente;
    liberarInfo(borrar->dato);            //Libero la memoria que apunta borrar->dato, que es de tipo TInfo
    delete  borrar;                        //Libero la memoria que aputna borrar, que es de tipo TLocalizaodr
  };
  cad->final = cad->inicio;
  delete  cad;                             //Finalmente libiero la memora que apunta cad, que es de tipo TCadena
};

bool esVaciaCadena(TCadena cad) {
  return (cad->inicio == NULL);
};

TLocalizador inicioCadena(TCadena cad) {
  
  // versión que sigue la especificación
    if (esVaciaCadena(cad)) {
      return NULL;
    } else {
      return cad->inicio;
    };
};

TLocalizador finalCadena(TCadena cad) {
  if (esVaciaCadena(cad)){
    return NULL;
  } else {
    return cad->final;
  };
};

TInfo infoCadena(TLocalizador loc, TCadena cad) {
  return loc->dato;
};

TLocalizador siguiente(TLocalizador loc, TCadena cad) {
  TLocalizador res =NULL;
  if (esFinalCadena(loc, cad)){
    return res;
  }else{
  res = loc->siguiente;
  };  
  return res;
};

TLocalizador anterior(TLocalizador loc, TCadena cad) {
  TLocalizador res=NULL;
  if (esInicioCadena(loc, cad)){
    return res;
  }else{
  res = loc->anterior;
  };  
  return res;
};

bool esFinalCadena(TLocalizador loc, TCadena cad) {
  if (esVaciaCadena(cad)) {
    return false;} 
  else if ((!esVaciaCadena(cad)) && (esLocalizador(loc))){
    return (loc->siguiente == NULL);
  }else {
    return false;
    };
};

bool esInicioCadena(TLocalizador loc, TCadena cad) {
   if (esVaciaCadena(cad)) {
    return false;} else if ((!esVaciaCadena(cad)) && (esLocalizador(loc))){
      return (loc->anterior == NULL);
    }else {
      return false;
    };
};

TCadena insertarAlFinal(TInfo i, TCadena cad) {
  TLocalizador aux = new nodoCadena;
  aux->dato = i;
  aux->siguiente = NULL;
  if (esVaciaCadena(cad)){
    aux->anterior = NULL;
    cad->final  = aux;
    cad->inicio = aux;
  }else {
    cad->final->siguiente= aux;
    aux->anterior = cad->final;
    cad->final = aux;
  };
  return cad;
};

TCadena insertarAntes(TInfo i, TLocalizador loc, TCadena cad) {
  TLocalizador aux = new nodoCadena;
  aux->dato = i;
  aux->siguiente= loc;
  if (esInicioCadena(loc, cad)){
    cad->inicio = aux;
    aux->anterior = NULL;
    loc->anterior = aux;
  }else{
    aux->anterior = loc->anterior;
    loc->anterior->siguiente = aux;
    loc->anterior = aux;
  };
  return cad;
};

TCadena removerDeCadena(TLocalizador loc, TCadena cad) {
  if ((esInicioCadena(loc, cad)) && (esFinalCadena(loc, cad))){
    cad->inicio = NULL;
    cad->final = NULL;
  }else if ((esInicioCadena(loc, cad)) && !(esFinalCadena(loc, cad))){
    cad->inicio = loc->siguiente;
    loc->siguiente->anterior = NULL;
  } else if ((esFinalCadena(loc, cad)) && !(esInicioCadena(loc, cad))){
    cad->final = loc->anterior;
    loc->anterior->siguiente = NULL;
  } else{
    loc->anterior->siguiente = loc->siguiente;
    loc->siguiente->anterior = loc->anterior;
  };  
  liberarInfo(loc->dato);
  delete  loc;
  return cad;
};

void imprimirCadena(TCadena cad) {
  TLocalizador aux = cad->inicio;
  while (aux != NULL){
    char* texto = infoATexto(aux->dato);
    printf("%s", texto );
    delete [] texto;
    aux = aux->siguiente;
  };
  printf("\n");
};

TLocalizador kesimo(nat k, TCadena cad) {
  TLocalizador loc = cad->inicio;
  nat i = 1;
  if (k == 0) return NULL; 
  else{
    while ((loc != NULL) && (i != k)){
      loc = loc->siguiente;
      i++;
    };
    if (loc == NULL) {
        return NULL;
    }else {
      return loc;
    }; 
  };
};

TCadena insertarSegmentoDespues(TCadena sgm, TLocalizador loc, TCadena cad) {
  if (esVaciaCadena(sgm)){
    delete sgm;
    return cad;
  }else{
    if (esVaciaCadena(cad)){
      cad->inicio = sgm->inicio;
      cad->final = sgm->final;
    }else if (esFinalCadena(loc,cad)){
      cad->final->siguiente = sgm->inicio;
      sgm->inicio->anterior = cad->final;
      cad->final = sgm->final;
    }else {
      sgm->inicio->anterior = loc;
      sgm->final->siguiente = loc->siguiente;
      loc->siguiente->anterior = sgm->final;
      loc->siguiente = sgm->inicio;
    };
    sgm->inicio = NULL;
    sgm->final = NULL;
    delete sgm;
  return cad;
  };
};

TCadena copiarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad) {
  TCadena res = crearCadena();
  
  if (esVaciaCadena(cad)){
    return res;
  }else{
    if (desde == hasta){
      TLocalizador p = new nodoCadena;
      res->inicio = p;
      res->final = p;
      p->siguiente = NULL;
      p->anterior = NULL;
      p->dato = copiaInfo(desde->dato);
      return res;
    }else{
      TLocalizador p = new nodoCadena;
      p->anterior = NULL;
      p->dato = copiaInfo(desde->dato);
      res->inicio = p;
      TLocalizador aux = hasta;
      while ( (aux != NULL) && (aux != desde) ){
        if (aux == hasta){
          p = new nodoCadena;
          p->dato = copiaInfo(aux->dato);
          p->anterior = res->inicio;
          p->siguiente = NULL;
          res->inicio->siguiente = p;
          res->final = p;
          aux = aux->anterior;
        }else {
          p = new nodoCadena;
          p->dato = copiaInfo(aux->dato);
          p->anterior = res->inicio;
          p->siguiente = res->inicio->siguiente;
          res->inicio->siguiente = p;
          aux = aux->anterior;
        };
      };//while
      return res;
    };
  };
};

TCadena borrarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad) {
  if (esVaciaCadena(cad)){
    return cad;
  } else if (desde == hasta) {
    removerDeCadena(desde,cad);
    return cad;
  } else {
    TLocalizador aux = desde;
    while (aux != hasta){
      aux = aux->siguiente;
      removerDeCadena(desde,cad);
      desde = aux;
    };
    removerDeCadena(hasta,cad);
    desde = NULL;
    delete desde;
    return cad;
  };
};

TCadena cambiarEnCadena(TInfo i, TLocalizador loc, TCadena cad) {
  loc->dato = i;
  return cad;
};

TCadena intercambiar(TLocalizador loc1, TLocalizador loc2, TCadena cad) {
  TInfo aux;
  aux = loc1->dato;
  loc1->dato = loc2->dato;
  loc2->dato = aux;
  return cad;
};

bool localizadorEnCadena(TLocalizador loc, TCadena cad) {
  if (esVaciaCadena(cad)){
    return false;
  }else{
    TLocalizador aux = cad->inicio;
    while ((aux->siguiente != NULL) && (aux != loc)) {
      aux = aux->siguiente;
    };
    return aux == loc;
  };
};

bool precedeEnCadena(TLocalizador loc1, TLocalizador loc2, TCadena cad) {
  bool bool_aux1 = localizadorEnCadena(loc1,cad);
  bool bool_aux2 = localizadorEnCadena(loc2,cad);

  if ( bool_aux1 && bool_aux2 ){
    if (loc1 == loc2){
      return true;
    } else {
      TLocalizador aux = loc1;
      while ( (aux != loc2) && (aux->siguiente != NULL) ){
        aux = aux->siguiente;
      };//while
      return aux == loc2;
    };//2do if else
  } else {
    return false;
  };//1er if else
};

TLocalizador siguienteClave(nat clave, TLocalizador loc, TCadena cad) {
  if (esVaciaCadena(cad) || (loc == NULL)){
    return NULL;
  } else{
    TLocalizador aux = loc;
    while ( (aux != NULL) && (clave != natInfo(aux->dato))){
      aux = aux->siguiente;
    };
    return aux;
  };
};

TLocalizador anteriorClave(nat clave, TLocalizador loc, TCadena cad) {
  if (esVaciaCadena(cad) || (loc == NULL)){
    return NULL;
  } else{
    TLocalizador aux = loc;
    while ( (aux != NULL) && (clave != natInfo(aux->dato))){
      aux = aux->anterior;
    };
    return aux;
  };
};

TLocalizador menorEnCadena(TLocalizador loc, TCadena cad) {
  if (esVaciaCadena(cad) || (loc == NULL)){
    return NULL;
  }else {
    TLocalizador aux = loc;
    TLocalizador res = aux;
    nat min = natInfo(aux->dato);
    while (aux != NULL){
      if (natInfo(aux->dato) < min){
        min = natInfo(aux->dato);
        res = aux;
      };
      aux = aux->siguiente;
    };
    return res;
  };
};
