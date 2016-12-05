#include<iostream>
using namespace std;
#include "TiposBasicos.h"
#include "Lista.h"
#include "Dicc.h"
#include "Conj.h"
#include "DiccString.h"
#include "Coordenada.h"
#include "Mapa.h"
#include <iostream>
namespace mt {

using namespace std;

// MARCH: Copy-paste much?
template<class T>
class ValueExpectationException : public std::exception {
public:
    ValueExpectationException() {}

    ValueExpectationException(T actual, T expected, string loc) :
        _actual(actual), _expected(expected), _location(loc) { }

    virtual ~ValueExpectationException() throw() { }

    virtual const char* what() const throw() {
        ostringstream os;
        os << "  at " << _location << endl;
        os << "    expected value: " << _expected << endl;
        os << "      actual value: " << _actual;
        return os.str().c_str();
    }

    T actual() {
        return _actual;
    }
    T expected() {
        return _expected;
    }
    string location() {
        return _location;
    }

private:
    T _actual;
    T _expected;
    string _location;
};

template<class T>
void make_error(T lhs, T rhs, string loc) {
    throw ValueExpectationException<T>(lhs, rhs, loc);
}

class MissingExceptionExpectationException : public std::exception {
public:
    MissingExceptionExpectationException() {}

    MissingExceptionExpectationException(string loc) :
        _location(loc) { }

    virtual ~MissingExceptionExpectationException() throw() { }

    virtual const char* what() const throw() {
        ostringstream os;
        os << "  at " << _location << endl;
        os << "    an exception was expected" << endl;
        os << "    no exception was thrown";
        throw os.str().c_str();
    }

    string location() {
        return _location;
    }

private:
    string _location;
};

void make_missing_exception_error(string loc) {
    throw MissingExceptionExpectationException(loc);
}

class WrongExceptionExpectationException : public std::exception {
public:
    WrongExceptionExpectationException() {}

    WrongExceptionExpectationException(string actual, string expected, string loc) :
        _actual(actual), _expected(expected), _location(loc) { }

    virtual ~WrongExceptionExpectationException() throw() { }

    virtual const char* what() const throw() {
        ostringstream os;
        os << "  at " << _location << endl;
        os << "    an unexpected exception ocurred" << endl;
        os << "    expected type: " << _expected << endl;
        os << "    but got: " << _actual;
        return os.str().c_str();
    }

    string actual() {
        return _actual;
    }
    string expected() {
        return _expected;
    }
    string location() {
        return _location;
    }

private:
    string _actual;
    string _expected;
    string _location;
};

template<typename T>
void make_wrong_type_exception_error(T e, const char* expected, string loc) {
    throw WrongExceptionExpectationException(e, expected, loc);
}

string location(const char* file, int line) {
    ostringstream os;
    os << file << ":" << line;
    return os.str().c_str();
}

string bool_to_s(bool b) {
    return b ? "true" : "false";
}

#define SUPPORT_ASSERT_EQ_ON(T) \
	void assert_eq(T lhs, T rhs, string loc) { if (!(lhs == rhs)) { make_error(lhs, rhs, loc); } }\


SUPPORT_ASSERT_EQ_ON(int)
SUPPORT_ASSERT_EQ_ON(double)
SUPPORT_ASSERT_EQ_ON(float)
void assert_eq(bool lhs, bool rhs, string loc) {
    if (lhs != rhs) {
        make_error(bool_to_s(lhs), bool_to_s(rhs), loc);
    }
}
void assert_eq(string lhs, string rhs, string loc) {
    if (lhs.compare(rhs) != 0) {
        make_error(lhs, rhs, loc);
    }
}
void assert_eq(const char* lhs, const char* rhs, string loc) {
    assert_eq(string(lhs), string(rhs), loc);
}

}

