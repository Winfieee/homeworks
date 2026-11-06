#include<stdio.h>
#include<stdlib.h>
#include<string.h> //strlen, strcpy, strcmp - pre retazce v dynamickych poliach

/* V2: ako v1, ale pribudli dynamicke polia (n, v 2, q, w, e).
   Struktury sa nesmu pouzit, preto kazdy zaznam ulozim ako JEDEN retazec, polozky oddelim znakom '#'.
   z_pole (zoznamCK.txt):  "IB1234#Jozko#Mrkvicka#20101980#A35#2"
   c_pole (checkin1.txt):  "IB1234#A35#2#25.20#18.15"  (tak ako je v subore)
   Takze pre kazdy subor mam jedno pole retazcov (char **) a pocet zaznamov (int). */

void uvolni(char ***pole, int *pocet) { //uvolnim kazdy retazec a potom samotne pole
    if (*pole != NULL) {
        for (int i = 0; i < *pocet; i++) {
            free((*pole)[i]);
        }
        free(*pole);
    }
    *pole = NULL;
    *pocet = 0;
}

void odstran_enter(char *buffer) { //fgets necha na konci '\n' (alebo "\r\n"), ten nechcem v poli
    int dlzka = strlen(buffer);
    while (dlzka > 0 && (buffer[dlzka-1] == '\n' || buffer[dlzka-1] == '\r')) {
        buffer[dlzka-1] = '\0';
        dlzka--;
    }
}

char *kopia(char *retazec) { //malloc presne tolko bajtov kolko treba (+1 pre '\0')
    char *novy = malloc(strlen(retazec) + 1);
    if (novy == NULL) return NULL;
    strcpy(novy, retazec);
    return novy;
}

void v(FILE **zoznam, FILE **checkin, char **z_pole, int z_pocet, char **c_pole, int c_pocet, int polia) {
    char buffer[100]; //v1 malo 27, ked bol riadok dlhsi fgets ho rozdelil na 2 casti a riadky sa posunuli
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
        rewind(*zoznam);
        while (fgets(buffer, sizeof(buffer), *zoznam) != NULL) {
            odstran_enter(buffer);
            if (buffer[0] == '\0') continue; //"(môže byť aj prázdny riadok)" - prazdne riadky preskocim
            if (buffer[0] == '#') { /*novy format: kazdy zaznam zacina '#', takze tu zacinam pocitat od 0
                                     (v1 resetovalo az na prazdnom riadku, ten tam ale byt nemusi)*/
                riadok = 0;
                continue;
            }
            riadok++; //1 = let, 2 = meno, 3 = priezvisko, 4 = datum, 5 = sedadlo, 6 = batozina
            if (riadok == 1) {
                printf("Označenie letu: %s\n", buffer);
            }
            if (riadok == 2) {
                sscanf(buffer, "%15s", meno); //%15s aby som neprepisal pamat za polom meno
            }
            if (riadok == 3) {
                sscanf(buffer, "%25s", priezvesk);
            }
            if (riadok == 4) {
                int d = strlen(buffer); //rok su posledne 4 cislice datumu DDMMRRRR
                vek = 2026 - ((buffer[d-4]-'0') * 1000 + (buffer[d-3]-'0') * 100 + (buffer[d-2]-'0') * 10
                    + (buffer[d-1]-'0'));
                printf("Meno a Priezvisko [vek]: %s %s [%d]\n", meno, priezvesk, vek);
            }
            if (riadok == 5) {
                printf("Označenie sedadla: %s\n\n", buffer);
            }
        }
    }
    else if (which_v == 2) {
        /*po aktivovaní program zistí, či dynamické polia boli naplnené (tj. príkaz n už bol aktivovaný).
          Ak polia ešte neboli naplnené, program vypíše správu „V2: Nenaplnene polia.“*/
        if (polia == 0) {
            printf("V2: Nenaplnene polia.\n");
            return;
        }
        for (int i = 0; i < z_pocet; i++) {
            char let[10], meno2[16], priezvisko[26], datum[10], sedadlo[5];
            int batozina;
            /* %[^#] = citaj vsetko az po znak '#' (bez neho), potom '#' preskocim */
            sscanf(z_pole[i], "%9[^#]#%15[^#]#%25[^#]#%9[^#]#%4[^#]#%d", let, meno2, priezvisko, datum,
                sedadlo, &batozina);
            int d = strlen(datum);
            vek = 2026 - ((datum[d-4]-'0') * 1000 + (datum[d-3]-'0') * 100 + (datum[d-2]-'0') * 10
                + (datum[d-1]-'0'));

            int najdeny = -1; //index zaznamu v c_pole s rovnakym letom aj sedadlom, -1 = nie je
            for (int j = 0; j < c_pocet; j++) {
                char c_let[10], c_sedadlo[5];
                sscanf(c_pole[j], "%9[^#]#%4[^#]", c_let, c_sedadlo);
                if (strcmp(c_let, let) == 0 && strcmp(c_sedadlo, sedadlo) == 0) {
                    najdeny = j;
                    break;
                }
            }

            printf("Oznacenie letu: %s\n", let);
            printf("Meno a Priezvisko [vek]: %s %s [%d]\n", meno2, priezvisko, vek);
            printf("Oznacenie sedadla: %c %s\n", sedadlo[0], &sedadlo[1]); //"A35" -> "A 35"
            if (najdeny == -1) {
                printf("Status: false\n");
                printf("Pocet batoziny: %d / 0\n\n", batozina);
            }
            else {
                char c_let[10], c_sedadlo[5];
                int c_batozina;
                sscanf(c_pole[najdeny], "%9[^#]#%4[^#]#%d", c_let, c_sedadlo, &c_batozina);
                printf("Status: true\n");
                printf("Pocet batoziny: %d / %d ", batozina, c_batozina);
                /* vahy su za 3. znakom '#': IB1234#A35#2#25.20#18.15
                   prejdem retazec a za kazdym '#' od tretieho precitam jedno realne cislo */
                int pocet_hashov = 0;
                int prva = 1; //pred prvou vahou nedavam ciarku
                for (int k = 0; c_pole[najdeny][k] != '\0'; k++) {
                    if (c_pole[najdeny][k] == '#') {
                        pocet_hashov++;
                        float vaha;
                        if (pocet_hashov >= 3 && sscanf(&c_pole[najdeny][k+1], "%f", &vaha) == 1) {
                            if (prva == 0) printf(",");
                            printf("[%.2f]", vaha);
                            prva = 0;
                        }
                    }
                }
                printf("\n\n");
            }
        }
    }
    else {
        printf("V: Nespravna volba vypisu.\n"); /*iné - program vypíše správu „V: Nespravna volba vypisu.“
        Správa je nasledovaná znakom konca riadku a program pokračuje v načítavaní ďalších príkazov.  */
        return;
    }
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

