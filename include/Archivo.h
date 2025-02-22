//
// Created by ronyrojas on 19/02/25.
//

#ifndef ARCHIVO_H
#define ARCHIVO_H
#include <string>
#include "ListaEnlazada.h"
#include "Palabra.h"
using namespace std;

class Archivo {
public:
    ListaEnlazada<Palabra> leerCSV(const string &rutaArchivo);

    ListaEnlazada<Palabra> ordenarAlfabeticamente();
};

#endif //ARCHIVO_H
