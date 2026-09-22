# Triqui-Móvil

Implementación en **C++** del juego **Triqui-Móvil** utilizando programación orientada a objetos (POO) y un algoritmo **Minimax** con profundidad de búsqueda 2.

El proyecto modela el tablero, los estados del juego y los movimientos posibles, permitiendo jugar contra una IA que analiza los movimientos disponibles mediante una función heurística.

## Descripción

Triqui-Móvil es una variante del juego de tres en línea en la que los jugadores pueden:

* Colocar una ficha en una casilla vacía.
* Mover una ficha propia una casilla en dirección horizontal o vertical.
* No se permiten movimientos diagonales.
* No se pueden ocupar casillas que ya contengan una ficha.
* El objetivo es conseguir tres fichas propias en línea.

El programa permite seleccionar si el jugador humano utiliza `X` u `O`. La IA utiliza automáticamente el símbolo contrario.

## Tecnologías

* **C++**
* **Programación Orientada a Objetos**
* **Algoritmo Minimax**
* **Búsqueda con profundidad 2**
* **Evaluación heurística**
* **STL (`vector`)**
* Compilador compatible con C++ estándar

## Estructura del proyecto

```text
Triqui_Movil/
│
├── main.cpp
│
├── Tablero.h
├── Tablero.cpp
│
├── Estado.h
├── Estado.cpp
│
├── Movimiento.h
├── Movimiento.cpp
│
├── GeneradorSucesores.h
├── GeneradorSucesores.cpp
│
├── Evaluador.h
├── Evaluador.cpp
│
├── MinMax.h
├── MinMax.cpp
│
├── Interfaz.h
├── Interfaz.cpp
│
├── Juego.h
└── Juego.cpp
```

## Arquitectura

El programa se divide en varias clases, cada una con una responsabilidad específica.

### `Tablero`

Representa físicamente el tablero de 3×3 mediante:

```cpp
char casillas[3][3];
```

Sus principales responsabilidades son:

* Inicializar el tablero vacío.
* Colocar fichas.
* Mover fichas.
* Comprobar si una casilla está vacía.
* Comprobar si existe una línea de tres.
* Comprobar si el tablero está lleno.
* Mostrar el tablero.

La validación del movimiento de una ficha utiliza la **distancia de Manhattan**:

```text
|filaOrigen - filaDestino| + |columnaOrigen - columnaDestino| = 1
```

Esto garantiza que una ficha únicamente pueda desplazarse una posición hacia arriba, abajo, izquierda o derecha.

---

### `Estado`

Representa el estado actual de la partida mediante:

```text
Estado = (Tablero, Turno)
```

La clase almacena:

* El tablero actual.
* El jugador que tiene el turno.

Sus responsabilidades principales son:

* Obtener el tablero.
* Obtener el turno.
* Cambiar el turno.
* Aplicar movimientos válidos.
* Determinar si existe un ganador.
* Determinar si el estado es terminal.

Un estado es terminal cuando:

1. `X` consigue tres en línea.
2. `O` consigue tres en línea.
3. El tablero se encuentra lleno.

---

### `Movimiento`

Representa una acción realizada por uno de los jugadores.

Existen dos tipos:

```text
COLOCAR
MOVER
```

Para colocar una ficha solamente se necesita una posición destino.

Para mover una ficha se almacenan:

```text
Fila origen
Columna origen
Fila destino
Columna destino
```

La posición de origen de una colocación se representa internamente con `-1`.

---

### `GeneradorSucesores`

Genera todos los movimientos legales disponibles en un estado.

Para cada estado se consideran:

#### Colocación

Se genera un movimiento por cada casilla vacía.

#### Movimiento

Se revisan las fichas pertenecientes al jugador actual y se comprueban sus posibles desplazamientos:

```text
↑ Arriba
↓ Abajo
← Izquierda
→ Derecha
```

Cada movimiento generado se almacena en un:

```cpp
vector<Movimiento>
```

Estos movimientos son posteriormente utilizados por Minimax para explorar los estados sucesores.

---

### `Evaluador`

Calcula qué tan favorable es un estado para la IA.

La evaluación siempre se realiza desde la perspectiva del jugador controlado por la IA.

## Función heurística

La función heurística utiliza las **8 posibles líneas de victoria**:

```text
3 filas
3 columnas
2 diagonales
```

Para cada línea se cuentan:

* Fichas de la IA.
* Fichas del oponente.
* Casillas vacías.

Los valores objetivos utilizados son:

| Situación en una línea              |  Valor |
| ----------------------------------- | -----: |
| Victoria de la IA                   | `+100` |
| Victoria del oponente               | `-100` |
| 2 fichas IA + 1 vacía               |  `+10` |
| 1 ficha IA + 2 vacías               |   `+1` |
| 2 fichas oponente + 1 vacía         |  `-10` |
| 1 ficha oponente + 2 vacías         |   `-1` |
| Línea vacía                         |    `0` |
| Línea con fichas de ambos jugadores |    `0` |

La función puede expresarse conceptualmente como:

