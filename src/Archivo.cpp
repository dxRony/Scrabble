//
// Created by ronyrojas on 26/02/25.
//

#include "../include/Archivo.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>

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
    ListaEnlazada<Palabra> *listaPalabras = this->leerCSV("../util/palabras.csv");
    if (!listaPalabras || listaPalabras->isEmpty()) {
        return listaPalabras;
    }
    bool intercambio;
    do {
        intercambio = false;
        Nodo<Palabra> *actual = listaPalabras->getCabeza();
        while (actual != nullptr && actual->getNext() != nullptr) {
            Nodo<Palabra> *siguiente = actual->getNext();
            if (actual->getValue().getContenido() > siguiente->getValue().getContenido()) {
                // En lugar de: swap(actual->getValue(), siguiente->getValue());
                Palabra temp = actual->getValue();
                actual->setValue(siguiente->getValue());
                siguiente->setValue(temp);
                intercambio = true;
            }
            actual = actual->getNext();
        }
    } while (intercambio);
    return listaPalabras; //devolviendo la lista ordenada
}