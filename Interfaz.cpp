#include "Interfaz.h"
#include "GeneradorSucesores.h"
#include <iostream>

using namespace std;

void Interfaz::mostrarEstado(const Estado &estado)
{

    cout << "\nTurno: " << estado.getTurno() << "\n";

    estado.getTablero().mostrar();
}

Movimiento Interfaz::pedirMovimiento(
    const Estado &estado,
    char jugador)
{

    int tipo;

    cout << "Jugador " << jugador << "\n";
    cout << "1. Colocar ficha\n";
    cout << "2. Mover ficha\n";
    cout << "Seleccione: ";
    cin >> tipo;

    if (tipo == 1)
    {

        int fila, columna;

        cout << "Fila (1-3): ";
        cin >> fila;

        cout << "Columna (1-3): ";
        cin >> columna;

        return Movimiento(
            jugador,
            "COLOCAR",
            fila - 1,
            columna - 1);
    }
    else
    {

        int filaOrigen, columnaOrigen;
        int filaDestino, columnaDestino;

        cout << "Fila origen: ";
        cin >> filaOrigen;

        cout << "Columna origen: ";
        cin >> columnaOrigen;

        cout << "Fila destino: ";
        cin >> filaDestino;

        cout << "Columna destino: ";
        cin >> columnaDestino;

        return Movimiento(
            jugador,
            "MOVER",
            filaOrigen - 1,
            columnaOrigen - 1,
            filaDestino - 1,
            columnaDestino - 1);
    }
}

void Interfaz::mostrarMovimiento(
    const Movimiento &movimiento)
{

    cout << "La IA realizo un movimiento.\n";
}