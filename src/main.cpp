#include <iostream>
#include "../include/MotorDeJuego.h"
#include <cstdlib>
#include <ctime>
using namespace std;
int main() {
    srand(time(nullptr));//semilla de aleatoriedad para toda la ejecucion
    cout << "Hello world!!" << "!\n";
    MotorDeJuego motorDeJuego;
    motorDeJuego.mostrarMenu();
    return 0;
}