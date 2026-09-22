#ifndef MOVIMIENTO_H
#define MOVIMIENTO_H

#include <string>
using namespace std;

class Movimiento{
    private:
    char jugador;
    string tipo;

    int filaOrigen;
    int columnaOrigen;

    int filaDestino;
    int columnaDestino;

    public:
    Movimiento(char jugador, string tipo, int filaDestino, int columnaDestino);

    Movimiento(char jugador, string tipo, int filaOrigen, int columnaOrigen, int filaDestino, int ColumnaDestino);

    char getJugador() const;
    string getTipo() const;

    int getFilaOrigen() const;
    int getColumnaOrigen()const;

    int getFilaDestino()const;
    int getColumnaDestino()const;
};
#endif
