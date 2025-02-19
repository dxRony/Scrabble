//
// Created by ronyrojas on 19/02/25.
//

#ifndef PALABRA_H
#define PALABRA_H

#include <string>
using namespace std;

class Palabra
{
private:
    string contenido;
    int puntuacion;
    bool palabraFormada;

public:
    Palabra();

    // getters
    string getContenido() const;
    int getPuntuacion() const;
    bool isPalabraFormada() const;

    // setters
    void setContenido(string contenido);
    void setPuntuacion(int puntuacion);
    void setPalabraFormada(bool palabraFormada);

    friend ostream& operator<<(ostream& os, const Palabra& palabra);
};

#endif //PALABRA_H
