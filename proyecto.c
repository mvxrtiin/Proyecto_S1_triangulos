/*
* ------------------------------------------------ *
*   Autores: Iván Maldonado, Martin Rojas
*   Fecha: 25.10.2025
*   Tema: Juego de triangulos con backstracking
* ------------------------------------------------ *
*/

/* -- Bibliotecas -- */
#include <stdio.h>
#include <string.h>

/* -- Constantes globales -- */
#define MAX_TRIANGULOS      (6)
#define PUNTUACION_INVALIDA (-1)
#define LADO_EXT    (0) // Representa el vertice exterior del triángulo
#define LADO_IZQ    (1) // Representa el vertice izquierdo del triángulo
#define LADO_DER    (2) // Representa el vertice derecho del triángulo

typedef struct triangulo {
    int lado[3];
} TRIANGULO;

/* -- Prototipos de funciones -- */
int leer_set(TRIANGULO [MAX_TRIANGULOS]);
void buscar_puntuacion_alta(int, TRIANGULO [MAX_TRIANGULOS], TRIANGULO [MAX_TRIANGULOS], int [MAX_TRIANGULOS], int *);
TRIANGULO rotar_triangulo(TRIANGULO, int);

/* -- Main -- */
int main() {
    TRIANGULO triangulos[MAX_TRIANGULOS], hexagono[MAX_TRIANGULOS];
    int puntuacion_total, triangulos_usados[MAX_TRIANGULOS];
    char separador[2];
    // Durante la ejecucion
    while (1) {
        // Lectura de sets de triangulos
        if (leer_set(triangulos) != 1) {
            break;
        }
        
        // Inicialización de variables
        puntuacion_total = PUNTUACION_INVALIDA;
        
        memset(triangulos_usados, 0, sizeof (triangulos_usados));
        
        // Backstracking
        buscar_puntuacion_alta(0, triangulos, hexagono, triangulos_usados, &puntuacion_total);
        
        // Resultados del backstracking
        if (puntuacion_total == -1) {
            printf("None\n");
        } else {
            printf("%d\n", puntuacion_total);
        }

        // Comprueba que exista un separador de sets 
        if (scanf("%s", separador) != 1) {
            break;
        }
        // Si el separador es $, se finaliza el programa
        if (separador[0] == '$') {
            break;
        }
    }
    return 0;
}

/* -- Funciones -- */
int leer_set(TRIANGULO triangulos[MAX_TRIANGULOS]) {
    int i, exito = 1;
    for (i = 0; i < MAX_TRIANGULOS; i++) {
        if (scanf("%d %d %d", &triangulos[i].lado[0], &triangulos[i].lado[1], &triangulos[i].lado[2]) != 3) {
            exito = 0;
            break;
        }
    }
    return exito;
}


TRIANGULO rotar_triangulo(TRIANGULO triangulo, int rotacion) {
    TRIANGULO triangulo_rotado;
    if (rotacion == 0) {
        triangulo_rotado.lado[LADO_EXT] = triangulo.lado[LADO_EXT];
        triangulo_rotado.lado[LADO_IZQ] = triangulo.lado[LADO_IZQ];
        triangulo_rotado.lado[LADO_DER] = triangulo.lado[LADO_DER];
    } else {
        if (rotacion == 1) {
            triangulo_rotado.lado[LADO_EXT] = triangulo.lado[LADO_IZQ];
            triangulo_rotado.lado[LADO_IZQ] = triangulo.lado[LADO_DER];
            triangulo_rotado.lado[LADO_DER] = triangulo.lado[LADO_EXT];
        } else {
            triangulo_rotado.lado[LADO_EXT] = triangulo.lado[LADO_DER];
            triangulo_rotado.lado[LADO_IZQ] = triangulo.lado[LADO_EXT];
            triangulo_rotado.lado[LADO_DER] = triangulo.lado[LADO_IZQ];
        }
    }
    return triangulo_rotado;
}

void buscar_puntuacion_alta(int pos_hexagono, TRIANGULO triangulos[MAX_TRIANGULOS], TRIANGULO hexagono[MAX_TRIANGULOS], int triangulos_usados[MAX_TRIANGULOS], int * puntuacion) {
    int i;
    // Evalua el ultimo triangulo en el hexagono
    if (pos_hexagono == 6) {
        if (hexagono[5].lado[LADO_DER] == hexagono[0].lado[LADO_IZQ]) {
            int aux_puntuacion = 0;
            // Se suman los lados exteriores de los triangulos
            for (i = 0; i < MAX_TRIANGULOS; i++) {
                aux_puntuacion += hexagono[i].lado[LADO_EXT];
            }
            // Si la suma de lados > la puntuacion acumulada, actualiza la puntuacion acumulada
            if (aux_puntuacion > *puntuacion) {
                *puntuacion = aux_puntuacion;
            }
        }
        return;
    }

    for (i = 0; i < MAX_TRIANGULOS; i++) {
        if (triangulos_usados[i] == 0) {
            for (int r = 0; r < 3; r++) {
                TRIANGULO triangulo_rotado = rotar_triangulo(triangulos[i], r);
                int es_valido = 1;
                
                if (pos_hexagono > 0) {
                    // Verifica si el valor de los vertices comunes entre dos triangulos son iguales
                    if (triangulo_rotado.lado[LADO_IZQ] != hexagono[pos_hexagono - 1].lado[LADO_DER]) {
                        es_valido = 0;
                    }
                }
                if (es_valido) {
                    hexagono[pos_hexagono] = triangulo_rotado;
                    
                    // Registra el triangulo i como usado
                    triangulos_usados[i] = 1;
                    
                    buscar_puntuacion_alta(pos_hexagono + 1, triangulos, hexagono, triangulos_usados, puntuacion);
                    triangulos_usados[i] = 0;
                }
            }
        }
    }
}