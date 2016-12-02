#include <iostream>
#include "mini_test.h"

#include "Driver.h"
//#include "Mapa.h"
//#include "TiposJuego.h"
//#include "Conj.h"

using namespace aed2;

void compila(){
	Mapa m;
	Coordenada primera(1,1);	
	m.agregarCoord(primera);
	Juego nuevo(m);
	ASSERT(nuevo.VerMapa().longitudMaxima() == 2);
	ASSERT(nuevo.VerMapa().latitudMaxima() == 2);
	ASSERT(nuevo.VerMapa().coordenadasMapa().Pertenece(primera));
	
}

void AgregaJugador(){
	Mapa m;
	Coordenada primera(1,1);
	m.agregarCoord(primera);
	Juego nuevo(m);
	Nat cero = nuevo.AgregarJugador();
	ASSERT(nuevo.estaConectado(cero) == false);
	ASSERT(nuevo.sanciones(cero) == 0);
	//typename DiccString< Nat>::Iterador pok nuevo.Pokemons(cero);
	ASSERT(nuevo.Pokemons(cero).HaySiguiente() == false);	
	ASSERT(nuevo.ProxID() == 1);
	ASSERT(nuevo.JugadoresConectados().EsVacio());
	ASSERT(nuevo.CantPokemonTotales() == 0);
	ASSERT(nuevo.HayPokemonCercano(primera)== false);
	ASSERT(nuevo.CrearIt().Siguiente() == cero);
	
}


void conectar(){
	Mapa m;
	Coordenada primera(1,1);
	Coordenada segunda(2,3);
	Coordenada tercera(3, 4);
	Coordenada cuarta(1, 2);
	Coordenada quinta(5, 2);
	m.agregarCoord(primera);
	m.agregarCoord(segunda);//aca
	m.agregarCoord(tercera);
	m.agregarCoord(cuarta);
	m.agregarCoord(quinta);
	Juego hola(m);
	ASSERT(hola.matrizJUGADORESLongitud() == 5);
	ASSERT(hola.matrizJUGADORESLatitud() == 6);
	ASSERT(hola.matrizPOKEMONLongtitud() == 5);
	ASSERT(hola.matrizPOKEMONLatitud() == 6);
	Nat cero = hola.AgregarJugador();
	hola.conectarse(cero, primera);
	ASSERT(hola.estaConectado(cero) == true);
	ASSERT(hola.sanciones(cero) == 0);
	ASSERT(hola.posicion(cero) == primera);
	ASSERT(hola.Pokemons(cero).HaySiguiente() == false);
	ASSERT(hola.ProxID() == 1);
	ASSERT(!hola.JugadoresConectados().EsVacio());
	ASSERT(hola.JugadoresConectados().Pertenece(cero));
	ASSERT(hola.CantPokemonTotales() == 0);
	ASSERT(hola.HayPokemonCercano(primera)== false);
	ASSERT(hola.CrearIt().Siguiente() == cero);	
}


void desconectar(){
	Mapa m;
	Coordenada primera(1,1);
	Coordenada segunda(2,3);
	Coordenada tercera(3, 4);
	Coordenada cuarta(1, 2);
	Coordenada quinta(5, 2);
	m.agregarCoord(primera);
	m.agregarCoord(segunda);//aca
	m.agregarCoord(tercera);
	m.agregarCoord(cuarta);
	m.agregarCoord(quinta);
	//hasta aca el mapa
	Juego hola(m);
	ASSERT(hola.matrizJUGADORESLongitud() == 5);
	ASSERT(hola.matrizJUGADORESLatitud() == 6);
	ASSERT(hola.matrizPOKEMONLongtitud() == 5);
	ASSERT(hola.matrizPOKEMONLatitud() == 6);
	Nat cero = hola.AgregarJugador();
	
	hola.conectarse(cero, primera);
	ASSERT(hola.estaConectado(cero) == true);
	ASSERT(hola.sanciones(cero) == 0);
	ASSERT(hola.posicion(cero) == primera);
	ASSERT(hola.Pokemons(cero).HaySiguiente() == false);	
	ASSERT(hola.Expulsados().EsVacio());	
	ASSERT(hola.ProxID() == 1);
	ASSERT(!hola.JugadoresConectados().EsVacio());
	ASSERT(hola.JugadoresConectados().Pertenece(cero));
	ASSERT(hola.CantPokemonTotales() == 0);
	ASSERT(hola.HayPokemonCercano(primera)== false);
	ASSERT(hola.CrearIt().Siguiente() == cero);	
	hola.desconectarse(0);
	ASSERT(hola.estaConectado(cero) == false);
	ASSERT(hola.sanciones(cero) == 0);
	ASSERT(hola.Pokemons(cero).HaySiguiente() == false);
	ASSERT(hola.Expulsados().EsVacio());
	ASSERT(hola.ProxID() == 1);
	ASSERT(hola.JugadoresConectados().EsVacio());
	ASSERT(!hola.JugadoresConectados().Pertenece(cero));
	ASSERT(hola.CantPokemonTotales() == 0);
	ASSERT(hola.HayPokemonCercano(primera)== false);
	ASSERT(hola.CrearIt().Siguiente() == cero);	
	
}



void AgregoPokemon(){
	Mapa m;
	Coordenada primera(1,1);
	Coordenada segunda(2,3);
	Coordenada tercera(3, 4);
	Coordenada cuarta(1, 2);
	Coordenada quinta(5, 2);
	m.agregarCoord(primera);
	m.agregarCoord(segunda);//aca
	m.agregarCoord(tercera);
	m.agregarCoord(cuarta);
	m.agregarCoord(quinta);
	ASSERT(m.hayCamino(primera, primera));
	ASSERT(m.hayCamino(segunda, segunda));
	ASSERT(m.hayCamino(tercera, tercera));
	ASSERT(m.hayCamino(cuarta, cuarta));
	ASSERT(m.hayCamino(quinta, quinta));
	ASSERT(m.hayCamino(primera, cuarta));
	ASSERT(!m.hayCamino(segunda, quinta));
	//hasta aca el mapa	
	Juego hola(m);
	ASSERT(hola.matrizJUGADORESLongitud() == 5);
	ASSERT(hola.matrizJUGADORESLatitud() == 6);
	ASSERT(hola.matrizPOKEMONLongtitud() == 5);
	ASSERT(hola.matrizPOKEMONLatitud() == 6);
	hola.AgregarPokemon("torchit", primera);		
	ASSERT(hola.CantMovimientosParaCaptura(primera) == 0);
	ASSERT(hola.CantPokemonTotales() == 1);
	ASSERT(hola.indiceDeRareza("torchit") == 0);
	//ASSERT(hola.pokemonEnPos(primera) == "torchit");
	//cout << "llega"<<endl;
	Conj<Coordenada> vacio;
	//cout << hola.posConPokemons(vacio).Siguiente().latitud() << ", " << hola.posConPokemons(vacio).Siguiente().longitud() <<endl;
	//ASSERT(hola.posConPokemons(vacio).Siguiente() == primera);	
	//ASSERT(hola.HayPokemonCercano(primera));
	//agregamos otros pokemons
	hola.AgregarPokemon("jericho", quinta);		
	ASSERT(hola.CantMovimientosParaCaptura(quinta) == 0);
	cout << "llega"<<endl;	
	ASSERT(hola.CantPokemonTotales() == 2);
	cout << hola.indiceDeRareza("jericho") << endl;
	ASSERT(hola.indiceDeRareza("jericho") == 50);
	//ASSERT(hola.indiceDeRareza("torchit") == 50);
	ASSERT(hola.pokemonEnPos(quinta) == "jericho");
	ASSERT(hola.HayPokemonCercano(quinta));
	//Conj<Coordenada>::Iterador iter = hola.posConPokemons(vacio);
	//ASSERT(iter.Siguiente() == primera);
	//iter.Avanzar();
	//ASSERT(iter.Siguiente() == quinta);
	//cout << hola.PosDePokemonCercano(quinta).latitud() <<"," << hola.PosDePokemonCercano(quinta).longitud() << endl;*/
	
	
	
}




