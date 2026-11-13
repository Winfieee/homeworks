#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *subor = NULL;
    subor = fopen("subor.txt", "r");
    if (subor == NULL) {
        return 0;
    }

    int velke[26] = {0};
    int male[26] = {0};
    char char_velke[26];
    int aktualny_znak;
    int posledny = '\n';
    int riadok = 1;

    for (int i = 0; i < 26; i++) {
        char_velke[i] = 'A' + i;
        printf("%c ", char_velke[i]);
    }
    printf("\n");

    while ((aktualny_znak = fgetc(subor)) != EOF) {
        posledny = aktualny_znak;
        if (aktualny_znak >= 'A' && aktualny_znak <= 'Z') {
            velke[aktualny_znak - 'A']++;
        }
        else if (aktualny_znak >= 'a' && aktualny_znak <= 'z') {
            male[aktualny_znak - 'a']++;
        }
        else if (aktualny_znak == '\n') {
            printf("%d", riadok);
            for (int i = 0; i < 26; i++) {
                printf(" %d", velke[i] + male[i]);
                velke[i] = 0;
                male[i] = 0;
            }
            printf("\n");
            riadok++;
        }
    }

    if (posledny != '\n') {
        printf("%d", riadok);
        for (int i = 0; i < 26; i++) {
            printf(" %d", velke[i] + male[i]);
        }
        printf("\n");
    }

    fclose(subor);
    return 0;
}