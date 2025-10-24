#include <stdio.h>

#define LEN 8

void mostrarTablero(int[LEN][LEN]);
int verificarMovimiento(int[LEN][LEN], int, int);
void solucionIterativa(int tablero[LEN][LEN], int *);
void solucionRecursiva(int tablero[LEN][LEN], int, int *);
void mostrarSolucion(int[LEN][LEN], int);

int main(void) {
    int tablero[LEN][LEN] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}};
    int num_soluciones = 0;
    mostrarTablero(tablero);
    solucionIterativa(tablero, &num_soluciones);
    num_soluciones = 1;
    solucionRecursiva(tablero, 0, &num_soluciones);
    return 0;
}

void mostrarTablero(int tablero[LEN][LEN]) {
    int fila, columna;
    printf("\n");
    printf("-   -   -   TABLERO    -    -   -\n\n");
    for (fila = 0; fila < LEN; fila++) {
        for (columna = 0; columna < LEN; columna++) {
            printf(".   ");
        }
        printf("\n");
    }
    printf("\n-   -   FIN DEL TABLERO    -    -\n");
}

int verificarMovimiento(int tablero[LEN][LEN], int fila, int columna) {
    int i, j;
    for (i = 0; i < fila; i++) {
        if (tablero[i][columna] == 1) return 0;
    }
    for (i = fila - 1, j = columna - 1; i >= 0 && j >= 0; i--, j--) {
        if (tablero[i][j] == 1) return 0;
    }
    for (i = fila - 1, j = columna + 1; i >= 0 && j < LEN; i--, j++) {
        if (tablero[i][j] == 1) return 0;
    }
    return 1;
}

void solucionIterativa(int tablero[LEN][LEN], int *num_soluciones) {
    int i = 0, j;
    int fila[LEN];
    for (int k = 0; k < LEN; k++) fila[k] = -1;
    while (i >= 0 && *num_soluciones < 1) {
        j = fila[i] + 1;
        while (j < LEN && !verificarMovimiento(tablero, i, j)) j++;
        if (j < LEN) {
            tablero[i][j] = 1;
            fila[i] = j;
            if (i == LEN - 1) {
                (*num_soluciones)++;
                mostrarSolucion(tablero, *num_soluciones);
            } else {
                i++;
                fila[i] = -1;
            }
        } else {
            i--;
            if (i >= 0) tablero[i][fila[i]] = 0;
        }
    }
}

void solucionRecursiva(int tablero[LEN][LEN], int fila, int *num_soluciones) {
    if (*num_soluciones >= 2) return;
    if (fila == LEN) {
        (*num_soluciones)++;
        mostrarSolucion(tablero, *num_soluciones);
        return;
    }
    for (int columna = 0; columna < LEN; columna++) {
        if (verificarMovimiento(tablero, fila, columna)) {
            tablero[fila][columna] = 1;
            solucionRecursiva(tablero, fila + 1, num_soluciones);
            tablero[fila][columna] = 0;
            if (*num_soluciones >= 2) return;
        }
    }
}

void mostrarSolucion(int tablero[LEN][LEN], int num_soluciones) {
    printf("\n-   -   -   SOLUCION: %d    -    -   -\n\n", num_soluciones);
    for (int fila = 0; fila < LEN; fila++) {
        for (int columna = 0; columna < LEN; columna++) {
            printf("%c   ", tablero[fila][columna] ? 'R' : '.');
        }
        printf("\n");
    }
    printf("\n-   -   FIN DEL TABLERO    -    -\n");
}