#define RUN_TEST(test) {\
{bool mt_ok = true;\
std::cout << #test << "..." << std::flush;\
try { test(); }\
catch (std::exception& e) { mt_ok = false; std::cout << "failed" << std::endl << e.what(); } \
catch (const char* msg) { mt_ok = false; std::cout << "failed" << std::endl << msg; } \
catch (...) { mt_ok = false; std::cout << "failed"; }\
if (mt_ok) { std::cout << "ok"; }\
std::cout << std::endl << std::flush;\
}\
}
#define ASSERT_EQ(lhs, rhs) { mt::assert_eq((lhs), (rhs), mt::location(__FILE__, __LINE__)); }
#define ASSERT(expr) { mt::assert_eq((expr), true, mt::location(__FILE__, __LINE__)); }

#define ASSERT_RAISE(code) {\
{bool mt_thrown = false;\
try { code; }\
catch (...) { mt_thrown = true; }\
if (!mt_thrown) { mt::make_missing_exception_error(mt::location(__FILE__, __LINE__)); }\
}\
}

#define ASSERT_RAISE_A(e_type, var, code) {\
{bool mt_thrown = false;\
try { code; }\
catch (e_type mt_e) { mt_thrown = true; var = mt_e; }\
catch (const std::exception &e) { mt::make_wrong_type_exception_error(e.what(), #e_type, mt::location(__FILE__, __LINE__)); }\
catch (...) { mt::make_wrong_type_exception_error("<unkown type>", #e_type, mt::location(__FILE__, __LINE__)); }\
if (!mt_thrown) { mt::make_missing_exception_error(mt::location(__FILE__, __LINE__)); }\
}\
}







//Chequea que el diccionario vacio no tenga claves
void test_claves_dicc_vacio2() {
    DiccString<int> d;
    ASSERT(d.Claves().Cardinal() == 0);
    d.Definir("", 1);
    ASSERT(d.Claves().Cardinal() == 1);
    d.Definir("hoaeoueoau", 2);
    ASSERT(d.Claves().Cardinal() == 2);
}


//Chequea el definir y definido
void test_definir_definido2() {
    DiccString<int> d;
    ASSERT(!d.Definido("hola"));
    d.Definir("hola",42);
    ASSERT( d.Definido("hola") );
    ASSERT( !d.Definido("casona") );
    ASSERT( !d.Definido("casa") );

    d.Definir("casona",13);
    ASSERT( d.Definido("hola") );
    ASSERT( d.Definido("casona") );
    ASSERT( !d.Definido("casa") );

    d.Definir("casa",6);
    ASSERT( d.Definido("hola") );
    ASSERT( d.Definido("casona") );
    ASSERT( d.Definido("casa") );
}



//cheque el obtener
void test_obtener2() {
    DiccString<int> d;
    d.Definir("hola",42);
    d.Definir("casa",22);

    ASSERT( d.Obtener("hola") == 42 );
    ASSERT( d.Obtener("casa") == 22 );
    d.Definir("hola", 22);
    ASSERT(d.Obtener("hola") == 22);
    d.Definir("hola", 24);
    ASSERT(d.Obtener("hola") == 24);
    d.Definir("hola", 25);
    ASSERT(d.Obtener("hola") == 25);
    d.Definir("h", 5);
    ASSERT(d.Obtener("h") == 5);
    d.Definir("h", 6);
    ASSERT(d.Obtener("h") == 6);
    d.Definir("h", 7);
    ASSERT(d.Obtener("h") == 7);
    d.Definir("holas", 5);
    ASSERT(d.Obtener("holas") == 5);
    d.Definir("holas", 6);
    ASSERT(d.Obtener("holas") == 6);
}

//cheque el borrar
void test_borrar_uno2() {
    DiccString<int> d;
    d.Definir("casa", 1);
    d.Borrar("casa");
    ASSERT(d.Definido("casa") == false);
    ASSERT(d.Claves().Cardinal() == 0);
}

void test_borrar2() {
    DiccString<int> d;
    d.Definir("hola",42);
    d.Definir("cas", 1);
    d.Definir("casa",22);
    d.Definir("casanova", 50);
    d.Borrar("casa");

    ASSERT( d.Definido("cas") );
    ASSERT( d.Definido("hola") );
    ASSERT( d.Definido("casanova") );
    ASSERT(!d.Definido("casa") );

    d.Borrar("casanova");
    ASSERT( d.Definido("cas") );
    ASSERT( d.Definido("hola") );
    ASSERT(!d.Definido("casanova") );
    ASSERT(!d.Definido("casa") );

    d.Borrar("cas");
    ASSERT(!d.Definido("cas") );
    ASSERT( d.Definido("hola") );
    ASSERT(!d.Definido("casanova") );
    ASSERT(!d.Definido("casa") );

    d.Borrar("hola");
    ASSERT(!d.Definido("cas") );
    ASSERT(!d.Definido("hola") );
    ASSERT(!d.Definido("casanova") );
    ASSERT(!d.Definido("casa") );

    ASSERT(d.Claves().Cardinal() == 0);
}

void test_copia_referencia2() {
    DiccString<int> d;
    d.Definir("hola",42);
    d.Definir("cas", 1);
    d.Definir("casa",22);
    d.Definir("casanova", 50);

    DiccString<int> d2(d);
    d.Borrar("casa");

    ASSERT(d.Claves().Cardinal() == d2.Claves().Cardinal()-1);
    ASSERT(d.Obtener("hola") == d2.Obtener("hola"));
    ASSERT(d.Obtener("cas") == d2.Obtener("cas"));
    ASSERT(d.Obtener("casanova") == d2.Obtener("casanova"));

    ASSERT(d.Definido("casa") == false);
    ASSERT(d2.Definido("casa") == true);
    ASSERT(d2.Obtener("casa") == 22);
}

void test_todos_prefijos2() {
    DiccString<int> d;
    DiccString< DiccString<int> > d2;

    d.Definir("hola", 1);
    d2.Definir("uno", d);
    ASSERT(d2.Claves().Cardinal() == 1);
    ASSERT(d2.Obtener("uno").Obtener("hola")     == 1);
    ASSERT(d2.Obtener("uno").Definido("holas")   == false);
    ASSERT(d2.Obtener("uno").Definido("holasa")  == false);
    ASSERT(d2.Definido("uno")  == true);
    ASSERT(d2.Definido("unodos")  == false);
    ASSERT(d2.Definido("unodostres") == false);


    d.Definir("holas", 2);
    d2.Definir("unodos", d);
    ASSERT(d2.Claves().Cardinal() == 2);
    ASSERT(d2.Obtener("unodos").Obtener("hola")     == 1);
    ASSERT(d2.Obtener("unodos").Obtener("holas")    == 2);
    ASSERT(d2.Obtener("unodos").Definido("holasa")  == false);
    ASSERT(d2.Definido("uno")  == true);
    ASSERT(d2.Definido("unodos")  == true);
    ASSERT(d2.Definido("unodostres") == false);

    d.Definir("holasa", 3);
    d2.Definir("unodostres", d);
    ASSERT(d2.Claves().Cardinal() == 3);
    ASSERT(d2.Obtener("unodostres").Obtener("hola")     == 1);
    ASSERT(d2.Obtener("unodostres").Obtener("holas")    == 2);
    ASSERT(d2.Obtener("unodostres").Obtener("holasa")   == 3);
    ASSERT(d2.Definido("uno")  == true);
    ASSERT(d2.Definido("unodos")  == true);
    ASSERT(d2.Definido("unodostres") == true);

    d2.Borrar("uno");
    ASSERT(d2.Definido("uno") == false);
    ASSERT(d2.Definido("unodos") == true);
    ASSERT(d2.Definido("unodostres") == true);

    d2.Borrar("unodos");
    ASSERT(d2.Definido("uno") == false);
    ASSERT(d2.Definido("unodos") == false);
    ASSERT(d2.Definido("unodostres") == true);

    d2.Borrar("unodostres");
    ASSERT(d2.Definido("uno") == false);
    ASSERT(d2.Definido("unodos") == false);
    ASSERT(d2.Definido("unodostres") == false);
}

void test_doble_definicion2() {
    DiccString<int> d;
    d.Definir("hola", 1);
    d.Definir("hola", 2);
    d.Definir("holas", 3);
    d.Definir("holas", 4);

    ASSERT(d.Obtener("hola") == 2);
    ASSERT(d.Obtener("holas") == 4);
}

void test_definicion_vacia2() {
    DiccString<int> d;
    cout << "finalyolo" <<endl;
    //	d.Definir("", 10);

    d.Definir("da", 12);
    d.Definir("dario", 13);
    d.Definir("hola", 14);
    cout << "finalyolo" <<endl;
    d.Borrar("da");
    //	ASSERT(d.Definido("") == true);
    ASSERT(d.Definido("da") == false);
    ASSERT(d.Definido("dario") == true);
    ASSERT(d.Definido("hola") == true);
    cout << "finalyolo" <<endl;
    d.Borrar("dario");
    //	ASSERT(d.Definido("") == true);
    ASSERT(d.Definido("da") == false);
    ASSERT(d.Definido("dario") == false);
    ASSERT(d.Definido("hola") == true);

    d.Borrar("hola");
    //	ASSERT(d.Definido("") == true);
    ASSERT(d.Definido("da") == false);
    ASSERT(d.Definido("dario") == false);
    ASSERT(d.Definido("hola") == false);

    //	d.Borrar("");
    //	ASSERT(d.Definido("") == false);
    ASSERT(d.Definido("da") == false);
    ASSERT(d.Definido("dario") == false);
    ASSERT(d.Definido("hola") == false);
}

void test_cardinal_claves2() {
    DiccString<int> d;
    d.Definir("hola", 10);

    DiccString<int> d2(d);
    d.Definir("chau", 10);

    ASSERT(d.Claves().Cardinal() == 2);
    ASSERT(d2.Claves().Cardinal() == 1);
}

void test_todos_prefijos_con_varias_hojas2() {
    DiccString<string> d;
    /*d.Definir("", "o");*/
    d.Definir("a", "o");
    d.Definir("ag", "o");
    d.Definir("aga", "o");
    d.Definir("agar", "o");
    d.Definir("agarr", "o");
    d.Definir("agarra", "o");
    d.Definir("agarram", "o");
    d.Definir("agarrame", "o");
    d.Definir("agarramel", "o");
    d.Definir("agarramela", "o");
    d.Definir("agarramelo", "o");
    d.Definir("agarramele", "o");
    d.Definir("agarramelu", "o");

    /*ASSERT(d.Claves().Cardinal() == 14);*/
    //	d.Borrar("");
    ASSERT(d.Claves().Cardinal() == 13);
    d.Borrar("a");
    ASSERT(d.Claves().Cardinal() == 12);
    d.Borrar("ag");
    ASSERT(d.Claves().Cardinal() == 11);
    d.Borrar("aga");
    ASSERT(d.Claves().Cardinal() == 10);
    d.Borrar("agar");
    ASSERT(d.Claves().Cardinal() == 9);
    d.Borrar("agarr");
    ASSERT(d.Claves().Cardinal() == 8);
    d.Borrar("agarra");
    ASSERT(d.Claves().Cardinal() == 7);
    d.Borrar("agarram");
    ASSERT(d.Claves().Cardinal() == 6);
    d.Borrar("agarrame");
    ASSERT(d.Claves().Cardinal() == 5);
    d.Borrar("agarramel");
    ASSERT(d.Claves().Cardinal() == 4);
    d.Borrar("agarramela");
    ASSERT(d.Claves().Cardinal() == 3);
    d.Borrar("agarramelo");
    ASSERT(d.Claves().Cardinal() == 2);
    d.Borrar("agarramele");
    ASSERT(d.Claves().Cardinal() == 1);
    d.Borrar("agarramelu");
    ASSERT(d.Claves().Cardinal() == 0);
}
void test_claves_dicc_vacio() {
    DiccString<int> d;
    ASSERT(d.Claves().Cardinal() == 0);
}


//Chequea el definir y definido
void test_definir_definido() {
    DiccString<int> d;
    d.Definir("hola",42);
//	ASSERT( d.Definido("hola") );
//	ASSERT( !d.Definido("casona") );
//	ASSERT( !d.Definido("casa") );
//	cout << "yolo1" <<endl;
    d.Definir("casona",13);
//	ASSERT( d.Definido("hola") );
//	ASSERT( d.Definido("casona") );
//	ASSERT( !d.Definido("casa") );
//	cout << "yolo2" <<endl;
    d.Definir("casa",6);
//	ASSERT( d.Definido("hola") );
//	ASSERT( d.Definido("casona") );
//	ASSERT( d.Definido("casa") );
//	cout << "yolo3" <<endl;
//	d.Borrar("casa");
//	ASSERT( d.Definido("hola") );
//	ASSERT( d.Definido("casona") );
//	ASSERT( !d.Definido("casa") );
//	d.Borrar("casona");
//	ASSERT( d.Definido("hola") );
//	ASSERT( !d.Definido("casona") );
//	ASSERT( !d.Definido("casa") );
//	cout << "yolo4" <<endl;
    DiccString<int>::Iterador it = d.CrearIt();
//	cout << it.SiguienteClave() <<endl;
//	cout << it.SiguienteSignificado() <<endl;
//	cout << it.Siguiente() <<endl;
//	cout << it.HaySiguiente() <<endl;

    d.Borrar("hola");

//	it = CrearIt(d);

    cout << it.SiguienteClave() <<endl;
    cout << it.SiguienteSignificado() <<endl;
//	cout << it.Siguiente() <<endl;
    cout << it.HaySiguiente() <<endl;
    it.Avanzar();
    cout << it.SiguienteClave() <<endl;
    cout << it.SiguienteSignificado() <<endl;
//	cout << it.Siguiente() <<endl;
    cout << it.HaySiguiente() <<endl;
//	cout << "yolo5" <<endl;
//	ASSERT( !d.Definido("hola") );
//	ASSERT( !d.Definido("casona") );
//	ASSERT( !d.Definido("casa") );


}



//cheque el obtener
void test_obtener() {
    DiccString<int> d;
    d.Definir("hola",42);
    d.Definir("casa",22);
    ASSERT( d.Obtener("hola") == 42 );
    ASSERT( d.Obtener("casa") == 22 );
    d.Definir("hola", 22);
    ASSERT(d.Obtener("hola") == 22);

}

void test_joaco() {
    DiccString<int> d;
    //	cout << "yolo" <<endl;
    d.Definir("hola",42);
    //	cout << "yolo" <<endl;
    d.Definir("holaa",2);
    //	cout << "yolo" <<endl;
    d.Definir("holasaasa",3);
    d.Definir("holasaasaa",4);
    d.Definir("hols", 32);
    d.Definir("ahhols", 33);
    d.Definir("h",44);

    ASSERT(d.Claves().Pertenece("hola"));
    ASSERT(d.Claves().Pertenece("holaa"));
    ASSERT(d.Claves().Pertenece("holasaasa"));
    ASSERT(d.Claves().Pertenece("holasaasaa"));
    ASSERT(d.Claves().Pertenece("hols"));
    ASSERT(d.Claves().Pertenece("ahhols"));
    ASSERT(d.Claves().Pertenece("h"));
    ASSERT(d.Claves().Cardinal() == 7);

    ASSERT( d.Definido("hola") );
    ASSERT( d.Definido("holaa") );
    ASSERT( d.Definido("holasaasa") );
    ASSERT( d.Definido("holasaasaa") );
    ASSERT( d.Definido("hols") );
    ASSERT( d.Definido("ahhols") );

    ASSERT_EQ( d.Obtener("hola"),42 );
    ASSERT_EQ( d.Obtener("holaa"),2 );
    ASSERT_EQ( d.Obtener("holasaasa"),3 );
    ASSERT_EQ( d.Obtener("holasaasaa"),4 );
    ASSERT_EQ( d.Obtener("hols"),32 );
    ASSERT_EQ( d.Obtener("h"),44 );
    ASSERT_EQ( d.Obtener("ahhols"),33 );

    d.Definir("holasaasaa",5);
    ASSERT( d.Definido("holasaasaa") );
    d.Borrar("holaa");

    d.Borrar("h");
//	cout << "yolo2" <<endl;
    d.Borrar("holasaasaa");
//	cout << "yolo3" <<endl;
    //	ASSERT(d.Claves().Pertenece("hola"));
    //	ASSERT(!d.Claves().Pertenece("holaa"));
    //	ASSERT(d.Claves().Pertenece("holasaasa"));
    //	ASSERT(!d.Claves().Pertenece("holasaasaa"));
    //	ASSERT(d.Claves().Pertenece("hols"));
    //	ASSERT(d.Claves().Pertenece("ahhols"));
    //	ASSERT(!d.Claves().Pertenece("h"));
    //	ASSERT(d.Claves().Cardinal() == 4);

    //	ASSERT( d.Definido("hola") );
    //	ASSERT( !d.Definido("holaa") );
    //	ASSERT( d.Definido("holasaasa") );
    //	ASSERT( !d.Definido("holasaasaa") );
}


//cheque el borrar
void test_borrar() {
    //Completar este test para:
    //Verificar que al borrar una palabra, esta deja de estar definida en el diccionario
    //Chequear que si dos palabras comparten prefijos y una de ellas se borrar, la otra debe seguir estando definida
    //Analizar que el borrado funciona bien si el diccionario tiene definido una sola palabra y esta se borra.

    DiccString<int> d;
    d.Definir("hola",42);
    d.Definir("casa",22);
    d.Definir("casas",22);
    d.Definir("cascada",22);
    ASSERT(d.Claves().Pertenece("hola"));
    ASSERT(d.Claves().Pertenece("casa"));
    ASSERT(d.Claves().Pertenece("casas"));
    ASSERT(d.Claves().Pertenece("cascada"));

    d.Borrar("casa");
    ASSERT( d.Definido("hola") );
    ASSERT(!d.Claves().Pertenece("casa"))
    ASSERT(!d.Definido("casa") );
    ASSERT(!d.Definido("c"));
    ASSERT( d.Definido("casas") );
    ASSERT( d.Definido("cascada") );

    d.Borrar("hola");
    ASSERT(!d.Claves().Pertenece("hola"));
    ASSERT(!d.Claves().Pertenece("casa"));
    ASSERT(d.Claves().Pertenece("casas"));
    ASSERT(d.Claves().Pertenece("cascada"));
    ASSERT(!d.Definido("hola"));

    d.Definir("casa", 22);

    d.Borrar("casas");
    ASSERT(!d.Claves().Pertenece("hola"));
    ASSERT(d.Claves().Pertenece("casa"));
    ASSERT(!d.Claves().Pertenece("casas"));
    ASSERT(d.Claves().Pertenece("cascada"));
    ASSERT(d.Definido("casa"));
    ASSERT(d.Definido("cascada"));

    d.Borrar("cascada");
    ASSERT(!d.Claves().Pertenece("hola"));
    ASSERT(d.Claves().Pertenece("casa"));
    ASSERT(!d.Claves().Pertenece("casas"));
    ASSERT(!d.Claves().Pertenece("cascada"));
    ASSERT( !d.Definido("hola") );

    d.Borrar("casa");
    ASSERT(!d.Claves().Pertenece("hola"));
    ASSERT(!d.Claves().Pertenece("casa"));
    ASSERT(!d.Claves().Pertenece("casas"));
    ASSERT(!d.Claves().Pertenece("cascada"));
    ASSERT(!d.Definido("casa") );
    ASSERT(!d.Definido("c"));
    ASSERT( !d.Definido("casas") );
    ASSERT( !d.Definido("cascada") );

    DiccString<int> d2;
    d2.Definir("h", 5);
    ASSERT(d2.Definido("h"));
    d2.Borrar("h");
    ASSERT(!d2.Definido("h"));

}

void test_claves() {
    DiccString<int> d;
    d.Definir("hola",42);
    d.Definir("casa",22);
    d.Definir("h",4);
    d.Definir("c",2);
    d.Definir("gato",10);
    d.Definir("cascada",3);
    ASSERT(d.Claves().Cardinal() == 6);
    ASSERT(d.Claves().Pertenece("hola"));
    ASSERT(d.Claves().Pertenece("h"));
    ASSERT(d.Claves().Pertenece("gato"));
    ASSERT(d.Claves().Pertenece("casa"));
    ASSERT(d.Claves().Pertenece("c"));
    ASSERT(!d.Claves().Pertenece("cas"));
    //	ASSERT(d.Claves().minimo() == "c");
    d.Borrar("hola");
    ASSERT(d.Claves().Cardinal() == 5);
    d.Borrar("casa");
    ASSERT(d.Claves().Cardinal() == 4);
    d.Borrar("h");
    ASSERT(d.Claves().Cardinal() == 3);
    d.Borrar("c");
    ASSERT(d.Claves().Cardinal() == 2);
    d.Borrar("gato");
    ASSERT(d.Claves().Cardinal() == 1);
    d.Borrar("cascada");
    ASSERT(d.Claves().Cardinal() == 0);
    DiccString<int> d3;
    DiccString<int> d4(d3);
    ASSERT(d3.Claves().Cardinal() == d4.Claves().Cardinal())
}

void test_constructor_por_copia() {
    DiccString<int> d;
    d.Definir("hola",42);
    d.Definir("casa",22);
    d.Definir("h",4);
    d.Definir("c",2);
    d.Definir("gato",10);
    d.Definir("cascada",3);
    DiccString<int> d2(d);
    ASSERT(d2.Definido("hola"));
    ASSERT(d2.Definido("casa"));
    ASSERT(d2.Definido("cascada"));
    ASSERT(d2.Definido("gato"));
    ASSERT(d.Claves().Cardinal() == d2.Claves().Cardinal());
    d.Borrar("hola");
    ASSERT(!d.Definido("hola"));
    ASSERT(d2.Definido("hola"));
    d2.Borrar("gato");
    ASSERT(d.Definido("gato"));
    ASSERT(!d2.Definido("gato"));
    d.Borrar("gato");
    d2.Borrar("hola");
    d.Borrar("casa");
    d2.Borrar("casa");
    d.Borrar("h");
    d2.Borrar("h");
    d2.Definir("gcs", 6);
    d.Borrar("c");
    d2.Borrar("c");
    d.Definir("ff", 4);
    d.Borrar("cascada");
    d2.Borrar("cascada");
    ASSERT(d2.Claves().Cardinal() == 1);
    ASSERT(d.Claves().Cardinal() == 1);
    DiccString<int> d3(d2);
    ASSERT(d3.Definido("gcs"));
}

int main() {

    RUN_TEST(test_joaco);
    RUN_TEST(test_claves_dicc_vacio);
    RUN_TEST(test_definir_definido);
    RUN_TEST(test_constructor_por_copia);
    RUN_TEST(test_claves);
    RUN_TEST(test_borrar);
    RUN_TEST(test_claves_dicc_vacio2);
    RUN_TEST(test_definir_definido2);
    RUN_TEST(test_obtener);
    RUN_TEST(test_obtener2);
    RUN_TEST(test_borrar_uno2);
    RUN_TEST(test_borrar2);
    RUN_TEST(test_copia_referencia2);
    RUN_TEST(test_todos_prefijos2);
    RUN_TEST(test_doble_definicion2);
    RUN_TEST(test_definicion_vacia2);
    RUN_TEST(test_cardinal_claves2);
    RUN_TEST(test_todos_prefijos_con_varias_hojas2);
//	//Realizar más test para chequear el funcionamiento del diccionario sobre trie.
//
    // MARCH: Geniales los tests del taller. Estaría bueno testear lo nuevo: la
    // devolución de significado por referencia y los iteradores.
    return 0;

}

















































//Coordenada nuevaC = Coordenada(7,1);
//Mapa mundo;
//mundo.agregarCoord(nuevaC);
//	Vector<int>* res = NULL;
//	Vector< Vector<int>* > yolo;
//	yolo.AgregarAtras(res);
//	RUN_TEST(test_joaco);
//	RUN_TEST(test_claves_dicc_vacio);
//	RUN_TEST(test_definir_definido);
//	RUN_TEST(test_obtener);
//	RUN_TEST(test_constructor_por_copia);
//	RUN_TEST(test_claves);
//	RUN_TEST(test_borrar);
