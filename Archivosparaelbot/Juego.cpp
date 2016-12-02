#include "Juego.h"



using namespace aed2;



Juego::Juego()
	: mundo_(), vectJug_(), pokemones_(), matrizJugadores_(), matrizPokemon_(), posdePokemon_(), pokemonsXjug_(), cantPokemon_(0){}//, referenciasAConjCoor_(){}
	

Juego::Juego(Mapa m)	
	: mundo_(m), vectJug_(), pokemones_(), posdePokemon_(), pokemonsXjug_(), cantPokemon_(0)//, referenciasAConjCoor_()
	{
		matrizPokemon_ = crearMatrizPok(m.longitudMaxima(), m.latitudMaxima());
		matrizJugadores_ = crearMatrizJug(m.longitudMaxima(), m.latitudMaxima());
	}	

Juego::Juego(Conj<Coordenada> cs) 
	: mundo_(cs), vectJug_(), pokemones_(), posdePokemon_(), pokemonsXjug_(), cantPokemon_(0) {}
/*
Juego::~Juego(){
	Conj<Conj<Coordenada> * >::Iterador it = referenciasAConjCoor_.CrearIt();
	while(it.HaySiguiente()){
		//Coordenada* elem = it.Siguiente();
		delete(it.Siguiente());//elem);
		it.Avanzar();
	}

}
*/
	 Nat Juego::cantMismaEspecie(const Pokemon & p) const{
	 	return (pokemones_.Obtener(p).PS + pokemones_.Obtener(p).PC);
	 } 




	Nat Juego::AgregarJugador(){
		dataJugador nuevo;
		DiccString<Nat> vacio;
		Lista<DiccString<Nat> >::Iterador iter = pokemonsXjug_.AgregarAtras(vacio);
		nuevo.pokemonescapturados = iter;
		vectJug_.AgregarAtras(nuevo);		
		return (vectJug_.Longitud() - 1);		
	}

	void Juego::AgregarPokemon(string p, Coordenada c){		
		
		(posdePokemon_).DefinirRapido(c,p);	
		Conj<typename Juego::capturadosyID> entrenadores = cercanos(c);
		//cout << "cercanos"<< entrenadores.Cardinal() << endl;
		// jajajajaja, podemos romper todo.			
		if(!pokemones_.Definido(p)) {
			pokemones_.Definir(p, dataPokemon(1,0));			
		}else{			
			pokemones_.Obtener(p).PS++;			 
		}
		//agregamos pokemon a pokemones
		typename Juego::infoHeap heap;		
		matrizPokemon_[c.longitud()][c.latitud()] = heap;		
		Coladeprioridad<typename Juego::capturadosyID>* rompe = &(matrizPokemon_[c.longitud()][c.latitud()].heap_);
		matrizPokemon_[c.longitud()][c.latitud()].HayBasura_ = false;			
		Conj<typename Juego::capturadosyID>::Iterador it = entrenadores.CrearIt();
		while(it.HaySiguiente()){
			Dicc<Nat, Coladeprioridad<typename Juego::capturadosyID>::Iterador>* hola = (&(matrizJugadores_[vectJug_[it.Siguiente().ID].posicion.longitud()][vectJug_[it.Siguiente().ID].posicion.latitud()]));					
			vectJug_[it.Siguiente().ID].posenColaDeCaptura.EliminarSiguiente();		//sino define doble		
			vectJug_[it.Siguiente().ID].posenColaDeCaptura = (*hola).DefinirRapido(it.Siguiente().ID, (*rompe).Encolar(it.Siguiente())); //DefinirRapido
			it.Avanzar();	
			/*if ((*rompe).Claves()>0){
			cout << "tope" << (*(*rompe).HEAP()).Dato().ID << endl;
			//cout << "claves" << (*rompe).Claves() << endl;
			if((*rompe).Claves() > 1){
			cout << "izquierda"<< (*(*(*rompe).HEAP()).IZQUIERDA()).Dato().ID << endl;
			if((*rompe).Claves() > 2){
			cout << "derecha"<< (*(*(*rompe).HEAP()).DERECHA()).Dato().ID << endl;
			}
		}
		}*/
		}		
		cantPokemon_ ++;	
	}

	void Juego::conectarse(Nat e, Coordenada c){
		vectJug_[e].conexion = true;	
		Coladeprioridad<typename Juego::capturadosyID> nueva;
		Coladeprioridad<typename Juego::capturadosyID>::Iterador dummy = nueva.CrearIt();			
		if(estaParaCaptura(c)){			
			Coordenada ACapturar = BuscarHeap(c);			
			typename Juego::capturadosyID espera(vectJug_[e].pokTotalAtrapados, e);						
			typename Coladeprioridad<typename Juego::capturadosyID>::Iterador iteradoralheap = (matrizPokemon_[ACapturar.longitud()][ACapturar.latitud()].heap_).Encolar(espera);		
			//cout << "iteradoralheap  " << iteradoralheap.Siguiente().numero << ", "<< iteradoralheap.Siguiente().ID << endl;
			vectJug_[e].posenColaDeCaptura = matrizJugadores_[c.longitud()][c.latitud()].DefinirRapido(e, iteradoralheap ); 	
		}else{			
		vectJug_[e].posenColaDeCaptura = matrizJugadores_[c.longitud()][c.latitud()].DefinirRapido(e, dummy);
		}	
		if(HayPokemonCercano(c)){
			Coordenada PosdePokemon = BuscarHeap(c);
			matrizPokemon_[PosdePokemon.longitud()][PosdePokemon.latitud()].contador_ = 0;
		}
		vectJug_[e].posicion = c;
	}

	void Juego::desconectarse(Nat e){
		vectJug_[e].conexion = false;		
		Coordenada c = vectJug_[e].posicion;				
		if(estaParaCaptura(c)){				
			vectJug_[e].posenColaDeCaptura.SiguienteSignificado().borrarSiguiente();		
		}		
		if(vectJug_[e].posenColaDeCaptura.HaySiguiente()){
		vectJug_[e].posenColaDeCaptura.EliminarSiguiente(); //elimino de la matriz Jugador
		}		
	}

