#ifndef JUEGO_H
#define JUEGO_H

#include "Estado.h"
#include "MinMax.h"

class Juego {
private:
    Estado estado;
    char jugadorHumano;
    char jugadorIA;
    MinMax ia;

public:
    Juego(char jugadorHumano);

    void iniciar();
};

#endif