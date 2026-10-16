#include <stdio.h>
#include <stdlib.h>

long rezervne_cislo(long x) {
    /* I used memory allocation and pointers because they are very complicated for me and I wanted to understand
    it on a practical task*/
    while (1) {
        int *arr = NULL;
        int count = 0;
        long i = 1;
        do {
            count++;
            int*temp = realloc(arr, count*sizeof(int));
            if (temp == NULL){
                free(arr);
                return 0;
            }
            arr = temp;
            arr[count-1] = (x/i) % 10;
            i *=10;
        } while (x/i > 0);
        x = 0;
        for (int j = 0; j < count; j++) x = x * 10 + arr[j];
        free(arr);
        return x;
    }

}
int main() {
    long a;
    printf("Nacitujte cisla pri kazdy novy vstup: \n");
    while (1) {
        scanf("%ld", &a);
        if (a < 0) a = labs(a);
        printf("%ld\n", rezervne_cislo(a));
        if (a == rezervne_cislo(a)) printf("Cislo %d je palindromom\n", a);
        else printf("Cislo %d nie je palindrom\n", a);
    }
    return 0;
}