void Juego::moverse(Nat e, Coordenada c){		
		Coordenada antiguaPos =  vectJug_[e].posicion; 
		//cout << "antiguaPos" <<  vectJug_[e].posicion.latitud()<< vectJug_[e].posicion.longitud() << endl;		
	if (not( antiguaPos.distEuclidea(c) > 100 or not mundo_.hayCamino(antiguaPos,c))){			
		vectJug_[e].posicion = c ;
		if(estaParaCaptura(antiguaPos)){				
			Coordenada AntiguoHeap = BuscarHeap(antiguaPos);
			Dicc<Nat, Coladeprioridad<typename Juego::capturadosyID>::Iterador>::Iterador bip = (matrizJugadores_[AntiguoHeap.longitud()][AntiguoHeap.latitud()].CrearIt() );			
			(vectJug_[e].posenColaDeCaptura.SiguienteSignificado()).borrarSiguiente();
			vectJug_[e].posenColaDeCaptura.EliminarSiguiente();	
		} 		
		if(estaParaCaptura(c)){	
				
			Coordenada VoyACapturarEste = BuscarHeap(c);					
			typename Juego:: capturadosyID captura(vectJug_[e].pokTotalAtrapados, e);						
			Coladeprioridad<typename Juego::capturadosyID>::Iterador iteradorAlHeap = ((matrizPokemon_[VoyACapturarEste.longitud()][VoyACapturarEste.latitud()]).heap_).Encolar(captura); 
			Dicc<Nat, Coladeprioridad<typename Juego::capturadosyID>::Iterador>::Iterador  posencola = matrizJugadores_[c.longitud()][c.latitud()].Definir(e,iteradorAlHeap);        
			vectJug_[e].posenColaDeCaptura = posencola; 
		}
		if(HayPokemonCercano(c) && HayPokemonCercano(antiguaPos)){		
			if (not(BuscarHeap(c) == BuscarHeap(antiguaPos))){							
			Coordenada PosDePokemon = BuscarHeap(c);
			(matrizPokemon_[PosDePokemon.longitud()][PosDePokemon.latitud()]).contador_  = 0;			
			Coordenada PosAnteriorDePokemon = BuscarHeap(antiguaPos);			
			if((matrizPokemon_[PosAnteriorDePokemon.longitud()][PosAnteriorDePokemon.latitud()]).heap_.EsVacia()){
			(matrizPokemon_[PosAnteriorDePokemon.longitud()][PosAnteriorDePokemon.latitud()]).contador_  = 0;	
			}			
		}

	} 
	else
	{
		
		if(HayPokemonCercano(c)){					
			Coordenada PosDePokemon = BuscarHeap(c); 
			(matrizPokemon_[PosDePokemon.longitud()][PosDePokemon.latitud()]).contador_  = 0;
		}
	}

		/*Coordenada PosDePokemon = BuscarHeap(c);*/ 		
		Dicc<Coordenada,String>::Iterador it = posdePokemon_.CrearIt(); 									
		while(it.HaySiguiente()){ 			
			if(HayPokemonCercano(c) && not(BuscarHeap(c) == it.SiguienteClave())){									
				//Coordenada posPokemon   = it.SiguienteClave();//problema con ref, por eso no se usa
				infoHeap &posActual = matrizPokemon_[it.SiguienteClave().longitud()][it.SiguienteClave().latitud()];
				if(HayUnJugadorCercano(it.SiguienteClave())){
				//	cout << "llega" << endl;
					(posActual).contador_ += 1;					
				}
				if((posActual).contador_ ==10){
					AuxCapturarPokemon(it) ;
					//cout << matrizPokemon_[it.SiguienteClave().longitud()][it.SiguienteClave().latitud()].HayBasura_ <<endl;
					it.EliminarSiguiente();					
				}else{
					if(it.HaySiguiente()){							
							it.Avanzar();
					}
				}				
			
			}
			else
			{ 
				//Coordenada &posPokemon  = it.SiguienteClave();
				infoHeap &posActual = matrizPokemon_[it.SiguienteClave().longitud()][it.SiguienteClave().latitud()];				
				if (not HayPokemonCercano(c)){				 
					if(HayUnJugadorCercano(it.SiguienteClave())){				
						posActual.contador_ += 1;							
					}
				}				
				if((posActual).contador_ ==10){ 									
						AuxCapturarPokemon(it);	
						//cout << matrizPokemon_[it.SiguienteClave().longitud()][it.SiguienteClave().latitud()].HayBasura_ <<endl;											
						it.EliminarSiguiente();		//el eliminar siguiente avanza el iterador																
					}else{						
						if(it.HaySiguiente()){							
							it.Avanzar();							
						}
					}					
			}		
		//	if(it.HaySiguiente()){				//el borrar avanza, por lo que el avanzar no hace falta	 siempre		
		//	it.Avanzar();//	}			
		}
	}
		if( antiguaPos.distEuclidea(c) > 100 or not mundo_.hayCamino(antiguaPos,c)){										
			vectJug_[e].sanciones = vectJug_[e].sanciones+1;
			if(vectJug_[e].sanciones==5){						
				if(HayPokemonCercano(antiguaPos)){//decia c en vez de antiguaPos					
					Coordenada VoyACapturarEste = BuscarHeap(antiguaPos);					
					if(mundo_.hayCamino(VoyACapturarEste,antiguaPos)){ 
						//Coladeprioridad<typename Juego::capturadosyID>	heap = matrizPokemon_[VoyACapturarEste.latitud()][VoyACapturarEste.longitud()].heap_;
					//(heap, vectJug_[e].posenColaDeCaptura.SiguienteSignificado()).borrarSiguiente();						 
						 (vectJug_[e].posenColaDeCaptura.SiguienteSignificado()).borrarSiguiente();						 
					}
				}											
				cantPokemon_ = cantPokemon_ - vectJug_[e].pokTotalAtrapados; 
				vectJug_[e].conexion = false; 					
				vectJug_[e].posicion = Coordenada(0,0);													
				DiccString<Nat>::Iterador itapokecap((vectJug_[e].pokemonescapturados.Siguiente()).CrearIt());															
				while(vectJug_[e].pokemonescapturados.Siguiente().CantClaves() > 0 ){ //itapokecap.HaySiguiente()						
					dataPokemon& pok = pokemones_.Obtener(itapokecap.SiguienteClave());	
					pok.PC = pok.PC - itapokecap.SiguienteSignificado(); 	
					//cout << "llega"<<endl;																
					if(pok.PS ==0 and pok.PC==0){	
						pokemones_.Borrar(itapokecap.SiguienteClave());															
						//el borrar siguiente "avanza" la clave					
					}
					//cout << "llega"<<endl;
					itapokecap.BorrarSiguiente();				
				}			
			
		}
		}	
		//cout << matrizPokemon_[1][1].HayBasura_ <<endl;
		//cout << "llega" << endl;	
		//cout << "contador" << matrizPokemon_[1][1].contador_<<endl;
		//cout << "llega"<< endl;
	} 

