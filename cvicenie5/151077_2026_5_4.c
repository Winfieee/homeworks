#include <stdio.h>

void vymen_ukazovatele(int **pointer_a, int **pointer_b) {
    int *old_a = *pointer_a;
    *pointer_a = *pointer_b;
    *pointer_b = old_a;
}

int main () {
    int a = 10, b = 14;
    int *pointer_a = &a;
    int *pointer_b = &b;
    for (int i = 1; i <= 2; i++) {
        printf("p_a: %p %d\n", pointer_a, *pointer_a);
        printf("p_b: %p %d\n", pointer_b, *pointer_b);
        vymen_ukazovatele(&pointer_a, &pointer_b);
    }
    return 0;
}