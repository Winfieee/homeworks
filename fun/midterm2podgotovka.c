#include <stdio.h>

int main() {
    char *datumy[] = {"20101980", "18121983", "05031999", "20101980", "11072001"};
    int k = 2, n = 5;
    int hist[10] = {0};
    for (int i = 0; i < n; i += k) {
        for (int j = 0; datumy[i][j] != '\0'; j ++) {
            hist[datumy[i][j]-'0']++;
        }
    }
    //и дальше копипаста выводим гистограмму
    return 0;
}