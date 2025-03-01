#ifndef LETRA_H
#define LETRA_H
#include <string>
using namespace std;

class Letra {
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

    friend ostream &operator<<(ostream &os, const Letra &l);
};
#endif //LETRA_H
