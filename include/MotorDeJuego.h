#ifndef MOTORDEJUEGO_H
#define MOTORDEJUEGO_H
#include "Reporte.h"

class MotorDeJuego {
public:
    MotorDeJuego();

    void mostrarMenu();

private:
    void nuevaPartida();

    void verReportes();

    bool finalizarEjecucion = false;

    Reporte reporte;
};
#endif //MOTORDEJUEGO_H
