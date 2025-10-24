#include <stdio.h>
#include <string.h>

#define TAM_MAX 100
#define LINEAS_MAX 1000

void ingresar_nombre(void);
void modificar(void);
void ordernar_nombres(void);
void ordernar_apellidos(void);
void encontrar_mas_largo(void);
void invertir_nombre_apellido(void);
void eliminar(void);
void mostrar_lista(void);
void buscar_nombre_o_apellido(void);

int main(void) {
    int opcion, caracter;
    while (1) {
        printf("-------------------------------------\n\n");
        printf("\nBienvenido, elige la opcion que mas prefieras.\n\n");
        printf("1.- Ingresar nombre.\n");
        printf("2.- Modificar linea.\n");
        printf("3.- Ordenar alfabeticamente por nombres.\n");
        printf("4.- Ordenar alfabeticamente por apellidos.\n");
        printf("5.- Encontrar el nombre mas largo.\n");
        printf("6.- Invertir la lista con el apellido y el nombre.\n");
        printf("7.- Eliminar linea.\n");
        printf("8.- Mostrar listado.\n");
        printf("9.- Buscar por nombre o apellido.\n");
        printf("10.- Salir.\n");
        printf("Opcion: ");
        if (scanf("%d", &opcion) != 1) {
            while ((caracter = getchar()) != '\n' && caracter != EOF);
            printf("Opcion no valida, porfavor ingrese un numero del 1 al 9.\n");
            continue;
        }
        while ((caracter = getchar()) != '\n' && caracter != EOF);
        switch (opcion) {
            case 1:
                printf("Ingresar nombre\n");
                printf("-------------------------------------\n\n");
                ingresar_nombre();
                break;
            case 2:
                printf("Modificar\n");
                printf("-------------------------------------\n\n");
                modificar();
                break;
            case 3:
                printf("Ordenar alfabeticamente por nombres\n");
                printf("-------------------------------------\n\n");
                ordernar_nombres();
                break;
            case 4:
                printf("Ordenar alfabeticamente por apellidos\n");
                printf("-------------------------------------\n\n");
                ordernar_apellidos();
                break;
            case 5:
                printf("Encontrar el nombre mas largo\n");
                printf("-------------------------------------\n\n");
                encontrar_mas_largo();
                break;
            case 6:
                printf("Invertir la lista con el apellido y el nombre\n");
                printf("-------------------------------------\n\n");
                invertir_nombre_apellido();
                break;
            case 7:
                printf("Eliminar\n");
                printf("-------------------------------------\n\n");
                eliminar();
                break;
            case 8:
                printf("Mostrar listado\n");
                printf("-------------------------------------\n\n");
                mostrar_lista();
                break;
            case 9:
                printf("Buscar por nombre o apellido\n");
                printf("-------------------------------------\n\n");
                buscar_nombre_o_apellido();
                break;
            case 10:
                printf("Saliendo....\n");
                printf("-------------------------------------\n\n");
                return 0;
            default:
                printf("Opcion no valida, porfavor ingrese un numero del 1 al 10.\n");
        }
    }
    return 0;
}

void ingresar_nombre(void) {
    int i = 0, caracter;
    char nombre[TAM_MAX];
    FILE *nombres = fopen("nombres.txt", "a");
    if (!nombres) {
        perror("No fue posible abrir el archivo");
        printf("-------------------------------------\n\n");
        return;
    }
    printf("Ingrese el nuevo nombre (ingrese 'q' para cancelar):\n");
    if (fgets(nombre, TAM_MAX, stdin) == NULL) {
        fclose(nombres);
        return;
    }
    int tam = strlen(nombre);
    if (tam > 0 && nombre[tam - 1] == '\n') {
        nombre[tam - 1] = '\0';
        tam--;
    }
    if (tam == 0) {
        printf("No se encontraron datos. No se guardo nada.\n");
        printf("-------------------------------------\n\n");
        fclose(nombres);
        return;
    }
    if (strcmp(nombre, "q") == 0 || strcmp(nombre, "Q") == 0) {
        printf("Saliendo...\n");
        printf("-------------------------------------\n\n");
        fclose(nombres);
        return;
    }
    for (int i = 0; i < tam; i++) {
        char c = nombre[i];
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) {
            printf("El nombre solo puede contener letras.\n");
            printf("-------------------------------------\n\n");
            fclose(nombres);
            return;
        }
    }
    fprintf(nombres, "\n%s", nombre);
    fclose(nombres);
    printf("\n-------------------------------------\n");
    printf("Nombre guardado exitosamente\n");
    printf("-------------------------------------\n\n");
}