void Conecto_cerca_de_pokemon(){
	Mapa m;
	Coordenada primera(1,1);
	Coordenada segunda(2,3);
	Coordenada tercera(3, 4);
	Coordenada cuarta(1, 2);
	Coordenada quinta(5, 2);
	m.agregarCoord(primera);
	m.agregarCoord(segunda);//aca
	m.agregarCoord(tercera);
	m.agregarCoord(cuarta);
	m.agregarCoord(quinta);
	Juego hola(m);
	Nat cero = hola.AgregarJugador();
	Nat uno = hola.AgregarJugador();	
	hola.AgregarPokemon("torchit", primera);
	hola.conectarse(cero, cuarta);
	hola.conectarse(uno, primera);
	hola.desconectarse(uno);
	
	
	
}


void Agrego_pok_cerca_de_jugador(){
	Mapa m;
	Coordenada primera(1,1);
	Coordenada segunda(2,3);
	Coordenada tercera(3, 4);
	Coordenada cuarta(1, 2);
	Coordenada quinta(5, 2);
	m.agregarCoord(primera);
	m.agregarCoord(segunda);//aca
	m.agregarCoord(tercera);
	m.agregarCoord(cuarta);
	m.agregarCoord(quinta);
	Juego hola(m);
	Nat cero = hola.AgregarJugador();
	Nat uno = hola.AgregarJugador();
	hola.conectarse(cero, cuarta);
	hola.conectarse(uno, primera);
	hola.AgregarPokemon("torchit", primera);
}


void Agrego_Juegador_cerca(){
	Mapa m;
	Coordenada primera(1,1);
	Coordenada segunda(2,3);
	Coordenada tercera(3, 4);
	Coordenada cuarta(1, 2);
	Coordenada quinta(5, 2);
	m.agregarCoord(primera);
	m.agregarCoord(segunda);//aca
	m.agregarCoord(tercera);
	m.agregarCoord(cuarta);
	m.agregarCoord(quinta);
	Juego hola(m);
	Nat cero = hola.AgregarJugador();	
	hola.conectarse(cero, primera);	
	hola.AgregarPokemon("torchit", primera);
	ASSERT(hola.HayUnJugadorCercano(primera));
}

void Agrego_cercanos(){
	Mapa m;
	Coordenada primera(1,1);
	Coordenada segunda(2,3);
	Coordenada tercera(3, 4);
	Coordenada cuarta(1, 2);
	Coordenada quinta(5, 2);
	m.agregarCoord(primera);
	m.agregarCoord(segunda);//aca
	m.agregarCoord(tercera);
	m.agregarCoord(cuarta);
	m.agregarCoord(quinta);
	Juego hola(m);
	Nat cero = hola.AgregarJugador();
	Nat uno = hola.AgregarJugador();
	Nat dos = hola.AgregarJugador();	
	hola.conectarse(cero, primera);
	hola.conectarse(uno, cuarta);	
	hola.conectarse(dos, primera);
	hola.AgregarPokemon("torchit", primera);
	ASSERT(hola.HayUnJugadorCercano(cuarta));
}


void Moverse(){
	Mapa m;
	Coordenada primera(1,1);
	Coordenada segunda(2,3);
	Coordenada tercera(3, 4);
	Coordenada cuarta(1, 2);
	Coordenada quinta(5, 2);
	Coordenada sexta(5,1);
	m.agregarCoord(primera);
	m.agregarCoord(segunda);//aca
	m.agregarCoord(tercera);
	m.agregarCoord(cuarta);
	m.agregarCoord(quinta);
	m.agregarCoord(sexta);
	cout << "distEuclidea"<< tercera.distEuclidea(primera)<< endl;
	Juego hola(m);
	Nat cero = hola.AgregarJugador();
	Nat uno = hola.AgregarJugador();
	Nat dos = hola.AgregarJugador();
	hola.conectarse(cero, primera);
	hola.conectarse(uno, quinta);
	//hola.conectarse(dos, primera);	
	hola.AgregarPokemon("torchit", primera);	
	hola.moverse(1, sexta);	
	hola.moverse(1,quinta);
	hola.moverse(1,sexta);
	hola.moverse(1, sexta);	
	hola.moverse(1,quinta);
	hola.moverse(1,sexta);
	hola.moverse(1,quinta);
	hola.moverse(1,quinta);
	hola.moverse(1,quinta);
	hola.moverse(1,sexta);	
	hola.AgregarPokemon("jerachi", primera);
	hola.desconectarse(cero);
	hola.moverse(1, sexta);	
	hola.moverse(1,quinta);
	hola.moverse(1,sexta);
	hola.moverse(1, sexta);	
	hola.moverse(1,quinta);
	hola.moverse(1,sexta);
	hola.moverse(1,quinta);
	hola.moverse(1,quinta);
	hola.moverse(1,quinta);
	hola.moverse(1,sexta);	
	//typename DiccString< Nat >::Iterador funca = hola.Pokemons(cero);
	//typename DiccString< Nat >::Iterador funcando = hola.Pokemons(dos);
	//while(funca.HaySiguiente()){
	//	cout << funcando.SiguienteClave() << ", " << funcando.SiguienteSignificado() << endl;
	//	cout << funca.SiguienteClave() << ", " << funca.SiguienteSignificado() << endl;		
	//		if(funca.HaySiguiente()){
	
	//funcando.Avanzar();
	//cout << funcando.SiguienteClave() << ", " << funcando.SiguienteSignificado() << endl;
	//funca.Avanzar();
	//	}
	//	}
	
	
	//hola.conectarse(dos, primera);
	
	
}


void GenerarCaptura(Juego j, Nat e, Coordenada c ){
	Nat i = 0;
	while(i < 10){
		j.moverse(e,c);
		i++;
	}
}


void se_desconecta(){
	Mapa m;
	Coordenada primera(1,1);
	Coordenada segunda(2,3);
	Coordenada tercera(3, 4);
	Coordenada cuarta(1, 2);
	Coordenada quinta(5, 2);
	Coordenada sexta(5,1);
	m.agregarCoord(primera);
	m.agregarCoord(segunda);//aca
	m.agregarCoord(tercera);
	m.agregarCoord(cuarta);
	m.agregarCoord(quinta);
	m.agregarCoord(sexta);
	Juego hola(m);
	Nat cero = hola.AgregarJugador();
	Nat uno = hola.AgregarJugador();
	Nat dos = hola.AgregarJugador();
	hola.conectarse(cero, primera);
	hola.conectarse(uno, quinta);
	hola.conectarse(dos, primera);
	hola.AgregarPokemon("torchit", primera);
	//hola.desconectarse(dos);	
	cout << "distEuclidea"<< tercera.distEuclidea(primera)<< endl;
	hola.moverse(1, sexta);	
	hola.moverse(1,quinta);
	hola.moverse(1,sexta);
	hola.moverse(1, sexta);	
	hola.moverse(1,quinta);
	hola.moverse(1,sexta);
	hola.moverse(1,quinta);
	hola.moverse(1,quinta);
	hola.moverse(1,quinta);
	hola.moverse(1,sexta);	
	hola.AgregarPokemon("jerachi", primera);
	hola.desconectarse(cero);
	hola.moverse(1, sexta);	
	hola.moverse(1,quinta);
	hola.moverse(1,sexta);
	hola.moverse(1, sexta);	
	hola.moverse(1,quinta);
	hola.moverse(1,sexta);
	hola.moverse(1,quinta);
	hola.moverse(1,quinta);
	hola.moverse(1,quinta);
	hola.moverse(1,sexta);	
	//typename DiccString< Nat >::Iterador funca = hola.Pokemons(cero);
	//typename DiccString< Nat >::Iterador funcando = hola.Pokemons(dos);
	//while(funca.HaySiguiente()){
	//	cout << funcando.SiguienteClave() << ", " << funcando.SiguienteSignificado() << endl;
	//	cout << funca.SiguienteClave() << ", " << funca.SiguienteSignificado() << endl;		
	//		if(funca.HaySiguiente()){
	
	//funcando.Avanzar();
	//cout << funcando.SiguienteClave() << ", " << funcando.SiguienteSignificado() << endl;
	//funca.Avanzar();
	//	}
	//	}
	
	
	//hola.conectarse(dos, primera);
	
	
}






