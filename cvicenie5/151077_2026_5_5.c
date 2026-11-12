#include<stdio.h>

int delitele(int x[], int pocetx, int y[], int delenec) {
    int j;
    for (int i=0; i<pocetx; i++) {
        if (delenec % x[i] == 0) {
            y[j] = x[i];
            j++;
        }
    }
    return j;
}

int main() {
    int x[] = {4, 7, 10, 2, 3, 9, 6, 5, 8, 12};
    int pocetx = 10;
    int y[sizeof(x)/sizeof(x[0])+1];
    int pocety = delitele(x, pocetx, y, 24);

    printf("pocety: %d\n", pocety);
    printf("y: {");
    for (int i=0; i<pocety; i++) {
        printf("%d", y[i]);
        if (i< pocety-1) printf(" ");
    }
    printf("}\n");
    return 0;
}