#include<stdio.h>
#include<stdlib.h>

void v(FILE **zoznam, FILE **checkin) {
    char buffer[27];
    char meno[16]; //15 + 1 preto ze jeden byte pouzijem pre /0
    char priezvesk[26];
    int riadok = 0;
    int vek;
    int which_v;
    scanf("%d", &which_v);
    if (which_v == 1) { //po aktivovaní program zistí, či txt súbory už boli otvorené (všetky 2 txt súbory)
        if (*zoznam == NULL) {
            *zoznam = fopen("zoznamCK.txt", "r"); //Ak súbory ešte neboli otvorené...
        }
        if (*checkin == NULL) {
            *checkin = fopen("checkin1.txt", "r"); //...program sa ich pokúsi otvoriť.
        }
        if (*zoznam == NULL || *checkin == NULL) {
            printf("V1: Neotvorene txt subory.\n"); //prípade, ak sa aspoň jeden txt súbor nepodarí otoriť
            return;                                       //program vypíše správu„V1: Neotvorene txt subory.“
        }
        else{
            rewind(*zoznam);
            while (fgets(buffer, sizeof(buffer), *zoznam) != NULL) {
                if (riadok % 7 == 1) { /*prva iteracia riadok = 0, scitam symbol "#". Formula pre premennu
                                    na iteracii cyklusu while napr. pre meno je 2+7n, pre priezvesko 3+7n...*/
                    printf("Označenie letu: %s", buffer);
                }
                if (riadok % 7 == 2) {
                    sscanf(buffer, "%s", meno);
                }
                if (riadok % 7 == 3) {
                    sscanf(buffer, "%s", priezvesk);
                }
                if (riadok % 7 == 4) {
                    vek = 2026 - ((buffer[4]-'0') * 1000 + (buffer[5]-'0') * 100 + (buffer[6]-'0') * 10
                        + (buffer[7]-'0'));
                    printf("Meno a Priezvisko [vek]: %s %s [%d]\n", meno, priezvesk, vek);
                }
                if (riadok % 7 == 5) {
                    printf("Označenie sedadla: %s\n", buffer);
                }
                riadok++;
                if (buffer[0] == '\n' || buffer[0] == '\0' || buffer[0] == '\r') {
                    /*Txt súbory budú obsahovať iba hodnoty, nie typy (názvy) položiek. Jednotlivé
                    záznamy budú v txt súbore oddelené prázdnym riadkom, tj. aj po poslednom
                    zázname sa bude nachádzať prázdny riadok - enter (vid. ukážka txt súboru vyššie). */
                    riadok = 0;
                }
            }
        }
    }
    else {
        printf("V: Nespravna volba vypisu.\n"); /*iné - program vypíše správu „V: Nespravna volba vypisu.“
        Správa je nasledovaná znakom konca riadku a program pokračuje v načítavaní ďalších príkazov.  */
        return;
    };
}

void h(FILE **zoznam) {
    if (*zoznam == NULL) {
        printf("H:Neotvoreny subor.\n");
        return;
    }
    else {
        rewind(*zoznam);
        int velke[26] = {0};
        int male[26] = {0};
        int cislo[10] = {0};
        char char_velke[26];//pretože pre každú číselnú hodnotu treba vybrať zodpovedajúce písmeno z abecedy
        char char_male[26];
        char char_cislo[10];
        int aktualny_znak;
        while ((aktualny_znak = fgetc(*zoznam)) != EOF) { //scitame sucit vsetkych jedinecnych pismen
            if (aktualny_znak >= 'A' && aktualny_znak <= 'Z') {
                velke[aktualny_znak - 'A']++;
            }
            else if (aktualny_znak >= 'a' && aktualny_znak <= 'z') {
                male[aktualny_znak - 'a']++;
            }
            else if (aktualny_znak >= '0' && aktualny_znak <= '9') {
                cislo[aktualny_znak - '0']++;
            }
        }
        for (int i = 0; i < 26; i++) { //uložme abecedu do poľa.
            char_velke[i] = 'A' + i;
            char_male[i] = 'a' + i;
        }
        for (int i = 0; i < 10; i++) {
            char_cislo[i] = '0' + i;
        }
        int temp_pocet; //pre bubble sort
        int temp_char;
        for (int i = 0; i < 26 - 1; i++) { //bubble sort velkych pismen
            for (int j = 0; j < 26 - i - 1; j++) {
                if (velke[j] < velke[j + 1]) {
                    temp_pocet = velke[j];
                    velke[j] = velke[j + 1];
                    velke[j + 1] = temp_pocet;
                    temp_char = char_velke[j];
                    char_velke[j] = char_velke[j+1];
                    char_velke[j+1] = temp_char;
                }
            }
        }
        for (int i = 0; i < 26 - 1; i++) { //bubble sort malych pismen
             for (int j = 0; j < 26 - i - 1; j++) {
                if (male[j] < male[j + 1]) {
                    temp_pocet = male[j];
                    male[j] = male[j + 1];
                    male[j + 1] = temp_pocet;
                    temp_char = char_male[j];
                    char_male[j] = char_male[j+1];
                    char_male[j+1] = temp_char;
                }
             }
        }
        for (int i = 0; i < 10 - 1; i++) { //bubble sort cisel
            for (int j = 0; j < 10 - i - 1; j++) {
                if (cislo[j] < cislo[j + 1]) {
                    temp_pocet = cislo[j];
                    cislo[j] = cislo[j + 1];
                    cislo[j + 1] = temp_pocet;
                    temp_char = char_cislo[j];
                    char_cislo[j] = char_cislo[j+1];
                    char_cislo[j+1] = temp_char;
                    }
                }
            }
        for (int i = 0; i < 26; i++) { //
            if (velke[i] > 0) {
                printf("%c : %d\n", char_velke[i], velke[i]);
            }
        }
        for (int i = 0; i < 26; i++) {
            if (male[i] > 0) {
                printf("%c : %d\n", char_male[i], male[i]);
            }
        }
        for (int i = 0; i < 10; i++) {
            if (cislo[i] > 0) {
                printf("%c : %d\n", char_cislo[i], cislo[i]);
            }
        }
        }
}

int main() {
    char program;
    FILE *zoznam = NULL, *checking = NULL;
    printf("Oberte fuknciu \n \nVstup v 1: informacia o letu.\nVstup h: histogram.\nq - quit\n");
    while (1) {
        scanf(" %c", &program);
        if (program == 'v') {
            v(&zoznam, &checking);
        }
        else if (program == 'h') {
            h(&zoznam);
        }
        else if (program == 'q') {
            break;
        }
        else {
            printf("Neexistujúci program. Oberte : h, v, q\n");
        }
    }
    if (zoznam != NULL) {
        fclose(zoznam);
    }
    if (checking != NULL) {
        fclose(checking);
    }
    return 0;
}