void Me_Voy(){
	Mapa m;
	Coordenada primera(1,1);
	Coordenada segunda(1,2);
	Coordenada tercera(11, 20);
	Coordenada cuarta(10, 20);
	Coordenada quinta(30, 25);
	Coordenada sexta(1,3);
	Coordenada septima(1,4);
	Coordenada octava(1,5);
	m.agregarCoord(primera);
	m.agregarCoord(segunda);//aca
	m.agregarCoord(tercera);
	m.agregarCoord(cuarta);
	m.agregarCoord(quinta);
	m.agregarCoord(sexta);
	m.agregarCoord(septima);
	m.agregarCoord(octava);
	Juego hola(m);
	Nat cero = hola.AgregarJugador();
	Nat uno = hola.AgregarJugador();
	Nat dos = hola.AgregarJugador();	
	hola.conectarse(cero, primera);
	hola.conectarse(uno, quinta);	
	hola.conectarse(dos, primera);
	hola.AgregarPokemon("torchit", primera);
	hola.moverse(1, quinta);	
	hola.moverse(1,quinta);
	hola.moverse(1, quinta);
	hola.moverse(1, quinta);	
	hola.moverse(1,quinta);
	hola.moverse(1, quinta);
	hola.moverse(1,quinta);
	hola.moverse(1,quinta);
	hola.moverse(1,quinta);
	hola.moverse(1,quinta);
	hola.AgregarPokemon("jerachi", primera);
	hola.moverse(dos, octava);
	cout << hola.MostrarTope( 1, 1)<< endl;
	//GenerarCaptura(hola, dos, quinta);
	//ASSERT(hola.HayUnJugadorCercano(cuarta));
}

void Entro(){
	Mapa m;
	Coordenada primera(1,1);
	Coordenada segunda(1,2);
	Coordenada tercera(11, 20);
	Coordenada cuarta(10, 20);
	Coordenada quinta(30, 25);
	Coordenada sexta(1,3);
	Coordenada septima(1,4);
	Coordenada octava(1,5);
	m.agregarCoord(primera);
	m.agregarCoord(segunda);//aca
	m.agregarCoord(tercera);
	m.agregarCoord(cuarta);
	m.agregarCoord(quinta);
	m.agregarCoord(sexta);
	m.agregarCoord(septima);
	m.agregarCoord(octava);
	Juego hola(m);
	Nat cero = hola.AgregarJugador();
	Nat uno = hola.AgregarJugador();
	Nat dos = hola.AgregarJugador();	
	hola.conectarse(cero, primera);
	hola.conectarse(uno, quinta);	
	hola.conectarse(dos, octava);
	hola.AgregarPokemon("torchit", primera);
	hola.moverse(1, quinta);	
	hola.moverse(1,quinta);
	hola.moverse(1, quinta);
	hola.moverse(1, quinta);	
	hola.moverse(1,quinta);
	hola.moverse(1, quinta);
	hola.moverse(1,quinta);
	hola.moverse(1,quinta);
	//hola.moverse(1,quinta);
	//hola.moverse(1,quinta);
	//hola.AgregarPokemon("jerachi", primera);
	hola.moverse(dos, primera);
	//cout << hola.MostrarTope( 1, 1)<< endl;
	//GenerarCaptura(hola, dos, quinta);
	//ASSERT(hola.HayUnJugadorCercano(cuarta));
}






void Expulsion_del_Eden(){
	Mapa m;
	Coordenada primera(1,1);
	Coordenada segunda(1,2);
	Coordenada tercera(11, 20);
	Coordenada cuarta(10, 20);
	Coordenada quinta(30, 25);
	Coordenada sexta(1,3);
	Coordenada septima(1,4);
	Coordenada octava(1,5);
	m.agregarCoord(primera);
	m.agregarCoord(segunda);//aca
	m.agregarCoord(tercera);
	m.agregarCoord(cuarta);
	m.agregarCoord(quinta);
	m.agregarCoord(sexta);
	m.agregarCoord(septima);
	m.agregarCoord(octava);
	Juego hola(m);
	Nat cero = hola.AgregarJugador();
	Nat uno = hola.AgregarJugador();
	Nat dos = hola.AgregarJugador();	
	hola.conectarse(cero, primera);
	hola.conectarse(uno, primera);	
	hola.conectarse(dos, tercera);
	hola.AgregarPokemon("torchit", primera);
	//hola.moverse(2, tercera);	
	//hola.moverse(2, tercera);
	//hola.moverse(2, tercera);
	//hola.moverse(2, tercera);	
	//hola.moverse(2, tercera);
	//hola.moverse(2, tercera);
	//hola.moverse(2, tercera);
	//hola.moverse(2, tercera);
	//hola.moverse(2, tercera);
	//hola.moverse(2, tercera);
	//hola.AgregarPokemon("torchit", primera);
	//hola.moverse(2, tercera);	
	//hola.moverse(2, tercera);
	//hola.moverse(2, tercera);
	//hola.moverse(2, tercera);	
	//hola.moverse(2, tercera);
	//hola.moverse(2, tercera);
	//hola.moverse(2, tercera);
	//hola.moverse(2, tercera);
	//hola.moverse(2, tercera);
	//hola.moverse(2, tercera);	
	hola.moverse(uno, quinta);	
	hola.moverse(uno, quinta);	
	hola.moverse(uno, quinta);	
	hola.moverse(uno, quinta);	
	hola.moverse(uno, quinta);
	//hola.desconectarse(dos);
	ASSERT(hola.sanciones(uno) == 5);
	//cout << hola.MostrarTope(1, 1) << endl;
	hola.moverse(uno, quinta);	
	ASSERT(hola.Expulsados().Pertenece(1));
	//hola.moverse(1, quinta);
	//typename Juego::Iterador adieu = hola.Jugadores();
	//Nat i = 10;
	//while(adieu.HaySiguiente()){
	//	cout << adieu.Siguiente() << endl;
	//	adieu.Avanzar();	
	//}
	
	//ASSERT(con.Pertenece(cero));
	//ASSERT(con.Pertenece(dos));
	//ASSERT(!(con.Pertenece(uno)));
	hola.desconectarse(cero);		
	cout << hola.estaConectado(cero) << endl;	
	Conj<Nat> con = hola.JugadoresConectados();
	ASSERT(!(con.Pertenece(cero)));
	ASSERT(con.Pertenece(dos));
	ASSERT(!(con.Pertenece(uno)));
	
	
	
	
	
}


