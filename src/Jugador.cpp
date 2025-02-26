//
// Created by ronyrojas on 19/02/25.
//
#include "../include/Jugador.h"
#include "../include/Letra.h"
#include <iostream>

using namespace std;

Jugador::Jugador(): nombre(""), puntuacion(0), cantidadTurnos(0), tiempoJugado(0), letras() {}


void Jugador::mostrarLetras()  {
    int numeroLetra = 0;
    Nodo<Letra> *actual = letras.obtenerCabeza();

    cout << "Letras (fichas) de " << nombre << ": \n";
    if (!actual) {
        cout << nombre << ", no tiene mas letras en su bolsa" << endl;
        return;
    }
    while (actual) {
        cout << numeroLetra << ".- Letra = " << actual->dato.getLetra()
             << ", punteo = " << actual->dato.getPunteo() << "; ";
        actual = actual->siguiente;
        numeroLetra++;
    }
    cout << endl;
}

void Jugador::ordenarLetrasPorPunteo() {
    //metodo a llamar para ordenar letras
    letras.setCabeza(mergeSort(letras.obtenerCabeza()));
}

Nodo<Letra>* Jugador::mergeSort(Nodo<Letra>* cabeza) {
    //algoritmo Merge Sort de complejidad O(n log n)
    if (!cabeza || !cabeza->siguiente) {
        return cabeza; //  cuando no hay cabeza o solo hay un nodo (el unico nodo es la cabeza)
    }
    Nodo<Letra>* medio = dividirLista(cabeza); //lLamando a metodo para dividir la lista general en 2
    Nodo<Letra>* izquierda = mergeSort(cabeza); // enviando la 1era mitad para dividir...
    Nodo<Letra>* derecha = mergeSort(medio); //enviando la 2da mitad tambien
    return fusionarListas(izquierda, derecha); //fusiona las 2 mitades para tener una lista ordenada
}

Nodo<Letra>* Jugador::dividirLista(Nodo<Letra>* cabeza) {
    Nodo<Letra>* lento = cabeza; //puntero que avanza un nodo a la vez
    Nodo<Letra>* rapido = cabeza->siguiente; //puntero que avanza 2 nodos a la vez

    while (rapido && rapido->siguiente) {
        //mientras existan estos punteros (cuando ya no hay rapido, lento estara a media lista)
        lento = lento->siguiente; //avanzando 1 puntero
        rapido = rapido->siguiente->siguiente; //avanzando 2 punteros
    }
    Nodo<Letra>* medio = lento->siguiente; //guardando el inicio de la 2da lista
    lento->siguiente = nullptr; // desliga ambas listas
    return medio; //devolviendo la 2da mitad
}

Nodo<Letra>* Jugador::fusionarListas(Nodo<Letra>* izquierda, Nodo<Letra>* derecha) {
    if (!izquierda) return derecha; //si no hay 2da lista, devuelve la 1ra
    if (!derecha) return izquierda; //si no hay 1ra lista, devuelve la 2da

    Nodo<Letra>* resultado = nullptr; //nodo que guardara el que tenga mayor punteo

    if (izquierda->dato.getPunteo() >= derecha->dato.getPunteo()) {
        //comparando ambos datos
        resultado = izquierda; //si el mayor es el de la izquierda
        resultado->siguiente = fusionarListas((izquierda->siguiente), derecha);
        // se compara el siguiente de la izquierda con el derecho
    } else {
        resultado = derecha; //si el mayo es el de la derecha
        resultado->siguiente = fusionarListas(izquierda, derecha->siguiente);
        //se compara el siguiente de la derecha con el izquierdo
    }
    return resultado; //devolviendo el nodo de mayor valor
}

int Jugador::mostrarOpcionesTurno() const {
    int opcion;
    cout << "\nEs tu turno " << nombre << endl;
    cout << "*********** Selecciona Una Opcion ***********" << endl;
    cout << "1. Colocar Letra (ficha)" << endl;
    cout << "2. Ver Tus Letras" << endl;
    cout << "3. Ver Palabras Jugables" << endl;
    cout << "Selecciona Una Opcion" << endl;
    cin >> opcion;
    return opcion;
}

// getters
string Jugador::getNombre() const { return nombre; }
int Jugador::getPuntuacion() const { return puntuacion; }
int Jugador::getCantidadTurnos() const { return cantidadTurnos; }
int Jugador::getTiempoJugado() const { return tiempoJugado; }
ListaEnlazada<Letra>& Jugador::getLetras() { return letras; }

// setters
void Jugador::setNombre(const string& nuevoNombre) { nombre = nuevoNombre; }
void Jugador::setPuntuacion(int puntos) { puntuacion = puntos; }
void Jugador::setCantidadTurnos(int turnoExtra) { cantidadTurnos = turnoExtra; }
void Jugador::setTiempoJugado(int tiempoExtra) { tiempoJugado = tiempoExtra; }
void Jugador::setLetra(const Letra &letra) { letras.agregarFinal(letra); }

ostream& operator<<(ostream& os, const Jugador& jugador) {
    os << "Nombre: " << jugador.getNombre()
       << ", Puntuación: " << jugador.getPuntuacion()
       << ", Turnos: " << jugador.getCantidadTurnos()
       << ", Tiempo Jugado: " << jugador.getTiempoJugado() << "s";
    return os;
}