Nat Juego::MostrarTope(Nat a, Nat b){
return	matrizPokemon_[a][b].heap_.tope().ID;
}

	Mapa Juego::VerMapa() const{
		return mundo_;
	}


	typename Juego::const_Iterador Juego::Jugadores(){
		typename Juego::const_Iterador nuevo = CrearIt();
		return nuevo;
	}

	bool Juego::estaConectado(Nat e) const{				
		return vectJug_[e].conexion;
	}

	Nat Juego::sanciones(Nat e) const{								//PROBLEMA							
		//return 0;
			return vectJug_[e].sanciones;
	}


	 Coordenada Juego::posicion(Nat e) const{
	    //Coordenada nuevo;
	 	//return nuevo;
	 	return vectJug_[e].posicion;
	  }


//VER WARNINGS DE DICCSTRING

	  DiccString< Nat>::const_Iterador Juego::Pokemons(Nat e) const{//Aca deberia??? ser DiccString(Nat)::Iterador
	  	//Dicc<pair<string, Nat> >::Iterador nuevo; 
	  	//return nuevo;	  	
	  	DiccString< Nat >::const_Iterador it;
	  	if(vectJug_[e].pokemonescapturados.HaySiguiente()){	  		
	  	 it = vectJug_[e].pokemonescapturados.Siguiente().CrearIt();
	  	}
	  	return it;

	  }


	 Conj<Nat> Juego::Expulsados() const {
	  	Conj<Nat> nuevo;
	  	Nat i = 0;
	  	while(i < vectJug_.Longitud()){
	  		if( vectJug_[i].sanciones >= 5){
	  			nuevo.AgregarRapido(i);
	  		}
	  		i++;
	  	}
	  	return nuevo;
	}

/*
  void Juego::Expulsados(Conj<Nat>& nuevo) const{	  	
	  	Nat i = 0;	  	
	  	while(i < vectJug_.Longitud()){	  	
	  		if( vectJug_[i].sanciones >= 5){	  		
	  		nuevo.AgregarRapido(i);	  		
	  		}
	  	i++;	

	  	}
	  	//return nuevo;

	  }
*/



/*
	  Conj<Coordenada>::const_Iterador Juego::posConPokemons() const{
	  	Conj<Coordenada>* dummy = new Conj<Coordenada>();
	  	referenciasAConjCoor_.Agregar(dummy);
	  	//return nuevo;	  		
	  	//cout << "antes dummy" << dummy.Cardinal()<< endl;  	
	  	Claves(posdePokemon_, (*dummy));	 
	  	//cout << "desues dummy" << dummy.Cardinal()<< endl;  	 
	  	Conj<Coordenada>::const_Iterador nuevo = dummy.CrearIt();	  	
	  	//cout << "iterador"<<nuevo.Siguiente().latitud() << nuevo.Siguiente().longitud() << endl;
	  	return nuevo;

	  }

*///La aridad no es la misma del tp
  Conj<Coordenada> Juego::posConPokemons() const{
	  	Conj<Coordenada> dummy;
	  	//referenciasAConjCoor_.Agregar(dummy);
	  	//return nuevo;	  		
	  	//cout << "antes dummy" << dummy.Cardinal()<< endl;  	
	  	Claves(posdePokemon_, dummy);	 
	  	//cout << "desues dummy" << dummy.Cardinal()<< endl;  	 
	  //	Conj<Coordenada>::const_Iterador nuevo = dummy.CrearIt();	  	
	  	//cout << "iterador"<<nuevo.Siguiente().latitud() << nuevo.Siguiente().longitud() << endl;
	  	return dummy;

	  }