void dos_capturas(){
	Mapa m;
	Coordenada primera(1,1);
	Coordenada segunda(1,2);
	Coordenada tercera(11, 20);
	Coordenada cuarta(10, 20);
	Coordenada quinta(30, 25);
	m.agregarCoord(primera);
	m.agregarCoord(segunda);//aca
	m.agregarCoord(tercera);
	m.agregarCoord(cuarta);
	m.agregarCoord(quinta);
	Juego hola(m);
	Nat cero = hola.AgregarJugador();
	Nat uno = hola.AgregarJugador();
	Nat dos = hola.AgregarJugador();	
	hola.conectarse(cero, primera);
	hola.conectarse(uno, tercera);	
	hola.conectarse(dos, quinta);
	hola.AgregarPokemon("torchit", primera);
	hola.AgregarPokemon("gabumon", tercera);
	hola.moverse(2, quinta);	
	hola.moverse(2, quinta);
	hola.moverse(2, quinta);
	hola.moverse(2, quinta);	
	hola.moverse(2, quinta);
	hola.moverse(2, quinta);
	hola.moverse(2, quinta);
	hola.moverse(2, quinta);
	hola.moverse(2, quinta);
	hola.moverse(2, quinta);
	cout << hola.Pokemons(uno).SiguienteClave() << endl;
	cout << hola.Pokemons(cero).SiguienteClave() << hola.Pokemons(cero).SiguienteSignificado() << endl;
	
	//	ASSERT(hola.Pokemons(uno).SiguienteClave() == "torchit");	
	//	ASSERT(hola.Pokemons(cero).SiguienteClave() == "gabumon");
	
	
	//ASSERT(hola.HayUnJugadorCercano(cuarta));
}


void salgo_y_entro(){
	Mapa m;
	Coordenada primera(1,1);
	Coordenada segunda(1,2);
	Coordenada tercera(5, 5);
	Coordenada cuarta(1,3);
	Coordenada quinta(1, 4);
	Coordenada sexta(1, 5);
	Coordenada septima(1, 6);
	Coordenada octava(1,7);
	Coordenada novena(1,8);
	Coordenada decima(1,9);
	Coordenada onceava(1,10);	
	ASSERT(onceava.distEuclidea(primera)> 25);
	ASSERT(onceava.distEuclidea(primera) <100);
	ASSERT(tercera.distEuclidea(primera)> 25);
	ASSERT(tercera.distEuclidea(primera) <100);
	m.agregarCoord(primera);
	m.agregarCoord(segunda);//aca
	m.agregarCoord(tercera);
	m.agregarCoord(cuarta);
	m.agregarCoord(quinta);
	m.agregarCoord(sexta);
	m.agregarCoord(septima);
	m.agregarCoord(octava);
	m.agregarCoord(novena);
	m.agregarCoord(decima);
	m.agregarCoord(onceava);	
	Juego hola(m);
	Nat cero = hola.AgregarJugador();
	Nat uno = hola.AgregarJugador();
	Nat dos = hola.AgregarJugador();	
	hola.conectarse(cero, onceava);
	hola.conectarse(uno, tercera);	
	hola.conectarse(dos, primera);
	hola.AgregarPokemon("torchit", primera);
	hola.AgregarPokemon("gabumon", onceava);
	hola.moverse(1, tercera);	
	hola.moverse(1, tercera);
	hola.moverse(1, tercera);	
	cout << hola.MostrarTope(1,1) << endl;
	hola.moverse(2, onceava);	
	hola.moverse(0, primera);//0 y el otro tambien 0
	cout << hola.MostrarTope(10,1) << endl;	
	hola.moverse(1, tercera);	
	hola.moverse(1, tercera);
	hola.moverse(1, tercera);
	hola.moverse(1, tercera);
	hola.moverse(1, tercera);
	hola.moverse(1, tercera);// NO DEBERIA SALTAR LA CAPTURA PERO SALTA
	hola.moverse(1, tercera);
	hola.moverse(1, tercera);
	hola.moverse(1, tercera);
	hola.moverse(1, tercera);	
	cout << hola.Pokemons(dos).SiguienteClave() <<  endl;
	cout << hola.Pokemons(cero).SiguienteClave() <<  endl;
	
}

void se_desconecta_real(){
	Mapa m;
	Coordenada primera(1,1);
	Coordenada segunda(2,3);
	Coordenada tercera(3, 4);
	Coordenada cuarta(1, 2);
	Coordenada quinta(5, 2);
	Coordenada sexta(5,1);
	m.agregarCoord(primera);
	m.agregarCoord(segunda);//aca
	m.agregarCoord(tercera);
	m.agregarCoord(cuarta);
	m.agregarCoord(quinta);
	m.agregarCoord(sexta);
	Juego hola(m);
	Nat cero = hola.AgregarJugador();
	Nat uno = hola.AgregarJugador();
	Nat dos = hola.AgregarJugador();
	hola.conectarse(cero, primera);
	hola.conectarse(uno, quinta);
	hola.conectarse(dos, primera);
	hola.AgregarPokemon("torchit", primera);
	//hola.desconectarse(dos);
	hola.moverse(1, sexta);	
	hola.moverse(1,quinta);
	hola.moverse(1,sexta);
	hola.moverse(1, sexta);	
	hola.moverse(1,quinta);
	hola.moverse(1,sexta);
	hola.moverse(1,quinta);
	hola.moverse(1,quinta);
	hola.moverse(1,quinta);
	hola.moverse(1,sexta);	
	hola.AgregarPokemon("jerachi", primera);
	hola.desconectarse(cero);	
	cout << hola.MostrarTope(1,1)<< endl;
}


void me_muevo_esperando(){
	Mapa m;
	Coordenada primera(1,1);
	Coordenada segunda(2,3);
	Coordenada tercera(3, 4);
	Coordenada cuarta(1, 2);
	Coordenada quinta(5, 2);
	Coordenada sexta(5,1);
	m.agregarCoord(primera);
	m.agregarCoord(segunda);//aca
	m.agregarCoord(tercera);
	m.agregarCoord(cuarta);
	m.agregarCoord(quinta);
	m.agregarCoord(sexta);
	Juego hola(m);
	Nat cero = hola.AgregarJugador();
	Nat uno = hola.AgregarJugador();
	Nat dos = hola.AgregarJugador();
	Nat tres = hola.AgregarJugador();
	Nat cuatro = hola.AgregarJugador();
	Nat cinco = hola.AgregarJugador();
	Nat seis = hola.AgregarJugador();
	Nat siete = hola.AgregarJugador();
	hola.AgregarPokemon("torchit", primera);
	hola.conectarse(cero, primera);
	hola.conectarse(uno, primera);
	hola.conectarse(dos, primera);
	hola.conectarse(tres, primera);
	hola.conectarse(cuatro, primera);
	hola.conectarse(cinco, primera);
	hola.conectarse(seis, primera);
	//hola.conectarse(siete, primera);
	hola.moverse(cero, primera);
	hola.moverse(cero, primera);
	hola.moverse(cero, primera);
	hola.moverse(cero, primera);
	hola.moverse(cero, primera);
	hola.moverse(cero, primera);
	hola.moverse(cero, primera);
	hola.moverse(cero, primera);
	hola.moverse(cero, primera);
	hola.moverse(cero, primera);
	hola.moverse(cero, primera);
	//cout << hola.MostrarTope(1,1)<< endl;
}

