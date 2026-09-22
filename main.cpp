#include "Juego.h"
#include <iostream>

using namespace std;

int main() {

    char jugador;

    cout << "Elige tu ficha (X/O): ";
    cin >> jugador;

    while (jugador != 'X' && jugador != 'O') {
        cout << "Seleccion invalida. Elige X u O: ";
        cin >> jugador;
    }

    Juego juego(jugador);

    juego.iniciar();

    return 0;
}