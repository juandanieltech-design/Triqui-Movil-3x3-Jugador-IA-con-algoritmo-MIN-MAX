#include <iostream>
#include <cmath>
#include "Tablero.h"

/*El tablero siempre comienza la partida encontrandose vacio sin ningun elemento x u o
presentes en sus casillas
*/
Tablero::Tablero()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            casillas[i][j] = ' ';
        }
    }
}

/*En caso de que la casilla este vacia en efecto devuelve esa posición vacia
 */
bool Tablero::estaVacia(int fila, int columna) const
{
    return casillas[fila][columna] == ' ';
}

/*Condiciones en las cuales el tablero puede concretar la acción de colocar la ficha
 */
bool Tablero::colocarFicha(int fila, int columna, char jugador)
{

    /*Solo es posible poner la ficha en una posición que abarca una matriz 3x3,
    posición 0,1,2 para filas y columnas, siendo cualquier otra posición mayor o menor al limite como invalida
    */
    if (fila < 0 || fila >= 3 || columna < 0 || columna >= 3)
    {
        return false;
    }

    /*Si la casilla no esta vacia y contiene algun elemento de jugador o IA en su interior no permite colocar un
    elemento en su interior
    */
    if (!estaVacia(fila, columna))
    {
        return false;
    }

    /*Si ya hay 3 fichas en algun simbolo no se puede colocar otra ficha más*/
    if (contarFichas(jugador) >= 3)
{
    return false;
}
    /*En cualquier otra condición es valido colocar la ficha, po(r lo que retornamos un valor verdadero y se coloca
    la ficha en la casilla correspondiente ejemplo: Colocar x en (0,2), Colocar o en (1,0)
    */
    casillas[fila][columna] = jugador;
    return true;
}

/*Condiciones en las que es valido mover una ficha
 */
bool Tablero::moverFicha(int filaOrigen, int columnaOrigen, int filaDestino, int columnaDestino, char jugador)
{
    /*Si tanto la casilla origen como la casilla destino indica tanto en fila o columna una posición que no abarca
    0,1,2 cumpliendo con las casillas de la matriz 3x3 se invalida
    */
    if (filaOrigen < 0 || filaDestino < 0 || filaOrigen >= 3 || filaDestino >= 3 || columnaOrigen < 0 ||
        columnaDestino < 0 || columnaOrigen >= 3 || columnaDestino >= 3)
    {
        return false;
    }
    /* Si la casilla que se pretende mover no es la equivalente a la del jugador que se encuentra jugando el turno
    correspondiente entonces no la podra mover, no puede mover la casilla del rival
    */
    if (casillas[filaOrigen][columnaOrigen] != jugador)
    {
        return false;
    }
    /*Si la casilla destino donde se pretende colocar la ficha a mover ya esta ocupada, entonces no la podrá
    mover, no se puede invadir casillas ajenas
    */
    if (!estaVacia(filaDestino, columnaDestino))
    {
        return false;
    }

    /*Calculo de distancia de manhattan, la suma entre el valor absoluto de la resta de fila origen y fila destino
    y el valor absoluto de la columna origen y la columna destino
    */
    int distancia = abs(filaOrigen - filaDestino) + abs(columnaOrigen - columnaDestino);

    /*Cualquier ficha de cualquiera de los dos jugadores unicamente se puede mover una unidad hacia adelante,
    de lo contrario no puede llevar a cabo la acción de moverse
    */
    if (distancia != 1)
    {
        return false;
    }

    /*Si ninguna de estas restricciones se cumple, entonces el jugador puede mover la ficha sin problema
     */

    casillas[filaOrigen][columnaOrigen] = ' ';
    casillas[filaDestino][columnaDestino] = jugador;

    return true;
}

/*Esta función se encarga de determinar si hay una linea de 3 con alguno de los dos simbolos x u o,
de esta forma determinando  un ganador, heuristica con las reglas del juego triqui movil
*/
bool Tablero::haylinea(char jugador) const
{
    /*Si horizontalmente se cumple que el mismo simbolo esta en linea 3 veces gana
     */
    for (int i = 0; i < 3; i++)
    {
        if (casillas[i][0] == jugador &&
            casillas[i][1] == jugador &&
            casillas[i][2] == jugador)
        {
            return true;
        }
    }

    /*Si verticalmente se cumple que el mismo simbolo esta en linea 3 veces gana
     */
    for (int j = 0; j < 3; j++)
    {
        if (casillas[0][j] == jugador &&
            casillas[1][j] == jugador &&
            casillas[2][j] == jugador)
            return true;
    }

    /*Si se cumple el 3 en linea en la diagonal (0,0), (1,1), (2,2) gana
     */
    if (casillas[0][0] == jugador &&
        casillas[1][1] == jugador &&
        casillas[2][2] == jugador)
    {
        return true;
    }

    /*Si se cumple el 3 en linea en la diagonal (0,2), (1,1), (2,0) gana
     */
    if (casillas[0][2] == jugador &&
        casillas[1][1] == jugador &&
        casillas[2][0] == jugador)
    {
        return true;
    }
    return false;
}
/*Cada simbolo tiene un maximo de 3 fichas
*/
int Tablero::contarFichas(char jugador) const
{
    int contador = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (casillas[i][j] == jugador)
            {
                contador++;
            }
        }
    }

    return contador;
}

/*Recorre toda la matriz para revisar si esta llena, si una sola casilla esta vacia retornara true
 */
bool Tablero::estaLleno() const
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (casillas[i][j] == ' ')
            {
                return false;
            }
        }
    }
    return true;
}

/*Devuelve una posición especifica del tablero, osea una de las casillas
función getter
*/
char Tablero::getCasilla(int fila, int columna) const
{
    return casillas[fila][columna];
}

/*Visualización del tablero y cada una de sus posiciones
 */
void Tablero::mostrar() const
{
    /*Primera fila del tablero
     */
    cout << "\n"
         << " " << casillas[0][0] << " | "
         << casillas[0][1] << " | "
         << casillas[0][2] << "\n";

    cout << "---+---+---\n";

    /*Segunda fila del tablero
     */
    cout << " " << casillas[1][0] << " | "
         << casillas[1][1] << " | "
         << casillas[1][2] << "\n";

    cout << "---+---+---\n";

    /*Tercera fila del tablero
     */
    cout << " " << casillas[2][0] << " | "
         << casillas[2][1] << " | "
         << casillas[2][2] << "\n\n";
}