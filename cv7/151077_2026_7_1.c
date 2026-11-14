#include<stdio.h>

int magicky(int n, int pole[n][n]) {
    int riadok = 0, stlpec = 0, diagonalmain = 0, diagonalsecondary = 0;
    for (int i = 0; i < n; i++) {
        riadok += pole[0][i];
        stlpec += pole[i][0];
        diagonalmain += pole[i][i];
        diagonalsecondary += pole[i][n - 1 - i];
    }

    for (int i = 0; i < n; i++) {
        diagonalmain += pole[i][i];
        diagonalsecondary += pole[i][n - 1 - i];
        for (int j = 0; j < n; j++) {
            riadok += pole[i][j];
            stlpec += pole[j][i];
        }
    }

    if (riadok == stlpec && riadok == diagonalmain && stlpec == diagonalsecondary) {
        return 1;
    }
}

int main() {
    int bign, n;

    printf("Nacitajte cislo N pre staticke pole pole[N][N]\n");
    scanf("%d", &bign);
    int pole[bign][bign];

    printf("Nacitajte cislo n pre stvorec rozmiera nxn\n");
    scanf("%d", &n);

    if (n>bign) return 1;

    for (int m = 0; m <= 1; m++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (m == 0) {
                    printf("Nacitajte bunku %dx%d\n", i+1, j+1);
                    scanf("%d", &pole[i][j]);
                }
                else {
                    printf("%d ", pole[i][j]);
                    if (j==n-1) printf("\n");
                }
            }
        }
    }
    if (magicky(n, pole) == 1) printf("Stvorecje magicky.\n");
    else printf("Stvorec nie je magicky.\n");

    return 0;
}