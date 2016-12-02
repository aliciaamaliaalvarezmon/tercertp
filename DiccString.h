#ifndef DICCSTRING_H
#define DICCSTRING_H


#include "Conj.h" //#include "Conj.hpp" para Luis
#include <string>
#include <iostream>
#include <cassert>
using namespace std;
using namespace aed2;

template<typename T>
class DiccString {
public:
    /**
    CONSTRUCTOR
    * Construye un diccionario vacio.
    **/
    DiccString();

    /**
    CONSTRUCTOR POR COPIA
    * Construye un diccionario por copia.
    **/
    DiccString(const DiccString<T>&);


    /**
    DESTRUCTOR
    **/
    ~DiccString();

    /**
    DEFINIR
    * Recibe una clave con su significado de tipo T y la define.
    * Si ya estaba definida, la reescribe.
    **/
    void Definir(const string& clave, const T& significado);

    /**
    DEFINIDO?
    * Devuelve un bool, que es true si la clave pasada está definida en
    * el diccionario.
    **/
    bool Definido(const string& clave) const;

    /**
    OBTENER
    * Dada una clave, devuelve su significado.
    * PRE: La clave está definida.
    --PRODUCE ALIASING--
    -- Versión modificable y no modificable
    **/
    const T& Obtener(const string& clave) const;
    T& Obtener(const string& clave);

    /**
    OBTENER
    * Dada una clave, la borra del diccionario junto a su significado.
    * PRE: La clave está definida.
    --PRODUCE ALIASING--
    **/
    void Borrar(const string& clave);





    /**
    claves
    * Devuelve las claves del diccionario.
    --NO PRODUCE ALIASING--
    **/
    const Conj<string>& Claves()const;

    Nat CantClaves();

    class Iterador;
    //
    typename DiccString<T>::Iterador CrearIt();
    typename DiccString<T>::const_Iterador CrearIt() const;

    class Iterador {
    public:
        Iterador();
        ///////////////////////////
        Iterador(const typename DiccString<T>::Iterador& otra);
        ///////////////////////////
        bool HaySiguiente() const;
        ///////////////////////////
        string  SiguienteClave();
        ///////////////////////////
        T& SiguienteSignificado();
        ///////////////////////////
        pair<string, T>  Siguiente();
        ///////////////////////////
        void BorrarSiguiente();
        //////////////////////////
        void Avanzar();
        /////////////////////////
        Conj<pair<string, T> > Siguientes();
    private:
        //borrar las claves del iterador y las de vos mismo.
        Iterador(DiccString<T>* d): dic(d) {
            claves = (*d).claves.CrearIt();
            //typename Conj<string>::Iterador it = claves.CrearIt();
            if(claves.HaySiguiente()) {
                siguiente = make_pair(claves.Siguiente(), (*d).Obtener(claves.Siguiente()));//rompe crear el iterador sino hay siguiente de claves.
            }//it.EliminarSiguiente();
        }
        friend typename DiccString<T>::Iterador DiccString<T>::CrearIt();
        friend class const_Iterador;
        Conj<string>::Iterador claves;
        pair<string, T> siguiente;
        DiccString<T>* dic;
    };

    class const_Iterador {
    public:
        const_Iterador();
        ///////////////////////////
        const_Iterador(const typename DiccString<T>::Iterador& otra) ;
        ///////////////////////////
        const_Iterador(const typename DiccString<T>::const_Iterador& otra) ;
        ///////////////////////////
        bool HaySiguiente() const;
        ///////////////////////////
        string  SiguienteClave() const;
        ///////////////////////////
        const T& SiguienteSignificado() const;
        ///////////////////////////
        pair<string, T>  Siguiente() const;
        ///////////////////////////
        //void BorrarSiguiente();
        //////////////////////////
        void Avanzar();
    private:
        //borrar las claves del iterador y las de vos mismo.
        const_Iterador(const DiccString<T>* d): dic(d) {
            claves = (*d).claves.CrearIt();
            //typename Conj<string>::Iterador it = claves.CrearIt();
            if(claves.HaySiguiente()) {
                siguiente = make_pair(claves.Siguiente(), (*d).Obtener(claves.Siguiente()));//rompe crear el iterador sino hay siguiente de claves.
            }//it.EliminarSiguiente();
        }
        friend typename DiccString<T>::const_Iterador DiccString<T>::CrearIt() const;

