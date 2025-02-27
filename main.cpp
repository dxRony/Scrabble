#include <iostream>
#include "include/MotorDeJuego.h"
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()

int main() {
    srand(time(nullptr));
    std::cout << "Hello world!!" << "!\n";
    MotorDeJuego motorDeJuego;
    motorDeJuego.mostrarMenu();
    return 0;
}