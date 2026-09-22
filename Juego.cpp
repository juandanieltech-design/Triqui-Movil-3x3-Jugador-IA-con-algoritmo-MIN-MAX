#include "Juego.h"
#include "Interfaz.h"
#include <iostream>

using namespace std;

Juego::Juego(char jugadorHumano)
    : jugadorHumano(jugadorHumano),
      jugadorIA(jugadorHumano == 'X' ? 'O' : 'X'),
      ia(jugadorIA) {
}

void Juego::iniciar() {

    cout << "\n=== TRIQUI-MOVIL ===\n";

    while (!estado.esTerminal()) {

        Interfaz::mostrarEstado(estado);

        if (estado.getTurno() == jugadorHumano) {

            Movimiento movimiento =
                Interfaz::pedirMovimiento(
                    estado,
                    jugadorHumano
                );

            if (!estado.aplicarMovimiento(movimiento)) {

                cout << "Movimiento invalido.\n";
            }

        } else {

            cout << "La IA esta pensando...\n";

            Movimiento movimiento =
                ia.obtenerMejorMovimiento(estado);

            estado.aplicarMovimiento(movimiento);

            Interfaz::mostrarMovimiento(movimiento);
        }
    }

    Interfaz::mostrarEstado(estado);

    char ganador = estado.ganador();

    if (ganador == jugadorHumano) {
        cout << "Ganaste.\n";
    }
    else if (ganador == jugadorIA) {
        cout << "La IA gano.\n";
    }
    else {
        cout << "Empate.\n";
    }
}