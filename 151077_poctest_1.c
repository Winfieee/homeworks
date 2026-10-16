 #include <stdio.h>

int main(void) {
    int N, M, D, x=1, y=1, Z, a;
    float b;
    printf("Zadaj tri cisla [N, M, D]\n");
    scanf("%d %d %d", &N, &M, &D);
    while (1){
        if (N>M || D<=0) {
            printf("%d - Zadaj tri cisla [N, M, D]\n", x);
            scanf("%d %d %d", &N, &M, &D);
            x++;
        }
        else break;
    }
    while (1) {
        printf("Zadaj cislo z intervalu <%d,%d>\n", N, M);
        scanf("%d", &Z);
        float c = Z;
        float d = D;
        float b = c/d;
        a = Z/D;
        if (Z >N && Z <M && a==b) {
            printf("Nacitanije prebehlo uspesne, z intervalu <%d,%d> si vybral cislo %d delitelne cislom %d.\n", N, M, Z, D);
            break;
        }
        else {
            printf("%d - Zadaj cisla [N, M]\n", y);
            y++;
        }
    }

    while (1) {
        printf("Zadaj cislo [N, M]:\n");
        scanf("%d, %d", &N, &M);
        if (N>= 1 && N<=9 && M>=1 && M<=5) {
            break;
        }
    }
    for (int i = 4 ; i < N ; i--) {
        for (int j=0; j<N; j++) {
            printf(" ");
        } // ne vstihol :((((
    }

    return 0;
}