#include <iostream>
#include "mini_test.h"

//#include "Juego.h"
#include "Mapa.h"
//#include "TiposJuego.h"
#include "Conj.h"

using namespace aed2;

void compila(){
	Mapa m;
	Coordenada primera(1,1);	
	m.agregarCoord(primera);
	//Juego nuevo(m);
	//ASSERT(nuevo.VerMapa().longitudMaxima() == 2);
	//ASSERT(nuevo.VerMapa().latitudMaxima() == 2);
	//ASSERT(nuevo.VerMapa().coordenadasMapa().Pertenece(primera));

	}


void Agregamos_Muchas_coordenadas(){
	Mapa m;
	Coordenada primera(1,1);
	Coordenada noprimera(1,2);
	Coordenada segunda(10,5);
	Coordenada tercera(5, 11);	
	Coordenada cien(99, 99);		
	m.agregarCoord(primera);
	ASSERT(m.posExiste(primera));
	m.agregarCoord(segunda);
	ASSERT(m.posExiste(primera));
	ASSERT(m.posExiste(segunda));
	m.agregarCoord(tercera);
	ASSERT(m.posExiste(primera));
	ASSERT(m.posExiste(segunda));
	ASSERT(m.posExiste(tercera));
	//Juego nuevo(m);
	ASSERT(m.longitudMaxima() == 12);
	ASSERT(m.latitudMaxima() == 11);
	ASSERT(!(m.hayCamino(primera, noprimera)));
	ASSERT(!m.posExiste(noprimera));
	m.agregarCoord(noprimera);
	ASSERT((m.hayCamino(primera, noprimera)));
	m.agregarCoord(cien);
	ASSERT(m.posExiste(cien));

	}
















int main() {
	RUN_TEST(compila);
	RUN_TEST(Agregamos_Muchas_coordenadas);
	return 0;
}






