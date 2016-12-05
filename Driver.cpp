#include "Driver.h"
#include "Juego.h"
#include "TiposJuego.h"
// Instanciar un mapa y un juego

Mapa coorsAMapa(const Conj< Coordenada > & cs) {
    Conj< Coordenada >::const_Iterador it = cs.CrearIt();
    Mapa m;
    while(it.HaySiguiente()) {
        m.agregarCoord(it.Siguiente());
        it.Avanzar();
    }
    return m;
}

Driver::Driver(const Conj< Coordenada > & cs) : game(coorsAMapa(cs)) {}
/*{
	Conj< Coordenada >::const_Iterador it = cs.CrearIt();
	Mapa m;
	while(it.HaySiguiente()){
		m.agregarCoord(it.Siguiente());
		it.Avanzar();
	}
	game(m);
}*/

Driver::~Driver()
{

}

void Driver::agregarPokemon(const Pokemon & p, const Coordenada & c)
{
    game.AgregarPokemon(p,c);
}

Jugador Driver::agregarJugador() {
    return game.AgregarJugador();
}

void Driver::conectarse(const Jugador & j, const Coordenada & c) {
    game.conectarse(j,c);
}

void Driver::desconectarse(const Jugador & j) {
    game.desconectarse(j);
}

void Driver::moverse(const Jugador & j, const Coordenada & c) {
    game.moverse(j,c);
}

Conj< Coordenada > Driver::mapa() const {
    return (game.VerMapa()).coordenadasMapa();
}

bool Driver::hayCamino(const Coordenada & c1, const Coordenada & c2) const {
    return (game.VerMapa()).hayCamino(c1,c2);
}

bool Driver::posExistente(const Coordenada & c) const {
    return (game.VerMapa()).posEnMapa(c);
}
Conj< Jugador > Driver::jugadores() const {
	Juego::const_Iterador it = game.Jugadores();
    Conj< Jugador > res;
    while(it.HaySiguiente()){
    	res.AgregarRapido((it.Siguiente()));
    	it.Avanzar();
    }
    return res;
   //return game.losjugadores();//it.Siguientes();//game.losjugadores();//game.JugadoresConj(it);
}
bool Driver::estaConectado(const Jugador & j) const {
    return (game.estaConectado(j));
}
Nat Driver::sanciones(const Jugador & j) const {
    return (game.sanciones(j));
}
Coordenada Driver::posicion(const Jugador & j) const {
    return (game.posicion(j));
}

Dicc< Pokemon , Nat > Driver::pokemons(const Jugador & j) const {
    DiccString< Nat >::const_Iterador it(game.Pokemons(j));
    Dicc< Pokemon , Nat > res;
    while(it.HaySiguiente()) {
        res.DefinirRapido(it.SiguienteClave(), it.SiguienteSignificado());
        it.Avanzar();
    }
    return res;
}
Conj< Jugador > Driver::expulsados() const {
    return game.Expulsados();
}

Conj< Coordenada > Driver::posConPokemons() const {
    return game.posConPokemons();
}

Pokemon Driver::pokemonEnPos(const Coordenada & c) const {
    return game.pokemonEnPos(c);
}
Nat Driver::cantMovimientosParaCaptura(const Coordenada & c) const {
    return game.CantMovimientosParaCaptura(c);
}
bool Driver::puedoAgregarPokemon(const Coordenada & c) const {
    return game.puedoAgregarPokemon(c);

}
bool Driver::hayPokemonCercano(const Coordenada & c) const {
    return game.HayPokemonCercanoDriver(c);
}
Coordenada Driver::posPokemonCercano(const Coordenada & c) const {
    return game.BuscarHeapDriver(c);
}
Conj<Jugador> Driver::entrenadoresPosibles(const Coordenada & c) const {
    /*Conj<typename Juego::capturadosyID>  entrenadores = game.cercanos(c);
    Conj<typename Juego::capturadosyID>::const_Iterador it = entrenadores.CrearIt();
    Conj<Jugador> res;
    while(it.HaySiguiente()){
    	res.AgregarRapido(it.Siguiente().ID);
    	it.Avanzar();
    }
    return res;*/
    return game.cercanosEntrenadores(c);
}
Nat Driver::indiceRareza(const Pokemon & p) const {
    return game.indiceDeRareza(p);
}
Nat Driver::cantPokemonsTotales() const {
    return game.CantPokemonTotales();
}
Nat Driver::cantMismaEspecie(const Pokemon & p) const {
    return game.cantMismaEspecie(p);
}
// TODO: Completar con el resto de las implementaciones