void indiceDeRareza(){
	Mapa m;
	Coordenada primera(1,1);
	Coordenada segunda(2,3);
	Coordenada tercera(3, 4);
	Coordenada cuarta(1, 2);
	Coordenada quinta(5, 2);
	Coordenada sexta(5,1);
	m.agregarCoord(primera);
	m.agregarCoord(segunda);//aca
	m.agregarCoord(tercera);
	m.agregarCoord(cuarta);
	m.agregarCoord(quinta);
	m.agregarCoord(sexta);
	Juego hola(m);
	Nat cero = hola.AgregarJugador();
	Nat uno = hola.AgregarJugador();
	Nat dos = hola.AgregarJugador();
	Nat tres = hola.AgregarJugador();
	Nat cuatro = hola.AgregarJugador();
	Nat cinco = hola.AgregarJugador();
	Nat seis = hola.AgregarJugador();
	Nat siete = hola.AgregarJugador();
	hola.AgregarPokemon("jerachi", quinta);
	hola.AgregarPokemon("torchit", primera);
	/*hola.AgregarPokemon("torchit", primera);
	hola.AgregarPokemon("torchit", primera);
	hola.AgregarPokemon("torchit", primera);
	hola.AgregarPokemon("torchit", primera);
	hola.AgregarPokemon("torchit", primera);
	hola.AgregarPokemon("torchit", primera);
	hola.AgregarPokemon("torchit", primera);
	hola.AgregarPokemon("torchit", primera);
	hola.AgregarPokemon("torchit", primera);
	hola.AgregarPokemon("torchit", primera);
	hola.AgregarPokemon("torchit", primera);
	hola.AgregarPokemon("torchit", primera);
	hola.AgregarPokemon("torchit", primera);*/
	hola.conectarse(tres, sexta);
	hola.conectarse(uno, primera);
	hola.conectarse(dos, primera);
	hola.moverse(dos, primera);
	hola.moverse(dos, primera);
	hola.moverse(dos, primera);
	hola.moverse(dos, primera);
	hola.moverse(dos, primera);
	hola.moverse(dos, primera);
	hola.moverse(dos, primera);
	hola.moverse(dos, primera);
	hola.moverse(dos, primera);
	hola.moverse(dos, primera);
	//DiccString<Nat> pokesJugador = 
	cout<< "atrapo un jerachi" << hola.Pokemons(tres).SiguienteClave() << endl;
	ASSERT(!hola.HayPokemonCercano(sexta));
	
	hola.moverse(tres, segunda);
	hola.moverse(tres, segunda);
	hola.moverse(tres, segunda);
	hola.moverse(tres, segunda);
	hola.moverse(tres, segunda);
	cout <<"Quiero un torchit"<< hola.indiceDeRareza("torchit") << endl;
}



//VER INDICE DE RAREZA

void cuatro_capturas(){
	Mapa m;
	Coordenada primera(1,1);
	Coordenada segunda(1,2);
	Coordenada tercera(5, 5);
	Coordenada cuarta(1,3);
	Coordenada quinta(1, 4);
	Coordenada sexta(1, 5);
	Coordenada septima(1, 6);
	Coordenada octava(1,7);
	Coordenada novena(1,8);
	Coordenada decima(1,9);
	Coordenada onceava(5,6);	
	ASSERT(onceava.distEuclidea(primera)> 25);
	ASSERT(onceava.distEuclidea(primera) <100);
	ASSERT(tercera.distEuclidea(primera)> 25);
	ASSERT(tercera.distEuclidea(primera) <100);
	m.agregarCoord(primera);
	m.agregarCoord(segunda);//aca
	m.agregarCoord(tercera);
	m.agregarCoord(cuarta);
	m.agregarCoord(quinta);
	m.agregarCoord(sexta);
	m.agregarCoord(septima);
	m.agregarCoord(octava);
	m.agregarCoord(novena);
	m.agregarCoord(decima);
	m.agregarCoord(onceava);	
	Juego hola(m);
	Nat cero = hola.AgregarJugador();
	Nat uno = hola.AgregarJugador();
	Nat dos = hola.AgregarJugador();
	Nat tres = hola.AgregarJugador();
	Nat cuatro = hola.AgregarJugador();
	Nat cinco = hola.AgregarJugador();
	Nat seis = hola.AgregarJugador();
	Nat siete = hola.AgregarJugador();
	hola.conectarse(cero, primera);
	hola.conectarse(uno, segunda);	
	hola.AgregarPokemon("torchit", primera);
	ASSERT(hola.pokemonEnPos(primera) == "torchit");
	hola.conectarse(dos, cuarta);
	hola.conectarse(tres, quinta);
	hola.conectarse(cuatro, tercera);
	hola.AgregarPokemon("jericho", tercera);
	ASSERT(hola.pokemonEnPos(tercera) == "jericho");
	hola.conectarse(cinco, onceava);
	hola.desconectarse(cuatro);
	hola.conectarse(cuatro, tercera);
	hola.AgregarPokemon("new", decima);
	ASSERT(hola.pokemonEnPos(decima) == "new");
	ASSERT(decima.distEuclidea(tercera) > 4);
	hola.conectarse(seis, decima);
	hola.conectarse(siete, sexta);
	hola.moverse(siete, sexta);
	hola.moverse(siete, sexta);
	hola.moverse(siete, sexta);
	hola.moverse(siete, sexta);
	hola.moverse(siete, sexta);
	hola.moverse(siete, sexta);
	hola.moverse(siete, sexta);
	hola.moverse(siete, sexta);
	hola.moverse(siete, sexta);
	hola.moverse(siete, sexta);
	hola.AgregarPokemon("torchit", primera);
	hola.AgregarPokemon("jericho", tercera);
	hola.AgregarPokemon("new", decima);
	ASSERT(hola.pokemonEnPos(primera) == "torchit");
	ASSERT(hola.pokemonEnPos(tercera) == "jericho");
	ASSERT(hola.pokemonEnPos(decima) == "new");
	Conj<Coordenada> dummy;	
	ASSERT(hola.posConPokemons().Pertenece(primera) );
	ASSERT(hola.posConPokemons().Pertenece(tercera) );
	ASSERT(hola.posConPokemons().Pertenece(decima) );
	/*Conj<Coordenada>::Iterador it = hola.posConPokemons(dummy);
	cout << it.Siguiente().latitud() << it.Siguiente().longitud() << endl;
	it.Avanzar();
	cout << it.Siguiente().latitud() << it.Siguiente().longitud() << endl;
	it.Avanzar();
	cout << it.Siguiente().latitud() << it.Siguiente().longitud() << endl;
	it.Avanzar();
	ASSERT(!it.HaySiguiente());*/
	hola.moverse(siete, sexta);
	hola.moverse(siete, sexta);
	hola.moverse(siete, sexta);
	hola.moverse(siete, sexta);
	hola.moverse(siete, sexta);
	hola.moverse(siete, sexta);
	hola.moverse(siete, sexta);
	hola.moverse(siete, sexta);
	hola.moverse(siete, sexta);
	ASSERT(hola.CantMovimientosParaCaptura(primera)== 9);
	ASSERT(hola.CantMovimientosParaCaptura(tercera)== 9);
	ASSERT(hola.CantMovimientosParaCaptura(decima)== 9);
	hola.moverse(siete, sexta);
	hola.desconectarse(cinco);
	ASSERT(hola.estaConectado(cero));
	ASSERT(hola.estaConectado(uno));
	ASSERT(hola.estaConectado(dos));
	ASSERT(hola.estaConectado(tres));
	ASSERT(hola.estaConectado(cuatro));
	ASSERT(!hola.estaConectado(cinco));
	ASSERT(hola.estaConectado(seis));
	ASSERT(hola.estaConectado(siete));
	ASSERT(hola.sanciones(cero) == 0 );
	ASSERT(hola.sanciones(uno) == 0);
	ASSERT(hola.sanciones(dos) == 0);
	ASSERT(hola.sanciones(tres) == 0);
	ASSERT(hola.sanciones(cuatro) == 0);
	ASSERT(hola.sanciones(cinco) == 0);
	ASSERT(hola.sanciones(seis) == 0);
	ASSERT(hola.sanciones(siete) == 0);
	//Conj<Coordenada> dummy2;	
	//	ASSERT(!(hola.posConPokemons(dummy2).HaySiguiente()));
	ASSERT((hola.posConPokemons().EsVacio()));
	ASSERT(hola.CantPokemonTotales()== 6);
	cout << "pokemons de dos " << hola.Pokemons(2).SiguienteClave() << ", " <<hola.Pokemons(2).SiguienteSignificado() << endl;
	cout << "pokemons de cinco " << hola.Pokemons(5).SiguienteClave() <<", " <<hola.Pokemons(5).SiguienteSignificado() << endl;
	cout << "pokemons de uno " << hola.Pokemons(1).SiguienteClave() << ", " <<hola.Pokemons(1).SiguienteSignificado() << endl;
	cout << "pokemons de cuatro " << hola.Pokemons(4).SiguienteClave() <<", " <<hola.Pokemons(4).SiguienteSignificado() << endl;
	cout << "pokemons de seis " << hola.Pokemons(6).SiguienteClave() <<", " <<hola.Pokemons(6).SiguienteSignificado() << endl;
	hola.moverse(dos, tercera);
	hola.moverse(dos, tercera);
	hola.moverse(dos, tercera);
	hola.moverse(dos, tercera);
	hola.moverse(dos, tercera);
	//Conj<Nat> dummy3;
	//hola.Expulsados(dummy3);
	ASSERT(hola.Expulsados().Pertenece(dos));	
	ASSERT(hola.CantPokemonTotales()== 5);
	
	
}

