#include "escuela_magia.h"
#include "../common/Common.h"

struct EscuelaDeMagiaSt {
   Set hechizos; // set de hechizos
   Map nombreMago; // map asociando nombres con magos
   MaxHeap magos; // max heap de magos
};

/// Prop�sito: Devuelve una escuela vac�a.
/// O(1)
EscuelaDeMagia fundarEscuela() {
   EscuelaDeMagia ret = new EscuelaDeMagiaSt;
   ret->hechizos = emptyS();
   ret->nombreMago = emptyM();
   ret->magos = emptyH();
   return ret;
}

/// Prop�sito: Indica si la escuela est� vac�a.
/// O(1)
bool estaVacia(EscuelaDeMagia m) {
   return isEmptyH(m->magos);
}

/// Prop�sito: Incorpora un mago a la escuela (si ya existe no hace nada).
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

/// Prop�sito: Devuelve los nombres de los magos registrados en la escuela.
/// O(m)
vector<string> magos(EscuelaDeMagia m) {
   return domM(m->nombreMago);
}

/// Prop�sito: Devuelve los hechizos que conoce un mago dado.
/// Precondici�n: Existe un mago con dicho nombre.
/// O(log m)
Set hechizosDe(string nombre, EscuelaDeMagia m) {
    return hechizosMago(lookupM(nombre, m->nombreMago));
}

/// Prop�sito: Dado un mago, indica la cantidad de hechizos que la escuela ha dado y �l no sabe.
/// Precondici�n: Existe un mago con dicho nombre.
/// O(log m)
int leFaltanAprender(string nombre, EscuelaDeMagia m) {
    return (sizeS(m->hechizos)) - (sizeS(hechizosDe(nombre, m)));
}

/// Prop�sito: Devuelve el mago que m�s hechizos sabe.
/// Precondici�n: La escuela no est� vac�a.
/// O(log m)
Mago unEgresado(EscuelaDeMagia m) {
    return maxH(m->magos);
}

/// Prop�sito: Devuelve la escuela sin el mago que m�s sabe.
/// Precondici�n: La escuela no est� vac�a.
/// O(log m)
void quitarEgresado(EscuelaDeMagia m) {
    deleteMax(m->magos);
    deleteM(nombreMago(maxH(m->magos)), m->nombreMago);
}

/// Prop�sito: Ense�a un hechizo a un mago existente, y si el hechizo no existe en la escuela es incorporado a la misma.
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

/// Prop�sito: Libera toda la memoria creada por la escuela (incluye magos, pero no hechizos).
void destruirEscuela(EscuelaDeMagia m) {
    destroyM(m->nombreMago);
    destroyH(m->magos);
}


