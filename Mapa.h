/* ========================================================================================
 * Implementación del módulo Mapa - Notas:
 * ---------------------------------------
 *
 * 13/11/2016: Los tipos 'Coordenada&' 'Conj<Coordenada>&' no son de tipo const.
 *			   Habría que considerar el ponerlos. De momento los saco xq tira
 *			   errores de compilación.
 *
 *			   La función 'hayCaminoQ' equivale a 'hayCamino?' del módulo Mapa.
 *
 * ========================================================================================
 */

#ifndef MAPA_H_
#define MAPA_H_

#include <string>
#include <ostream>
#include <iostream>
//#include "Coordenada.h"
#include "TiposBasicos.h"
#include "TiposJuego.h"
#include "Conj.h"
#include "Vector.h"
using namespace std;
using namespace aed2;

class Mapa {
public:
    // Genera un mapa vacío.
    Mapa();

    Mapa(const Mapa& otro);

    Mapa(const Conj<Coordenada> cs);
    ~Mapa();

    // Agrega la coordenada al mapa.
    void agregarCoord(Coordenada c);

    // Devuelve ancho de mapa.
    const Nat& longitudMaxima() const;

    // Devuelve altura de mapa.
    const Nat& latitudMaxima() const;

    // Devuelve las coordenadas del mapa.
    const Conj<Coordenada>& coordenadasMapa() const;

    // Dice si la coordenada pertenece al conjunto de coordenadas del mapa.
    bool posExiste(Coordenada& c) const;

    // Devuelve true si los dos caminos estan conectados.
    bool hayCamino(Coordenada c, Coordenada c2) const;

    // Devuelve true si existe un camino que conecte a las coordenadas.
    bool hayCaminoQ(Coordenada& c, Nat i, Nat j, Conj<Coordenada>& cs) const;

    // Devuelve true si existe un camino que conecte a las coordenadas por arriba.
    bool existeCaminoPorArriba(Coordenada& c, Conj<Coordenada>& cs) const;

    // Devuelve true si existe un camino que conecte a las coordenadas por abajo.
    bool existeCaminoPorAbajo(Coordenada& c, Conj<Coordenada>& cs) const;

    // Devuelve true si existe un camino que conecte a las coordenadas por derecha.
    bool existeCaminoPorDerecha(Coordenada& c, Conj<Coordenada>& cs) const;

    // Devuelve true si existe un camino que conecte a las coordenadas por izquierda.
    bool existeCaminoPorIzquierda(Coordenada& c, Conj<Coordenada>& cs) const;

    bool posEnMapa(Coordenada c) const;


    // Crea una matriz con las coordenadas del mapa.
    //Arreglo<Arreglo<bool> > crearMatrizMapa(Coordenada& c) const;

    Conj<Coordenada> Lindantes(Conj<Coordenada> c,Conj<Coordenada> coordenadas,Conj<Coordenada> res) const;

    Arreglo <Arreglo < bool> > MatrizDeFalse(Nat k, Nat j);

    Arreglo <Arreglo < bool> > Noesta();

    void Rellenar(Arreglo <Arreglo < bool> >& matriz,Conj<Coordenada> linda);
private:
    // CAMBIO de Vector<Vector<Vector<Vector<bool> >* > >
    Vector<Vector<Arreglo<Arreglo<bool> > > > matriz;
    Nat longitudmaxima;
    Nat latitudmaxima;
    Conj<Coordenada> coordenadas;
};

#endif