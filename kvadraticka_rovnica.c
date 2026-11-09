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
        return pocet;
    }
    Dsqr = sqrt(D);
    *prvy = (-B + Dsqr) / (2.0f*A);
    *druhy = (-B - Dsqr) / (2.0f*A);
    if (D == 0) {
        pocet = 1;
    } else {
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
    pocet = kvadraticka_rovnica(&a, &b, &c, &prvy, &druhy);
    if (pocet == 0) {
        printf("Pocet korenov kvadratickej rovnice je: %d\n", pocet);
    } else if (pocet == 1) {
        printf("Pocet korenov kvadratickej rovnice je: %d\nKoren ma hodnotu %.5f", pocet, prvy);
    } else {
        printf("Pocet korenov kvadratickej rovnice je: %d\nPrvy koren ma hodnotu %.5f\nDruhy koren ma "
            "hodnotu %.5f", pocet, prvy, druhy);
    }
    return 0;
}