void modificar(void) {
    char lineas[LINEAS_MAX][TAM_MAX];
    char nombre[TAM_MAX];
    int contador = 0;
    FILE *nombres = fopen("nombres.txt", "r");
    if (!nombres) {
        perror("No se pudo abrir el archivo");
        printf("-------------------------------------\n\n");
        return;
    }
    while (contador < LINEAS_MAX && fgets(nombre, sizeof(nombre), nombres)) {
        int tam = strlen(nombre);
        if (tam > 0 && nombre[tam - 1] == '\n') nombre[tam - 1] = '\0';
        strncpy(lineas[contador], nombre, TAM_MAX - 1);
        lineas[contador][TAM_MAX - 1] = '\0';
        contador++;
    }
    fclose(nombres);
    if (contador == 0) {
        printf("No hay líneas para modificar.\n");
        printf("-------------------------------------\n\n");
        return;
    }
    printf("Listado de nombres:\n");
    for (int i = 0; i < contador; i++) {
        printf("%d. %s\n", i + 1, lineas[i]);
    }
    printf("-------------------------------------\n\n");
    int linea_modificar;
    printf("Ingrese el numero de la linea a modificar: ");
    if (scanf("%d", &linea_modificar) != 1 || linea_modificar < 1 || linea_modificar > contador) {
        printf("Numero invalido.\n");
        while (getchar() != '\n');
        return;
    }
    linea_modificar--;
    while (getchar() != '\n');
    printf("Ingrese el nuevo nombre: ");
    if (fgets(nombre, TAM_MAX, stdin) == NULL) {
        printf("No se ingreso nada.\n");
        printf("-------------------------------------\n\n");
        return;
    }
    int tam = strlen(nombre);
    if (tam > 0 && nombre[tam - 1] == '\n') nombre[tam - 1] = '\0';

    if (strlen(nombre) == 0) {
        printf("No se ingreso texto. No se modifica la linea.\n");
        printf("-------------------------------------\n\n");
        return;
    }
    strncpy(lineas[linea_modificar], nombre, TAM_MAX - 1);
    lineas[linea_modificar][TAM_MAX - 1] = '\0';
    nombres = fopen("temp.txt", "w");
    if (!nombres) {
        perror("No se pudo abrir el archivo");
        printf("-------------------------------------\n\n");
        return;
    }
    for (int i = 0; i < contador; i++) {
        fprintf(nombres, "%s\n", lineas[i]);
    }
    fclose(nombres);
    if (remove("nombres.txt") != 0) {
        perror("No se pudo eliminar nombres.txt");
        printf("-------------------------------------\n\n");
        return;
    }
    if (rename("temp.txt", "nombres.txt") != 0) {
        perror("No se pudo renombrar temp.txt");
        printf("-------------------------------------\n\n");
        return;
    }

    printf("Linea modificada exitosamente\n");
    printf("-------------------------------------\n\n");
}

