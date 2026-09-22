#include "Estado.h"
#include "Movimiento.h"

/*Establece que el turno inicial siempre es el simbolo X no importa si es el jugador humano o la IA
quien utiliza el simbolo para la partida
*/
Estado::Estado()
{
    turno = 'X';
}

/*De manera constante obtiene los estados actuales del tablero a medida que avanza la partida*/
Tablero Estado::getTablero() const
{
    return tablero;
}
/*Devuelve el caracter del turno actual*/
char Estado::getTurno() const
{
    return turno;
}

/*Realiza los respectivos cambios de turno, para pasar de X a O y de O a X segun avance el juego*/
void Estado::cambiarTurno()
{
    if (turno == 'X')
    {
        turno = 'O';
    }
    else
    {
        turno = 'X';
    }
}

/*Aplica el movimiento si se cumplen todas las condiciones para que sea un movimiento legal
 */
bool Estado::aplicarMovimiento(const Movimiento &movimiento)
{
    /*En caso de que no sea el turno del jugador no se le permitira hacer ningun movimiento
     */
    if (movimiento.getJugador() != turno)
    {
        return false;
    }

    bool resultado = false;

    /*Dependiendo del movimiento a realizar, el turno obtiene filas y columnas origen o solo filas y columnas
    destino.*/
    if (movimiento.getTipo() == "COLOCAR")
    {
        resultado = tablero.colocarFicha(
            movimiento.getFilaDestino(),
            movimiento.getColumnaDestino(),
            turno);
    }
    else if (movimiento.getTipo() == "MOVER")
    {
        resultado = tablero.moverFicha(
            movimiento.getFilaOrigen(),
            movimiento.getColumnaOrigen(),
            movimiento.getFilaDestino(),
            movimiento.getColumnaDestino(),
            turno);
    }

    if (resultado)
    {
        cambiarTurno();
    }
    return resultado;
}
/*Establece el estado ganador tomando como base principal el simbolo que haya conseguido obtener los 3 en linea,
retornando el simbolo del ganador o vacio si ninguno ha ganado en cada turno*/
char Estado::ganador() const
{

    if (tablero.haylinea('X'))
    {
        return 'X';
    }

    if (tablero.haylinea('O'))
    {
        return 'O';
    }

    return ' ';
}

/*En caso de que el tablero termine lleno en sus 9 casillas, independientemente de si al final alguien gano o no,
se establece el estado como un estado terminal, osea la ejecución finaliza*/
bool Estado::esTerminal() const
{

    if (ganador() != ' ')
    {
        return true;
    }

    return tablero.estaLleno();
}
