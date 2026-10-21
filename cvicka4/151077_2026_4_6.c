#include<stdio.h>

int main() {
    FILE *text = fopen("text.txt","r");
    if (text == NULL) {
        printf("Chyba otvorenia suboru 'text.txt'\n");
        return 1;
    }
    int ch;
    int pocet_medzier = 0;
    while ((ch = fgetc(text)) != EOF && ch != '*') {
        if (ch == 'x' || ch == 'X') printf("Precital som X\n");
        else if (ch == 'y' || ch == 'Y') printf("Precital som Y\n");
        else if (ch == '#' || ch == '$' || ch == '&') printf("Precital som Z\n");
        else if (ch == ' ') pocet_medzier++;
    }
    printf("Koniec\nPocet nacitanych medzier: %d\n", pocet_medzier);
    fclose(text);
    return 0;
}