void ordernar_nombres(void) {
    char lineas[LINEAS_MAX][TAM_MAX];
    char nombre[TAM_MAX];
    int contador = 0;
    FILE *nombres = fopen("nombres.txt", "r");
    if (!nombres) {
        perror("No fue posible abrir el archivo");
        printf("-------------------------------------\n\n");
        return;
    }
    while (contador < LINEAS_MAX && fgets(nombre, sizeof(nombre), nombres)) {
        int tam = strlen(nombre);
        if (tam > 0 && nombre[tam - 1] == '\n') nombre[tam - 1] = '\0';
        strncpy(lineas[contador], nombre, TAM_MAX - 1);
        lineas[contador][TAM_MAX - 1] = '\0';
        contador++;
    }
    fclose(nombres);
    for (int i = 0; i < contador - 1; i++) {
        for (int j = i + 1; j < contador; j++) {
            char nombre_i[TAM_MAX], nombre_j[TAM_MAX];
            int k = 0;
            while (lineas[i][k] != ' ' && lineas[i][k] != '\0') {
                nombre_i[k] = lineas[i][k];
                k++;
            }
            nombre_i[k] = '\0';
            k = 0;
            while (lineas[j][k] != ' ' && lineas[j][k] != '\0') {
                nombre_j[k] = lineas[j][k];
                k++;
            }
            nombre_j[k] = '\0';
            if (strcmp(nombre_i, nombre_j) > 0) {
                char temp[TAM_MAX];
                strcpy(temp, lineas[i]);
                strcpy(lineas[i], lineas[j]);
                strcpy(lineas[j], temp);
            }
        }
    }
    nombres = fopen("nombres.txt", "w");
    if (!nombres) {
        perror("No fue posible abrir el archivo");
        printf("-------------------------------------\n\n");
        return;
    }
    for (int i = 0; i < contador; i++) {
        fprintf(nombres, "%s\n", lineas[i]);
    }
    fclose(nombres);
    printf("El archivo fue ordenado.\n");
    printf("-------------------------------------\n\n");
}

void ordernar_apellidos(void) {
    char lineas[LINEAS_MAX][TAM_MAX];
    char nombre[TAM_MAX];
    int contador = 0;
    FILE *nombres = fopen("nombres.txt", "r");
    if (!nombres) {
        perror("No fue posible abrir el archivo");
        printf("-------------------------------------\n\n");
        return;
    }

    while (contador < LINEAS_MAX && fgets(nombre, sizeof(nombre), nombres)) {
        int tam = strlen(nombre);
        if (tam > 0 && nombre[tam - 1] == '\n') nombre[tam - 1] = '\0';
        strncpy(lineas[contador], nombre, TAM_MAX - 1);
        lineas[contador][TAM_MAX - 1] = '\0';
        contador++;
    }
    fclose(nombres);
    for (int i = 0; i < contador - 1; i++) {
        for (int j = i + 1; j < contador; j++) {
            char apellido_i[TAM_MAX], apellido_j[TAM_MAX];
            int len_i = strlen(lineas[i]), len_j = strlen(lineas[j]);
            int inicio;
            for (inicio = len_i - 1; inicio >= 0 && lineas[i][inicio] != ' '; inicio--);
            strcpy(apellido_i, &lineas[i][inicio + 1]);
            for (inicio = len_j - 1; inicio >= 0 && lineas[j][inicio] != ' '; inicio--);
            strcpy(apellido_j, &lineas[j][inicio + 1]);
            if (strcmp(apellido_i, apellido_j) > 0) {
                char temp[TAM_MAX];
                strcpy(temp, lineas[i]);
                strcpy(lineas[i], lineas[j]);
                strcpy(lineas[j], temp);
            }
        }
    }
    nombres = fopen("nombres.txt", "w");
    if (!nombres) {
        perror("No fue posible abrir el archivo");
        printf("-------------------------------------\n\n");
        return;
    }

    for (int i = 0; i < contador; i++) {
        fprintf(nombres, "%s\n", lineas[i]);
    }
    fclose(nombres);
    printf("Archivo ordenado.\n");
    printf("-------------------------------------\n\n");
}

