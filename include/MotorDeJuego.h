#ifndef MOTORDEJUEGO_H
#define MOTORDEJUEGO_H

//#include "Partida.h"
//#include "Reporte.h"
#include <iostream>

class MotorDeJuego
{
public:
    MotorDeJuego();
    void mostrarMenu();

private:
    void nuevaPartida();
    void verReportes();
    bool finalizarEjecucion = false;
};

#endif //MOTORDEJUEGO_H
