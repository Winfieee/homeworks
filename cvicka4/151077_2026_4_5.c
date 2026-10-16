#include <stdio.h>
#include <stdlib.h>

int main() {
    char x;
    FILE *fileread = fopen("novy.txt", "w");
    FILE *filewrite = fopen("znak.txt", "rb");
    if (fileread == NULL || filewrite == NULL) return 1;



    printf("Nacitajte 's' kak chcete skopirovat obsah suboru znak.txt\n");
    scanf("%c", &x);
    for (int i = 1; i <= 10; i++) {
        fprintf(fileread, "%d * %.2f = %.2f\n", i, x, x * i);
    }
    return 0;
}