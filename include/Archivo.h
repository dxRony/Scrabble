//
// Created by ronyrojas on 19/02/25.
//

#ifndef ARCHIVO_H
#define ARCHIVO_H
#include <string>
#include "ListaEnlazada.h"
#include "Palabra.h"
using namespace std;

class Archivo
{
public:
    Archivo();

    ListaEnlazada<Palabra> leerCSV(const string &rutaArchivo);

    ListaEnlazada<Palabra> ordenarAlfabeticamente(ListaEnlazada<Palabra> &listaPalabras);
};

#endif //ARCHIVO_H
