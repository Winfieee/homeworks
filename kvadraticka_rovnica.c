#include<stdio.h>
#include<math.h>

int kvadraticka_rovnica(int *a, int *b, int *c, float *prvy, float *druhy) {
    int pocet = 0;
    float D = 0;
    float Dsqr = 0;
    int A = *a;
    int B = *b;
    int C = *c;
    D = (float)B*B - 4.0f*A*C;
    if (D < 0) {
        pocet = 0;
    }
    if (D == 0) {
        *prvy = -B / (2.0f*A);
        pocet = 1;
    }
    if (D > 0) {
        Dsqr = sqrt(D);
        *prvy = (-B + Dsqr) / (2.0f*A);
        *druhy = (-B - Dsqr) / (2.0f*A);
        pocet = 2;
    }
    return pocet;
}

int main () {
    int a, b, c;
    int pocet;
    float prvy = 0;
    float druhy = 0;
    scanf("%d %d %d",&a,&b,&c);
    while (a == 0) {
        printf("Zadajte iny koeficient a\n");
        scanf("%d",&a);
    }
    printf("Pocet korenov kvadratickej rovnice je: %d\n", pocet = kvadraticka_rovnica(&a, &b, &c, &prvy, &druhy));
    if (pocet == 1) {
        printf("Koren ma hodnotu %.5f", prvy);
    }
    if (pocet == 2) {
        printf("Prvy koren ma hodnotu %.5f\nDruhy koren ma hodnotu %.5f", prvy, druhy);
    }
    return 0;
}
