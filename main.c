#include <stdio.h>

void ingresar(char nom[5][30], int *dem, float *tiem, float *rec, int *c) {
    printf("Nombre del producto: ");
    scanf("%s", nom[*c]);

    printf("Cantidad demandada: ");
    scanf("%d", &dem[*c]);
    while (dem[*c] <= 0) {
        printf("No puede ser negativo ni cero, ingrese otra vez: ");
        scanf("%d", &dem[*c]);
    }

    printf("Tiempo por unidad: ");
    scanf("%f", &tiem[*c]);
    while (tiem[*c] <= 0) {
        printf("No puede ser negativo ni cero, ingrese otra vez: ");
        scanf("%f", &tiem[*c]);
    }

    printf("Recursos por unidad: ");
    scanf("%f", &rec[*c]);
    while (rec[*c] <= 0) {
        printf("No puede ser negativo ni cero, ingrese otra vez: ");
        scanf("%f", &rec[*c]);
    }

    *c = *c + 1;
}

void mostrar(char nom[5][30], int *dem, float *tiem, float *rec, int c) {
    printf("\nNombre\t\tDemanda\t\tTiempo\t\tRecursos\n");

    for (int i = 0; i < c; i++) {
        printf("%s\t\t%d\t\t%.2f\t\t%.2f\n", nom[i], dem[i], tiem[i], rec[i]);
    }
}

int buscar(char nom[5][30], int c, char buscado[30]) {
    for (int i = 0; i < c; i++) {
        int j = 0;
        int iguales = 1;

        // Compara letra por letra hasta llegar al final de la palabra (\0)
        while (nom[i][j] != '\0' || buscado[j] != '\0') {
            if (nom[i][j] != buscado[j]) {
                iguales = 0;
                break;
            }
            j++;
        }

        if (iguales == 1) {
            return i;
        }
    }

    return -1;
}

void editar(char nom[5][30], int *dem, float *tiem, float *rec, int pos) {
    printf("Nuevo nombre: ");
    scanf("%s", nom[pos]);

    printf("Nueva demanda: ");
    scanf("%d", &dem[pos]);
    while (dem[pos] <= 0) {
        printf("Ingrese un valor positivo: ");
        scanf("%d", &dem[pos]);
    }

    printf("Nuevo tiempo: ");
    scanf("%f", &tiem[pos]);
    while (tiem[pos] <= 0) {
        printf("Ingrese un valor positivo: ");
        scanf("%f", &tiem[pos]);
    }

    printf("Nuevos recursos: ");
    scanf("%f", &rec[pos]);
    while (rec[pos] <= 0) {
        printf("Ingrese un valor positivo: ");
        scanf("%f", &rec[pos]);
    }
}

void eliminar(char nom[5][30], int *dem, float *tiem, float *rec, int pos, int *c) {
    for (int i = pos; i < *c - 1; i++) {
        // Pasa las 30 letras del nombre siguiente a la posicion actual
        for (int j = 0; j < 30; j++) {
            nom[i][j] = nom[i + 1][j];
        }

        dem[i] = dem[i + 1];
        tiem[i] = tiem[i + 1];
        rec[i] = rec[i + 1];
    }

    *c = *c - 1;
}

float calcTiempo(int *dem, float *tiem, int c) {
    float suma = 0;

    for (int i = 0; i < c; i++) {
        suma = suma + (dem[i] * tiem[i]);
    }

    return suma;
}

float calcRecursos(int *dem, float *rec, int c) {
    float suma = 0;

    for (int i = 0; i < c; i++) {
        suma = suma + (dem[i] * rec[i]);
    }

    return suma;
}

int main(void) {
    char nom[5][30];
    int dem[5];
    float tiem[5];
    float rec[5];

    int c = 0;
    int op, pos;
    char buscarNom[30];
    float tDisp, rDisp, tTotal, rTotal;

    do {
        printf("\nMenu de Produccion\n");
        printf("1. Ingresar producto\n");
        printf("2. Mostrar productos\n");
        printf("3. Editar producto\n");
        printf("4. Eliminar producto\n");
        printf("5. Calcular produccion\n");
        printf("6. Salir\n");
        printf("Opcion: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                if (c < 5) {
                    ingresar(nom, dem, tiem, rec, &c);
                } else {
                    printf("Ya estan llenos los 5 productos\n");
                }
                break;

            case 2:
                if (c == 0) {
                    printf("No hay datos ingresados\n");
                } else {
                    mostrar(nom, dem, tiem, rec, c);
                }
                break;

            case 3:
                if (c == 0) {
                    printf("No hay datos ingresados\n");
                } else {
                    printf("Nombre del producto a editar: ");
                    scanf("%s", buscarNom);
                    pos = buscar(nom, c, buscarNom);

                    if (pos != -1) {
                        editar(nom, dem, tiem, rec, pos);
                    } else {
                        printf("No se encontro el producto\n");
                    }
                }
                break;

            case 4:
                if (c == 0) {
                    printf("No hay datos ingresados\n");
                } else {
                    printf("Nombre del producto a eliminar: ");
                    scanf("%s", buscarNom);
                    pos = buscar(nom, c, buscarNom);

                    if (pos != -1) {
                        eliminar(nom, dem, tiem, rec, pos, &c);
                        printf("Producto eliminado\n");
                    } else {
                        printf("No se encontro el producto\n");
                    }
                }
                break;

            case 5:
                if (c == 0) {
                    printf("Primero ingrese productos\n");
                } else {
                    printf("Tiempo disponible en la fabrica: ");
                    scanf("%f", &tDisp);
                    while (tDisp <= 0) {
                        printf("Ingrese un valor positivo: ");
                        scanf("%f", &tDisp);
                    }

                    printf("Recursos disponibles en la fabrica: ");
                    scanf("%f", &rDisp);
                    while (rDisp <= 0) {
                        printf("Ingrese un valor positivo: ");
                        scanf("%f", &rDisp);
                    }

                    tTotal = calcTiempo(dem, tiem, c);
                    rTotal = calcRecursos(dem, rec, c);

                    printf("\nTiempo total requerido: %.2f\n", tTotal);
                    printf("Recursos totales requeridos: %.2f\n", rTotal);

                    if (tTotal <= tDisp && rTotal <= rDisp) {
                        printf("Si se puede cumplir con la demanda\n");
                    } else {
                        printf("No se puede cumplir con la demanda\n");
                    }
                }
                break;

            case 6:
                printf("Fin del programa\n");
                break;

            default:
                printf("Opcion incorrecta\n");
                break;
        }
    } while (op != 6);

    return 0;
}
