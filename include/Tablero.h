//
// Created by ronyrojas on 19/02/25.
//

#ifndef TABLERO_H
#define TABLERO_H

class Tablero {
private:
    int filas;
    int columnas;
    bool espacioActivo;

public:
    Tablero();

    //getters
    int getFilas() const;

    int getColumnas() const;

    bool getEspacioActivo() const;

    //setters
    void setFilas(int filas);

    void setColummnas(int columnas);

    void setEspacioActivo(bool activar);
};

#endif //TABLERO_H
