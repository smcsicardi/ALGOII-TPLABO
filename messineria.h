#ifndef MESSINERIA_H_
#define MESSINERIA_H_

#include <iostream>
#include <cassert>
using namespace std;

/*
 * Se puede asumir que el tipo T tiene constructor por copia y operator==
 * No se puede asumir que el tipo T tenga operator=
 */
template<typename T>
class Messineria {

  public:

	/*
	 * Crea una secta nueva sin adeptos.
	 */
	Messineria();

	/*
	 * Una vez copiada, ambas Messinerias deben ser independientes,
	 * es decir, cuando se borre una no debe borrar la otra.
	 */
	Messineria(const Messineria<T>&);

	/*
	 * Acordarse de liberar toda la memoria!
	 */
	~Messineria();

	/*
	 * Agrega un nuevo adepto a la Messineria. Si ya tenemos al Elegido
	 * el nuevo adepto deberá arrodillarse a la izquierda de él. En caso
	 * contrario, se arrodillará a la izquierda del que está alabando.
	 */
	void golDeMessi(const T&);

	/*
	 * Elimina de la secta al adepto pasado por parámetro. Si el mismo tenía
	 * el turno de alabar, debe pasar al siguiente (en caso de que haya).
	 */
	void golDeCristiano(const T&);

	/*
	 * Devuelve el adepto que está albando.
	 *
	 * PRE: Hay adeptos en la Messineria.
	 */
	const T& adeptoAlabando() const;

    /*
	 * Devuelve el próximo elemento según el orden dado.
	 * Quien alaba debe cambiar. Con lo cual sucesivas llamadas a esta función
	 * retornan distintos valores.
	 *
	 * PRE: Hay adeptos en la Messineria.
	 */
	const T& alabarMessi();

	/*
	 * Cambia el turno de alabar al inmediato anterior.
	 *
	 */
	void olvideAlabarloUnPocoMas();

	/*
	 * Selecciona al adepto que está alabando como el Elegido.
	 *
	 * PRE: Hay adeptos en la Messineria y no hay Elegido.
	 */
	void escogerElegido();

    /*
	 * Indica si esta presente el Elegido entre los adeptos.
	 */
	bool hayElegido() const;

	/*
	* Elimina de la secta al Elegido.
	*
	* PRE: hay Elegido en la Messinería.
	*/
	void traidor();

	/*
	* El Elegido interrumpe el tuno y pasa a ser el que está alabando
	*
	* PRE: hay Elegido en la Messinería.
	*/
	void interrumpirTurno();

	/*
	 * Devuelve al Elegido.
	 *
	 * PRE: Hay Elegido en la Messineria.
	 */
	const T& dameElegido() const;

	/*
	 * Dice si la Messineria tiene o no adeptos.
	 */
	bool esVacia() const;

	/*
	 * Devuelve la cantidad de adeptos a la Messineria.
	 */
	int tamanio() const;

	/*
	 * Devuelve true si las Messinerias son iguales.
	 */
	bool operator==(const Messineria<T>&) const;

	/*
	 * Debe mostrar la ronda por el ostream (y retornar el mismo).
	 * Messineria vacio: []
	 * Messineria con 2 elementos (e1 es el actual): [e1, e2]
	 * Messineria con 2 elementos (e2 es el actual y e1 es el Elegido): [e2, e1*]
	 * Messineria con 3 elementos (e1 es el actual, e2 fue agregado antes que e3,
	 * e1 fue agregado antes que e2): [e1, e2, e3]
	 */
	ostream& mostrarMessineria(ostream&) const;


  private:
	/*
	 * No se puede modificar esta funcion.
	 */
	Messineria<T>& operator=(const Messineria<T>& otra) {
		assert(false);
		return *this;
	}

	/*
	 * Aca va la implementación del nodo.
	 */
	struct Nodo {
    T adepto;
    Nodo* anterior;
    Nodo* siguiente;
	};
    int longitud;
    Nodo* elegido;
    Nodo* elQueAlaba;
    Nodo* interrumpido;
};

template<class T>
ostream& operator<<(ostream& out, const Messineria<T>& a) {
	return a.mostrarMessineria(out);
}

// Implementación a hacer por los alumnos.
template<typename T>
Messineria<T>::Messineria() {
    longitud = 0;
    elQueAlaba = NULL;
    elegido = NULL;
    interrumpido = NULL;
    }

template<typename T>
Messineria<T>::Messineria(const Messineria<T>& otra) {
    longitud = otra.longitud;
    elQueAlaba = NULL;
    elegido = NULL;
    if (otra.esVacia()){
        interrumpido = NULL;
        } else{
            elQueAlaba = new Nodo;
            elQueAlaba->adepto = otra.elQueAlaba->adepto;
            elQueAlaba->anterior = NULL;
            elQueAlaba->siguiente = NULL;

            Nodo* recorrer = elQueAlaba;
            Nodo* recorrerOtra = otra.elQueAlaba;
            for (int i = 0;i<longitud-1;i++) {
                recorrer->siguiente = new Nodo;
                recorrer->siguiente->adepto = recorrerOtra->siguiente->adepto;
                recorrer->siguiente->anterior = recorrer;
                recorrer->siguiente->siguiente = NULL;
                if (otra.interrumpido == recorrerOtra) {
                    interrumpido = recorrer;
                }
                if (otra.elegido == recorrerOtra) {
                    elegido = recorrer;
                }
                recorrer = recorrer->siguiente;
                recorrerOtra = recorrerOtra->siguiente;
            }
            recorrer->siguiente = elQueAlaba;
            elQueAlaba->anterior = recorrer;
        }
}
template<typename T>
Messineria<T>::~Messineria() {
    if (elQueAlaba!=NULL) {
        Nodo* recorrer;
        int i=0;
        int l = longitud;
        for(i = 0;i<l-2;i++) {
                recorrer = elQueAlaba->siguiente;
                delete elQueAlaba;
                elQueAlaba = recorrer;
                longitud--;
            }
        if (longitud==2) {
                delete elQueAlaba->siguiente;
            }
        delete elQueAlaba;
        elQueAlaba = NULL;
        elegido = NULL;
        longitud = 0;
    }
//    cout << "ESTÁS DESTRUYENDO" << endl;
}