```text
H(S) = suma de los valores de las 8 líneas
```

Por ejemplo, si una línea contiene:

```text
X | X |  
```

y `X` es la IA:

```text
+10
```

Si la línea contiene:

```text
O | O |  
```

y `O` es el oponente:

```text
-10
```

La victoria tiene prioridad sobre la evaluación de líneas individuales:

```cpp
if (estado.ganador() == jugadorIA)
    return 100;

if (estado.ganador() == oponente)
    return -100;
```

De esta manera, una victoria siempre es considerada mucho más favorable que cualquier ventaja parcial.

---

## Minimax

La IA utiliza el algoritmo **Minimax** para seleccionar sus movimientos.

La búsqueda utiliza una profundidad de:

```text
2
```

El proceso general es:

```text
Estado actual
      │
      ▼
Movimientos posibles de la IA
      │
      ▼
Estado sucesor
      │
      ▼
Movimientos posibles del oponente
      │
      ▼
Estado sucesor
      │
      ▼
Evaluación heurística
```

La IA busca maximizar el valor obtenido:

```text
MAX → IA
```

Mientras que durante la simulación del oponente se busca minimizarlo:

```text
MIN → Oponente
```

La IA selecciona el movimiento cuyo estado posterior produzca el mayor valor esperado después de considerar la respuesta del oponente.

Los valores se inicializan utilizando:

```cpp
numeric_limits<int>::min()
```

para MAX y:

```cpp
numeric_limits<int>::max()
```

para MIN.

Esto permite comparar correctamente todos los movimientos disponibles.

---

## Flujo de una jugada

Una jugada sigue aproximadamente este proceso:

```text
1. Se obtiene el Estado actual
              ↓
2. Se determina el jugador del turno
              ↓
3. GeneradorSucesores crea movimientos legales
              ↓
4. Minimax simula los movimientos
              ↓
5. Evaluador calcula el valor de cada estado
              ↓
6. Minimax selecciona el mejor movimiento
              ↓
7. Estado aplica el movimiento
              ↓
8. Se cambia el turno
              ↓
9. Se muestra el nuevo tablero
```

---

## Interfaz

La clase `Interfaz` se encarga de la interacción con el usuario.

Permite:

* Mostrar el tablero.
* Mostrar el jugador actual.
* Seleccionar entre colocar o mover una ficha.
* Introducir las coordenadas.
* Informar cuando la IA realiza un movimiento.

Las coordenadas introducidas por el usuario utilizan valores de `1` a `3`, mientras que internamente C++ utiliza índices de `0` a `2`.

Por ejemplo:

```text
Usuario: fila 3, columna 2

Internamente:

fila = 3 - 1 = 2
columna = 2 - 1 = 1
```

---

## Flujo general del programa

El programa comienza solicitando al usuario su ficha:

```text
Elige tu ficha (X/O):
```

Si el usuario selecciona:

```text
X
```

la IA utiliza:

```text
O
```

Si el usuario selecciona:

```text
O
```

la IA utiliza:

```text
X
```

El juego comienza con el turno de `X`, independientemente de si `X` pertenece al jugador humano o a la IA.

La partida continúa hasta alcanzar un estado terminal.

Al finalizar se informa:

```text
Ganaste.
```

o:

```text
La IA gano.
```

o:

```text
Empate.
```

## Compilación

Desde la carpeta del proyecto:

```bash
g++ *.cpp -o triqui_movil
```

Después:

```bash
./triqui_movil
```

## Ejemplo de ejecución

```text
Elige tu ficha (X/O): O

=== TRIQUI-MOVIL ===

Turno: X

   |   |
---+---+---
   |   |
---+---+---
   |   |

La IA esta pensando...
La IA realizo un movimiento.

Turno: O

 X |   |
---+---+---
   |   |
---+---+---
   |   |

Jugador O
1. Colocar ficha
2. Mover ficha
Seleccione:
```

## Objetivos del proyecto

El proyecto tiene como objetivo aplicar conceptos de:

* Programación Orientada a Objetos.
* Representación de estados.
* Generación de sucesores.
* Validación de movimientos.
* Búsqueda en espacios de estados.
* Algoritmos de decisión para juegos.
* Funciones heurísticas.
* Algoritmo Minimax.
* Separación de responsabilidades entre clases.

## Conceptos de ingeniería aplicados

El diseño busca separar las diferentes responsabilidades del sistema:

```text
Tablero
  └── Representación física

Estado
  └── Situación actual de la partida

Movimiento
  └── Acción posible

GeneradorSucesores
  └── Movimientos legales

Evaluador
  └── Valoración del estado

MinMax
  └── Toma de decisiones de la IA

Interfaz
  └── Interacción con el usuario

Juego
  └── Control del flujo de la partida
```

Esta separación permite modificar componentes individuales sin concentrar toda la lógica del juego en una única clase.

## Autor

**Juan Daniel Vargas Pedraza**

Proyecto académico desarrollado en C++ como aplicación de conceptos de programación orientada a objetos, representación de estados, búsqueda y toma de decisiones mediante Minimax.