void n(FILE **zoznam, FILE **checkin, char ***z_pole, int *z_pocet, char ***c_pole, int *c_pocet, int *polia) {
    /*Ak aspoň jeden zo súborov nie je otvorený (t.j. ešte nebol vykonaný príkaz ‘v 1’), táto voľba nič
      nezmení a vypíše správu „N: Neotvoreny subor.“*/
    if (*zoznam == NULL || *checkin == NULL) {
        printf("N: Neotvoreny subor.\n");
        return;
    }
    //Ak už boli polia predtým vytvorené, sú najprv korektne dealokované a potom sa vytvoria nové.
    uvolni(z_pole, z_pocet);
    uvolni(c_pole, c_pocet);

    char buffer[256];
    int pocet_z = 0, pocet_c = 0;
    //1. prechod: spočíta počet záznamov v jednotlivých txt súboroch
    rewind(*zoznam);
    while (fgets(buffer, sizeof(buffer), *zoznam) != NULL) {
        if (buffer[0] == '#') pocet_z++; //kazdy zaznam zacina '#'
    }
    rewind(*checkin);
    while (fgets(buffer, sizeof(buffer), *checkin) != NULL) {
        odstran_enter(buffer);
        if (buffer[0] != '\0') pocet_c++; //jeden neprazdny riadok = jeden zaznam
    }

    //dynamicky vytvorí polia podľa počtu záznamov (malloc)
    *z_pole = malloc(pocet_z * sizeof(char *));
    *c_pole = malloc(pocet_c * sizeof(char *));
    if ((pocet_z > 0 && *z_pole == NULL) || (pocet_c > 0 && *c_pole == NULL)) {
        free(*z_pole);
        free(*c_pole);
        *z_pole = NULL;
        *c_pole = NULL;
        return;
    }

    //2. prechod: zapíše jednotlivé záznamy v takom poradí, v akom sú v textovom súbore
    char let[10], meno[16], priezvisko[26], datum[10], sedadlo[5], batozina[3];
    int riadok = 0;
    rewind(*zoznam);
    while (fgets(buffer, sizeof(buffer), *zoznam) != NULL && *z_pocet < pocet_z) {
        odstran_enter(buffer);
        if (buffer[0] == '\0') continue;
        if (buffer[0] == '#') {
            riadok = 0;
            continue;
        }
        riadok++; //rovnake cislovanie ako vo v(): 1 let ... 6 batozina
        if (riadok == 1) sscanf(buffer, "%9s", let);
        if (riadok == 2) sscanf(buffer, "%15s", meno);
        if (riadok == 3) sscanf(buffer, "%25s", priezvisko);
        if (riadok == 4) sscanf(buffer, "%9s", datum);
        if (riadok == 5) sscanf(buffer, "%4s", sedadlo);
        if (riadok == 6) { //posledna polozka -> mam cely zaznam, spojim ho do jedneho retazca
            sscanf(buffer, "%2s", batozina);
            char zaznam[100];
            sprintf(zaznam, "%s#%s#%s#%s#%s#%s", let, meno, priezvisko, datum, sedadlo, batozina);
            (*z_pole)[*z_pocet] = kopia(zaznam);
            (*z_pocet)++;
        }
    }
    rewind(*checkin);
    while (fgets(buffer, sizeof(buffer), *checkin) != NULL && *c_pocet < pocet_c) {
        odstran_enter(buffer);
        if (buffer[0] == '\0') continue;
        (*c_pole)[*c_pocet] = kopia(buffer); //riadok checkinu ulozim presne tak ako je
        (*c_pocet)++;
    }
    *polia = 1; //Pri tejto voľbe program negeneruje žiaden výstup.
}

