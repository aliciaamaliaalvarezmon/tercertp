#include "Mapa.h"

Mapa::Mapa() :  matriz() , longitudmaxima(0), latitudmaxima(0), coordenadas() {}

Mapa::Mapa(const Conj<Coordenada> cs) : matriz() , longitudmaxima(0), latitudmaxima(0), coordenadas(){
	Conj<Coordenada>::const_Iterador it = cs.CrearIt();
	while(it.HaySiguiente()){
		agregarCoord(it.Siguiente());
		it.Avanzar();
	}
	
}

Mapa::~Mapa(){/*
	Nat i = 0;
	Nat j = 0;
	while(i < latitudmaxima){
	//Vector<Vector<Vector<bool > > >* esperanza = &(matriz[i]);
	while(j < longitudmaxima){
	Vector<Vector<bool> >* elem  = &(matriz[i][j]);
	Nat a = 0;			
	while(a < latitudmaxima){
	Vector<bool>* podemos = &(matriz[i][j][a]);
	delete(podemos);
	a++;
} 	
	delete(elem);
	j++;
}
	//	delete(esperanza);
	i++;
}
	*/
}



/*CONSULTA: esta bien inicializarlo así?*/
/*
void Mapa::agregarCoord(Coordenada& c){
coordenadas.AgregarRapido(c);
Vector< Vector<Vector<bool> > >* fila = new Vector< Vector<Vector<bool> > >; 
Vector<Vector<bool> >* elem = new Vector<Vector<bool> >;
if(c.latitud() >= latitudmaxima and c.longitud() >= longitudmaxima){
while(fila->Longitud() <= c.longitud()){
fila->AgregarAtras(*elem);
}
while(matriz.Longitud() <= c.latitud()){
matriz.AgregarAtras(*fila);
}
Nat i = 0;
while(i< matriz.Longitud()){
while(matriz[i].Longitud()<= c.longitud()){
matriz[i].AgregarAtras(*elem);
}
i++;
}
latitudmaxima = c.latitud()+1;
longitudmaxima = c.longitud()+1;
}else{
if(c.latitud() >= latitudmaxima){
//			cout << "la latitud empato" <<endl;
while(fila->Longitud() < longitudmaxima){
fila->AgregarAtras(*elem);
}
while(matriz.Longitud() <= c.latitud()+1){
matriz.AgregarAtras(*fila);
}
latitudmaxima = c.latitud()+1;
}else{
//			cout << "entre aca" <<endl;
if(c.longitud() >= longitudmaxima){
Nat i = 0;
while(i< matriz.Longitud()){
while(matriz[i].Longitud()<= c.longitud()){
matriz[i].AgregarAtras(*elem);
}
i++;
}
longitudmaxima = c.longitud()+1;
}
}

}
Nat i=0;
cout << "longitudmaxima:" << longitudmaxima<<endl;
cout << "latitudmaxima:" << latitudmaxima<<endl;
cout << "latitud de la Matriz:" << matriz.Longitud()<<endl;
while(i<matriz.Longitud()){
cout << "La Longitud de la matriz es : " << matriz[i].Longitud() <<endl;
i++;
}
//	cout <<"Latitud: " << latitudmaxima <<endl;
//	cout << "Longitud: " << longitudmaxima <<endl;
Conj<Coordenada> coords = coordenadas;
Conj<Coordenada>::Iterador it = coords.CrearIt();
while(it.HaySiguiente()){
Coordenada paraLasRelaciones = it.Siguiente();
Conj<Coordenada> vacio;
vacio.Agregar(paraLasRelaciones);
Conj<Coordenada> res;
//		cout << "YoloA" <<endl;
res = Lindantes(vacio,coords,res);
//		cout << "YoloB1" <<endl;
Vector <Vector <bool> > matrizF = MatrizDeFalse(latitudmaxima+1,longitudmaxima+1);
//		cout << "Latitud de la matriz de caminos: " << matriz.Longitud() <<endl;
//		int i=0;
//		while(i<matriz.Longitud()){
//		cout <<"Longitud de la matriz de caminos: " << matriz[i].Longitud() <<endl;
//		i++;
//		}
Rellenar(matrizF,res);
//		cout << "YoloD3" <<endl;
(matriz[it.Siguiente().latitud()][it.Siguiente().longitud()]) = matrizF;
//		cout << "YoloE4" <<endl;
it.Avanzar();
}

}
*/
void Mapa::agregarCoord(Coordenada c){
	coordenadas.AgregarRapido(c);
	const Nat londecoor = c.longitud() +1;
	const Nat latdecoor = c.latitud() + 1;
	Nat longitudanterior = longitudmaxima;
	Nat latitudanterior = latitudmaxima;
	Vector< Arreglo <Arreglo<bool> > >* fila = new Vector< Arreglo<Arreglo<bool> > >;	 	
	Arreglo<Arreglo<bool> >* elem = new Arreglo<Arreglo<bool> >(latdecoor);	
	for (int k = 0; k < latdecoor; k++) {	
		(*elem).Definir(k, Arreglo<bool>(londecoor));
	}		
	if(c.latitud() >= latitudmaxima and c.longitud() >= longitudmaxima){
		while(fila->Longitud() <= c.longitud()){
			fila->AgregarAtras(*elem);
		}
		while(matriz.Longitud() <= c.latitud()){
			matriz.AgregarAtras(*fila);
		}
		Nat i = 0;
		while(i< matriz.Longitud()){
			while(matriz[i].Longitud()<= c.longitud()){
				matriz[i].AgregarAtras(*elem);
			}
			i++;
		}
		latitudmaxima = c.latitud()+1;
		longitudmaxima = c.longitud()+1;
	}else{
		if(c.latitud() >= latitudmaxima){
			//			cout << "la latitud empato" <<endl;
			while(fila->Longitud() < longitudmaxima){
				fila->AgregarAtras(*elem);
			}
			while(matriz.Longitud() <= c.latitud()+1){
				matriz.AgregarAtras(*fila);
			}
			latitudmaxima = c.latitud()+1;
		}else{
			//			cout << "entre aca" <<endl;
			if(c.longitud() >= longitudmaxima){
				Nat i = 0;
				while(i< matriz.Longitud()){
					while(matriz[i].Longitud()<= c.longitud()){
						matriz[i].AgregarAtras(*elem);
					}
					i++;
				}
				longitudmaxima = c.longitud()+1;
			}
		}
		
	}
	Nat lati = 0;
	while(lati < latitudmaxima){
		Nat longi = 0;
		while(longi < longitudmaxima){
			Coordenada ver(lati, longi);
			if(coordenadas.Pertenece(ver) == false){								
				matriz[lati][longi] =  Noesta();//MatrizDeFalse(latitudmaxima+1, longitudmaxima +1);
			}
			longi++;
		}
		lati++;
	}
	Conj<Coordenada> coords = coordenadas;
	Conj<Coordenada>::Iterador it = coords.CrearIt();
	cout << "Coordenada a agregar:" <<endl;
	cout << c.longitud() <<"  " << c.latitud() <<endl;
	while(it.HaySiguiente()){
		Coordenada paraLasRelaciones = it.Siguiente();
		Conj<Coordenada> vacio;
		vacio.Agregar(paraLasRelaciones);
		pair< Conj<Coordenada>, pair<Nat,Nat> >res;
		res.first.Agregar(paraLasRelaciones);
		Nat	n =0;
		Nat m=0;
		res = Lindantes(vacio,coords,res.first,n,m);	
//		cout <<res.second.first <<endl;
//		cout <<res.second.second <<endl;
		if(res.second.first==0 and res.second.second==0){
			res.second.first=it.Siguiente().longitud();
			res.second.second=it.Siguiente().latitud();
		}
//		cout <<"" <<endl;
//		cout <<res.second.first <<endl;
//		cout <<res.second.second <<endl;
		cout << "Coordenada a relacionar:" <<endl;
		cout << it.Siguiente().longitud() <<"  " << it.Siguiente().latitud() <<endl;
		Arreglo <Arreglo <bool> > matrizF = MatrizDeFalse(res.second.second + 1,res.second.first +1);
		cout << "Tamaño de la matriz de relaciones:" <<endl;
		cout <<matrizF[0].Tamanho() <<"  " << matrizF.Tamanho() <<endl;
		/*cout  <<endl;*/
		Conj<Coordenada>::Iterador it5 = res.first.CrearIt();
		cout <<"Lindantes:" <<endl;
		while(it5.HaySiguiente()){
			cout << it5.Siguiente().longitud() << "  " << it5.Siguiente().latitud() <<endl;
			it5.Avanzar();
		}
//		cout <<"Coordenada que voy a agregar:" <<endl;
//		cout << it.Siguiente().longitud() << "  " << it.Siguiente().latitud() <<endl;
		Rellenar(matrizF,res.first);
		(matriz[it.Siguiente().latitud()][it.Siguiente().longitud()]) = matrizF;	
		it.Avanzar();
	}	
	
	delete(elem);
	delete(fila);
	cout << "Siguiente ejecucion" <<endl;
}









