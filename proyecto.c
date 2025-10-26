/*
* ---------------------------------------------------------- *
*   Autores: Iván Maldonado Rodríguez, Martin Rojas Arenas
*   Tema: Juego de triangulos con backstracking
*   Fecha: 25.10.2025
*   Docentes: Hugo Araya Carrasco, Luis Ponce Rosales
*   Carrera: Ingeniería Civil Informática
* ---------------------------------------------------------- *
*/

/* ||-- Bibliotecas --|| */
#include <stdio.h>
#include <string.h>

/* ||-- Constantes globales --|| */
#define MAX_TRIANGULOS      (6)
#define PUNTUACION_INVALIDA (-1)
/* Lados del triangulo: Exterior(0), Izquierdo(1), Derecho(2) */
#define LADO_EXT    (0)
#define LADO_IZQ    (1)
#define LADO_DER    (2)

typedef struct triangulo {
    int lado[3];
} TRIANGULO;

/* ||-- Prototipos de funciones --|| */
void limpiar_buffer();
int leer_set(TRIANGULO [MAX_TRIANGULOS]);
void buscar_puntuacion_alta(int, TRIANGULO [MAX_TRIANGULOS], TRIANGULO [MAX_TRIANGULOS], int [MAX_TRIANGULOS], int *);
TRIANGULO rotar_triangulo(TRIANGULO, int);

/* ||-- Main --|| */
int main() {
    TRIANGULO triangulos[MAX_TRIANGULOS], hexagono[MAX_TRIANGULOS];
    int puntuacion_total, triangulos_usados[MAX_TRIANGULOS];
    char separador[2];
    
    while (1) {
        /* Lectura de sets de triangulos */
        if (leer_set(triangulos) != 1) {
            /* Si hay un set invalido lee el separador y continua */
            if (scanf("%1s", separador) != 1){
                break;
            }
            /* Limpia el búfer, evita caracteres no deseados */
            limpiar_buffer();
            /* Revisa si el separador es un simbolo de peso o no*/
            if (separador[0] == '$'){
                break;
            } else {
                continue;
            }
        }
        
        
        /* Inicialización de variables */
        puntuacion_total = PUNTUACION_INVALIDA;
        
        memset(triangulos_usados, 0, sizeof (triangulos_usados));
        
        /* Backstracking */ 
        buscar_puntuacion_alta(0, triangulos, hexagono, triangulos_usados, &puntuacion_total);
        
        /* Verifica si el hexagono tiene solución válido y muestra la salida */
        if (puntuacion_total == -1) {
            printf("None\n");
        } else {
            printf("%d\n", puntuacion_total);
        }

        /* Comprueba que exista un separador de sets (*) al leer */ 
        if (scanf("%1s", separador) != 1) {
            break;
        }
        /* Limpia el búfer, evita caracteres extra */
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        /* Si el separador es $, se finaliza el programa */
        if (separador[0] == '$') {
            break;
        }
    }
    return 0;
}

/* -- Funciones -- */
void limpiar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int leer_set(TRIANGULO triangulos[MAX_TRIANGULOS]) {
    int i, exito = 1;
    for (i = 0; i < MAX_TRIANGULOS; i++) {
        if (scanf("%d %d %d", &triangulos[i].lado[0], &triangulos[i].lado[1], &triangulos[i].lado[2]) != 3) {
            exito = 0;
            limpiar_buffer();
            break;
        }
        /* Limpia el búfer despues de salir de scanf (elimina valores extra) */
        limpiar_buffer();
    }
    return exito;
}

TRIANGULO rotar_triangulo(TRIANGULO triangulo, int rotacion) {
    TRIANGULO triangulo_rotado;
    /* Asegura que el valor de rotacion 0, 1 o 2 */
    rotacion = rotacion % 3;
    
    switch (rotacion) {
        case 0: {
            triangulo_rotado.lado[LADO_EXT] = triangulo.lado[LADO_EXT];
            triangulo_rotado.lado[LADO_IZQ] = triangulo.lado[LADO_IZQ];
            triangulo_rotado.lado[LADO_DER] = triangulo.lado[LADO_DER];
            break;
        }
        case 1: {
            triangulo_rotado.lado[LADO_EXT] = triangulo.lado[LADO_IZQ];
            triangulo_rotado.lado[LADO_IZQ] = triangulo.lado[LADO_DER];
            triangulo_rotado.lado[LADO_DER] = triangulo.lado[LADO_EXT];
            break;
        }
        case 2: {
            triangulo_rotado.lado[LADO_EXT] = triangulo.lado[LADO_DER];
            triangulo_rotado.lado[LADO_IZQ] = triangulo.lado[LADO_EXT];
            triangulo_rotado.lado[LADO_DER] = triangulo.lado[LADO_IZQ];
            break;
        }
    }
    return triangulo_rotado;
}

void buscar_puntuacion_alta(int pos_hexagono, TRIANGULO triangulos[MAX_TRIANGULOS], TRIANGULO hexagono[MAX_TRIANGULOS], int triangulos_usados[MAX_TRIANGULOS], int * puntuacion) {
    int i, rotacion;
    
    /* Evalua el ultimo triangulo en el hexagono */
    if (pos_hexagono == 6) {
        if (hexagono[5].lado[LADO_DER] == hexagono[0].lado[LADO_IZQ]) {
            int aux_puntuacion = 0;

            /* Se calcula la suma de los lados exteriores del hexagono */
            for (i = 0; i < MAX_TRIANGULOS; i++) {
                aux_puntuacion += hexagono[i].lado[LADO_EXT];
            }
            /* Si la suma de lados > la puntuacion acumulada, actualiza la puntuacion acumulada */
            if (aux_puntuacion > *puntuacion) {
                *puntuacion = aux_puntuacion;
            }
        }
        return;
    }
    for (i = 0; i < MAX_TRIANGULOS; i++) {
        if (triangulos_usados[i] == 0) {
            for (rotacion = 0; rotacion < 3; rotacion++) {
                TRIANGULO triangulo_rotado = rotar_triangulo(triangulos[i], rotacion);
                int es_valido = 1;
                
                if (pos_hexagono > 0) {
                    /* Verifica si el valor de los vertices comunes entre dos triangulos son iguales */
                    if (triangulo_rotado.lado[LADO_IZQ] != hexagono[pos_hexagono - 1].lado[LADO_DER]) {
                        es_valido = 0;
                    }
                }
                if (es_valido) {
                    hexagono[pos_hexagono] = triangulo_rotado;
                    
                    /* Marca el triangulo como usado para continuar el recorrido */ 
                    triangulos_usados[i] = 1;
                    /* Se llama a la función para avanzar al siguiente triangulo del hexagono */
                    buscar_puntuacion_alta(pos_hexagono + 1, triangulos, hexagono, triangulos_usados, puntuacion);
                    /* Desmarca el triangulo para probar otras combinaciones */ 
                    triangulos_usados[i] = 0;
                }
            }
        }
    }
}