void encontrar_mas_largo(void) {
    char buffer[TAM_MAX];
    char mas_largo[TAM_MAX];
    int tam_max = 0;
    FILE *nombres = fopen("nombres.txt", "r");
    if (!nombres) {
        perror("No fue posible abrir el archivo");
        printf("-------------------------------------\n\n");
        return;
    }

    while (fgets(buffer, sizeof(buffer), nombres)) {
        int tam = strlen(buffer);
        if (tam > 0 && buffer[tam - 1] == '\n') {
            buffer[tam - 1] = '\0';
            tam--;
        }
        if (tam > tam_max) {
            tam_max = tam;
            strcpy(mas_largo, buffer);
        }
    }
    fclose(nombres);
    if (tam_max > 0) {
        printf("El nombre mas largo es: %s\n", mas_largo);
        printf("Con %d caracteres.\n", tam_max);
        printf("-------------------------------------\n\n");
    } else {
        printf("El archivo esta vacio.\n");
        printf("-------------------------------------\n\n");
    }
}

void invertir_nombre_apellido(void) {
    char lineas[LINEAS_MAX][TAM_MAX];
    char nombre[TAM_MAX];
    int contador = 0;
    FILE *nombres = fopen("nombres.txt", "r");
    if (!nombres) {
        perror("No fue posible abrir el archivo");
        printf("-------------------------------------\n\n");
        return;
    }
    while (contador < LINEAS_MAX && fgets(nombre, sizeof(nombre), nombres)) {
        int tam = strlen(nombre);
        if (tam > 0 && nombre[tam - 1] == '\n') nombre[tam - 1] = '\0';
        strncpy(lineas[contador], nombre, TAM_MAX - 1);
        lineas[contador][TAM_MAX - 1] = '\0';
        contador++;
    }
    fclose(nombres);

    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        perror("No fue posible abrir el archivo");
        printf("-------------------------------------\n\n");
        return;
    }
    for (int i = 0; i < contador; i++) {
        char copia[TAM_MAX];
        int espacio = -1;
        for (int j = 0; lineas[i][j]; j++) {
            if (lineas[i][j] == ' ') {
                espacio = j;
                break;
            }
        }
        if (espacio != -1) {
            char apellido[TAM_MAX];
            strcpy(apellido, &lineas[i][espacio + 1]);
            char nombre_tmp[TAM_MAX];
            strncpy(nombre_tmp, lineas[i], espacio);
            nombre_tmp[espacio] = '\0';
            strcpy(copia, apellido);
            strcat(copia, " ");
            strcat(copia, nombre_tmp);
        } else {
            strncpy(copia, lineas[i], TAM_MAX - 1);
            copia[TAM_MAX - 1] = '\0';
        }

        fprintf(temp, "%s\n", copia);
    }
    fclose(temp);
    if (remove("nombres.txt") != 0) {
        perror("No se pudo eliminar nombres.txt");
        printf("-------------------------------------\n\n");
        return;
    }
    if (rename("temp.txt", "nombres.txt") != 0) {
        perror("No se pudo renombrar temp.txt a nombres.txt");
        printf("-------------------------------------\n\n");
        return;
    }

    printf("Los nombres y apellidos fueron invertidos correctamente.\n");
    printf("-------------------------------------\n\n");
}

