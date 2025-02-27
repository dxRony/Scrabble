//
// Created by ronyrojas on 26/02/25.
//

#ifndef MOTORDEJUEGO_H
#define MOTORDEJUEGO_H

class MotorDeJuego {
public:
    MotorDeJuego();

    void mostrarMenu();

private:
    void nuevaPartida();

    void verReportes();

    bool finalizarEjecucion = false;
};
#endif //MOTORDEJUEGO_H