void lonely_soldier_boy(){
	Mapa m;
	Coordenada primera(1,1);
	Coordenada segunda(1,2);
	Coordenada tercera(5, 5);
	Coordenada cuarta(1,3);
	Coordenada quinta(1, 4);
	Coordenada sexta(1, 5);
	Coordenada septima(1, 6);
	Coordenada octava(1,7);
	Coordenada novena(1,8);
	Coordenada decima(1,9);
	Coordenada onceava(5,6);	
	ASSERT(onceava.distEuclidea(primera)> 25);
	ASSERT(onceava.distEuclidea(primera) <100);
	ASSERT(tercera.distEuclidea(primera)> 25);
	ASSERT(tercera.distEuclidea(primera) <100);
	m.agregarCoord(primera);
	m.agregarCoord(segunda);//aca
	m.agregarCoord(tercera);
	m.agregarCoord(cuarta);
	m.agregarCoord(quinta);
	m.agregarCoord(sexta);
	m.agregarCoord(septima);
	m.agregarCoord(octava);
	m.agregarCoord(novena);
	m.agregarCoord(decima);
	m.agregarCoord(onceava);	
	Juego hola(m);
	Nat cero = hola.AgregarJugador();
	Nat uno = hola.AgregarJugador();
	Nat dos = hola.AgregarJugador();
	Nat tres = hola.AgregarJugador();
	Nat cuatro = hola.AgregarJugador();
	Nat cinco = hola.AgregarJugador();
	Nat seis = hola.AgregarJugador();
	Nat siete = hola.AgregarJugador();
	hola.conectarse(dos, primera);
	hola.conectarse(cero,tercera);
	hola.AgregarPokemon("torchit", cuarta);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.AgregarPokemon("torchit", cuarta);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.AgregarPokemon("jericho", cuarta);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.AgregarPokemon("gabumon", cuarta);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.AgregarPokemon("gabumon", sexta);
	hola.moverse(dos, septima);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(cero, tercera);
	hola.moverse(dos, tercera);
	hola.moverse(dos, tercera);
	hola.moverse(dos, tercera);
	hola.moverse(dos, tercera);
	hola.moverse(dos, tercera);
	ASSERT(hola.CantPokemonTotales() == 0);
	
}


//poner jugador
//poner pokemon
//capturar
//3 veces +
//moverse
//capturar otro
//todo bien
//expulso
//veo que quede bien