void eliminar(void) {
    char lineas[LINEAS_MAX][TAM_MAX];
    char nombre[TAM_MAX];
    int contador = 0;
    FILE *nombres = fopen("nombres.txt", "r");
    if (!nombres) {
        perror("No fue posible abrir nombres.txt");
        printf("-------------------------------------\n\n");
        return;
    }
    while (contador < LINEAS_MAX && fgets(nombre, sizeof(nombre), nombres)) {
        int tam = strlen(nombre);
        if (tam > 0 && nombre[tam - 1] == '\n') nombre[tam - 1] = '\0';
        strncpy(lineas[contador], nombre, TAM_MAX - 1);
        lineas[contador][TAM_MAX - 1] = '\0';
        contador++;
    }
    fclose(nombres);
    if (contador == 0) {
        printf("No hay líneas para eliminar.\n");
        printf("-------------------------------------\n\n");
        return;
    }
    printf("Listado de nombres:\n");
    for (int i = 0; i < contador; i++) {
        printf("%d. %s\n", i + 1, lineas[i]);
    }
    int linea_eliminar;
    printf("Ingrese el numero de la linea a eliminar: ");
    if (scanf("%d", &linea_eliminar) != 1 || linea_eliminar < 1 || linea_eliminar > contador) {
        printf("Número invalido.\n");
        printf("-------------------------------------\n\n");
        while (getchar() != '\n');
        return;
    }
    linea_eliminar--;
    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        perror("No se pudo abrir temp.txt");
        printf("-------------------------------------\n\n");
        return;
    }
    for (int i = 0; i < contador; i++) {
        if (i != linea_eliminar) {
            fprintf(temp, "%s\n", lineas[i]);
        }
    }
    fclose(temp);
    if (remove("nombres.txt") != 0) {
        perror("No se pudo eliminar nombres.txt");
        printf("-------------------------------------\n\n");
        return;
    }
    if (rename("temp.txt", "nombres.txt") != 0) {
        perror("No se pudo renombrar temp.txt a nombres.txt");
        printf("-------------------------------------\n\n");
        return;
    }
    printf("Linea eliminada correctamente.\n");
    printf("-------------------------------------\n\n");
}

void mostrar_lista(void) {
    char nombre[TAM_MAX];
    FILE *nombres = fopen("nombres.txt", "r");
    if (!nombres) {
        perror("No fue posible abrir el archivo");
        printf("-------------------------------------\n\n");
        return;
    }

    int i = 1;
    printf("Los nombres que contengan tildes pueden contener errores al mostrarse en pantalla\n\n");
    printf("-------------------------------------\n\n");

    while (fgets(nombre, sizeof(nombre), nombres) != NULL) {
        int tam_nombre = strlen(nombre);
        if (tam_nombre > 0 && nombre[tam_nombre - 1] == '\n') {
            nombre[tam_nombre - 1] = '\0';
        }
        printf("%d. %s\n", i, nombre);
        i++;
    }

    if (i == 1) {
        printf("El archivo no contiene datos\n");
        printf("-------------------------------------\n\n");
    }

    fclose(nombres);
}

void buscar_nombre_o_apellido(void) {
    char nombre[TAM_MAX];
    int encontrado = 0;
    FILE *nombres = fopen("nombres.txt", "r");
    if (!nombres) {
        perror("No se pudo abrir el archivo");
        printf("-------------------------------------\n\n");
        return;
    }
    char busqueda[TAM_MAX];
    printf("Ingrese el nombre o apellido a buscar: ");
    if (fgets(busqueda, TAM_MAX, stdin) == NULL) {
        fclose(nombres);
        return;
    }
    int tam = strlen(busqueda);
    if (tam > 0 && busqueda[tam - 1] == '\n') busqueda[tam - 1] = '\0';
    if (strlen(busqueda) == 0) {
        printf("No se ingreso texto.\n");
        printf("-------------------------------------\n\n");
        fclose(nombres);
        return;
    }
    int linea = 1;
    while (fgets(nombre, sizeof(nombre), nombres)) {
        int len = strlen(nombre);
        if (len > 0 && nombre[len - 1] == '\n') nombre[len - 1] = '\0';
        if (strstr(nombre, busqueda) != NULL) {
            printf("Encontrado en linea %d: %s\n", linea, nombre);
            encontrado = 1;
        }
        linea++;
    }
    if (!encontrado) {
        printf("No se encontraron coincidencias.\n");
        printf("-------------------------------------\n\n");
    }
    fclose(nombres);
}