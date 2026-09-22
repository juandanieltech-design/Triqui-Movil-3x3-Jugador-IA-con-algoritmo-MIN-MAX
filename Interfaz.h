#ifndef INTERFAZ_H
#define INTERFAZ_H

#include "Estado.h"
#include "Movimiento.h"

class Interfaz
{
public:
    static void mostrarEstado(const Estado &estado);

    static Movimiento pedirMovimiento(
        const Estado &estado,
        char jugador);

    static void mostrarMovimiento(
        const Movimiento &movimiento);
};

#endif