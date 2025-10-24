#include <stdio.h>
#define LEN 5

int punto_silla(int (*)[LEN], int *, int *, int *);

int main(void){
    int valor;
    int cord_x, cord_y;
    int matriz[LEN][LEN];

    FILE *entrada = fopen("matriz5x5.txt", "r");
    if(!entrada){
        printf("No se encontro el archivo.");
        return 1;
    }
    /* Lee desde el archivo y traspasa los datos a una matriz */
    for(int fila = 0; fila < LEN; fila++){
        for(int columna = 0; columna < LEN; columna++){
            fscanf (entrada, "%d", &matriz[fila][columna]);  
        }
    }
    fclose(entrada);

    if(punto_silla(matriz, &valor, &cord_x, &cord_y) != 1){
        printf("Punto silla encontrado en posicion (%d, %d) con valor %d.", cord_x, cord_y, valor);
    }
    else{
        printf("No se encontraron puntos silla en la matriz.");
    }
    return 0;
}

int punto_silla(int (*matriz)[LEN], int *valor, int *x, int *y){
    int flag_min_fila, flag_max_col;

    /* Busca el mínimo en su fila y el máximo en su columna */
    for(int i = 0; i < LEN; i++){ /* Selecciona la fila */
        for(int j = 0; j < LEN; j++){ /* Selecciona la columna */
            /* Se asume que la condición de punto silla es verdadera */
            flag_min_fila = 1;
            flag_max_col = 1;
            /* Busca si es el mínimo en su fila */
            for(int k = 0; k < LEN; k++){
                if(matriz[i][k] < matriz[i][j]){
                    flag_min_fila = 0;
                    break;
                }
            }
            /* Busca si es el máximo en su columna */
            for(int k = 0; k < LEN; k++){
                if(matriz[k][j] > matriz[i][j]){
                    flag_max_col = 0;
                    break;
                }
            }

            /* Se verifica la condición y se retornan valores */
            if(flag_min_fila == 1 && flag_max_col == 1){
                *valor = matriz[i][j];
                *x = i;
                *y = j;
                return 0;
            }
        }
    }
    return 1;
}