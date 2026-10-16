#include <stdio.h>
#include <stdlib.h>

int main() {
    char x, buffer[256];
    FILE *fw = fopen("novy.txt", "w"), *fr = fopen("znak.txt", "r");
    if (fr == NULL || fw == NULL) return 1;

    printf("Nacitajte 's', ak chcete skopirovat obsah suboru znak.txt, iny symbol ak v console\n");
    scanf("%c", &x);
    if (x == 's') {
        for (int i = 1; fgets(buffer, sizeof(buffer), fr) != NULL; i++) {
            fputs(buffer, fw);
        }
    }
    else {
        for (int i = 1; fgets(buffer, sizeof(buffer), fr) != NULL; i++) {
            printf("%s", buffer);
        }
    }
    fclose(fw);
    fclose(fr);
    return 0;
}