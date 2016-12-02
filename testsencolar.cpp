#include <iostream>
#include "mini_test.h"

#include "ColadeprioridadH54.h"
#include "Conj.h"

using namespace aed2;

void compila(){
	Coladeprioridad<int> hola;
	ASSERT(hola.EsVacia());
}

void encolar_uno_y_dejar_vacia(){
	Coladeprioridad<int> hola;
	Coladeprioridad<int>::Iterador it = hola.Encolar(6);
	ASSERT(hola.Claves() == 1);
	ASSERT(hola.Nivel() == 0);
	ASSERT(it.HaySiguiente());
	ASSERT(it.Siguiente() == 6);	
	//hola.Desencolar();
	//cout << hola.HEAP() << endl;	
	//ASSERT((*hola.HEAP()).Dato() == 6);	
	//ASSERT(hola.EsVacia());
	//hola.Encolar(5);
	//hola.Encolar(1);
	//cout << (*hola.HEAP()).Dato() << endl;
	//cout << (*(*hola.HEAP()).IZQUIERDA()).Dato() << endl;
	//hola.Encolar(9);
	//hola.Encolar(10);
	//hola.Encolar(0);		
	//ASSERT(hola.Claves() == 5);
	//ASSERT(hola.tope() == 0);

}



void encolar_dos_y_dejar_vacia(){
	Coladeprioridad<int> hola;
	Coladeprioridad<int>::Iterador it = hola.Encolar(6);	
	ASSERT(hola.Claves() == 1);
	ASSERT(hola.Nivel() == 0);
	ASSERT(it.HaySiguiente());
	ASSERT(it.Siguiente() == 6);
	Coladeprioridad<int>::Iterador segit = hola.Encolar(5);
	ASSERT(hola.Claves() == 2);
	ASSERT(hola.Nivel() == 1);
	ASSERT(segit.HaySiguiente());
	ASSERT(segit.Siguiente() == 5);
	ASSERT(hola.tope() == 5);
	hola.Desencolar();	
	ASSERT(hola.Claves() == 1);
	ASSERT(hola.Nivel() == 0);
	ASSERT(hola.tope() == 6);
	hola.Desencolar();
	ASSERT(hola.Claves() == 0);
	ASSERT(hola.Nivel() == 0);	

	ASSERT(hola.EsVacia());
}




void encolar_tres_y_dejar_vacia(){
	Coladeprioridad<int> hola;
	Coladeprioridad<int>::Iterador it = hola.Encolar(6);
	Coladeprioridad<int>::Iterador it2 = hola.Encolar(5);
	 Coladeprioridad<int>::Iterador it3 = hola.Encolar(7);
	 it3.borrarSiguiente();	
	// ASSERT(hola.Claves() == 3);
	// ASSERT(hola.Nivel() == 1);
	// ASSERT(hola.tope() == 5);
	// hola.Desencolar();
	// ASSERT(hola.Claves() == 2);
	//ASSERT(hola.Nivel() == 1);	
	 //ASSERT(hola.tope() == 6);




	ASSERT(!hola.EsVacia());
}



void desencolar_el_hijoDer(){
	Coladeprioridad<int> hola;
	//Coladeprioridad<int>::Iterador it = hola.Encolar(6);
	 hola.Encolar(6);	
	 hola.Encolar(5);
	 hola.Encolar(7);
	 hola.Encolar(8);
	 hola.Encolar(9);
	 hola.Encolar(10);
	 ASSERT(hola.Claves() == 6);
	 ASSERT(hola.Nivel() == 2);
	 ASSERT(hola.tope() == 5);	 
	 ASSERT((*(*hola.HEAP()).IZQUIERDA()).Dato() == 6);
	 ASSERT((*(*hola.HEAP()).DERECHA()).Dato() == 7);
	 ASSERT((*(*(*hola.HEAP()).IZQUIERDA()).IZQUIERDA()).Dato() == 8	);
	 ASSERT((*(*(*hola.HEAP()).IZQUIERDA()).DERECHA()).Dato() == 9	);
	 hola.Desencolar();
	 ASSERT(hola.Claves() == 5);
	 ASSERT(hola.Nivel() == 2);
	 cout<< hola.tope()<< endl;
	 ASSERT(hola.tope() == 6);
	 ASSERT((*(*hola.HEAP()).IZQUIERDA()).Dato() == 8);
	 ASSERT((*(*hola.HEAP()).DERECHA()).Dato() == 7);
	 ASSERT((*(*(*hola.HEAP()).IZQUIERDA()).IZQUIERDA()).Dato() == 10);
	 ASSERT((*(*(*hola.HEAP()).IZQUIERDA()).DERECHA()).Dato() == 9);


	 //hola.Desencolar();
	 //ASSERT(hola.Claves() == 2);
	 //ASSERT(hola.Nivel() == 1);	
	 //ASSERT(hola.tope() == 6);




	ASSERT(!hola.EsVacia());
}


