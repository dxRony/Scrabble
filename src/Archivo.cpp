//
// Created by ronyrojas on 19/02/25.
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
    Nodo<Palabra> *actual = listaPalabras->getRaiz(); //obteniendo la cabeza de la lista
    while (actual != nullptr) {
        // minetras el nodo actual exista
        Nodo<Palabra> *siguiente = actual->getNext(); //obteniendo el nodo siguiente de la lista
        while (siguiente != nullptr) {
            //si el nodo siguiente existe
            if (actual->getValue().getContenido() > siguiente->getValue().getContenido()) {
                //comparando el contenido para determinar si es mayor
                swap(actual->getValue(), siguiente->getValue());
            }
            siguiente = siguiente->getNext(); //yendo al siguiente nodo (siguiente del siguiente)
        }
        actual = actual->getNext(); //el actual nodo se convierte en el siguiente del actual
    }
    return listaPalabras; //devolviendo la lista ordenada
}
