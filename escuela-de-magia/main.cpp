#include <iostream>
#include <cstdlib>
#include <vector>
#include "../hechizo/hechizo.h"
#include "../mago/mago.h"
#include "../set/set.h"
#include "../map/map.h"
#include "../maxheap/maxheap.h"
#include "escuela_magia.h"
#include "../common/Common.h"

using namespace std;

/// Proposito: Retorna todos los hechizos aprendidos por los magos.
/// Eficiencia: ?
Set hechizosAprendidos(EscuelaDeMagia m) {
    Set ret = emptyS();
    for(int i=0; i<(magos(m)).size(); i++){
        string nombre = magos(m)[i];
        Set hechizos = hechizosDe(nombre, m);
        ret = unionS(hechizos, ret);
    }
    return ret;
}

/// Proposito: Indica si existe un mago que sabe todos los hechizos enseñados por la escuela.
/// Eficiencia: ?
bool hayUnExperto(EscuelaDeMagia m) {
    for(int i=0; i<(magos(m)).size(); i++){
        //int cant_hechizos_mago = sizeS(hechizosDe(magos(m)[i]));
        if(leFaltanAprender(magos(m)[i], m)==0){
            return true;
        }
    }
    return false;
}

/// Proposito: Devuelve una maxheap con los magos que saben todos los hechizos dados por la escuela, quitándolos de la escuela.
/// Eficiencia: ?
MaxHeap egresarExpertos(EscuelaDeMagia m) {
   MaxHeap ret = emptyH();
   while(hayUnExperto(m)){
       insertH(unEgresado(m), ret);
       //cout<<"guardo uno"<<endl;
       quitarEgresado(m);
       //cout<<"quito el que guardo"<<endl;
   }
   //cout<<"salio del while"<<endl;
   return ret;
}

/// Escribir algunas pruebas para las funciones de la interfaz
/// de escuela de magia, y también las de usuario.

int main()
{
    cout<<""<<endl;
    cout<<"################################ IMPLEMENTACION ##############################"<<endl;
    cout<<""<<endl;
    EscuelaDeMagia escuela = fundarEscuela();
    cout<<"-la escuela esta vacia: "<<estaVacia(escuela)<<endl<<endl;

    registrar("m1", escuela);
    registrar("m2", escuela);
    for(int i=0; i<2; i++){
        cout<<"-nombre de mago " << i <<": "<< magos(escuela)[i]<<endl;
    }

    cout<<""<<endl;
    Hechizo h1 = crearHechizo("h1", 1);
    Hechizo h2 = crearHechizo("h2", 2);
    Hechizo h11 = crearHechizo("h11", 11);
    Hechizo h22 = crearHechizo("h22", 22);
    enseniar(h1, "m1", escuela);
    enseniar(h2, "m1", escuela);
    enseniar(h11, "m2", escuela);
    enseniar(h22, "m2", escuela);
    cout<<"-m1 aprendio h1: "<<belongsS(h1,hechizosDe("m1", escuela))<<endl;
    cout<<"-m1 aprendio h2: "<<belongsS(h2,hechizosDe("m1", escuela))<<endl;
    cout<<"-m2 aprendio h11: "<<belongsS(h11,hechizosDe("m2", escuela))<<endl;
    cout<<"-m2 aprendio h22: "<<belongsS(h22,hechizosDe("m2", escuela))<<endl;

    cout<<""<<endl;
    registrar("m3", escuela);
    cout<<"-cant. hechizos esperada 4" <<endl;
    cout<<" cant. ret.: "<<leFaltanAprender("m3", escuela)<<endl;

    cout<<""<<endl;
    //enseniar un hechizo mas a un m1
    Hechizo h3 = crearHechizo("h3", 3);
    Hechizo h4 = crearHechizo("h4", 3);
    Hechizo h5 = crearHechizo("h5", 3);
    enseniar(h3, "m1", escuela);
    enseniar(h4, "m1", escuela);
    enseniar(h5, "m1", escuela);
    cout<<"-m1 aprendio h3: "<<belongsS(h3,hechizosDe("m1", escuela))<<endl;
    cout<<"-m1 aprendio h4: "<<belongsS(h3,hechizosDe("m1", escuela))<<endl;
    cout<<"-m1 aprendio h5: "<<belongsS(h3,hechizosDe("m1", escuela))<<endl;
    //llamar a unEgresado y assert que el nombre es el m1
    cout<<"-mago egresado esperado m1"<<endl;
    cout<<" mago retornado: " << nombreMago(unEgresado(escuela))<<endl;

    cout<<""<<endl;
    //hacer quitarEgresado
    quitarEgresado(escuela);
    //corroborar que en el dom del map no esta el nombre m1
    cout<<"cant. magos luego de egresar uno: "<<magos(escuela).size()<<endl;
    for(int i=0; i<2; i++){
        cout<<magos(escuela)[i]<<" != m1"<<endl;
    }
    cout<<""<<endl;
    cout<<""<<endl;

    cout<<"################################ USUARIO ################################"<<endl;
    cout<<""<<endl;

    cout<<"cant. de hechizos esperada: 2"<<endl;
    cout<<"cant. de hechizos retornada: "<<sizeS(hechizosAprendidos(escuela))<<endl;

    cout<<""<<endl;
    // para hayUnExperto
    // imprimir si hay un experto, deberia dar false
    cout<<"hayUnExperto caso false: "<<hayUnExperto(escuela)<<endl;
    // enseñar el resto de los hechizos al m2
    enseniar(h3, "m2", escuela);
    enseniar(h4, "m2", escuela);
    enseniar(h5, "m2", escuela);
    enseniar(h1, "m2", escuela);
    enseniar(h2, "m2", escuela);
    // imprimir de nuevo
    cout<<"hayUnExperto caso true: "<<hayUnExperto(escuela)<<endl;

    cout<<""<<endl;
    cout<<"cant. magos: "<<magos(escuela).size()<<endl;

    // para egresarExpertos
    // usar la funcion y chequear que la escuela no tiene al m2
    egresarExpertos(escuela);
    //registrar("m4", escuela);
    cout<<"cant. magos luego de egresar expertos: "<<magos(escuela).size()<<endl;

    return 0;
}