/*


	  Conj<Coordenada>::Iterador Juego::posConPokemons(Conj<Coordenada>& dummy){
	  	
	  	//return nuevo;	  		
	  	//cout << "antes dummy" << dummy.Cardinal()<< endl;  	
	  	Claves(posdePokemon_, dummy);	 
	  	//cout << "desues dummy" << dummy.Cardinal()<< endl;  	 
	  	Conj<Coordenada>::Iterador nuevo = dummy.CrearIt();	  	
	  	//cout << "iterador"<<nuevo.Siguiente().latitud() << nuevo.Siguiente().longitud() << endl;
	  	return nuevo;

	  }
*/



	  	bool Juego::puedoAgregarPokemon(Coordenada c) const{
	  		bool res = true;
			Nat i;
			if (c.longitud() < 5){
				i = 0;
			}else{
				i = c.longitud() - 5;			
			}
			Nat j;
			while( (i <= c.longitud() + 5) and (res == true)){				
				if (c.latitud() < 5){					
					j = 0;									
				}else{					
					j = c.latitud() - 5;
				}							
				while( (j <= c.latitud() + 5) and (res == true)){	
					Coordenada ver(j,i);										
					if(ver.longitud() < mundo_.longitudMaxima() and ver.latitud() < mundo_.latitudMaxima()){
					bool a = mundo_.posEnMapa(ver);					
					bool b = (c.distEuclidea(ver) <= 25);						
					bool d = (!(matrizPokemon_[ver.longitud()][ver.latitud()].HayBasura_));
					//bool e = mundo_.hayCamino(c, ver);
					//cout << "ver: "<< ver.latitud() <<", " << ver.longitud() << endl;
					//cout << "posEnMapa  " << a <<"distancia " << b << "Basura " << d << "camino "<< e << endl;						
					if( a and b and d){
						res = false;
					}
					}
					j++;
				}
				i++;
			}
	     	return (res and mundo_.posEnMapa(c));


	  	}



	    String Juego::pokemonEnPos(Coordenada c) const{	  
	    	return posdePokemon_.Significado(c);

	   }

	     Nat Juego::CantMovimientosParaCaptura(Coordenada c) const{	    
	    	return matrizPokemon_[c.longitud()][c.latitud()].contador_;
	    	//string p = posdePokemon_.Significado(c);
	    	//return pokemones_.Obtener(p).Significado(c); 

	    }

	     Nat Juego::ProxID(){	 
	     	return vectJug_.Longitud();
	     }


	     Conj<Nat> Juego::JugadoresConectados(){    
	     	Conj<Nat> nuevo;
	     	Nat i = 0;
	     	while( i < vectJug_.Longitud()){
	     		if((vectJug_[i].sanciones < 5) and (vectJug_[i].conexion)){     		
	     			nuevo.AgregarRapido(i);
	     		}
	     		i++;
	     	}
	     	return nuevo;
	     }







	    Nat Juego::indiceDeRareza(string p) const{ 	    
	    	Nat capturados = (pokemones_.Obtener(p)).PC;
	    	Nat salvajes = (pokemones_.Obtener(p)).PS;
	    	Nat cant = capturados + salvajes;
	    	return 100 - ((100 * cant)/cantPokemon_);
	    }


	    Nat Juego::CantPokemonTotales() const{
	    	return cantPokemon_;
	    }

	     bool Juego::HayPokemonCercano(Coordenada c) const{	     	
	     	bool res = false;
			Nat i;
			if (c.longitud() < 2){
				i = 0;
			}else{
				i = c.longitud() -2;			
			}
			Nat j;
			while( (i <= c.longitud() + 2) and (res == false)){				
				if (c.latitud() < 2){					
					j = 0;									
				}else{					
					j = c.latitud() -2;
				}							
				while( (j <= c.latitud() + 2) and (res == false)){	
					Coordenada ver(j,i);										
					if(ver.longitud() < mundo_.longitudMaxima() and ver.latitud() < mundo_.latitudMaxima()){
					bool a = mundo_.posEnMapa(ver);					
					bool b = (c.distEuclidea(ver) <= 4);						
					bool d = (!(matrizPokemon_[ver.longitud()][ver.latitud()].HayBasura_));
					bool e = mundo_.hayCamino(c, ver);
					//cout << "ver: "<< ver.latitud() <<", " << ver.longitud() << endl;
					//cout << "posEnMapa  " << a <<"distancia " << b << "Basura " << d << "camino "<< e << endl;						
					if( a and b and d and e){
						res = true;
					}
					}
					j++;
				}
				i++;
			}
	     	return res;
	     }

		bool Juego::HayPokemonCercanoDriver(Coordenada c) const{	     	
	     	bool res = false;
			Nat i;
			if (c.longitud() < 2){
				i = 0;
			}else{
				i = c.longitud() -2;			
			}
			Nat j;
			while( (i <= c.longitud() + 2) and (res == false)){				
				if (c.latitud() < 2){					
					j = 0;									
				}else{					
					j = c.latitud() -2;
				}							
				while( (j <= c.latitud() + 2) and (res == false)){	
					Coordenada ver(j,i);										
					if(ver.longitud() < mundo_.longitudMaxima() and ver.latitud() < mundo_.latitudMaxima()){
					//bool a = mundo_.posEnMapa(ver);					
					bool b = (c.distEuclidea(ver) <= 4);						
					bool d = (!(matrizPokemon_[ver.longitud()][ver.latitud()].HayBasura_));

					//cout << "ver: "<< ver.latitud() <<", " << ver.longitud() << endl;
					//cout << "posEnMapa  " << a <<"distancia " << b << "Basura " << d << "camino "<< e << endl;						
					if( b and d){
						res = true;
					}
					}
					j++;
				}
				i++;
			}
	     	return res;
	     }	     


	     typename Juego::Iterador Juego::CrearIt(){
	     	Vector<dataJugador>* jug = &(this->vectJug_);
	     	typename Juego::Iterador nuevo(jug);
	     	return nuevo;
	     }


	     typename Juego::const_Iterador Juego::CrearIt() const{
	     	Vector<dataJugador> jug = (this->vectJug_);
	     	typename Juego::const_Iterador nuevo(&jug);
	     	return nuevo;
	     }
