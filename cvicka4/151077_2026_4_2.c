#include <stdio.h>

double tyzdenna_mzda(double h_mzda, double hod) {
    return h_mzda * hod;
}

int main() {
    int vstupy;
    printf("Nacitajte pocet vstupov:\n");
    scanf("%d", &vstupy);
    printf("Nacitajte hodinovu mzdu a pocet hodin %d-krat:\n", vstupy);
    for (int i = 0; i < vstupy; i++) {
        double a, b;
        scanf("%lf %lf", &a, &b);
        printf("Hod. mzda: %.2f Euro/hod, hodin: %.2f, spolu: %.2f Euro\n", a, b, tyzdenna_mzda(a,b));
    }
    return 0;
}