void posPokemonCercano(){
	Mapa m;
	Coordenada existe(0,0);
	Coordenada primera(1,1);
	Coordenada segunda(1,2);
	Coordenada tercera(5, 5);
	Coordenada cuarta(1,3);
	Coordenada quinta(1, 4);
	Coordenada sexta(1, 5);
	Coordenada septima(1, 6);
	Coordenada octava(1,7);
	Coordenada novena(1,8);
	Coordenada decima(1,9);
	Coordenada onceava(5,6);
	Conj<Coordenada> cs;
	cs.Agregar(existe);	
	cs.Agregar(primera);
	cs.Agregar(segunda);//aca
	cs.Agregar(tercera);
	cs.Agregar(cuarta);
	cs.Agregar(quinta);
	cs.Agregar(sexta);
	cs.Agregar(septima);
	cs.Agregar(octava);
	cs.Agregar(novena);
	cs.Agregar(decima);
	cs.Agregar(onceava);	
	Driver hola(cs);//Juego hola(m);
	Nat cero = hola.agregarJugador();
	Nat uno = hola.agregarJugador();
	Nat dos = hola.agregarJugador();
	Nat tres = hola.agregarJugador();
	Nat cuatro = hola.agregarJugador();
	Nat cinco = hola.agregarJugador();
	Nat seis = hola.agregarJugador();
	Nat siete = hola.agregarJugador();
	/*ASSERT(hola.puedoAgregarPokemon(primera));
	ASSERT(hola.puedoAgregarPokemon(segunda));
	ASSERT(hola.puedoAgregarPokemon(tercera));
	ASSERT(hola.puedoAgregarPokemon(cuarta));
	ASSERT(hola.puedoAgregarPokemon(quinta));
	ASSERT(hola.puedoAgregarPokemon(sexta));
	ASSERT(hola.puedoAgregarPokemon(septima));
	ASSERT(hola.puedoAgregarPokemon(octava));
	ASSERT(hola.puedoAgregarPokemon(novena));
	ASSERT(hola.puedoAgregarPokemon(decima));
	ASSERT(hola.puedoAgregarPokemon(onceava));
	ASSERT(hola.puedoAgregarPokemon(existe));*/
	hola.agregarPokemon("torchit", primera);
	/*ASSERT(!hola.puedoAgregarPokemon(existe));
	ASSERT(!hola.puedoAgregarPokemon(segunda));
	ASSERT(!hola.puedoAgregarPokemon(cuarta));
	ASSERT(!hola.puedoAgregarPokemon(quinta));
	ASSERT(!hola.puedoAgregarPokemon(sexta));
	ASSERT(!hola.puedoAgregarPokemon(septima));
	ASSERT(hola.puedoAgregarPokemon(octava));
	ASSERT(hola.puedoAgregarPokemon(novena));*/
	hola.agregarPokemon("mew", novena);
	//ASSERT(hola.pokemonEnPos(novena) == "mew");
	//ASSERT(hola.pokemonEnPos(primera) == "torchit");
	hola.conectarse(cero, existe);
	//ASSERT(existe.distEuclidea(primera)<= 4);
	//ASSERT(!hola.HayPokemonCercano(hola.posicion(cero)));
	//ASSERT(hola.BuscarHeap(hola.posicion(cero)) == primera);
	hola.conectarse(uno, cuarta);
	//ASSERT(hola.HayPokemonCercano(hola.posicion(uno)));
	//ASSERT(hola.BuscarHeap(hola.posicion(uno)) == primera);
	hola.conectarse(dos, cuarta);
	hola.conectarse(tres, cuarta);
	hola.conectarse(cuatro, cuarta);
	hola.conectarse(cinco, octava );	
	//cout << hola.CantMovimientosParaCaptura(primera)<<endl;
	//ASSERT(hola.BuscarHeap(hola.posicion(dos)) == primera);
	//ASSERT(hola.BuscarHeap(hola.posicion(tres)) == primera);
	//ASSERT(hola.BuscarHeap(hola.posicion(cuatro)) == primera);
	//ASSERT(!hola.BuscarHeap(hola.posicion(cinco)) == novena);
	//ASSERT(octava.distEuclidea(primera) > 25);
	//cout << hola.CantMovimientosParaCaptura(primera)<<endl;
	hola.moverse(cinco, octava);
	hola.moverse(cinco, octava);
	hola.moverse(cinco, octava);
	hola.moverse(cinco, octava);
	hola.moverse(cinco, octava);
	hola.moverse(cinco, octava);
	//cout << hola.CantMovimientosParaCaptura(primera)<<endl;
	hola.moverse(cinco, octava);
	hola.moverse(cinco, octava);
	
	//cout << hola.CantMovimientosParaCaptura(primera)<<endl;
	hola.moverse(cinco, octava);
	hola.moverse(cinco, octava);
	ASSERT(primera.distEuclidea(cuarta)<= 4);
	ASSERT(hola.pokemons(cuatro).Definido("torchit"));
//	ASSERT(!hola.pokemons(tres).HaySiguiente());
//	ASSERT(!hola.pokemons(dos).HaySiguiente());
//	ASSERT(!hola.pokemons(uno).HaySiguiente());
/*	ASSERT(!hola.HayPokemonCercano(hola.posicion(uno)));
	ASSERT(hola.puedoAgregarPokemon(existe));
	ASSERT(hola.puedoAgregarPokemon(primera));*/
	hola.agregarPokemon("snorlax", primera);		
	//ASSERT(!hola.puedoAgregarPokemon(hola.posicion(cero)));
	hola.moverse(cinco, octava);
	hola.moverse(cinco, octava);
	hola.moverse(cinco, octava);
	hola.moverse(cinco, octava);
	hola.moverse(cinco, octava);
	hola.moverse(cinco, octava);
	//cout << hola.CantMovimientosParaCaptura(primera)<<endl;
	hola.moverse(cinco, octava);
	hola.moverse(cinco, octava);
	//cout << hola.CantMovimientosParaCaptura(primera)<<endl;
	hola.moverse(cinco, octava);	
	hola.moverse(cinco, octava);
	ASSERT(hola.pokemons(cuatro).Definido("torchit"));
	ASSERT(hola.pokemons(tres).Definido("snorlax"));	
	//ASSERT(!hola.pokemons(dos).HaySiguiente());
	//ASSERT(!hola.pokemons(uno).HaySiguiente());
	ASSERT(hola.puedoAgregarPokemon(existe));
	ASSERT(hola.puedoAgregarPokemon(primera));
	hola.agregarPokemon("gabumon", primera);
	ASSERT(!hola.puedoAgregarPokemon(hola.posicion(cero)));
	hola.moverse(cinco, octava);
	hola.moverse(cinco, octava);
	hola.moverse(cinco, octava);
	hola.moverse(cinco, octava);
	hola.moverse(cinco, octava);
	hola.moverse(cinco, octava);
	//cout << hola.CantMovimientosParaCaptura(primera)<<endl;
	hola.moverse(cinco, octava);
	hola.moverse(cinco, octava);
	//cout << hola.CantMovimientosParaCaptura(primera)<<endl;
	hola.moverse(cinco, octava);
	hola.moverse(cinco, octava);
	ASSERT(hola.pokemons(cuatro).Definido("torchit"));	
	ASSERT(hola.pokemons(tres).Definido("snorlax"));
	ASSERT(hola.pokemons(dos).Definido("gabumon"));
	//ASSERT(!hola.pokemons(uno).HaySiguiente());
	ASSERT(hola.puedoAgregarPokemon(existe));
	ASSERT(hola.puedoAgregarPokemon(primera));
	hola.agregarPokemon("mew", primera);
	ASSERT(!hola.puedoAgregarPokemon(hola.posicion(cero)));
	hola.moverse(cinco, octava);
	hola.moverse(cinco, octava);
	hola.moverse(cinco, octava);
	hola.moverse(cinco, octava);
	hola.moverse(cinco, octava);
	hola.moverse(cinco, octava);
	//cout << hola.CantMovimientosParaCaptura(primera)<<endl;
	hola.moverse(cinco, octava);
	hola.moverse(cinco, octava);
	//cout << hola.CantMovimientosParaCaptura(primera)<<endl;
	hola.moverse(cinco, octava);
	hola.moverse(cinco, octava);
	ASSERT(hola.pokemons(cuatro).Definido("torchit"));
	ASSERT(hola.pokemons(tres).Definido("snorlax"));
	ASSERT(hola.pokemons(dos).Definido("gabumon"));
	ASSERT(hola.pokemons(uno).Definido("mew"));
	ASSERT(hola.puedoAgregarPokemon(existe));
	ASSERT(hola.puedoAgregarPokemon(primera));
	
	
	
	
	
	
	
}

void generarCaptura(Driver& d,Nat e,Coordenada c){
	d.moverse(e,c);
	d.moverse(e,c);
	d.moverse(e,c);
	d.moverse(e,c);
	d.moverse(e,c);
	d.moverse(e,c);
	d.moverse(e,c);
	d.moverse(e,c);
	d.moverse(e,c);
	d.moverse(e,c);
}

void luis(){
	Mapa m;
	Coordenada existe(0,0);
	Coordenada primera(1,1);
	Coordenada segunda(1,2);
	Coordenada tercera(5, 5);
	Coordenada cuarta(1,3);
	Coordenada quinta(1, 4);
	Coordenada sexta(1, 5);
	Coordenada septima(1, 6);
	Coordenada octava(1,7);
	Coordenada novena(1,8);
	Coordenada decima(1,9);
//	Coordenada onceava(5,6);
	Conj<Coordenada> cs;
	cs.Agregar(existe);
	cs.Agregar(primera);
	cs.Agregar(segunda);
	cs.Agregar(tercera);
	cs.Agregar(cuarta);
	cs.Agregar(quinta);
	cs.Agregar(sexta);
	cs.Agregar(septima);
	cs.Agregar(octava);
	cs.Agregar(novena);
	cs.Agregar(decima);
	Driver juego(cs);
	cout <<"empieza el juego" <<endl;
	Nat ash= juego.agregarJugador();
	Nat gary= juego.agregarJugador();
	Nat alan= juego.agregarJugador();
	Nat korina= juego.agregarJugador();
	Nat shota = juego.agregarJugador();
	juego.conectarse(ash,primera);
	juego.conectarse(gary,primera);
	juego.conectarse(alan,tercera);
	juego.conectarse(korina,sexta);
	juego.conectarse(shota,decima);
	juego.agregarPokemon("umbreon",primera);
	cout <<"empieza el juego1" <<endl;
	juego.agregarPokemon("charizard",tercera);
	cout <<"empieza el juego2" <<endl;
	juego.agregarPokemon("lucario",sexta);
	cout <<"empieza el juego3" <<endl;
	juego.agregarPokemon("sceptile",decima);
	cout <<"empieza el juego4" <<endl;
	generarCaptura(juego,ash,primera);
	/*juego.moverse(ash, primera);
	juego.moverse(ash,primera);
	juego.moverse(ash,primera);
	juego.moverse(ash,primera);
	juego.moverse(ash, primera);
	juego.moverse(ash, primera);
	juego.moverse(ash, primera);
	juego.moverse(ash, primera);
	juego.moverse(ash, primera);
	juego.moverse(ash, primera);*/

	cout <<"empieza el juego5" <<endl;
	
}



