#include "set.h"
#include "../common/Common.h"

struct Node {
   Hechizo elem; // el elemento que este nodo almacena
   Node* next; // siguiente nodo de la cadena de punteros
};

struct SetSt {
   int size; // cantidad de elementos del conjunto
   Node* first; // puntero al primer elemento
};

/**
  Invariantes de representacion:
    - size es la cantidad de nodos
    - no hay nodos con hechizos repetidos
**/

/// Proposito: retorna un conjunto de hechizos vacio
/// Costo: O(1)
Set emptyS() {
   Set s = new SetSt;
    s->size = 0;
    s->first = NULL;
    return s;
}

/// Proposito: retorna la cantidad de hechizos
/// Costo: O(1)
int sizeS(Set s) {
   return s->size;
}

/// Proposito: indica si el hechizo pertenece al conjunto
/// Costo: O(h), h = cantidad de hechizos
bool belongsS(Hechizo h, Set s) {
    Node* n = s->first;
    while(n != NULL) {
        if(mismoHechizo(n->elem, h)){
            return true;
        }
        else{
            n = n->next;
        }
    }
    delete n;
    return false;
}

/// Proposito: agrega un hechizo al conjunto
/// Costo: O(h), h = cantidad de hechizos
void addS(Hechizo h, Set s) { //falta caso null
    if(not belongsS(h,s)){
        Node* n = new Node;
        n->elem = h;
        n->next = s->first;
        s->first = n;
        s->size++;
    }
}

/// Proposito: borra un hechizo del conjunto (si no existe no hace nada)
/// Costo: O(h), h = cantidad de hechizos
void removeS(Hechizo h, Set s) {
    Node* anterior = NULL;
    Node* act = s->first;

    if(belongsS(h,s)){
        string ret;
        while(act->elem != h){
            anterior = act;
            act = act->next;
        }
        if(anterior == NULL){
            s->first = act->next; //caso para ant=null act=nodo
            delete act;
        }
        else{
            anterior->next = act->next;
            delete act;
        }
        s->size = s->size-=1;
    }
}

void printS(Set s){
    Node* n = s->first;
    int i = 0;
    while(n!=NULL){
        cout<<"elemento " << i << " de lista: " << n << endl;
        n = n->next;
        i +=1;
    }
}

/// Proposito: borra toda la memoria consumida por el conjunto (pero no la de los hechizos)
/// Costo: O(n)
/// recuerda los hechizos pero borra la estructura
void destroyS(Set s) {
    Node* sig ;
    if(s->first != NULL){
        sig = s->first->next;
        while(sig != NULL){
            delete s->first;
            s->first = sig;
            sig = s->first->next;
        }
    }
}

/// Proposito: retorna un nuevo conjunto que es la union entre ambos (no modifica estos conjuntos)
/// Costo: O(h^2), h = cantidad de hechizos
Set unionS(Set s1, Set s2) {
    Set ret = emptyS();
    Node* s1fst; //= s1->first;
    Node* s2fst ;//= s1->first;

    if(s2->first == NULL){ // devuelve s1 si el otro esta vacio
        return s1;
    }

    if(s1->first == NULL){ // devuelve s2 si el otro esta vaci el nodoo
        return s2;
    }


    if(s1->first != NULL){ // asigna el nodo 1 de s1 a s1fst si es que existe el nodo
        s1fst = s1->first;
    }

    if(s2->first != NULL){ // asigna el nodo 1 de s2 a s2fst si es que existe el nodo
        s2fst = s2->first;
    }

    //if(s1 != s2){
    while(s1fst != NULL){
        addS(s1fst->elem, ret);
        s1fst = s1fst->next;
    }
    //}
    //printS(ret);

    while(s2fst != NULL){
        addS(s2fst->elem, ret);
        s2fst = s2fst->next;
    }
    //printS(ret);
    return ret;
}











