#include<stdio.h>
#include<math.h>

int kvadraticka_rovnica(int *a, int *b, int *c, float *prvy, float *druhy) {
    int A = *a;
    int B = *b;
    int C = *c;
    float D = (float)B*B - 4.0f*A*C;
    float Dsqr = 0;
    if (D < 0) {
        return 0;
    }
    Dsqr = sqrt(D);
    *prvy = (-B + Dsqr) / (2.0f*A);
    *druhy = (-B - Dsqr) / (2.0f*A);
    if (D == 0) {
        return 1;
    }
    return 2;
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
    pocet = kvadraticka_rovnica(&a, &b, &c, &prvy, &druhy);
    printf("Pocet korenov kvadratickej rovnice je: %d\nPrvy koren ma hodnotu %.5f\nDruhy koren ma "
        "hodnotu %.5f", pocet, prvy, druhy);
    return 0;
}
