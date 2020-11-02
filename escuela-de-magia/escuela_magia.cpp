#include "escuela_magia.h"
#include "../common/Common.h"

struct EscuelaDeMagiaSt {
   Set hechizos; // set de hechizos
   Map nombreMago; // map asociando nombres con magos
   MaxHeap magos; // max heap de magos
};

/// Propósito: Devuelve una escuela vacía.
/// O(1)
EscuelaDeMagia fundarEscuela() {
   EscuelaDeMagia ret = new EscuelaDeMagiaSt;
   ret->hechizos = emptyS();
   ret->nombreMago = emptyM();
   ret->magos = emptyH();
   return ret;
}

/// Propósito: Indica si la escuela está vacía.
/// O(1)
bool estaVacia(EscuelaDeMagia m) {
   return isEmptyH(m->magos);
}

/// Propósito: Incorpora un mago a la escuela (si ya existe no hace nada).
/// O(log m)
void registrar(string nombre, EscuelaDeMagia m) {
    if(lookupM(nombre, m->nombreMago) == NULL){
        Mago mago = crearMago(nombre);
        //cout<<"-se creo el mago"<<endl;

        assocM(nombre, mago, m->nombreMago);
        //cout<<"-se agrego al map"<<endl;

        insertH(mago, m->magos);
        //cout<<"-se incerto en la heap"<<endl<<endl;
    }
}

/// Propósito: Devuelve los nombres de los magos registrados en la escuela.
/// O(m)
vector<string> magos(EscuelaDeMagia m) {
   return domM(m->nombreMago);
}

/// Propósito: Devuelve los hechizos que conoce un mago dado.
/// Precondición: Existe un mago con dicho nombre.
/// O(log m)
Set hechizosDe(string nombre, EscuelaDeMagia m) {
    return hechizosMago(lookupM(nombre, m->nombreMago));
}

/// Propósito: Dado un mago, indica la cantidad de hechizos que la escuela ha dado y él no sabe.
/// Precondición: Existe un mago con dicho nombre.
/// O(log m)
int leFaltanAprender(string nombre, EscuelaDeMagia m) {
    return (sizeS(m->hechizos)) - (sizeS(hechizosDe(nombre, m)));
}

/// Propósito: Devuelve el mago que más hechizos sabe.
/// Precondición: La escuela no está vacía.
/// O(log m)
Mago unEgresado(EscuelaDeMagia m) {
    return maxH(m->magos);
}

/// Propósito: Devuelve la escuela sin el mago que más sabe.
/// Precondición: La escuela no está vacía.
/// O(log m)
void quitarEgresado(EscuelaDeMagia m) {
    deleteMax(m->magos);
    deleteM(nombreMago(maxH(m->magos)), m->nombreMago);
}

/// Propósito: Enseña un hechizo a un mago existente, y si el hechizo no existe en la escuela es incorporado a la misma.
/// O(m . log m + log h)
void enseniar(Hechizo h, string nombre, EscuelaDeMagia m) {
    // sacar mago del map
    //refrescar la heap
    MaxHeap actualizacion = emptyH();
    aprenderHechizo(h, lookupM(nombre, m->nombreMago));
    addS(h, m->hechizos);
    for(int i=0; i<sizeH(m->magos); i++){
        if(nombreMago(maxH(m->magos)) != nombre){
            insertH(maxH(m->magos), actualizacion);
        }
        deleteMax(m->magos);
    }
    insertH(lookupM(nombre, m->nombreMago), actualizacion);
    m->magos = actualizacion;
}

/// Propósito: Libera toda la memoria creada por la escuela (incluye magos, pero no hechizos).
void destruirEscuela(EscuelaDeMagia m) {
    destroyM(m->nombreMago);
    destroyH(m->magos);
}


