#include "hechizo.h"
#include "../common/Common.h"

struct HechizoSt {
   string nombre;
   int poder;
};

/// Proposito: crea un hechizo dado un nombre y un poder
Hechizo crearHechizo(string nombre, int poder) {
    Hechizo h = new HechizoSt;
    h->nombre = nombre;
    h->poder = poder;
    return h;
}

/// Proposito: retorna el nombre del hechizo
string nombreHechizo(Hechizo h) {
   //Hechizo h = h;
   return h->nombre;
}

/// Proposito: retorna el poder de un hechizo
int poderHechizo(Hechizo h) {
   //Hechizo h = h;
   return h->poder;

}

/// Proposito: indica si un hechizo tiene el mismo nombre que otro
/// Costo: O(1)
bool mismoHechizo(Hechizo h1, Hechizo h2) {
   string a = nombreHechizo(h1);
   string b = nombreHechizo(h2);
   return a==b;
}

/// Proposito: indica si el primer hechizo es mas poderoso que el otro
/// Costo: O(1)
bool masPoderoso(Hechizo h1, Hechizo h2) {
   int a = poderHechizo(h1);
   int b = poderHechizo(h2);
   return a>b;
}

void printHechizo(Hechizo h) {
   cout << "Hechizo: {" << endl;
   cout << "  nombre: " << h->nombre << endl;
   cout << "  poder: " << h->poder << endl;
   cout << "}" << h->poder << endl;
}

/// Proposito: libera la memoria
void destroyHechizo(Hechizo h) {
   delete h;
}

