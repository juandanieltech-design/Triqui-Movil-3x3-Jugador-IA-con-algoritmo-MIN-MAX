#ifndef EVALUADOR_H
#define EVALUADOR_H

#include "Estado.h"

class Evaluador
{
public:
    static int evaluar(const Estado &estado, char jugadorIA);
};

#endif