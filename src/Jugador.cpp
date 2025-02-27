//
// Created by ronyrojas on 26/02/25.
//

//
// Created by ronyrojas on 19/02/25.
//
#include "../include/Jugador.h"
#include "../include/Letra.h"
#include <iostream>

using namespace std;

Jugador::Jugador() {
    nombre = "";
    puntuacion = 0;
    cantidadTurnos = 0;
    tiempoJugado = 0;
    letras = new ListaEnlazada<Letra>();
}

void Jugador::mostrarLetras() const {
    // Verificamos si el jugador tiene letras
    if (letras == nullptr || letras->isEmpty()) {
        cout << "El jugador no tiene letras en su inventario." << endl;
        return;
    }

    // Recorremos la lista de letras
    for (int i = 0; i < letras->getTamano(); i++) {
        // Obtenemos la letra en la posición actual
        Letra *letraActual = letras->obtenerDatoEnPosicion(i);

        // Mostramos la información de la letra
        if (letraActual != nullptr) {
            cout << i + 1 << ") Letra: " << letraActual->getLetra()
                    << ", Punteo: " << letraActual->getPunteo() << "; ";
        }
    }
}

void Jugador::ordenarLetrasPorPunteo() {
    if (letras == nullptr || letras->isEmpty()) return;
    letras->setCabeza(mergeSort(letras->getCabeza())); //llamando a metodo para ordenar la lista usando mergeSort
}

Nodo<Letra> *Jugador::mergeSort(Nodo<Letra> *cabeza) {
    if (cabeza == nullptr || cabeza->getNext() == nullptr) {
        return cabeza; // si la lista esta vacía o con un elemento, ya esta ordenada
    }

    // dividiendo la lista en dos mitades
    Nodo<Letra> *mitad = dividirLista(cabeza);

    // ordenando ambas mitades de manera recursiva
    Nodo<Letra> *izquierda = mergeSort(cabeza);
    Nodo<Letra> *derecha = mergeSort(mitad);

    // fusionar las mitades ya ordenadas
    return fusionarListas(izquierda, derecha);
}

Nodo<Letra> *Jugador::dividirLista(Nodo<Letra> *cabeza) {
    if (cabeza == nullptr) return nullptr;

    Nodo<Letra> *lento = cabeza;
    Nodo<Letra> *rapido = cabeza->getNext();

    // avanzando rapido dos pasos y lento un paso, para obtener el largo de la lista y la mitad
    while (rapido != nullptr && rapido->getNext() != nullptr) {
        lento = lento->getNext();
        rapido = rapido->getNext()->getNext();
    }

    // sepraando la lista a la mitda
    Nodo<Letra> *mitad = lento->getNext();
    lento->setNext(nullptr); // desvinculando la mitad de la lista original y devolviendola
    return mitad;
}

Nodo<Letra> *Jugador::fusionarListas(Nodo<Letra> *izquierda, Nodo<Letra> *derecha) {
    if (izquierda == nullptr) {
        return derecha;
    }
    if (derecha == nullptr) {
        return izquierda;
    }
    Nodo<Letra> *resultado = nullptr;
    // comparando puntajes de derecha e izq y fusionando listas
    if (izquierda->getValue().getPunteo() >= derecha->getValue().getPunteo()) {
        resultado = izquierda;
        resultado->setNext(fusionarListas(izquierda->getNext(), derecha));
    } else {
        resultado = derecha;
        resultado->setNext(fusionarListas(izquierda, derecha->getNext()));
    }
    return resultado;
}

int Jugador::mostrarOpcionesTurno() const {
    int opcion;
    cout << "\nEs tu turno " << nombre << endl;
    cout << "*********** Selecciona Una Opcion ***********" << endl;
    cout << "1. Colocar Letra (ficha)" << endl;
    cout << "2. Ver Tus Letras" << endl;
    cout << "3. Ver Palabras Jugables" << endl;
    cout << "4. Pasar turno" << endl;
    cout << "5. Terminar Partida" << endl;
    cout << "Selecciona Una Opcion" << endl;
    cin >> opcion;
    return opcion;
}

// getters
string Jugador::getNombre() const {
    return nombre;
}

int Jugador::getPuntuacion() const {
    return puntuacion;
}

int Jugador::getCantidadTurnos() const {
    return cantidadTurnos;
}

int Jugador::getTiempoJugado() const {
    return tiempoJugado;
}

ListaEnlazada<Letra> *Jugador::getLetras() {
    return letras;
}

// setters
void Jugador::setNombre(const string &nombre) {
    this->nombre = nombre;
}

void Jugador::setPuntuacion(int puntuacion) {
    this->puntuacion = puntuacion;
}

void Jugador::setCantidadTurnos(int cantidadTurnos) {
    this->cantidadTurnos = cantidadTurnos;
}

void Jugador::setTiempoJugado(int tiempoJugado) {
    this->tiempoJugado = tiempoJugado;
}

void Jugador::setLetras(ListaEnlazada<Letra> *letras) {
    this->letras = letras;
}

ostream &operator<<(ostream &os, const Jugador &jugador) {
    os << "Nombre: " << jugador.getNombre()
            << ", Puntuación: " << jugador.getPuntuacion()
            << ", Turnos: " << jugador.getCantidadTurnos()
            << ", Tiempo Jugado: " << jugador.getTiempoJugado() << "s";
    return os;
}