/*
	      Conj<Nat> Juego::JugadoresConj( typename Juego::const_Iterador& it) const{	      	
	     // Juego::const_Iterador it = (*this).CrearIt();
			Conj< Jugador > res;
			//cout<< "llega"<< endl;
			cout << it.HaySiguiente() << endl;
			while(it.HaySiguiente()){				
				res.AgregarRapido(it.Siguiente());
				it.Avanzar();
			}	
					
			return res;	

	     }
*/



//FUNCIONES PRIVADAS


		void Juego::Claves(const Dicc<Coordenada, string> dicc, Conj<Coordenada>& vacio) const{
			//Conj<Coordenada> nuevo;			
			typename Dicc<Coordenada, string>::const_Iterador it = dicc.CrearIt();			
			while(it.HaySiguiente()){			
				vacio.AgregarRapido(it.SiguienteClave());				
				it.Avanzar();				
				}			
		} 
		/*
		Conj< Coordenada > Juego::Claves(Dicc<Coordenada, string> dicc){
			//Conj<Coordenada> nuevo;

			typename Dicc<Coordenada, string>::Iterador it = dicc.CrearIt();			
			while(it.HaySiguiente()){
				//cout << "Cantidad de claves" << posdePokemon_.CantClaves() << endl;
				//cout << "claves " << it.SiguienteClave().latitud() << ", " << it.SiguienteClave().longitud() <<endl;
				nuevo.AgregarRapido(it.SiguienteClave());				
				it.Avanzar();
				//cout << "candinal" << nuevo.Cardinal() << endl;
			}
			while(cantidaddeclaves > 0){				
				cout << "claves " << it.SiguienteClave().latitud() << ", " << it.SiguienteClave().longitud() <<endl;
				nuevo.AgregarRapido(it.SiguienteClave());
				it.Avanzar();
				cantidaddeclaves--;
			}	

			//return nuevo;
		} */


		void Juego::Claves(Dicc<Nat, Coladeprioridad<typename Juego::capturadosyID>::Iterador > dicc, Conj<Nat>& vacio) const {			
			typename Dicc<Nat, Coladeprioridad<typename Juego::capturadosyID>::Iterador >::Iterador it = dicc.CrearIt();
			while(it.HaySiguiente()){
				vacio.AgregarRapido(it.SiguienteClave());//AgregarRapido
				it.Avanzar();
			}			
		} 

