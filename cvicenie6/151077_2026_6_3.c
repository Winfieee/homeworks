#include <stdio.h>
#include <stdlib.h>

int alokuj_2D_pole(int ***pole, int n, int m) {
    *pole = (int **)malloc(n * sizeof(int *));
    if (*pole == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        (*pole)[i] = (int *)malloc(m * sizeof(int));
        if ((*pole)[i] == NULL) {
            for (int k = 0; k < i; k++) {
                free((*pole)[k]);
            }
            free(*pole);
            return 1;
        }
    }

    return 0;
}

void vypis_2D_pole(int **pole, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j > 0) {
                printf(" ");
            }
            printf("%d", pole[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n, m;
    printf("Nacitajte reozmery pola n, m\n");
    scanf("%d %d", &n, &m);

    int **pole = NULL;
    if (alokuj_2D_pole(&pole, n, m) == 1) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("Nacitajte hodnotu bunky %dx%d\n", i+1, j+1);
            scanf("%d", &pole[i][j]);
        }
    }

    vypis_2D_pole(pole, n, m);

    for (int i = 0; i < n; i++) {
        free(pole[i]);
    }
    free(pole);

    return 0;
}