void q(char ***z_pole, int *z_pocet, int polia) {
    int y;
    scanf("%d", &y);
    char let[10], meno[16], priezvisko[26], datum[10], sedadlo[5];
    int batozina;
    //Dáta sa budú načítavať z klávesnice vo formáte súboru zoznamCK.txt (bez '#')
    scanf("%9s %15s %25s %9s %4s %d", let, meno, priezvisko, datum, sedadlo, &batozina);
    if (polia == 0) { //data precitam aj tak, aby nezostali v scanf a neboli brane ako prikazy
        printf("Q: Polia nie su vytvorene.\n");
        return;
    }
    //Y=1 reprezentuje pozíciu pole[0]. Ak je Y väčšie ako počet záznamov, záznam sa pridá na koniec poľa.
    int pozicia = y - 1;
    if (pozicia > *z_pocet) pozicia = *z_pocet;
    if (pozicia < 0) pozicia = 0;

    char **temp = realloc(*z_pole, (*z_pocet + 1) * sizeof(char *)); //ako v 4_3: realloc cez temp
    if (temp == NULL) return; //stare pole zostalo cele
    *z_pole = temp;
    for (int i = *z_pocet; i > pozicia; i--) { //posuniem vsetko od pozicie o 1 doprava
        (*z_pole)[i] = (*z_pole)[i-1];
    }
    char zaznam[100];
    sprintf(zaznam, "%s#%s#%s#%s#%s#%d", let, meno, priezvisko, datum, sedadlo, batozina);
    (*z_pole)[pozicia] = kopia(zaznam);
    (*z_pocet)++;
}

void w(char ***z_pole, int *z_pocet, int polia) {
    char let[10];
    scanf("%9s", let);
    if (polia == 0) {
        printf("W: Polia nie su vytvorene.\n");
        return;
    }
    int vymazane = 0;
    int novy_pocet = 0;
    for (int i = 0; i < *z_pocet; i++) {
        char z_let[10];
        sscanf((*z_pole)[i], "%9[^#]", z_let);
        if (strcmp(z_let, let) == 0) { //tento let mazem
            free((*z_pole)[i]);
            vymazane++;
        }
        else { //tento nechavam, posuniem ho dopredu na miesto vymazanych
            (*z_pole)[novy_pocet] = (*z_pole)[i];
            novy_pocet++;
        }
    }
    *z_pocet = novy_pocet;
    //Dynamické polia udržujte tak, aby nezaberali miesto v pamäti pre nepotrebné záznamy.
    if (novy_pocet == 0) {
        free(*z_pole);
        *z_pole = NULL;
    }
    else {
        char **temp = realloc(*z_pole, novy_pocet * sizeof(char *));
        if (temp != NULL) *z_pole = temp;
    }
    printf("W: Vymazalo sa : %d zaznamov !\n", vymazane);
}