        Conj<string>::const_Iterador claves;
        pair<string, T> siguiente;
        const DiccString<T>* dic;
    };




private:

    struct Nodo {
        Nodo** siguientes;
        pair<Conj<String>::Iterador,T>* definicion;
        Nodo() {
            siguientes = new Nodo*[256];
            for (int i = 0; i < 256; i++) {
                siguientes[i] = NULL;
            }
            definicion = NULL;
        }
        ~Nodo() {
            delete definicion;
            delete [] siguientes;
        }
    };

    //TODO: funciones auxiliares

    Nodo* raiz;
    Conj<string> claves;
    // funciones auxiliares
    bool estaenhoja(const string& clave, Nodo* puntero);
    bool eshoja(Nodo* puntero);
    int letras(Nodo* puntero);

};








template <typename T>
DiccString<T>::DiccString()
    : raiz(NULL), claves() {
}


template <typename T>
DiccString<T>::DiccString(const DiccString& d) {
    if(d.raiz == NULL) {
        Conj<string> hola;
        raiz = NULL;
        claves = hola;
    } else {
        raiz = NULL;
        Conj<string> hola;
        claves = hola;
        Conj<String> conjClaves(d.Claves());
        Conj<String>::Iterador it = conjClaves.CrearIt();
        while(conjClaves.Cardinal() > 0 ) {
            const string Clave = it.Siguiente();
            const T significado = d.Obtener(Clave);
            Definir(Clave, significado);
            it.EliminarSiguiente();
        }
    }

    //TODO

}


/*


template <typename T>
DiccString<T>::~DiccString(){
	if (raiz!= NULL){
		Conj<String>::Iterador it = claves.CrearIt();
		while(claves.Cardinal() > 0){
			it.EliminarSiguiente();
		}
	}
	raiz = NULL;
	//TODO

}
*/

template <typename T>
DiccString<T>::~DiccString() {
    if (raiz!= NULL) {
        Conj<String>::Iterador it = claves.CrearIt();
        while(it.HaySiguiente()) {
            string clave = it.Siguiente();
            it.Avanzar();
            Borrar(clave);
        }
    }
    raiz = NULL;
    //TODO

}
template <typename T>
Nat DiccString<T>::CantClaves() {
    return claves.Cardinal();
}



template <typename T>
void DiccString<T>::Definir(const string& clave, const T& significado) {
    //string clavetrue = clave;
    if(Definido(clave)) {
        int i =0;
        Nodo* recorredor = raiz;
        while (i < clave.size()) {
            recorredor = recorredor -> siguientes[int(clave[i])];
            i++;
        }
        (*(*recorredor).definicion).first.EliminarSiguiente();
        delete((*recorredor).definicion);
        Conj<String>::Iterador it =  claves.AgregarRapido(clave);
        recorredor->definicion = new pair<Conj<String>::Iterador, T>(it,(significado));//T antes de significado
    } else {
        Conj<String>::Iterador it =  claves.AgregarRapido(clave);
        if (raiz == NULL) {
            raiz = new Nodo();
            int i = 0;
            Nodo* definidor = raiz;
            while( i < clave.size()) {
                definidor -> siguientes[int(clave[i])] = new Nodo();
                definidor = definidor ->siguientes[int(clave[i])];
                i++;
            }
            definidor->definicion = new pair<Conj<String>::Iterador, T>(it,significado);

        } else {
            int i = 0;
            Nodo* definidor = raiz;
            while( i < clave.size()) {
                if(definidor -> siguientes[int(clave[i])] == NULL) {
                    definidor -> siguientes[int(clave[i])] = new Nodo();
                }
                definidor = definidor ->siguientes[int(clave[i])];
                i++;
            }
            definidor->definicion = new pair<Conj<String>::Iterador, T>(it,significado);
        }
    }
    //TODO

}