void desencolar_el_hijoDer_de_verdad(){
	Coladeprioridad<int> hola;
	//Coladeprioridad<int>::Iterador it = hola.Encolar(6);
	 hola.Encolar(7);	
	 hola.Encolar(5);
	 hola.Encolar(6);
	 hola.Encolar(8);	
	 ASSERT(hola.Claves() == 4);
	 ASSERT(hola.Nivel() == 2);
	 ASSERT(hola.tope() == 5);	 	
	 hola.Desencolar();
	 ASSERT(hola.Claves() == 3);
	 ASSERT(hola.Nivel() == 1);
	 ASSERT(hola.tope() == 6);
	 ASSERT((*(*hola.HEAP()).IZQUIERDA()).Dato() == 7);
	 ASSERT((*(*hola.HEAP()).DERECHA()).Dato() == 8);
	 //ASSERT((*(*(*hola.HEAP()).IZQUIERDA()).IZQUIERDA()).Dato() == 10);
	 //ASSERT((*(*(*hola.HEAP()).IZQUIERDA()).DERECHA()).Dato() == 9);


	 //hola.Desencolar();
	 //ASSERT(hola.Claves() == 2);
	 //ASSERT(hola.Nivel() == 1);	
	 //ASSERT(hola.tope() == 6);




	ASSERT(!hola.EsVacia());
}

void armo_y_desarmo(){
	Coladeprioridad<int> hola;
	//Coladeprioridad<int>::Iterador it = hola.Encolar(6);
	 hola.Encolar(6);	
	 hola.Encolar(5);
	 hola.Encolar(7);
	 hola.Encolar(8);
	 hola.Encolar(1);
	 hola.Encolar(9);
	 ASSERT(hola.Claves() == 6);
	 ASSERT(hola.Nivel() == 2);
	 ASSERT(hola.tope() == 1);	 
	 ASSERT((*(*hola.HEAP()).IZQUIERDA()).Dato() == 5);
	 ASSERT((*(*hola.HEAP()).DERECHA()).Dato() == 7);
	 ASSERT((*(*(*hola.HEAP()).IZQUIERDA()).IZQUIERDA()).Dato() == 8	);
	 ASSERT((*(*(*hola.HEAP()).IZQUIERDA()).DERECHA()).Dato() == 6	);
	 ASSERT((*(*(*hola.HEAP()).DERECHA()).IZQUIERDA()).Dato() == 9	);
	 hola.Desencolar();
	 ASSERT(hola.Claves() == 5);
	 ASSERT(hola.Nivel() == 2);
	 cout<< hola.tope()<< endl;
	 ASSERT(hola.tope() == 5);
	 ASSERT((*(*hola.HEAP()).IZQUIERDA()).Dato() == 6);
	 ASSERT((*(*hola.HEAP()).DERECHA()).Dato() == 7);
	 ASSERT((*(*(*hola.HEAP()).IZQUIERDA()).IZQUIERDA()).Dato() == 8);
	 ASSERT((*(*(*hola.HEAP()).IZQUIERDA()).DERECHA()).Dato() == 9);
	 hola.Desencolar();
	 ASSERT(hola.Claves() == 4);
	 ASSERT(hola.Nivel() == 2);
	 cout<< hola.tope()<< endl;
	 ASSERT(hola.tope() == 6);
	 ASSERT((*(*hola.HEAP()).IZQUIERDA()).Dato() == 8);
	 ASSERT((*(*hola.HEAP()).DERECHA()).Dato() == 7);
	 ASSERT((*(*(*hola.HEAP()).IZQUIERDA()).IZQUIERDA()).Dato() == 9);
	 hola.Desencolar();
	 ASSERT(hola.Claves() == 3);
	 ASSERT(hola.Nivel() == 1);
	 cout<< hola.tope()<< endl;
	 ASSERT(hola.tope() == 7);
	 ASSERT((*(*hola.HEAP()).IZQUIERDA()).Dato() == 8);
	 ASSERT((*(*hola.HEAP()).DERECHA()).Dato() == 9);
	 hola.Desencolar();
	 ASSERT(hola.Claves() == 2);
	 ASSERT(hola.Nivel() == 1);
	 cout<< hola.tope()<< endl;
	 ASSERT(hola.tope() == 8);
	 ASSERT((*(*hola.HEAP()).IZQUIERDA()).Dato() == 9);
	 hola.Desencolar();
	 ASSERT(hola.Claves() == 1);
	 ASSERT(hola.Nivel() == 0);
	 cout<< hola.tope()<< endl;
	 ASSERT(hola.tope() == 9);
	 hola.Desencolar();
	 ASSERT(hola.Claves() == 0);
	 ASSERT(hola.Nivel() == 0);
	 ASSERT(hola.EsVacia());


}





void borro_vacio(){
	Coladeprioridad<int> hola;
	Coladeprioridad<int>::Iterador it = hola.Encolar(6);
	it.borrarSiguiente();
	ASSERT(hola.EsVacia());
}


