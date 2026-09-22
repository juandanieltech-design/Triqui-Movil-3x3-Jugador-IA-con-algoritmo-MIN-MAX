#include "MinMax.h"
#include "GeneradorSucesores.h"
#include "Evaluador.h"
#include <limits>

/*Se establece quien es el jugadorIA y quien es el oponente humano, lo que debemos entender es que
si el jugadorIA es X el oponente humano es O, en caso contrario oponente humano sería X*/
MinMax::MinMax(char jugadorIA)
{
    this->jugadorIA = jugadorIA;

    if (jugadorIA == 'X')
    {
        oponente = 'O';
    }
    else
    {
        oponente = 'X';
    }
}

int MinMax::minimax(const Estado &estado, int profundidad, bool maximizando)
{
    /*Exploramos estados en cada nivel hasta que se acaban los niveles por explorar o se determina que la
    partida ha finalizado, de ahi fnialmente evaluamos el puntaje que determina la ventaja que posee la IA
    o el jugador humano*/
    if (profundidad == 0 || estado.esTerminal())
    {
        return Evaluador::evaluar(estado, jugadorIA);
    }

    /*A partir del estado en el que nos encontramos buscamos todos los movimientos legales que puede realizar
    el jugadorIA desde aqui*/
    vector<Movimiento> movimientos = GeneradorSucesores::generarMovimientos(estado);

    /*movimiento MAX, el jugadorIA va a probar todos los movimientos posibles y escogera cual le produce el resultado
    más alto*/
    if (maximizando)
    {
        /*El mejor valor se declara en numeric limits para tomar el valor más pequeño posible en un atributo entero,
        con el objetivo que lo primero que obtengamos sea por fuerza mejor que el inicial*/
        int mejorValor = numeric_limits<int>::min();

        /*Debemos recorrer cada uno de los movimientos posibles*/
        for (const Movimiento &movimiento : movimientos)
        {
            /*realizamos una copia o respaldo del estado actual para impedir modificar el original y que eso condicione
            la partida*/
            Estado sucesor = estado;
            sucesor.aplicarMovimiento(movimiento);

            /*identificamos que podria pasar si el oponente decide responder a nuestro movimiento*/
            int valor = minimax(
                sucesor,
                profundidad - 1,
                false);

            /*en caso de el valor actual ser mejor que mejor valor registrado ese valor se convierte en el mejor
            valor*/
            if (valor > mejorValor)
            {
                mejorValor = valor;
            }
        }
        return mejorValor;
    }
    /*Entramos al movimiento MIN, porque aca dejamos de simular a la IA y comenzamos a simular al oponente*/
    else
    {
        /*aca es el mejor valor posible, pero aca es el mayor valor posible en una variable entera, ya que para
        el jugador humano oponente la IA quiere buscar los valores más bajos, que para ella representa los peores
        escenarios posibles*/
        int mejorValor = numeric_limits<int>::max();
        for (const Movimiento &movimiento : movimientos)
        {
            Estado sucesor = estado;
            sucesor.aplicarMovimiento(movimiento);

            int valor = minimax(
                sucesor,
                profundidad - 1,
                true);
            if (valor < mejorValor)
            {
                mejorValor = valor;
            }
        }
        return mejorValor;
    }
}

Movimiento MinMax::obtenerMejorMovimiento(const Estado &estado)
{
    /*Obtenemos todos los movimientos legales que puede realizar la IA desde el estado actual,
    ya que debemos analizar cada una de las opciones disponibles para determinar cual es la mejor*/
    vector<Movimiento> movimientos = GeneradorSucesores::generarMovimientos(estado);

    /*Tomamos el primer movimiento como el mejor movimiento inicialmente, aunque este puede cambiar
    posteriormente cuando comparemos el valor de todos los movimientos disponibles*/
    Movimiento mejorMovimiento = movimientos[0];

    /*Inicializamos el mejor valor con el número entero más pequeño posible para garantizar que
    cualquier valor obtenido de un movimiento sea inicialmente mejor que este*/
    int mejorValor = numeric_limits<int>::min();

    /*Recorremos todos los movimientos posibles para analizar que tan favorable resulta cada uno
    para la IA*/
    for (const Movimiento &movimiento : movimientos)
    {
        /*Creamos una copia del estado actual para aplicar el movimiento que estamos analizando
        sin modificar el estado original de la partida*/
        Estado sucesor = estado;
        sucesor.aplicarMovimiento(movimiento);

        /*Simulamos lo que ocurriria despues de que la IA realiza este movimiento, pasando el turno
        al oponente y disminuyendo la profundidad de exploracion*/
        int valor = minimax(
            sucesor,
            1,
            false);

        /*Si el valor obtenido es mayor que el mejor valor registrado hasta el momento, este
        movimiento pasa a ser la mejor opcion encontrada para la IA*/
        if (valor > mejorValor)
        {
            mejorValor = valor;
            mejorMovimiento = movimiento;
        }
    }

    /*Finalmente devolvemos el movimiento que produjo el mejor valor para la IA*/
    return mejorMovimiento;
}
