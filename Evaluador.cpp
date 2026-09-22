#include "Evaluador.h"

int Evaluador::evaluar(const Estado &estado, char jugadorIA)
{

    char oponente;
    /*La IA define quien es su rival, si X u O
     */
    if (jugadorIA == 'X')
    {
        oponente = 'O';
    }
    else
    {
        oponente = 'X';
    }
    /*En nuestra heuristica entre mayor el valor de forma positiva es más favorable para el jugador IA
    en este caso si el puntaje es 100 indica que el jugadorIA ha ganado la partida
    */
    if (estado.ganador() == jugadorIA)
    {
        return 100;
    }
    /*En nuestra heuristica entre mayor sea el valor de forma negativa es más favorable para el oponente humano,
    en este caso si es el puntaje es -100 indica que el oponente humano ha ganado la partida*/
    if (estado.ganador() == oponente)
    {
        return -100;
    }

    Tablero tablero = estado.getTablero();

    int valor = 0;
    /*Estas son las posibles combinaciones de 3 casillas que permiten que cualquiera de los dos jugadores consiga
    la victoria*/
    int lineas[8][3] = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
        {0, 3, 6},
        {1, 4, 7},
        {2, 5, 8},
        {0, 4, 8},
        {2, 4, 6}};

    /*Vamos a recorrer las 8 posibles lineas con tal de determinar la cantidad de casillas vacias, ocupadas por
    el jugador IA o el oponente humano*/
    for (int i = 0; i < 8; i++)
    {
        int cantidadIA = 0;
        int cantidadOponente = 0;
        int vacias = 0;
        /*Dentro de las 8 posibles lineas vamos a explorar como es logico explorar las 3 posiciones de cada linea,
        eso si gracias a dividir entre 3 y modular entre 3 permite convertir la posicion a filas y columnas*/
        for (int j = 0; j < 3; j++)
        {
            int posicion = lineas[i][j];
            int fila = posicion / 3;
            int columna = posicion % 3;
            /*Obtener la casilla dentro del tablero gracias a la fila y columna dentro de la posición correspondiente*/
            char casilla = tablero.getCasilla(fila, columna);

            if (casilla == jugadorIA)
            {
                cantidadIA++;
            }
            else if (casilla == oponente)
            {
                cantidadOponente++;
            }
            else
            {
                vacias++;
            }
        }
        /*Si en alguna de las 8 lineas posibles, tenemos 2 casillas ocupadas por el jugadorIA y 1 vacia se suman 10 puntos,
        como se propuso en la heuristica de forma previa antes de comenzar a codificar*/
        if (cantidadIA == 2 && vacias == 1)
        {
            valor += 10;
        }
        else if (cantidadIA == 1 && vacias == 2)
        {
            valor += 1;
        }
        else if (cantidadOponente == 2 && vacias == 1)
        {
            valor -= 10;
        }
        else if (cantidadOponente == 1 && vacias == 2)
        {
            valor -= 1;
        }
    }
    return valor;
}
