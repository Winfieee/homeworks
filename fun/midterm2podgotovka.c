#include <stdio.h>

int main() {
    int i;
    scanf("%d", &i);
    for (int j = 0; j<i; j++) {
        print("%d\n", j);
    }
    return 0;
}