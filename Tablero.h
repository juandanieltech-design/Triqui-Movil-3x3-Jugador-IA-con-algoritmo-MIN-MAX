#ifndef Tablero_h
#define Tablero_h

#include <iostream>
using namespace std;

class Tablero
{
private:
   char casillas[3][3];

public:
   Tablero();
   bool colocarFicha(int fila, int columna, char jugador);
   bool moverFicha(int filaOrigen, int columnaOrigen, int filaDestino, int columnaDestino, char jugador);
   bool estaVacia(int fila, int columna) const;
   bool haylinea(char jugador) const;
   bool estaLleno() const;

   char getCasilla(int fila, int columna) const;

   void mostrar() const;
};

#endif