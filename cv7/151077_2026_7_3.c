#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char a[50] = "Cauko";
    char b[50];
    int n;

    printf("strlen: %d\n", (int)strlen(a));

    strcpy(b, a);
    printf("strcpy: %s\n", b);

    strcat(b, " svet");
    printf("strcat: %s\n", b);

    printf("strcmp: %d\n", strcmp(a, b));

    printf("Nacitajte vlastne pole retazcov:\n");
    scanf("%d", &n);
    getchar();

    char **pole = malloc(sizeof(char *) * n);

    for (int i = 0; i < n; i++) {
        int dlzka = 0;
        char c;
        pole[i] = malloc(1);
        while ((c = getchar()) != '\n') {
            pole[i] = realloc(pole[i], dlzka +2);
            pole[i][dlzka] = c;
            dlzka++;
        }
        pole[i][dlzka] = '\0';
    }

    for (int i = 0; i < n; i++) printf("%s\n", pole[i]);

    for (int i = 0; i < n; i++) free(pole[i]);
    free(pole);
}