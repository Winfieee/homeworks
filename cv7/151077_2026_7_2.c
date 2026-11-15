#include <stdio.h>

int main () {
    int n;
    printf("Nacitujte nezaporne cele cisla: \n");
    while (scanf("%d", &n) == 1) {
        char abeceda[27];
        for (int i = 0; i < 26; i++) {
            abeceda[i] = 'a' + i;
        }
        abeceda[26] = '\0';

        for (int i = 0; i<n; i++) {
            int index = i*n;
            if ((i+1) % 2 == 0) {
                for (int j = n - 1; j >= 0; j--) {
                    printf("%c ", abeceda[(index + j) % 26]);
                }
            }
            else {
                for (int j = 0; j<n; j++) {
                    printf("%c ", abeceda[(index + j) % 26]);
                }
            }
            printf("\n");
        }

    }
    return 0;
}