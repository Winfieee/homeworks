#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *prvy_subor = fopen("prvy.txt","r");
    FILE *druhy_subor= fopen("druhy.txt","r");
    if (prvy_subor == NULL || druhy_subor == NULL) {
        printf("Subory su neotvorene\n");
        return 1;
    }

    int prvy_znak, druhy_znak;
    int pocet_roznych_znakov = 0, pocetznakysubor1 = 0, pocetznakysubor2 = 0;

    while ((prvy_znak = fgetc(prvy_subor)) + (druhy_znak = fgetc(druhy_subor)) != -2) {
        pocetznakysubor1 += (prvy_znak != EOF);
        pocetznakysubor2 += (druhy_znak != EOF);
        pocet_roznych_znakov += (prvy_znak != EOF && druhy_znak != EOF && prvy_znak != druhy_znak);
    }

    if (pocet_roznych_znakov == 0 && pocetznakysubor1 == pocetznakysubor2) {
        printf("Subory su identicke\n");
    }
    else {
        printf("Pocet roznych znakov: %d\n", pocet_roznych_znakov);
        if (pocetznakysubor1 != pocetznakysubor2) {
            printf("Jeden zo suborov je dlhsi o %d znakov\n", abs(pocetznakysubor1 - pocetznakysubor2));
        }
    }
    fclose(prvy_subor);
    fclose(druhy_subor);
    return 0;
}
