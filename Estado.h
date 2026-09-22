#ifndef ESTADO_H
#define ESTADO_H

#include "Tablero.h"

class Movimiento;

class Estado
{
private:
    Tablero tablero;
    char turno;

public:
    Estado();

    Tablero getTablero() const;
    char getTurno() const;

    void cambiarTurno();

    bool aplicarMovimiento(const Movimiento& movimiento);

    bool esTerminal() const;
    char ganador() const;
};

#endif