#include <iostream>
#include "../include/MotorDeJuego.h"
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()
using namespace std;
int main() {
    srand(time(nullptr));//semilla de aleatoriedad para toda la ejecucion
    cout << "Hello world!!" << "!\n";
    MotorDeJuego motorDeJuego;
    motorDeJuego.mostrarMenu();
    return 0;
}