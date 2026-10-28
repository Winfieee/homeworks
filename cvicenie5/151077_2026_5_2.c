#include<stdio.h>
int maximum(int *a, int *b) {
    if (*a > *b) return *a;
    else return *b;
}

int main() {
    int a, b;
    printf("Nacitajte 2 celych cisla\n");
    scanf("%d %d",&a,&b);
    printf("Maxiumum: %d\n", maximum(&a, &b));
}