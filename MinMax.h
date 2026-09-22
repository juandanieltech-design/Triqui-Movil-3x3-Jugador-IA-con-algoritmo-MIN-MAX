#ifndef MINMAX_H
#define MINMAX_H

#include "Estado.h"
#include "Movimiento.h"

class MinMax{
    private:
    char jugadorIA;
    char oponente;

    int minimax(const Estado& estado, int profundidad, bool maximizando);

    public:
    MinMax(char jugadorIA);
    Movimiento obtenerMejorMovimiento(const Estado& estado);
};
#endif