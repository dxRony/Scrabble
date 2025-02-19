//
// Created by ronyrojas on 19/02/25.
//

#ifndef LETRA_H
#define LETRA_H

#include <string>

class Letra
{
private:
    string letra;
    int punteo;

public:
    Letra();

    //getters
    string getLetra() const;
    int getPunteo() const;

    //setters
    void setLetra(string letra);
    void setPunteo(int punteo);
};

#endif //LETRA_H
