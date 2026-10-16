#include <stdio.h>
#include <stdlib.h>

int main() {
    float x;
    FILE *file = fopen("nasobky.txt", "w");
    if (file == NULL) {
        return 1;
    }
    printf("Nacitajte realne cislo\n");
    scanf("%f", &x);
    for (int i = 1; i <= 10; i++) {
        fprintf(file, "%d * %.2f = %.2f\n", i, x, x * i);
    }
    return 0;
}