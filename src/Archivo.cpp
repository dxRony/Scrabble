#include "../include/Archivo.h"
#include <fstream>
#include <sstream>
#include <iostream>

ListaEnlazada<Palabra> *Archivo::leerCSV(const string &rutaArchivo) {
    auto *listaPalabras = new ListaEnlazada<Palabra>();
    ifstream archivo(rutaArchivo, ios::in);
    if (!archivo.is_open()) {
        cerr << "Error al abrir archivo.csv " << rutaArchivo << endl;
        return listaPalabras;
    }

    string linea;
    while (getline(archivo, linea)) {
        // leyendo linea por linea
        stringstream ss(linea); //dividiendo la linea en palabras
        string palabraTexto;

        while (getline(ss, palabraTexto, ',')) {
            //extrayendo las palabras separadas por coma
            palabraTexto.erase(0, palabraTexto.find_first_not_of(" \t")); //eliminando espacios en blanco
            palabraTexto.erase(palabraTexto.find_last_not_of(" \t") + 1);

            if (!palabraTexto.empty()) {
                // si hay palabra
                Palabra palabra; // se crea el objeto palabra
                palabra.setContenido(palabraTexto); // se asigna la palabra leida
                palabra.setPuntuacion(0); // puntuacion inicial
                palabra.setPalabraFormada(false); // estado inicial
                listaPalabras->insertar(palabra); // se agrega al final de la lista
            }
        }
    }
    archivo.close();
    return listaPalabras;
}

ListaEnlazada<Palabra> *Archivo::ordenarAlfabeticamente() {
    //mandando a leer el archivo y guardar las palabras en listaPalabras
    cout << "Ingresa la ruta del archivo.csv..." << endl;
    string rutaArchivo;
    cin >> rutaArchivo;
    ListaEnlazada<Palabra> *listaPalabras = this->leerCSV(rutaArchivo);
    if (!listaPalabras || listaPalabras->isEmpty()) {
        return listaPalabras;
    }
    bool hayCambio;
    do {
        //usando algoritmo bubble sort para la ordenacion
        hayCambio = false;//para ver si se intercambio una palabra en cada recorrido del do while
        Nodo<Palabra> *actual = listaPalabras->getCabeza();//obteniendo la cabeza de la lista
        while (actual != nullptr && actual->getNext() != nullptr) {
            //mientras hayan palabras en la lista
            Nodo<Palabra> *siguiente = actual->getNext();//guardando el nodo siguiente del nodo actual
            if (actual->getValue().getContenido() > siguiente->getValue().getContenido()) {
                //comparando contenido del actual con el del siguiente
                //aplicando intercambio de nodos
                Palabra temp = actual->getValue();//guardando el actual temporalmente
                actual->setValue(siguiente->getValue());//en actual se guarda el siguiente
                siguiente->setValue(temp);//en siguiente se guarda el temporal
                hayCambio = true;
            }
            actual = actual->getNext();//guardando el siguiente en actual
        }
        //ciclando hasta que ya no haya intercambio
    } while (hayCambio);
    return listaPalabras; //devolviendo la lista ordenada alfabeticamente
}