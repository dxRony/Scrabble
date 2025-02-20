//
// Created by ronyrojas on 19/02/25.
//

#ifndef LETRA_H
#define LETRA_H

#include <string>
using namespace std;

class Letra
{
private:
    char letra;
    int punteo;

public:
    Letra();

    //getters
    char getLetra() const;
    int getPunteo() const;

    //setters
    void setLetra(char letra);
    void setPunteo(int punteo);

    // Declaración de la sobrecarga como amiga
    friend ostream& operator<<(ostream& os, const Letra& l);
};

#endif //LETRA_H
