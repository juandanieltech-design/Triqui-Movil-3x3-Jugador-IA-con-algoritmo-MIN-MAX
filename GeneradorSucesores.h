#ifndef GENERADORSUCESORES_H
#define GENERADORSUCESORES_H

#include <vector>
#include "Movimiento.h"
#include "Estado.h"

using namespace std;

class GeneradorSucesores
{
public:
    static vector<Movimiento> generarMovimientos(const Estado &estado);
};
#endif
