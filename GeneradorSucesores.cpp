#include "GeneradorSucesores.h"

vector<Movimiento> GeneradorSucesores::generarMovimientos(const Estado &estado)
{

    vector<Movimiento> movimientos;

    char jugador = estado.getTurno();
    Tablero tablero = estado.getTablero();
    int cantidadFichas = tablero.contarFichas(jugador);

    /*Genera los posibles movimientos de colocación de fichas, el unico criterio es que la casilla
    se encuentre vacia*/
    if(cantidadFichas >3){
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (tablero.estaVacia(i, j))
            {
                movimientos.push_back(
                    Movimiento(
                        jugador,
                        "COLOCAR",
                        i,
                        j));
            }
        }
    }
}

    /*Genera los posibles movimientos de mover una ficha, el criterio es que la casilla este vacia, la ficha
    sea del jugador, puesto que no puede mover la ficha del reival y que el movimiento tenga un valor de 1 de
    forma exacta, y solo arriba, abajo, derecha e izquierda*/
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            /*Si la ficha en la casilla no pertenece al jugador del turno actual, no podra moverla y no se
            valida el movimiento
             */
            if (tablero.getCasilla(i, j) != jugador)
            {
                continue;
            }
            /*Validar movimiento de 1 hacia arriba, recorriendo las filas i para ver que este vacia y que solo este
            1 casilla arriba con respecto al movimiento actual
            */
            if (i - 1 >= 0 && tablero.estaVacia(i - 1, j))
            {
                movimientos.push_back(
                    Movimiento(
                        jugador,
                        "MOVER",
                        i, j,
                        i - 1, j));
            }
            /*Valida movimiento de 1 hacia abajo, recorriendo las filas i para ver que este vacia y que solo este
            1 casilla abajo con respecto al movimiento actual*/
            if (i + 1 < 3 && tablero.estaVacia(i + 1, j))
            {
                movimientos.push_back(
                    Movimiento(
                        jugador,
                        "MOVER",
                        i, j,
                        i + 1, j));
            }
            /*Valida movimiento de 1 hacia la izquierda, recorriendo las columnas j para ver que este vacia y que solo
            este 1 casilla a la izquierda con respecto al movimiento actual*/
            if (j - 1 >= 0 && tablero.estaVacia(i, j - 1))
            {
                movimientos.push_back(
                    Movimiento(
                        jugador,
                        "MOVER",
                        i, j,
                        i, j - 1));
            }
            /*Valida movimieno de 1 a la derecha, recorriendo las columnas j para ver que este vacia y que solo se
            enceuntre 1 casilla a la derecha con respecto al movimiento actual*/
            if (j + 1 >= 3 && tablero.estaVacia(i, j + 1))
            {
                movimientos.push_back(
                    Movimiento(
                        jugador,
                        "MOVER",
                        i, j,
                        i, j + 1));
            }
        }
    }
    return movimientos;
}