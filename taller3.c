#include <stdio.h> 
 
#define FILAS 10 
#define COLUMNAS 10 
#define FALSO 0
#define VERDADERO 1 

void mostrarLaberinto(void); 
void mostrarSolucion(void);
void tipomovimientoVF(int fila, int columna, int *encontrado); 
void calcularRutas(int fila, int columna, int *encontrado); 
void jugar(void); 

char laberinto[FILAS][COLUMNAS] = { 
    {'A', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' '}, 
    {'#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' '}, 
    {' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' '}, 
    {' ', '#', '#', ' ', '#', '#', '#', ' ', '#', ' '}, 
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' '}, 
    {'#', '#', '#', '#', '#', ' ', '#', ' ', '#', ' '}, 
    {' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' '}, 
    {' ', '#', '#', '#', '#', ' ', '#', '#', '#', ' '}, 
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' '}, 
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', 'B'} 
    }; 


int main(void) {
    printf("----- ----- ----- ----- ----- ----- ----- ----- ----- -----\n"); 
    printf("----- ----- ----- ----- ----- ----- ----- ----- ----- -----\n");
    printf("----- ----- ------ ESQUEMA DEL LABERINTO ----- ------ -----\n");
    printf("----- ----- ----- ----- ----- ----- ----- ----- ----- -----\n");
    printf("----- ----- ----- ----- ----- ----- ----- ----- ----- -----\n\n");
    mostrarLaberinto(); 
    printf("----- ----- ----- ----- ----- ----- ----- ----- ----- ------\n"); 
    printf("----- ----- ----- ----- ----- ----- ----- ----- ----- ------\n");
    printf("----- -- BUSCANDO EL CAMINO DEL LABERINTO RECURSIVO ----- --\n");
    printf("----- ----- ----- ----- ----- ----- ----- ----- ----- ------\n");
    printf("----- ----- ----- ----- ----- ----- ----- ----- ----- ------\n\n");
    jugar();
    return 0; 
}

void mostrarLaberinto(void) { 
    for (int i = 0; i < FILAS; i++) { 
        for (int j = 0; j < COLUMNAS; j++) { 
            printf("    %c ", laberinto[i][j]); 
        } 
        printf("    \n"); 
    } 
    printf("    \n"); 
} 
 
void mostrarSolucion(void){
    printf("----- ----- ----- ----- ----- ----- ----- ----- ----- -----\n");
    printf("----- ----- ----- ----- ----- ----- ----- ----- ----- -----\n");
    printf("----- ----- ----- SOLUCION DEL LABERINTO ----- ----- ------\n");
    printf("----- ----- ----- ----- ----- ----- ----- ----- ----- -----\n");
    printf("----- ----- ----- ----- ----- ----- ----- ----- ----- -----\n\n");
    for(int i = 0; i < FILAS; i++){
        for(int j = 0; j < COLUMNAS; j++){
            char c = laberinto[i][j];
            if(c == 'A' || c == 'B' || c == '*'){
                printf("    %c ", c);
            }
            else{
                printf("      ");
            }
        }
        printf("    \n");
    }
    printf("    \n");
}

void jugar(void){
    int fila_A = -1, col_A = -1;
    int encontrado = FALSO;

    /* Busca A (inicio) */
    for(int i = 0; i < FILAS; i++){
        for(int j = 0; j < COLUMNAS; j++){
            if(laberinto[i][j] == 'A'){
                fila_A = i;
                col_A = j;
                break;
            }
        }
        if(fila_A != -1)
            break;
    }
    if(fila_A == -1){
        printf("----- ERROR: NO SE ENCONTRO LA CELDA DE INICIO -----\n");
        return;
    }

    /* Verificar que existan rutas */
    calcularRutas(fila_A, col_A, &encontrado);
    if(encontrado){
        mostrarLaberinto();
        mostrarSolucion();
    }
    else{
        printf("----- NO EXISTE UN CAMINO DESDE A HASTA B -----\n");
        mostrarLaberinto();
    }
}

void calcularRutas(int fila, int columna, int *encontrado){
    /* Verificar si se esta en alguno de los limites del laberinto */
    if(fila < 0 || fila >= FILAS || columna < 0 || columna >= COLUMNAS)
        return;
    /* Si ya se encontro, no seguir */
    if(*encontrado)
        return;
    char pos_ac = laberinto[fila][columna];

    /* Si se encuentra un muro o una celda ya visitada anteriormente, no seguir */
    if(pos_ac == '#' || pos_ac == 'N')
        return;
    /* Si la celda actual contiene la B (marca de salida), no seguir */
    if(pos_ac == 'B'){
        *encontrado = VERDADERO;
        return;
    }

    /* Crea una marca 'N' para señalar que esa celda ya fue recorrida */
    if(pos_ac != 'A')
        laberinto[fila][columna] = 'N';

    tipomovimientoVF(fila, columna, encontrado);

    if(*encontrado){
        if(pos_ac != 'A' && pos_ac != 'B'){
            laberinto[fila][columna] = '*';
            return;
        }
    }

    if(pos_ac != 'A')
        laberinto[fila][columna] = pos_ac;
}


void tipomovimientoVF(int fila, int columna, int *encontrado){
    /* Abajo */
    if(!(*encontrado))
        calcularRutas(fila + 1, columna, encontrado);
    /* Arriba */
    if(!(*encontrado))
        calcularRutas(fila - 1, columna, encontrado);
    /* Derecha */
    if(!(*encontrado))
        calcularRutas(fila, columna + 1, encontrado);
    /* Izquierda */
    if(!(*encontrado))
        calcularRutas(fila, columna - 1, encontrado);
}