/*
		Conj< Nat > Juego::Claves(Dicc<Nat, Coladeprioridad<typename Juego::capturadosyID>::Iterador > dicc){
			Conj<Nat> nuevo;
			typename Dicc<Nat, Coladeprioridad<typename Juego::capturadosyID>::Iterador >::Iterador it = dicc.CrearIt();
			while(it.HaySiguiente()){
				nuevo.Agregar(it.SiguienteClave());//AgregarRapido
				it.Avanzar();
			}
			return nuevo;
		} 
*/





	    Vector<Vector<Dicc<Nat, Coladeprioridad<typename Juego::capturadosyID >::Iterador> > > Juego::crearMatrizJug(Nat lon, Nat lat){
	    	Nat i = 0;
	    	Vector<Vector<Dicc<Nat, Coladeprioridad<Juego::capturadosyID >::Iterador> > > nuevo;
	    	while(i < lon){
	    		Vector<Dicc<Nat, Coladeprioridad<Juego::capturadosyID >::Iterador> > posiciones;
	    		Nat j = 0;
	    		while(j < lat){
	    			Dicc<Nat, Coladeprioridad<Juego::capturadosyID >::Iterador> dicc;
	    			posiciones.AgregarAtras(dicc);
	    			j++;
	    		}
	    		nuevo.AgregarAtras(posiciones);
	    		i++;
	    	}
	    	return nuevo;
	    	 

	    }

		Vector<Vector<typename Juego::infoHeap> > Juego::crearMatrizPok(Nat lon, Nat lat){
			Nat i = 0;			
			Vector<Vector<infoHeap> > nuevo;
			while(i < lon){
				Vector<infoHeap> posiciones;
				Nat j= 0;
				while(j < lat){
					typename Juego::infoHeap dummy;
					posiciones.AgregarAtras(dummy);
					j++;
				}
				nuevo.AgregarAtras(posiciones);
				i++;
			}
			return nuevo;
		}


	Conj< typename Juego::capturadosyID> Juego::cercanos(Coordenada c) const{
		Conj<typename Juego::capturadosyID> nuevo;
		Nat i;
		if (c.longitud() < 2){
			i = 0;
		}else{
			i = c.longitud() -2;			
		}
		Nat j;		
		while( i <= c.longitud() + 2){
			if (c.latitud() < 2){
				j = 0;
			}else{
				j = c.latitud() -2;
			}
			while(j <= c.latitud() + 2){
				Coordenada ver(j,i);				
				if(ver.longitud() < mundo_.longitudMaxima() and ver.latitud() < mundo_.latitudMaxima()){
				bool a = (mundo_.posEnMapa(ver)); //puede fallar								
				bool b = (c.distEuclidea(ver) <= 4);				
				Conj<Nat> dummy; // Claves requiere un conjunto vacio pasado como parametro de entrada.				
				Claves(matrizJugadores_[ver.longitud()][ver.latitud()], dummy);								
				bool d = (!(dummy.EsVacio()));				
				bool e = mundo_.hayCamino(ver, c);				
				if(a and b and d and e){				
					Conj<Nat>::const_Iterador it = dummy.CrearIt();
					while (it.HaySiguiente()){
						typename Juego::capturadosyID hola(vectJug_[it.Siguiente()].pokTotalAtrapados ,it.Siguiente() );
						nuevo.AgregarRapido(hola);
						it.Avanzar();
					}					
				}
				}
				j++;
			}
			i++;
		}

		return nuevo;

	}


	Conj<Nat> Juego::cercanosEntrenadores(Coordenada c) const{
		Conj<Nat> nuevo;
		Nat i;
		if (c.longitud() < 2){
			i = 0;
		}else{
			i = c.longitud() -2;			
		}
		Nat j;		
		while( i <= c.longitud() + 2){
			if (c.latitud() < 2){
				j = 0;
			}else{
				j = c.latitud() -2;
			}
			while(j <= c.latitud() + 2){
				Coordenada ver(j,i);
				if(ver.longitud() < mundo_.longitudMaxima() and ver.latitud() < mundo_.latitudMaxima()){
				bool a = (mundo_.posEnMapa(ver)); //puede fallar				
				bool b = (c.distEuclidea(ver) <= 4);
				Conj<Nat> dummy; // Claves requiere un conjunto vacio pasado como parametro de entrada.
				Claves(matrizJugadores_[ver.longitud()][ver.latitud()], dummy);				
				bool d = (!(dummy.EsVacio()));
				bool e = mundo_.hayCamino(ver, c);
				if(a and b and d and e){				
					Conj<Nat>::const_Iterador it = dummy.CrearIt();
					while (it.HaySiguiente()){						
						nuevo.AgregarRapido(it.Siguiente());
						it.Avanzar();
					}					
				}
				}
				j++;
			}
			i++;
		}

		return nuevo;

	}






	bool Juego::HayUnJugadorCercano(Coordenada c){
		Conj<typename Juego::capturadosyID> nuevo;
		Nat i;
		if(c.longitud() < 2){
			 i = 0;
		}else{
			i = c.longitud()-2;
		}
		Nat j = 0;	
		bool aux = false;
		while(i <= c.longitud() + 2){
			if(c.latitud() < 2){
				j = 0; 
			}else{
				j = c.latitud() -2;
			}
			while(j <= c.latitud() + 2 ){
				Coordenada ver(j,i);
				if(ver.longitud() < mundo_.longitudMaxima() and ver.latitud() < mundo_.latitudMaxima()){
				bool a = (mundo_.posEnMapa(ver)); //puede fallar
				bool b = (c.distEuclidea(ver) <= 4);
				bool d = ((matrizJugadores_[ver.longitud()][ver.latitud()]).CantClaves() > 0);					
				bool e = mundo_.hayCamino(ver, c);
				//cout << "ver" << ver.latitud() <<"," <<ver.longitud() <<",posenMapa? " << a << "esta" << d << endl;
				//cout<< "hay camino: " << mundo_.hayCamino(c, ver) << endl;
				if(a and b and d and e){
					aux = true;					
				}
				}
				j++;
			}
			i++;
		}
		return aux;

	}

	bool Juego::estaParaCaptura(Coordenada posDelJug){
		//pareciera que faltara revisar el contador.
		bool res = false;			
		if(HayPokemonCercano(posDelJug)){					
			Coordenada posDelPoke = BuscarHeap(posDelJug);				
			res = mundo_.hayCamino(posDelJug, posDelPoke);
		}		
		return res;

	}
/*
	Coordenada Juego::BuscarHeap(Coordenada c)const{
		Coordenada nueva;
		Nat i;		
		bool AunNoLoEncontre = false;
		if(c.longitud() < 2){
			 i = 0;
		}else{
			i = c.longitud()-2;
		}
		Nat j = 0;	
		while((i<= c.longitud() +2) and (AunNoLoEncontre == false)){
			if(c.latitud() < 2){
				j = 0; 
			}else{
				j = c.latitud() -2;
			}
			while((j<= c.latitud() +2) and (AunNoLoEncontre == false)){
				Coordenada ver(j,i);				
				if(ver.longitud() < mundo_.longitudMaxima() and ver.latitud() < mundo_.latitudMaxima()){				
				if(mundo_.posEnMapa(ver) and c.distEuclidea(ver) <= 4){								
					if((matrizPokemon_[i][j].HayBasura_) == false){										
						nueva =  ver;						
						AunNoLoEncontre = true;
					}
				}
				}
				j++;
			}
			i++;
		}				
		return nueva;

	}*/




