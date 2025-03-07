#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include "ListaEnlazada.h"
#include "Letra.h"
using namespace std;

class Jugador {
private:
    string nombre;
    int puntuacion;
    int cantidadTurnos;
    int tiempoJugado;
    ListaEnlazada<Letra> *letras;
    //encapsulando metodos
    Nodo<Letra>* mergeSort(Nodo<Letra>* cabeza);
    Nodo<Letra>* dividirLista(Nodo<Letra>* cabeza);
    Nodo<Letra>* fusionarListas(Nodo<Letra>* izquierda, Nodo<Letra>* derecha);
public:
    Jugador();

    void mostrarLetras() const;

    void ordenarLetrasPorPunteo();

    int mostrarOpcionesTurno() const;

    //getters
    string getNombre() const;

    int getPuntuacion() const;

    int getCantidadTurnos() const;

    int getTiempoJugado() const;

    ListaEnlazada<Letra>* getLetras();

    //setters
    void setNombre(const string &nuevoNombre);

    void setPuntuacion(int puntos);

    void setCantidadTurnos(int turnoExtra);

    void setTiempoJugado(int tiempoExtra);

    void setLetras(ListaEnlazada<Letra> *letras);

    friend ostream &operator<<(ostream &os, const Jugador &jugador);
};

#endif //JUGADOR_H
