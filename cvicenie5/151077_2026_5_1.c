#include<stdio.h>

void nacitaj(float *a, float *b) {
    printf("Nacitajte dva realnych cisla, ktore oznacaju dlzky stran obdlznika\n");
    scanf("%f %f", a, b);
}

void vypocitaj(float a, float b, float *obsah, float *obvod) {
    *obsah = a*b;
    *obvod = 2*a + 2*b;
}
int main() {
    float a, b, obsah, obvod;
    nacitaj(&a, &b);
    vypocitaj(a, b, &obsah, &obvod);
    printf("Obsah: %.3f\n", obsah);
    printf("Obvod: %.3f\n", obvod);
}