#include<stdio.h>

int zisti_prvocislo(int cislo) {
    if (cislo <= 1) return -1;
    for (int i=2; i<cislo; i++) {
        if (cislo % i == 0) return -1;
    }
    return 1;
}
int main() {
    int a,b, cislo;
    printf("Nacitajte 2 cele cisla:\n");
    scanf("%d %d",&a, &b);
    if (a>=b) {
        int temp = b;
        b = a;
        a = temp;
    }
    for (cislo=a; cislo<=b; cislo++) {
        if (zisti_prvocislo(cislo) == 1) printf("%d\n", cislo);
    }
    return 0;
}