char **e(char **c_pole, int c_pocet, int polia) {
    char sedadlo[5];
    scanf("%4s", sedadlo);
    if (polia == 0) {
        printf("E: Polia nie su vytvorene.\n");
        return c_pole;
    }
    //zistí koľko batožiny sa odovzdalo pre dané sedadlo (moze byt viac zaznamov, napr. A15 je 2x)
    int spolu = 0;
    for (int i = 0; i < c_pocet; i++) {
        char c_let[10], c_sedadlo[5];
        int c_batozina;
        sscanf(c_pole[i], "%9[^#]#%4[^#]#%d", c_let, c_sedadlo, &c_batozina);
        if (strcmp(c_sedadlo, sedadlo) == 0) spolu += c_batozina;
    }
    //pre každú batožinu bude možné zadať novú váhu z klávesnice
    float *vahy = malloc((spolu + 1) * sizeof(float)); //+1 aby malloc(0) nikdy nebol
    if (vahy == NULL) return c_pole;
    printf("Zadaj %d vahy: ", spolu);
    for (int i = 0; i < spolu; i++) {
        scanf("%f", &vahy[i]);
    }
    //Program najprv vypíše pôvodný obsah poľa v tvare v akom je uložený v txt súbore...
    printf("\n");
    for (int i = 0; i < c_pocet; i++) {
        printf("%s\n", c_pole[i]);
    }
    //...zmenim zaznamy s tymto sedadlom: poskladam retazec znova s novymi vahami
    int index_vahy = 0;
    for (int i = 0; i < c_pocet; i++) {
        char c_let[10], c_sedadlo[5];
        int c_batozina;
        sscanf(c_pole[i], "%9[^#]#%4[^#]#%d", c_let, c_sedadlo, &c_batozina);
        if (strcmp(c_sedadlo, sedadlo) == 0) {
            char novy[256];
            int dlzka = sprintf(novy, "%s#%s#%d", c_let, c_sedadlo, c_batozina);
            for (int k = 0; k < c_batozina; k++) {
                dlzka += sprintf(novy + dlzka, "#%.2f", vahy[index_vahy]); //pridam na koniec retazca
                index_vahy++;
            }
            char *nova_kopia = kopia(novy);
            if (nova_kopia != NULL) {
                free(c_pole[i]); //stary retazec uz netreba
                c_pole[i] = nova_kopia;
            }
        }
    }
    free(vahy);
    //...a potom zmenený obsah poľa.
    printf("\n");
    for (int i = 0; i < c_pocet; i++) {
        printf("%s\n", c_pole[i]);
    }
    return c_pole; //Funkcia vracia zmenený obsah poľa naspäť do funkcie main.
}

int main() {
    char program;
    FILE *zoznam = NULL, *checking = NULL;
    char **z_pole = NULL, **c_pole = NULL; //dynamicke polia: zoznamCK.txt a checkin1.txt
    int z_pocet = 0, c_pocet = 0;
    int polia = 0; //0 = prikaz n este nebol, 1 = polia su vytvorene
    printf("Oberte fuknciu \n \nVstup v 1: informacia o letu.\nVstup v 2: vypis z dynamickych poli.\n"
           "Vstup h: histogram.\nVstup n: vytvorenie dynamickych poli.\nVstup q Y: pridanie zaznamu.\n"
           "Vstup w LET: vymazanie letu.\nVstup e SEDADLO: zmena vah batoziny.\nk - koniec\n");
    while (1) {
        if (scanf(" %c", &program) != 1) break; //koniec vstupu (EOF) - aby sa cyklus nezacyklil
        if (program == 'v') {
            v(&zoznam, &checking, z_pole, z_pocet, c_pole, c_pocet, polia);
        }
        else if (program == 'h') {
            h(&zoznam);
        }
        else if (program == 'n') {
            n(&zoznam, &checking, &z_pole, &z_pocet, &c_pole, &c_pocet, &polia);
        }
        else if (program == 'q') { //q je teraz pridanie zaznamu, koniec je preto k
            q(&z_pole, &z_pocet, polia);
        }
        else if (program == 'w') {
            w(&z_pole, &z_pocet, polia);
        }
        else if (program == 'e') {
            c_pole = e(c_pole, c_pocet, polia);
        }
        else if (program == 'k') {
            break;
        }
        else {
            printf("Neexistujúci program. Oberte : v, h, n, q, w, e, k\n");
        }
    }
    uvolni(&z_pole, &z_pocet); //pred koncom uvolnim vsetku dynamicku pamat
    uvolni(&c_pole, &c_pocet);
    if (zoznam != NULL) {
        fclose(zoznam);
    }
    if (checking != NULL) {
        fclose(checking);
    }
    return 0;
}