template<typename T>
void Messineria<T>::golDeMessi(const T& nuevo) {
    longitud++;
    if (longitud == 1) {
        elQueAlaba = new Nodo;
        elQueAlaba->adepto = nuevo;
        elQueAlaba->anterior = elQueAlaba;
        elQueAlaba->siguiente = elQueAlaba;
        elegido = NULL;
    } else {
        if (longitud == 2) {
            Nodo* nuevoAdepto = new Nodo;
            nuevoAdepto->adepto = nuevo;
            nuevoAdepto->anterior = elQueAlaba;
            nuevoAdepto->siguiente = elQueAlaba;

            elQueAlaba->anterior = nuevoAdepto;
            elQueAlaba->siguiente = nuevoAdepto;
        } else {
            if (elegido == NULL) {
                Nodo* nuevoAdepto = new Nodo;
                nuevoAdepto->adepto = nuevo;
                nuevoAdepto->anterior = elQueAlaba->anterior;
                nuevoAdepto->siguiente = elQueAlaba;

                elQueAlaba->anterior->siguiente = nuevoAdepto;
                elQueAlaba->anterior = nuevoAdepto;

            } else {
                Nodo* nuevoAdepto = new Nodo;
                nuevoAdepto->adepto = nuevo;
                nuevoAdepto->anterior = elegido->anterior;
                nuevoAdepto->siguiente = elegido;
                elegido->anterior->siguiente = nuevoAdepto;
                elegido->anterior = nuevoAdepto;
            }
        }
    }

}
//borra todos los cristianos
template<typename T>
void Messineria<T>::golDeCristiano(const T& cristiano){
    Nodo* auxSig;
    Nodo* auxAnt;
    if (elQueAlaba->adepto == cristiano) {
        alabarMessi();
    }
    Nodo* recorrer = elQueAlaba;
    int l = longitud;
    for (int i = 0; i<l; i++) {
        if (recorrer->adepto == cristiano) {
            auxAnt = recorrer->anterior;
            auxSig = recorrer->siguiente;
            auxAnt->siguiente = auxSig;
            auxSig->anterior = auxAnt;
            if(recorrer==elegido) {
            elegido=NULL;
            interrumpido = NULL;
            }
            if(recorrer==interrumpido) {
            interrumpido = NULL;
            }
            delete recorrer;
            recorrer = auxAnt;
            longitud--;
        }
        recorrer = recorrer->siguiente;
    }
}

template<typename T>
const T& Messineria<T>::adeptoAlabando() const {
    return elQueAlaba->adepto;
}

template<typename T>
const T& Messineria<T>::alabarMessi(){
    elQueAlaba = elQueAlaba->siguiente;
    return elQueAlaba->adepto;
}


template<typename T>
void Messineria<T>::olvideAlabarloUnPocoMas(){
    elQueAlaba = elQueAlaba->anterior;
}


template<typename T>
void Messineria<T>::escogerElegido(){
    elegido = elQueAlaba;
}


template<typename T>
bool Messineria<T>::hayElegido() const{
    return (elegido!=NULL);
}


template<typename T>
void Messineria<T>::traidor(){
    if (elegido == elQueAlaba) {
        alabarMessi();
    }
    golDeCristiano(elegido->adepto);
    elegido = NULL;
    interrumpido = NULL;
}

template<typename T>
void Messineria<T>::interrumpirTurno(){
    interrumpido = elQueAlaba;
    elQueAlaba = elegido;
}

template<typename T>
const T& Messineria<T>::dameElegido() const{
    return elegido->adepto;
}

template<typename T>
bool Messineria<T>::esVacia() const{
    return longitud==0;
}

template<typename T>
int Messineria<T>::tamanio() const{
    return this->longitud;
}

template<typename T>
bool Messineria<T>::operator==(const Messineria<T>& otra) const{
    bool res = (longitud == otra.longitud);
    res = (res && elQueAlaba->adepto == otra.elQueAlaba->adepto && elegido == otra.elegido && interrumpido == otra.interrumpido);
    Nodo* recorrer1;
    Nodo* recorrer2;
    recorrer1 = elQueAlaba;
    recorrer2 = otra.elQueAlaba;
    for (int i = 0; res && i<longitud;i++){
        res = (recorrer1->adepto = recorrer2->adepto);
    }
    return res;
}

template<typename T>
ostream& Messineria<T>::mostrarMessineria(ostream& os) const{
    int i = 0;
    Nodo* aImprimir;
    if (elQueAlaba == NULL) {
    os << "[]" << endl;
    } else{
        aImprimir = elQueAlaba;
        os << "[";
        while (i<longitud-1) {
            os << aImprimir->adepto << ", ";
            aImprimir = aImprimir->siguiente;
            i++;
        }
        os << aImprimir->adepto << "]" << endl;
    }
    return os;
}

#endif //MESSINERIA_H_
