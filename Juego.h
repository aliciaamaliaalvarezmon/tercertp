#ifndef AED2_JUEGO_H_
#define AED2_JUEGO_H_

#include <ostream>
#include "TiposBasicos.h"
#include <string>
#include "DiccString.h"
#include "ColadeprioridadH.h"
#include "Mapa.h"
#include "Conj.h"
#include "Dicc.h"
#include "Vector.h"


using namespace std;
namespace aed2
{
	class Juego{
	public:
		class Iterador;
		class const_Iterador;
		Juego();
		Juego(Mapa m);
		Juego(const Conj<Coordenada> cs);
		
		
	  Nat AgregarJugador();
	  Coordenada BuscarHeapDriver(Coordenada c) const;

		bool HayPokemonCercanoDriver(Coordenada c) const;

	  bool puedoAgregarPokemon(Coordenada c) const;

       void AgregarPokemon(string p, Coordenada c);

       void conectarse(Nat e, Coordenada c);

       void desconectarse(Nat e);

       void moverse(Nat e, Coordenada c);

       Mapa VerMapa() const;

       Juego::const_Iterador Jugadores();

       Conj<Nat> losjugadores()const;

       bool estaConectado(Nat e) const;

       Nat sanciones(Nat e) const;

       Coordenada posicion(Nat e) const;

      DiccString< Nat >::const_Iterador  Pokemons(Nat e) const;

      Conj<Nat> Expulsados() const;

      //La aridad no es la misma del tp
      Conj<Coordenada> posConPokemons() const; 

       String pokemonEnPos(Coordenada c) const;

      Nat CantMovimientosParaCaptura(Coordenada c) const;

       Nat ProxID();

		Nat MostrarTope(Nat a, Nat b);
	
       Conj<Nat> JugadoresConectados();
      
       Nat indiceDeRareza(string p) const;

       Nat CantPokemonTotales() const;

       bool HayPokemonCercano(Coordenada c) const;

       Coordenada PosDePokemonCercano(Coordenada c);   

       Nat cantMismaEspecie(const Pokemon & p) const;         

       Iterador CrearIt(); 
       const_Iterador CrearIt() const; 

        Nat matrizJUGADORESLongitud();
		Nat matrizPOKEMONLongtitud();
		Nat matrizJUGADORESLatitud();
		Nat matrizPOKEMONLatitud();
	bool HayUnJugadorCercano(Coordenada c);
 
	private:	

		struct capturadosyID
		{
			Nat numero;
			Nat ID;

			capturadosyID(): numero(0), ID(0){}; 
			capturadosyID(const Nat num,const Nat i ): numero(num), ID(i){};			

			bool operator < (const typename Juego::capturadosyID& otra) const;
			bool operator == (const typename Juego::capturadosyID& otra) const;
			bool operator > (const typename Juego::capturadosyID& otra) const;
			//podria ser const al final


		};



		struct dataJugador
		{
			bool conexion;
			Nat sanciones;
			Coordenada posicion;
			Nat pokTotalAtrapados;
			Lista<DiccString<Nat> >::Iterador pokemonescapturados;
			Dicc<Nat, Coladeprioridad < typename Juego::capturadosyID >::Iterador>::Iterador posenColaDeCaptura;
			

			dataJugador()
			: conexion(0), sanciones(0), posicion(), pokTotalAtrapados(0), pokemonescapturados(), posenColaDeCaptura()
			{}
		

		};


		
		struct dataPokemon
		{
			Nat PS;
			Nat PC;	

			dataPokemon(): PS(0), PC(0){}; 
			dataPokemon(Nat s, Nat c): PS(s), PC(c){};
			
		};

		struct infoHeap
		{
			Coladeprioridad<typename Juego::capturadosyID> heap_;
			bool HayBasura_;
			Nat contador_;

			infoHeap(): heap_(), HayBasura_(true), contador_(0) {};//el haybasura, al poner el pokemon, pasa a ser false
		};

		Mapa mundo_;
		Vector<typename Juego::dataJugador> vectJug_;
		DiccString<typename Juego::dataPokemon> pokemones_;
		Vector<Vector<Dicc<Nat, Coladeprioridad<typename Juego::capturadosyID>::Iterador> > > matrizJugadores_;//(pokcapturados, ID)
		Vector<Vector<typename Juego::infoHeap> > matrizPokemon_;
		Dicc<Coordenada, String> posdePokemon_;//(coordenada,pokemon)
		Lista<DiccString<Nat> > pokemonsXjug_;//puede estar dentro de data jugador
		Nat cantPokemon_;
		


		
		Vector<Vector<Dicc<Nat, Coladeprioridad<typename Juego::capturadosyID>::Iterador> > > crearMatrizJug(Nat n, Nat m);

		Vector<Vector< typename Juego::infoHeap> > crearMatrizPok(Nat n, Nat m);
		
		

	

		bool estaParaCaptura(Coordenada posDelJug);

		

		void AuxCapturarPokemon(Dicc<Coordenada, string>::Iterador& it);

		
		void Claves(Dicc<Coordenada, string> dicc, Conj<Coordenada>& vacio) const;
		void Claves(Dicc<Nat, Coladeprioridad<typename Juego::capturadosyID>::Iterador > dicc, Conj<Nat>& vacio) const;
	

		

	public:
		Coordenada BuscarHeap(Coordenada c) const;
		Conj<typename Juego::capturadosyID> cercanos(Coordenada c) const;
		Conj<Nat> cercanosEntrenadores(Coordenada c) const;
   class Iterador
  		{
    	    public:     

      	Iterador(const typename Juego::Iterador& otro);

     	Iterador& operator = (const typename Juego::Iterador& otro);

      	bool HaySiguiente();// const;
     
      	Nat Siguiente();

     	void Avanzar();


   


  	private:

    
    	//typename Juego::dataJugador
      	Vector<dataJugador>* elementos_;
      	Nat posicion_;


      	Iterador(){
        elementos_= NULL;
        posicion_ = 0;        
      }

      	Iterador(Vector<dataJugador>* jug){
      	elementos_ = jug;
      	posicion_ =  0;		
      	}
      

      friend typename Juego::Iterador Juego::CrearIt();
      friend class Juego::const_Iterador; 
       
  };

    class const_Iterador
  		{
    	    public:     

      	const_Iterador(const typename Juego::const_Iterador& otro);
      	const_Iterador(const typename Juego::Iterador& otro);

     	const_Iterador& operator = (const typename Juego::const_Iterador& otro);

      	bool HaySiguiente() const;
     
      	Nat Siguiente();

     	void Avanzar();

     	Conj<Nat> Siguientes() const ;



  	private:

    
    	//typename Juego::dataJugador
      	Vector<dataJugador>* elementos_;
      	Nat posicion_;


      	const_Iterador(){
        elementos_= NULL;
        posicion_ = 0;        
      }

      	const_Iterador(Vector<dataJugador>* jug){
      	elementos_ = jug;
      	posicion_ =  0;		
      	}
      

      
      friend typename Juego::const_Iterador Juego::CrearIt() const; 
       
  };



 

  










		










	};
}



























#endif // AED2_JUEGO_H_INCLUDED