Coordenada Juego::BuscarHeap(Coordenada c) const{	     	
	     	Coordenada nueva;
	     	bool aux = false;
	     	Nat i = 0;
	     	if (c.longitud() < 2){
				i = 0;
			}else{
				i = c.longitud() -2;			
			}
			Nat j;		
			while( (i <= c.longitud() + 2) and (aux == false)){
				if (c.latitud() < 2){
					j = 0;
				}else{
					j = c.latitud() -2;
				}
				while( (j <= c.latitud() + 2)and (aux == false)){
					Coordenada ver(j,i);					
					if(ver.longitud() < mundo_.longitudMaxima() and ver.latitud() < mundo_.latitudMaxima()){
					bool a = mundo_.posEnMapa(c);
					bool b = (c.distEuclidea(ver) <= 4);
					bool d = (!(matrizPokemon_[ver.longitud()][ver.latitud()].HayBasura_));
					//Coordenada prue(1,1);
					//cout << "ver" << ver.latitud() <<"," <<ver.longitud() <<"," << matrizPokemon_[ver.longitud()][ver.latitud()].HayBasura_ << endl;
					//cout<< "hay camino: " << mundo_.hayCamino(c, ver) << endl;
					bool e = mundo_.hayCamino(c, ver);
					if(a and b and d and e){
						aux = true;
						nueva = ver;
					}
					}
					j++;
				}
				i++;
			}
	     	return nueva;
	     }

Coordenada Juego::BuscarHeapDriver(Coordenada c) const{	     	
	     	Coordenada nueva;
	     	bool aux = false;
	     	Nat i = 0;
	     	if (c.longitud() < 2){
				i = 0;
			}else{
				i = c.longitud() -2;			
			}
			Nat j;		
			while( (i <= c.longitud() + 2) and (aux == false)){
				if (c.latitud() < 2){
					j = 0;
				}else{
					j = c.latitud() -2;
				}
				while( (j <= c.latitud() + 2)and (aux == false)){
					Coordenada ver(j,i);					
					if(ver.longitud() < mundo_.longitudMaxima() and ver.latitud() < mundo_.latitudMaxima()){
					//bool a = mundo_.posEnMapa(c);
					bool b = (c.distEuclidea(ver) <= 4);
					bool d = (!(matrizPokemon_[ver.longitud()][ver.latitud()].HayBasura_));
					//Coordenada prue(1,1);
					//cout << "ver" << ver.latitud() <<"," <<ver.longitud() <<"," << matrizPokemon_[ver.longitud()][ver.latitud()].HayBasura_ << endl;
					//cout<< "hay camino: " << mundo_.hayCamino(c, ver) << endl;
					
					if( b and d){
						aux = true;
						nueva = ver;
					}
					}
					j++;
				}
				i++;
			}
	     	return nueva;
	     }


























	void Juego::AuxCapturarPokemon(Dicc<Coordenada, string>::Iterador& it){
		//cout << matrizPokemon_[it.SiguienteClave().longitud()][it.SiguienteClave().latitud()].HayBasura_ <<endl;
		infoHeap& dameLaData = matrizPokemon_[it.SiguienteClave().longitud()][it.SiguienteClave().latitud()];
		dataJugador& jugador = vectJug_[(((dameLaData).heap_).tope()).ID];		
		if(not ((jugador.pokemonescapturados).Siguiente()).Definido(it.SiguienteSignificado())){ 
			(jugador.pokemonescapturados.Siguiente()).Definir(it.SiguienteSignificado(),1);
		}
		else 
		{
			(jugador.pokemonescapturados.Siguiente()).Definir(it.SiguienteSignificado(),(jugador.pokemonescapturados.Siguiente()).Obtener(it.SiguienteSignificado())+1);
		}	
		jugador.pokTotalAtrapados++;
		dataPokemon& BuscarEnElTrie = pokemones_.Obtener(it.SiguienteSignificado()); 
		BuscarEnElTrie.PS = (BuscarEnElTrie.PS)-1; 
		BuscarEnElTrie.PC = (BuscarEnElTrie.PC)+1;	
		Coladeprioridad<typename Juego::capturadosyID> dummy;
		/*Dicc<Coordenada,string> pokpos;
		Dicc<Coordenada,string>::Iterador itpos = pokpos.CrearIt();*/
		matrizPokemon_[it.SiguienteClave().longitud()][it.SiguienteClave().latitud()].heap_ = dummy;
		matrizPokemon_[it.SiguienteClave().longitud()][it.SiguienteClave().latitud()].HayBasura_= true;
		matrizPokemon_[it.SiguienteClave().longitud()][it.SiguienteClave().latitud()].contador_ = 0;
		//cout << matrizPokemon_[it.SiguienteClave().longitud()][it.SiguienteClave().latitud()].HayBasura_ <<endl;
	}
















//ITERADOR Y STRUCTS


Juego::Iterador::Iterador(const typename Juego::Iterador& otro)
  : elementos_(otro.elementos_), posicion_(otro.posicion_)
{}

typename Juego::Iterador& Juego::Iterador::operator= (const typename Juego::Iterador& otro)
{
  elementos_ = otro.elementos_;
  posicion_ = otro.posicion_;
  return *this;
}


bool Juego::Iterador::HaySiguiente(){
	Nat i = posicion_;
	bool hayAlguno = false;
	while(i < ((*elementos_).Longitud()) && (hayAlguno == false)){
		typename Juego::dataJugador  jugActual = (*elementos_)[i];
		if(jugActual.sanciones < 5){
			hayAlguno = true;
		}
		i++;
	}
	return hayAlguno;
}// const;
     
