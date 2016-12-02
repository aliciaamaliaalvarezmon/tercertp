#ifndef TIPOSJUEGO_H_
#define TIPOSJUEGO_H_
#include "Conj.h"
#include "TiposBasicos.h"

typedef unsigned int Jugador;
typedef std::string Pokemon;
using namespace aed2;
struct Coordenada
{
	Nat lat;
	Nat lon;
	Coordenada(Nat latitud, Nat longitud) : lat(latitud), lon(longitud)
	{
	}
	Coordenada(){
		lat = 0;
		lon = 0;
	}
	
	Coordenada( const Coordenada& otro):
		lat(otro.lat), lon(otro.lon)
	{}
	
	Coordenada& operator=(const Coordenada& otro){
		lat =otro.lat;
		lon = otro.lon;
		return (*this);
	}
	
	//Coordenada::Coordenada(Nat n, Nat m){
	//	lat = n;
	//	lon = m;
	//}
	
	const Nat& latitud() const {
		return lat;
	}
	
	const Nat& longitud() const {
		return lon;
	}
	
	Nat distEuclidea(const Coordenada& c) const {
		Nat x;
		Nat y;
		if(this->lat < c.latitud()){
			x = (c.latitud() - this->lat) * (c.latitud() - this->lat);
		}
		else{
			x = (this->lat - c.latitud()) * (this->lat - c.latitud());
		}
		
		if(this->lon < c.longitud()){
			y = (c.longitud() - this->lon) * (c.longitud() - this->lon);
		}
		else{
			y = (this->lon - c.longitud()) * (this->lon - c.longitud());
		}
		return x+y;
	}
	
	Coordenada CoordenadaArriba() const {
		return Coordenada(lat+1, lon);
	}
	
	Coordenada CoordenadaAbajo() const {
		return Coordenada(lat-1, lon);
	}
	
	Coordenada CoordenadaALaDerecha() const {
		return Coordenada(lat, lon+1);
	}
	
	Coordenada CoordenadaALaIzquierda() const{
		return Coordenada(lat, lon-1);	
	}
	
	bool operator == (const Coordenada& otro) const{
		return lat == otro.lat && lon == otro.lon;
	}
	
	Conj<Coordenada> Lindantes() const{
		Conj<Coordenada> res;
		Coordenada c(latitud(),longitud());
		Coordenada abajo(c.CoordenadaAbajo().latitud(),c.CoordenadaAbajo().longitud());
		Coordenada arriba(c.CoordenadaArriba().latitud(),c.CoordenadaArriba().longitud());
		Coordenada derecha(c.CoordenadaALaDerecha().latitud(),c.CoordenadaALaDerecha().longitud());
		Coordenada izquierda(c.CoordenadaALaIzquierda().latitud(),c.CoordenadaALaIzquierda().longitud());
		res.Agregar(abajo);
		res.Agregar(arriba);
		res.Agregar(izquierda);
		res.Agregar(derecha);
		return res;
	}
};

//bool operator == (const Coordenada& c1, const Coordenada& c2){
// return c1.latitud == c2.latitud() and c1.longitud == c2.longitud;
//}
//
//bool operator != (const Coordenada& c1, const Coordenada& c2){
// return not (c1 == c2);
//}



#endif
