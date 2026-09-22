#include "Movimiento.h"

using namespace std;

/*Se establece que en una primera instancia que no hay un origen valido, por eso,
para eso fila y columna origen tienen valor -1, el movimiento de colocar una ficha que no esta
previamente establecida en el tablero*/
Movimiento::Movimiento(char jugador, string tipo, int filaDestino, int columnaDestino)
{
    this->jugador = jugador;
    this->tipo = tipo;

    this->filaOrigen = -1;
    this->columnaOrigen = -1;

    /*Destino establecido*/
    this->filaDestino = filaDestino;
    this->columnaDestino = columnaDestino;
}

/*Se establece que en esta instancia ya hay al menos una ficha con un origen valido, porque funciona para
el movimiento de tomar una ficha que ya esta en alguna posición del tablero, y moverla
*/
Movimiento::Movimiento(char jugador, string tipo, int filaOrigen, int columnaOrigen,
                       int filaDestino, int columnaDestino)
{
    this->jugador = jugador;
    this->tipo = tipo;

    /*Finalmente existe una filaOrigen*/
    this->filaOrigen = filaOrigen;
    this->columnaOrigen = columnaOrigen;

    /*Destino establecido*/
    this->filaDestino = filaDestino;
    this->columnaDestino = columnaDestino;
}

/*Obtener el jugador en el momento actual de ejecutar un turno*/
char Movimiento::getJugador() const
{
    return jugador;
}

/*Obtener el tipo de movimiento a realizar en el movimiento actual*/
string Movimiento::getTipo() const
{
    return tipo;
}

/*Obtener la fila origen a utilizar*/
int Movimiento::getFilaOrigen() const
{
    return filaOrigen;
}

/*Obtener la columna origen a utilizar*/
int Movimiento::getColumnaOrigen() const
{
    return columnaOrigen;
}

/*Obtener la fila destino a utilizar*/
int Movimiento::getFilaDestino() const
{
    return filaDestino;
}

/*Obtener la columna destino a utilizar*/
int Movimiento::getColumnaDestino() const
{
    return columnaDestino;
}