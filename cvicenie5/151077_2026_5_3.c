#include<stdio.h>
#include<math.h>

int kvadraticka_rovnica(int *a, int *b, int *c, float *prvy, float *druhy) {
    int pocet = 0;
    int A = *a;
    int B = *b;
    int C = *c;
    float Dsqr = sqrt(B*B - 4*A*C);
    if (isnan(Dsqr)) {
        return 0;
    }
    if (Dsqr == 0) {
        *prvy = -B / (2.0f*A);
        pocet = 1;
    }
    if (Dsqr > 0) {
        *prvy = (-1*B + Dsqr) / (2.0f*A);
        *druhy = (-1*B - Dsqr) / (2.0f*A);
        pocet = 2;
    }
    return pocet;
}

int main () {
    int a, b, c, pocet;
    float prvy = 0, druhy = 0;
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