void habra_camino(){
	Mapa m;
	Coordenada existe(0,0);
	Coordenada primera(1,1);
	Coordenada segunda(1,2);
	Coordenada tercera(5, 5);
	Coordenada cuarta(1,3);
	Coordenada quinta(1, 4);
	Coordenada sexta(1, 5);
	Coordenada septima(1, 6);
	Coordenada octava(1,7);
	Coordenada novena(1,8);
	Coordenada decima(1,9);
//	Coordenada onceava(5,6);
	Conj<Coordenada> cs;
	cs.Agregar(existe);
	cs.Agregar(primera);
	cs.Agregar(segunda);
	cs.Agregar(tercera);
	cs.Agregar(cuarta);
	cs.Agregar(quinta);
	cs.Agregar(sexta);
	cs.Agregar(septima);
	cs.Agregar(octava);
	cs.Agregar(novena);
	cs.Agregar(decima);
	Driver juego(cs);
ASSERT(juego.hayCamino(primera, segunda));
ASSERT	(juego.hayCamino(primera, cuarta));
ASSERT	(juego.hayCamino(segunda,cuarta));
ASSERT(juego.hayCamino(primera, sexta));
ASSERT(juego.hayCamino(segunda,sexta));
ASSERT(	juego.hayCamino(cuarta,sexta));
ASSERT(juego.hayCamino(quinta, primera));
ASSERT(	juego.hayCamino(primera, decima));
ASSERT(juego.hayCamino(octava, segunda));
ASSERT(juego.hayCamino(tercera, primera)==false);
	/*cout <<"empieza el juego" <<endl;
	Nat ash= juego.agregarJugador();
	Nat gary= juego.agregarJugador();
	Nat alan= juego.agregarJugador();
	Nat korina= juego.agregarJugador();
	Nat shota = juego.agregarJugador();
	juego.conectarse(ash,primera);
	juego.conectarse(gary,primera);
	juego.conectarse(alan,tercera);
	juego.conectarse(korina,sexta);
	juego.conectarse(shota,decima);
	juego.agregarPokemon("umbreon",primera);
	cout <<"empieza el juego1" <<endl;
	juego.agregarPokemon("charizard",tercera);
	cout <<"empieza el juego2" <<endl;
	juego.agregarPokemon("lucario",sexta);
	cout <<"empieza el juego3" <<endl;
	juego.agregarPokemon("sceptile",decima);
	cout <<"empieza el juego4" <<endl;
	generarCaptura(juego,ash,primera);
	/*juego.moverse(ash, primera);
	juego.moverse(ash,primera);
	juego.moverse(ash,primera);
	juego.moverse(ash,primera);
	juego.moverse(ash, primera);
	juego.moverse(ash, primera);
	juego.moverse(ash, primera);
	juego.moverse(ash, primera);
	juego.moverse(ash, primera);
	juego.moverse(ash, primera);*/

	cout <<"empieza el juego5" <<endl;
	
}



void Jugadores_Son(){
	Mapa m;
	Coordenada existe(0,0);
	Coordenada primera(1,1);
	Coordenada segunda(1,2);
	Coordenada tercera(5, 5);
	Coordenada cuarta(1,3);
	Coordenada quinta(1, 4);
	Coordenada sexta(1, 5);
	Coordenada septima(1, 6);
	Coordenada octava(1,7);
	Coordenada novena(1,8);
	Coordenada decima(1,9);
//	Coordenada onceava(5,6);
	Conj<Coordenada> cs;
	cs.Agregar(existe);
	cs.Agregar(primera);
	cs.Agregar(segunda);
	cs.Agregar(tercera);
	cs.Agregar(cuarta);
	cs.Agregar(quinta);
	cs.Agregar(sexta);
	cs.Agregar(septima);
	cs.Agregar(octava);
	cs.Agregar(novena);
	cs.Agregar(decima);
	Driver juego(cs);
	cout <<"empieza el juego" <<endl;
	/*Nat ash= juego.agregarJugador();
	Nat gary= juego.agregarJugador();
	Nat alan= juego.agregarJugador();
	Nat korina= juego.agregarJugador();
	Nat shota = juego.agregarJugador();
	ASSERT(juego.jugadores().Pertenece(ash));
	ASSERT(juego.jugadores().Pertenece(alan));
	ASSERT(juego.jugadores().Pertenece(gary));
	ASSERT(juego.jugadores().Pertenece(korina));
	ASSERT(juego.jugadores().Pertenece(shota));
	juego.conectarse(ash,primera);*/
	int i=0;
	while(i<100){
		juego.agregarJugador();
		i++;
	}
	Conj<Nat> jug = juego.jugadores();
	Conj<Nat>::Iterador it = jug.CrearIt();
	while(it.HaySiguiente()){
		cout << it.Siguiente() <<endl;
		it.Avanzar();
	}
	juego.conectarse(1,tercera);
	juego.conectarse(0,primera);
	juego.agregarPokemon("snorlax", primera);	
	cout << juego.posPokemonCercano(segunda).latitud() << "  " <<juego.posPokemonCercano(segunda).longitud() <<endl;
	cout << juego.posPokemonCercano(primera).latitud() << "  " <<juego.posPokemonCercano(primera).longitud() <<endl;
	cout << juego.posPokemonCercano(cuarta).latitud() << "  " <<juego.posPokemonCercano(cuarta).longitud() <<endl;
	generarCaptura(juego,1,tercera);

	juego.agregarPokemon("greninja", segunda);
	cout << juego.posPokemonCercano(segunda).latitud() << "  " <<juego.posPokemonCercano(segunda).longitud() <<endl;
	cout << juego.posPokemonCercano(primera).latitud() << "  " <<juego.posPokemonCercano(primera).longitud() <<endl;
	cout << juego.posPokemonCercano(cuarta).latitud() << "  " <<juego.posPokemonCercano(cuarta).longitud() <<endl;
	/*juego.conectarse(gary,primera);
	juego.conectarse(alan,tercera);
	juego.conectarse(korina,sexta);
	juego.conectarse(shota,decima);*/
	//typename Juego::const_Iterador it = juego.CrearIt();

	//ASSERT(juego.jugadores().EsVacio() == false);
	//ASSERT(juego.Jugadores().Siguiente()== ash);

}

































int main() {
	RUN_TEST(Jugadores_Son);
	/*RUN_TEST(luis);
	RUN_TEST(habra_camino);
	RUN_TEST(compila);
	RUN_TEST(AgregaJugador);
	RUN_TEST(conectar);
	RUN_TEST(desconectar);
	RUN_TEST(AgregoPokemon);
	RUN_TEST(Conecto_cerca_de_pokemon);
	RUN_TEST(Agrego_pok_cerca_de_jugador);
	RUN_TEST(Agrego_Juegador_cerca);
	RUN_TEST(Agrego_cercanos);
	RUN_TEST(Moverse);
	RUN_TEST(dos_capturas);
	RUN_TEST(se_desconecta);
	RUN_TEST(Me_Voy);
	RUN_TEST(Entro);
	RUN_TEST(Expulsion_del_Eden);
	RUN_TEST(salgo_y_entro);
	RUN_TEST(se_desconecta_real);
	RUN_TEST(me_muevo_esperando);
	RUN_TEST(indiceDeRareza);
	RUN_TEST(cuatro_capturas);
	RUN_TEST(lonely_soldier_boy);
	RUN_TEST(posPokemonCercano);*/
	return 0;
}