Mapa::Mapa(const Mapa& otro)
	:  matriz(otro.matriz), longitudmaxima(otro.longitudmaxima), latitudmaxima(otro.latitudmaxima), coordenadas(otro.coordenadas)
{}

const Nat& Mapa::longitudMaxima() const {
	return longitudmaxima;
}

const Nat& Mapa::latitudMaxima() const {
	return latitudmaxima;
}

const Conj<Coordenada>& Mapa::coordenadasMapa() const {
	return coordenadas;
}


pair< Conj<Coordenada>, pair<Nat,Nat> > Mapa::Lindantes(Conj<Coordenada> c,Conj<Coordenada> coordenadas,Conj<Coordenada> res,Nat n , Nat m) const{
	Conj<Coordenada>::Iterador it =c.CrearIt();
	Conj<Coordenada> ParaLaRecursion;
	while(it.HaySiguiente()){
		Conj<Coordenada> lindastesDeC = (it.Siguiente()).Lindantes();
		Conj<Coordenada>::Iterador it2 = lindastesDeC.CrearIt();
		while(it2.HaySiguiente()){
			/*cout << n << "  " << m << endl;*/
			if(coordenadas.Pertenece(it2.Siguiente())){
				if(n<it2.Siguiente().longitud()){
					
					n=it2.Siguiente().longitud();
					
				}
				if(m< it2.Siguiente().latitud()){
					m=it2.Siguiente().latitud();
				}
				res.Agregar(it2.Siguiente());
				ParaLaRecursion.Agregar(it2.Siguiente());
				coordenadas.Eliminar(it2.Siguiente());
			}
			it2.Avanzar();
		}
		it.Avanzar();
	}
	if(ParaLaRecursion.Cardinal()!=0){
		return Lindantes(ParaLaRecursion,coordenadas,res,n,m);
	}else{
		return make_pair(res,make_pair(n,m));
	}
}