template <typename T>
bool DiccString<T>::Definido(const string& clave) const {
    bool b = true;
    if( raiz == NULL) {
        b = false;
    } else {
        int i = 0;
        Nodo* recorredor = raiz;
        while( i < clave.size() && b) {
            if( recorredor->siguientes[int(clave[i])] != NULL) {
                recorredor = recorredor->siguientes[int(clave[i])];
            } else {
                b = false;
            }
            i++;
        }
        if(b) {
            b = (recorredor->definicion != NULL);
        }
    }
    //TODO
    return b;

}

template <typename T>
T& DiccString<T>::Obtener(const string& clave) {
    int i =0;
    Nodo* recorredor = raiz;
    while (i < clave.size()) {
        recorredor = recorredor -> siguientes[int(clave[i])];
        i++;
    }
    return (*((*recorredor).definicion)).second;
    //TODO

}


template <typename T>
const T& DiccString<T>::Obtener(const string& clave) const {
    int i =0;
    Nodo* recorredor = raiz;
    while (i < clave.size()) {
        recorredor = recorredor -> siguientes[int(clave[i])];
        i++;
    }
    return (*(recorredor -> definicion)).second;
    //TODO

}


template <typename T>
const Conj<string>& DiccString<T>::Claves()const {
    return claves;
}


template <typename T>
void DiccString<T>::Borrar(const string& clave) {
    if( Definido(clave) == true) {
        if ( claves.Cardinal() == 1) {
            int i =0;
            Nodo* borrador;
            while(i < clave.size()) {
                borrador = raiz;
                raiz = raiz->siguientes[int(clave[i])];
                delete(borrador);
                i++;
            }
            borrador = raiz;
            (borrador->definicion)->first.EliminarSiguiente();
            delete(borrador);
            raiz = NULL;
        } else {
            if(!estaenhoja(clave, raiz)) {
                Nodo* borrador = raiz;
                int i = 0;
                while(i < clave.size()) {
                    borrador = borrador -> siguientes[int(clave[i])];
                    i++;
                }
                (borrador->definicion)->first.EliminarSiguiente();
                delete(borrador-> definicion);
                borrador->definicion = NULL;
            } else {
                Nodo* padre =raiz;
                Nodo* borrador = raiz;
                Nodo* borradorreal = raiz;
                int i = 0;
                int j = 0;
                while(i < clave.size()) {
                    borrador = borrador -> siguientes[int(clave[i])];
                    if((borrador -> definicion != NULL && (!eshoja(borrador))) || (letras(borrador) > 1) ) {
                        padre = borrador;
                        j = i;
                    }
                    i++;
                }
                j++;
                if(padre == raiz ) {
                    borradorreal = padre-> siguientes[int(clave[0])];
                    borrador = borradorreal;
                    padre -> siguientes[int(clave[0])] = NULL;
                } else {
                    borradorreal = padre-> siguientes[int(clave[j])];
                    borrador = borradorreal;
                    padre -> siguientes[int(clave[j])] = NULL;
                    j++;
                }
                while(j< clave.size()) {
                    borrador = borradorreal;
                    borradorreal = borradorreal->siguientes[int(clave[j])];
                    delete(borrador);
                    j++;
                }
                borrador= borradorreal;
                (borrador->definicion)->first.EliminarSiguiente();
                delete(borrador);
                borradorreal = NULL;
            }
        }
        //		claves.remover(clave);
    }
    //TODO
}


template <typename T>
bool DiccString<T>::estaenhoja(const string& clave, Nodo* puntero) {
    int i =0;
    Nodo* recorredor = puntero;
    while (i < clave.size()) {
        recorredor = recorredor -> siguientes[int(clave[i])];
        i++;
    }
    i = 0;
    bool b = true;
    while(i < 256 && b) {
        if (recorredor -> siguientes[i] != NULL) {
            b = false;
        }
        i++;
    }
    return b;
}



