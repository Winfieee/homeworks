#include<stdio.h>
#include<stdlib.h>

int main() {
    int n, pocet = 0;
    printf("Najitajte cislo 'n': \n");
    scanf("%d",&n);
    char *blok = (char *)malloc(n * sizeof(char));
    if (blok == NULL) {
        return 1;
    }

    printf("Najitajte standartny vstup: \n");
    for (int i = 0; i < n; i++) {
        if (i == 0) scanf(" %c",blok+i);
        else scanf("%c",blok+i);
    }

    for (int i = n-1; i>=0; i--) {
        printf("%c", *(blok+i));
    }
    printf("\n");

    free(blok);
    return 0;
}