Arreglo <Arreglo < bool> > Mapa::MatrizDeFalse(Nat i, Nat j){
	const Nat longi = j;
	const Nat lati = i;
	Arreglo <Arreglo < bool> >* res = new Arreglo <Arreglo < bool> >(lati);
	for (int k = 0; k < lati; k++) {		
		(*res).Definir(k, Arreglo<bool>(longi));		
	}	
	//Vector <bool>* nuevo  = new Vector < bool>;11
	
	bool f;
	f= false;
	Nat a = 0;
	Arreglo <bool>* nuevo = new Arreglo < bool>(j);
	while(a < i){		
		//Arreglo <bool>* nuevo = new Arreglo < bool>(j);
		//Arreglo <bool> nuevo;
		Nat b = 0; 
		while(b < j){
			(*nuevo).Definir(b, false);			
		b++;
		}		
		res->Definir(a, (*nuevo));
		//delete(nuevo);		
		a++;
	}	
	Arreglo <Arreglo < bool> > resi = (*res);
	delete(res);
	delete(nuevo);
	//	cout << res->Longitud() <<"     " << nuevo->Longitud() <<endl;
	return resi;
}


Arreglo <Arreglo < bool> > Mapa::Noesta(){
	Arreglo <Arreglo < bool> >* res = new Arreglo <Arreglo < bool> >(0);
	Arreglo <Arreglo < bool> > resi = (*res);
	delete(res);
	return resi;
}















void Mapa::Rellenar(Arreglo <Arreglo < bool> >& matriz,Conj<Coordenada> linda){
	Conj<Coordenada>::Iterador it = linda.CrearIt();
	while(it.HaySiguiente()){
		(matriz)[it.Siguiente().latitud()][it.Siguiente().longitud()]=true;
	it.Avanzar();
	}
	
}

bool Mapa::hayCamino(Coordenada c, Coordenada c2) const{
	if(c.latitud()<= latitudmaxima && c.longitud() <= longitudmaxima){
		const Arreglo<Arreglo<bool> >& relaciones = matriz[c.longitud()][c.latitud()];
		if(c2.latitud() < relaciones.Tamanho()   && c2.longitud() < relaciones[0].Tamanho()){
			return relaciones[c2.longitud()][c2.latitud()];
		}else{
			return false;
		}
	}else{
		return false;
	}
	
	
}


bool Mapa::posEnMapa(Coordenada c) const{
	return ((matriz[c.latitud()][c.longitud()]).Tamanho() > 0);
	//return   (matriz[0][0])[0][0];
	
}

bool Mapa::posExiste(Coordenada& c) const{
	return coordenadas.Pertenece(c);
}