template <typename T>
bool DiccString<T>::eshoja(Nodo* puntero) {
    int i =0;
    bool b = true;
    while(i < 256 && b) {
        if (puntero -> siguientes[i] != NULL) {
            b = false;
        }
        i++;
    }
    return b;
}

template <typename T>
int DiccString<T>::letras(Nodo* puntero) {
    int i =0;
    int contador = 0;
    while(i < 256) {
        if(puntero->siguientes[i] != NULL) {
            contador++;
        }
        i++;
    }
    return contador;

}












//////////ITERDADOR
/////////////////////////////////////////////////
template<typename T>
DiccString<T>::Iterador::Iterador()
    : dic(NULL)
{}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename T>
DiccString<T>::Iterador::Iterador(const typename DiccString<T>::Iterador& otro)
    : claves(otro.claves),   siguiente(otro.siguiente), dic(otro.dic)
{}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename T>
bool DiccString<T>::Iterador::HaySiguiente() const {
    return (claves.HaySiguiente());
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename T>
string  DiccString<T>::Iterador::SiguienteClave() {
    return (siguiente.first);
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename T>
T& DiccString<T>::Iterador::SiguienteSignificado() {
    return (siguiente.second);
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename T>
void DiccString<T>::Iterador::BorrarSiguiente() {
    (*dic).Borrar(claves.Siguiente());
    claves = (*dic).claves.CrearIt();
    if(claves.HaySiguiente()) {
        siguiente = make_pair(claves.Siguiente(), (*dic).Obtener(claves.Siguiente()));
    }
}
//VA A ROMPER





///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename T>
void DiccString<T>::Iterador::Avanzar() {
    claves.Avanzar();
    if(claves.HaySiguiente()) {
        string id = claves.Siguiente();
        T significado(dic->Obtener(id));
        siguiente = make_pair(claves.Siguiente(),significado);
    }
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//template<typename T>
template<typename T>
pair<string, T>  DiccString<T>::Iterador::Siguiente() {
    return siguiente;
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename T>
Conj<pair<string, T> > DiccString<T>::Iterador::Siguientes() {
    Conj<pair<string, T> > nuevo;
    typename Conj<pair<string, T> >::Iterador recorro = (*this).claves;
    while(recorro.HaySiguiente()) {
        nuevo.AgregarRapido(recorro.Siguiente(), (*this).dicc.Obtener(recorro.Siguiente()));
        recorro.Avanzar();
    }
    return nuevo;
}






///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////


//template<typename T>
template<typename T>
typename DiccString<T>::Iterador DiccString<T>::CrearIt() {
    return Iterador(this);
}

//////////CONST_ITERDADOR
/////////////////////////////////////////////////
template<typename T>
DiccString<T>::const_Iterador::const_Iterador()
    : dic(NULL)
{}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename T>
DiccString<T>::const_Iterador::const_Iterador(const typename DiccString<T>::Iterador& otro)
    : claves(otro.claves),   siguiente(otro.siguiente), dic(otro.dic)
{}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename T>
DiccString<T>::const_Iterador::const_Iterador(const typename DiccString<T>::const_Iterador& otro)
    : claves(otro.claves),   siguiente(otro.siguiente), dic(otro.dic)
{}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename T>
bool DiccString<T>::const_Iterador::HaySiguiente() const {
    return (claves.HaySiguiente());
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename T>
string  DiccString<T>::const_Iterador::SiguienteClave() const {
    return (siguiente.first);
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename T>
const T& DiccString<T>::const_Iterador::SiguienteSignificado() const {
    return (siguiente.second);
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

template<typename T>
void DiccString<T>::const_Iterador::Avanzar() {
    claves.Avanzar();
    if(claves.HaySiguiente()) {
        string id = claves.Siguiente();
        T significado(dic->Obtener(id));
        siguiente = make_pair(claves.Siguiente(),significado);
    }
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

template<typename T>
pair<string, T>  DiccString<T>::const_Iterador::Siguiente() const {
    return siguiente;
}


template<typename T>
typename DiccString<T>::const_Iterador  DiccString<T>::CrearIt() const {
    return const_Iterador(this);
}







































#endif