void borro_del_final(){
	Coladeprioridad<int> hola;
	Coladeprioridad<int>::Iterador it = hola.Encolar(6);
	Coladeprioridad<int>::Iterador itseg = hola.Encolar(7);	
	//ASSERT(hola.Claves() == 2);
	//ASSERT(hola.Nivel() == 1);
	//ASSERT(hola.tope() == 6);	 
	itseg.borrarSiguiente();	
	//ASSERT(hola.Claves() == 1);
	//ASSERT(hola.Nivel() == 0);
	//cout << hola.tope() << endl;
	//ASSERT(hola.tope() == 6);	
	//cout << ((*(*(hola.HEAP())).IZQUIERDA())).Dato() << endl;
	//ASSERT((*(hola.HEAP())).DERECHA() == NULL); 
	//it.borrarSiguiente();
	
}


void borro_del_medio(){
		Coladeprioridad<int> hola;
	//Coladeprioridad<int>::Iterador it = hola.Encolar(6);
	 Coladeprioridad<int>::Iterador itultimo = hola.Encolar(6);	
	 Coladeprioridad<int>::Iterador it = hola.Encolar(5);
	 Coladeprioridad<int>::Iterador itter = hola.Encolar(7);
	 hola.Encolar(8);
	 hola.Encolar(1);
	 hola.Encolar(9);
	 ASSERT(hola.Claves() == 6);
	 ASSERT(hola.Nivel() == 2);
	 ASSERT(hola.tope() == 1);	 
	 ASSERT((*(*hola.HEAP()).IZQUIERDA()).Dato() == 5);
	 ASSERT((*(*hola.HEAP()).DERECHA()).Dato() == 7);
	 ASSERT((*(*(*hola.HEAP()).IZQUIERDA()).IZQUIERDA()).Dato() == 8	);
	 ASSERT((*(*(*hola.HEAP()).IZQUIERDA()).DERECHA()).Dato() == 6	);
	 ASSERT((*(*(*hola.HEAP()).DERECHA()).IZQUIERDA()).Dato() == 9	);
	 it.borrarSiguiente();
	 ASSERT(hola.Claves() == 5);
	 ASSERT(hola.Nivel() == 2);
	 cout<< hola.tope()<< endl;
	 ASSERT(hola.tope() == 1);
	 ASSERT((*(*hola.HEAP()).IZQUIERDA()).Dato() == 6);
	 ASSERT((*(*hola.HEAP()).DERECHA()).Dato() == 7);
	 ASSERT((*(*(*hola.HEAP()).IZQUIERDA()).IZQUIERDA()).Dato() == 8);
	 ASSERT((*(*(*hola.HEAP()).IZQUIERDA()).DERECHA()).Dato() == 9);
	 Coladeprioridad<int>::Nodo* raiz = hola.HEAP();
	 Coladeprioridad<int>::Nodo* funca = (*(hola.recorrocamino(raiz, 1, 2)));
	 ASSERT((*funca).Dato() == 7);
	 itultimo.borrarSiguiente();
	 ASSERT(hola.Claves() == 4);
	 ASSERT(hola.Nivel() == 2);
	 cout<< hola.tope()<< endl;
	 ASSERT(hola.tope() == 1);
	 ASSERT((*(*hola.HEAP()).IZQUIERDA()).Dato() == 8);	 
	 ASSERT((*(*hola.HEAP()).DERECHA()).Dato() == 7);
	 ASSERT((*(*(*hola.HEAP()).IZQUIERDA()).IZQUIERDA()).Dato() == 9);
	 itter.borrarSiguiente();
}












void encolo_dos(){
	Coladeprioridad<int> hola;
	 hola.Encolar(6);
	 hola.Encolar(7);	
	ASSERT(hola.Claves() == 2);
	ASSERT(hola.Nivel() == 1);
	ASSERT(hola.tope() == 6);		
	ASSERT((*(hola.HEAP())).DERECHA() == NULL); 	
}




void encolarvuela(){
Coladeprioridad<int> hola;
hola.Encolar(5);
hola.Encolar(1);
hola.Encolar(4);
ASSERT(hola.Nivel() == 1);
cout <<"no va mas"<<endl;
hola.Encolar(3);
ASSERT(hola.tope() == 1);





}


int main() {
	RUN_TEST(encolarvuela);
	RUN_TEST(compila);
	RUN_TEST(encolar_uno_y_dejar_vacia);
	RUN_TEST(encolar_dos_y_dejar_vacia);
	RUN_TEST(encolar_tres_y_dejar_vacia);
	RUN_TEST(desencolar_el_hijoDer);
	RUN_TEST(desencolar_el_hijoDer_de_verdad);
	RUN_TEST(armo_y_desarmo);
	RUN_TEST(borro_vacio);
	RUN_TEST(borro_del_final);
	RUN_TEST(encolo_dos);
	RUN_TEST(borro_del_medio);
	return 0;
}