Nat Juego::Iterador::Siguiente(){
	Nat i = posicion_;
	Nat resAux;
	if(i != 0){
		resAux = i;
	}else{
		if((*elementos_)[i].sanciones < 5){
			resAux = i;
		}else{
		Avanzar();
		resAux = posicion_;
		}		
	}
	return resAux;
}

void Juego::Iterador::Avanzar(){

	if ((posicion_+1) < (*elementos_).Longitud()){
	Nat i = posicion_ + 1;	
	bool tengoQueParar = false;
	while(i < ((*elementos_).Longitud()) && (tengoQueParar == false)){
		if((*elementos_)[i].sanciones < 5){
			tengoQueParar = true;
		}
	  i++;	
	}
	posicion_ = i-1;	
}else
 posicion_++;
}




//ITERADOR CONSTANTE
/////////////////////////////////////////

Juego::const_Iterador::const_Iterador(const typename Juego::Iterador& otro)
  : elementos_(otro.elementos_), posicion_(otro.posicion_)
{}

Juego::const_Iterador::const_Iterador(const typename Juego::const_Iterador& otro)
  : elementos_(otro.elementos_), posicion_(otro.posicion_)
{}



typename Juego::const_Iterador& Juego::const_Iterador::operator= (const typename Juego::const_Iterador& otro)
{
  elementos_ = otro.elementos_;
  posicion_ = otro.posicion_;
  return *this;
}


bool Juego::const_Iterador::HaySiguiente() const{
	
	Nat i = posicion_;
	bool hayAlguno = false;
	while(i < ((*elementos_).Longitud()) && (hayAlguno == false)){		

		typename Juego::dataJugador  jugActual = (*elementos_)[i];		
		if(jugActual.sanciones < 5){
			hayAlguno = true;
		}
		i++;
	}	
	return hayAlguno;

}// const;
     

void Juego::const_Iterador::Avanzar(){

	if ((posicion_+1) < (*elementos_).Longitud()){
	Nat i = posicion_ + 1;	
	bool tengoQueParar = false;
	while(i < ((*elementos_).Longitud()) && (tengoQueParar == false)){
		if((*elementos_)[i].sanciones < 5){
			tengoQueParar = true;
		}
	  i++;	
	}
	posicion_ = i-1;	
}else
 posicion_++;
}




Nat Juego::const_Iterador::Siguiente() {
	Nat i = posicion_;
	Nat resAux;
	if(i != 0){
		(resAux) = i;
	}else{
		if((*elementos_)[i].sanciones < 5){
			(resAux) = i;
		}else{
		(*this).Avanzar();
		(resAux) = posicion_;
		}		
	}
	return resAux;
}

Conj<Nat> Juego::const_Iterador::Siguientes() const{
	Conj< Nat > res;
	Nat i = posicion_;
	while(i< (*elementos_).Longitud()){
		if((*elementos_)[i].sanciones < 5){
			res.AgregarRapido(i);
		}
		i++;
	}	
	return res;
}


Conj<Nat> Juego::losjugadores()const{
	Conj< Nat > res;	
	Nat i = 0;
	while(i< (vectJug_).Longitud()){
		if((vectJug_[i].sanciones < 5)){
			res.AgregarRapido(i);
		}
		i++;
	}	
	return res;
}




//STRUCTS
//////////////////////////////////////////




/*
bool Juego::EstaParaCaptura(Coordenada c){
	if(HayPokemonCercano(c)){
		Coordenada poke = BuscarHeap(c);
		return this->mundo_.hayCamino(c,poke);
	}else{
		return false;
	}
}
*/

//Una tupla es menor a otra si tiene menos pokemons capturados. En caso de ser los mismo, es menor el de ID mas alto
bool Juego::capturadosyID::operator < (const typename Juego::capturadosyID& otra) const
{
	if( numero < otra.numero ){
		return true;
	}
	if(numero > otra.numero){
		return false;
	}
	if( numero == otra.numero){
		return (ID > otra.ID);
	} 
  

  }

bool Juego::capturadosyID::operator == (const typename Juego::capturadosyID& otra) const
{
	return (numero == otra.numero) and  (ID == otra.ID);
  

  }






bool Juego::capturadosyID::operator > (const typename Juego::capturadosyID& otra) const
{
	return ((((*this) < otra) == false ) and (((*this) == otra) == false));

  }



//TESTING



  Nat Juego::matrizJUGADORESLongitud(){
  	return matrizJugadores_.Longitud();
  }//(pokcapturados, ID)



Nat Juego::matrizPOKEMONLongtitud(){
	return matrizPokemon_.Longitud();
}

Nat Juego::matrizJUGADORESLatitud(){
  	return matrizJugadores_[0].Longitud();
  }//(pokcapturados, ID)



Nat Juego::matrizPOKEMONLatitud(){
	return matrizPokemon_[0].Longitud();
}

//COUTS DE DESCONECTAR
/*	Coladeprioridad<typename Juego::capturadosyID>::Iterador crear = matrizPokemon_[1][1].heap_.CrearIt();
			cout << "hello"<< crear.Siguiente().ID <<", "<< crear.Siguiente().numero << endl;
			crear.borrarSiguiente();
			Coladeprioridad<typename Juego::capturadosyID>::Iterador crear2 = matrizPokemon_[1][1].heap_.CrearIt();
			cout << "hello"<< crear2.Siguiente().ID <<", "<< crear2.Siguiente().numero << endl;

			cout << "matriz"<<(*matrizPokemon_[1][1].heap_.HEAP()).Dato().ID << ", "<<(*matrizPokemon_[1][1].heap_.HEAP()).Dato().numero <<endl;	*/