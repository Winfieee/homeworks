#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void v1(FILE **zoznam, FILE **checkin) {
    char buffer[27];
    char meno[16]; //15 + 1 preto ze jeden byte pouzijem pre /0
    char priezvesk[26];
    int riadok = 0;
    int vek;
    { //po aktivovaní program zistí, či txt súbory už boli otvorené (všetky 2 txt súbory)
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


/* ===================== Pomocne funkcie pre 2. verziu ===================== */

// odstrani znaky konca riadku (\n, \r) z konca retazca
void orez(char *s) {
    int dlzka = (int) strlen(s);
    while (dlzka > 0 && (s[dlzka - 1] == '\n' || s[dlzka - 1] == '\r' || s[dlzka - 1] == ' ')) {
        s[--dlzka] = '\0';
    }
}

// vytvori dynamicku kopiu retazca (malloc presne na dlzku retazca + '\0')
char *kopia(const char *s) {
    char *nova = (char *) malloc(strlen(s) + 1);
    if (nova != NULL) {
        strcpy(nova, s);
    }
    return nova;
}

// korektne dealokuje vsetky dynamicke polia a nastavi ich na NULL
void uvolni_polia(char ***lety, char ***mena, char ***priezviska, char ***datumy, char ***sedadla,
                  int **batozina, int *pocet,
                  char ***c_lety, char ***c_sedadla, int **c_pocet, double ***c_vahy, int *c_zaznamy) {
    for (int i = 0; i < *pocet; i++) { //najprv uvolnime kazdy retazec samostatne
        free((*lety)[i]);
        free((*mena)[i]);
        free((*priezviska)[i]);
        free((*datumy)[i]);
        free((*sedadla)[i]);
    }
    free(*lety); free(*mena); free(*priezviska); free(*datumy); free(*sedadla); free(*batozina);
    *lety = *mena = *priezviska = *datumy = *sedadla = NULL;
    *batozina = NULL;
    for (int i = 0; i < *c_zaznamy; i++) {
        free((*c_lety)[i]);
        free((*c_sedadla)[i]);
        free((*c_vahy)[i]); //pole vah pre jeden checkin
    }
    free(*c_lety); free(*c_sedadla); free(*c_pocet); free(*c_vahy);
    *c_lety = *c_sedadla = NULL;
    *c_pocet = NULL;
    *c_vahy = NULL;
    *pocet = -1;     //-1 znamena: polia nie su vytvorene
    *c_zaznamy = -1;
}

/* ===================== n - vytvorenie dynamickych poli ===================== */
void n(FILE **zoznam, FILE **checkin,
       char ***lety, char ***mena, char ***priezviska, char ***datumy, char ***sedadla,
       int **batozina, int *pocet,
       char ***c_lety, char ***c_sedadla, int **c_pocet, double ***c_vahy, int *c_zaznamy) {
    char buffer[256];
    if (*zoznam == NULL || *checkin == NULL) { //subory este neboli otvorene prikazom v 1
        printf("N: Neotvoreny subor.\n");
        return;
    }
    if (*pocet >= 0) { //ak uz polia existuju, najprv ich dealokujeme
        uvolni_polia(lety, mena, priezviska, datumy, sedadla, batozina, pocet,
                     c_lety, c_sedadla, c_pocet, c_vahy, c_zaznamy);
    }

    // 1. spocitanie zaznamov v zoznamCK.txt (kazdy zaznam zacina riadkom "#")
    int pz = 0;
    rewind(*zoznam);
    while (fgets(buffer, sizeof(buffer), *zoznam) != NULL) {
        orez(buffer);
        if (buffer[0] == '#') {
            pz++;
        }
    }
    // 2. spocitanie zaznamov v checkin1.txt (kazdy neprazdny riadok je jeden zaznam)
    int pc = 0;
    rewind(*checkin);
    while (fgets(buffer, sizeof(buffer), *checkin) != NULL) {
        orez(buffer);
        if (buffer[0] != '\0') {
            pc++;
        }
    }

    // 3. dynamicka alokacia poli podla poctu zaznamov (+1 aby malloc nedostal 0)
    *lety = (char **) malloc((pz + 1) * sizeof(char *));
    *mena = (char **) malloc((pz + 1) * sizeof(char *));
    *priezviska = (char **) malloc((pz + 1) * sizeof(char *));
    *datumy = (char **) malloc((pz + 1) * sizeof(char *));
    *sedadla = (char **) malloc((pz + 1) * sizeof(char *));
    *batozina = (int *) malloc((pz + 1) * sizeof(int));
    *c_lety = (char **) malloc((pc + 1) * sizeof(char *));
    *c_sedadla = (char **) malloc((pc + 1) * sizeof(char *));
    *c_pocet = (int *) malloc((pc + 1) * sizeof(int));
    *c_vahy = (double **) malloc((pc + 1) * sizeof(double *));

    // 4. naplnenie poli zo zoznamCK.txt v poradi ako su v subore
    int i = -1;      //index aktualneho zaznamu
    int polozka = 0; //ktora polozka zaznamu sa cita (1 - let, 2 - meno, ... 6 - batozina)
    rewind(*zoznam);
    while (fgets(buffer, sizeof(buffer), *zoznam) != NULL && i < pz) {
        orez(buffer);
        if (buffer[0] == '\0') { //prazdne riadky preskakujeme
            continue;
        }
        if (buffer[0] == '#') { //zaciatok noveho zaznamu
            i++;
            polozka = 1;
            continue;
        }
        if (i < 0) {
            continue;
        }
        switch (polozka) {
            case 1: (*lety)[i] = kopia(buffer); break;
            case 2: (*mena)[i] = kopia(buffer); break;
            case 3: (*priezviska)[i] = kopia(buffer); break;
            case 4: (*datumy)[i] = kopia(buffer); break;
            case 5: (*sedadla)[i] = kopia(buffer); break;
            case 6: (*batozina)[i] = atoi(buffer); break;
            default: break;
        }
        polozka++;
    }
    *pocet = pz;

    // 5. naplnenie poli z checkin1.txt, format: LET#SEDADLO#POCET#VAHA#VAHA...
    i = 0;
    rewind(*checkin);
    while (fgets(buffer, sizeof(buffer), *checkin) != NULL && i < pc) {
        orez(buffer);
        if (buffer[0] == '\0') {
            continue;
        }
        char *cast = strtok(buffer, "#");
        (*c_lety)[i] = kopia(cast != NULL ? cast : "");
        cast = strtok(NULL, "#");
        (*c_sedadla)[i] = kopia(cast != NULL ? cast : "");
        cast = strtok(NULL, "#");
        (*c_pocet)[i] = (cast != NULL) ? atoi(cast) : 0;
        (*c_vahy)[i] = (double *) malloc(((*c_pocet)[i] + 1) * sizeof(double)); //pole vah pre dany checkin
        for (int j = 0; j < (*c_pocet)[i]; j++) {
            cast = strtok(NULL, "#");
            (*c_vahy)[i][j] = (cast != NULL) ? atof(cast) : 0.0;
        }
        i++;
    }
    *c_zaznamy = pc;
    //pri tejto volbe program negeneruje ziaden vystup
}

/* ===================== v 2 - vypis z dynamickych poli ===================== */
void v2(char **lety, char **mena, char **priezviska, char **datumy, char **sedadla, int *batozina, int pocet,
        char **c_lety, char **c_sedadla, int *c_pocet, double **c_vahy, int c_zaznamy) {
    if (pocet < 0) { //polia este neboli naplnene prikazom n
        printf("V2: Nenaplnene polia.\n");
        return;
    }
    for (int i = 0; i < pocet; i++) {
        int dlzka = (int) strlen(datumy[i]);
        int rok = (dlzka >= 4) ? atoi(datumy[i] + dlzka - 4) : 0; //rok = posledne 4 cislice datumu
        // hladame checkin pre rovnaky let a rovnake sedadlo
        int k = -1;
        for (int j = 0; j < c_zaznamy; j++) {
            if (strcmp(c_lety[j], lety[i]) == 0 && strcmp(c_sedadla[j], sedadla[i]) == 0) {
                k = j;
                break;
            }
        }
        printf("Oznacenie letu: %s\n", lety[i]);
        printf("Meno a Priezvisko [vek]: %s %s [%d]\n", mena[i], priezviska[i], 2026 - rok);
        printf("Oznacenie sedadla: %c %s\n", sedadla[i][0], sedadla[i] + 1); //rad (medzera) cislo
        printf("Status: %s\n", (k >= 0) ? "true" : "false");
        printf("Pocet batoziny: %d / %d", batozina[i], (k >= 0) ? c_pocet[k] : 0);
        if (k >= 0) {
            for (int j = 0; j < c_pocet[k]; j++) {
                printf("%s[%.2f]", (j == 0) ? " " : ",", c_vahy[k][j]); //vahy oddelene ciarkou
            }
        }
        printf("\n\n"); //zaznamy oddelene prazdnym riadkom
    }
}

/* ===================== q - pridanie zaznamu na poziciu Y ===================== */
void q(char ***lety, char ***mena, char ***priezviska, char ***datumy, char ***sedadla,
       int **batozina, int *pocet) {
    int y;
    char let[64], meno[64], priezvisko[64], datum[64], sedadlo[64];
    int bat;
    scanf("%d", &y);
    if (*pocet < 0) {
        printf("Q: Polia nie su vytvorene.\n");
        return;
    }
    scanf("%63s", let);
    if (strcmp(let, "#") == 0) { //ak pouzivatel zada aj znak # ako v subore, preskocime ho
        scanf("%63s", let);
    }
    scanf("%63s %63s %63s %63s %d", meno, priezvisko, datum, sedadlo, &bat);

    int poz = y - 1; //Y=1 reprezentuje poziciu pole[0]
    if (poz < 0) poz = 0;
    if (poz > *pocet) poz = *pocet; //Y vacsie ako pocet zaznamov -> pridanie na koniec

    int novy = *pocet + 1;
    // zvacsenie poli o jeden prvok
    *lety = (char **) realloc(*lety, novy * sizeof(char *));
    *mena = (char **) realloc(*mena, novy * sizeof(char *));
    *priezviska = (char **) realloc(*priezviska, novy * sizeof(char *));
    *datumy = (char **) realloc(*datumy, novy * sizeof(char *));
    *sedadla = (char **) realloc(*sedadla, novy * sizeof(char *));
    *batozina = (int *) realloc(*batozina, novy * sizeof(int));
    // posunutie zaznamov za poziciou o jedno doprava
    for (int i = *pocet; i > poz; i--) {
        (*lety)[i] = (*lety)[i - 1];
        (*mena)[i] = (*mena)[i - 1];
        (*priezviska)[i] = (*priezviska)[i - 1];
        (*datumy)[i] = (*datumy)[i - 1];
        (*sedadla)[i] = (*sedadla)[i - 1];
        (*batozina)[i] = (*batozina)[i - 1];
    }
    // zapis noveho zaznamu
    (*lety)[poz] = kopia(let);
    (*mena)[poz] = kopia(meno);
    (*priezviska)[poz] = kopia(priezvisko);
    (*datumy)[poz] = kopia(datum);
    (*sedadla)[poz] = kopia(sedadlo);
    (*batozina)[poz] = bat;
    *pocet = novy;
}

/* ===================== w - vymazanie zaznamov pre dany let ===================== */
void w(char ***lety, char ***mena, char ***priezviska, char ***datumy, char ***sedadla,
       int **batozina, int *pocet) {
    char let[64];
    scanf("%63s", let);
    if (*pocet < 0) {
        printf("W: Polia nie su vytvorene.\n");
        return;
    }
    int ostava = 0; //pocet zaznamov, ktore ostanu
    for (int i = 0; i < *pocet; i++) {
        if (strcmp((*lety)[i], let) == 0) { //zaznam pre dany let -> uvolnime jeho pamat
            free((*lety)[i]);
            free((*mena)[i]);
            free((*priezviska)[i]);
            free((*datumy)[i]);
            free((*sedadla)[i]);
        }
        else { //zaznam ponechame a posunieme ho dopredu
            (*lety)[ostava] = (*lety)[i];
            (*mena)[ostava] = (*mena)[i];
            (*priezviska)[ostava] = (*priezviska)[i];
            (*datumy)[ostava] = (*datumy)[i];
            (*sedadla)[ostava] = (*sedadla)[i];
            (*batozina)[ostava] = (*batozina)[i];
            ostava++;
        }
    }
    int vymazane = *pocet - ostava;
    // zmensenie poli, aby nezaberali miesto pre nepotrebne zaznamy (+1 aby realloc nedostal 0)
    *lety = (char **) realloc(*lety, (ostava + 1) * sizeof(char *));
    *mena = (char **) realloc(*mena, (ostava + 1) * sizeof(char *));
    *priezviska = (char **) realloc(*priezviska, (ostava + 1) * sizeof(char *));
    *datumy = (char **) realloc(*datumy, (ostava + 1) * sizeof(char *));
    *sedadla = (char **) realloc(*sedadla, (ostava + 1) * sizeof(char *));
    *batozina = (int *) realloc(*batozina, (ostava + 1) * sizeof(int));
    *pocet = ostava;
    printf("W: Vymazalo sa : %d zaznamov !\n", vymazane);
}

// vypise pole checkinov v tvare ako v txt subore
void vypis_checkin(char **c_lety, char **c_sedadla, int *c_pocet, double **c_vahy, int c_zaznamy) {
    for (int i = 0; i < c_zaznamy; i++) {
        printf("%s#%s#%d", c_lety[i], c_sedadla[i], c_pocet[i]);
        for (int j = 0; j < c_pocet[i]; j++) {
            printf("#%.2f", c_vahy[i][j]);
        }
        printf("\n");
    }
}

/* ===================== e - zmena vah batoziny pre dane sedadlo ===================== */
void e(char **c_lety, char **c_sedadla, int *c_pocet, double **c_vahy, int c_zaznamy) {
    char sedadlo[64];
    scanf("%63s", sedadlo);
    if (c_zaznamy < 0) {
        printf("E: Polia nie su vytvorene.\n");
        return;
    }
    // pre kazdy zaznam s danym sedadlom nacitame nove vahy (zatial do pomocneho pola)
    double **nove = (double **) malloc((c_zaznamy + 1) * sizeof(double *));
    for (int i = 0; i < c_zaznamy; i++) {
        nove[i] = NULL;
        if (strcmp(c_sedadla[i], sedadlo) == 0) {
            nove[i] = (double *) malloc((c_pocet[i] + 1) * sizeof(double));
            printf("Zadaj %d váhy: ", c_pocet[i]);
            for (int j = 0; j < c_pocet[i]; j++) {
                scanf("%lf", &nove[i][j]);
            }
        }
    }
    vypis_checkin(c_lety, c_sedadla, c_pocet, c_vahy, c_zaznamy); //povodny obsah pola
    printf("\n");
    // zapis novych vah priamo do pola (pole je predane cez smernik, zmena sa prejavi aj v main)
    for (int i = 0; i < c_zaznamy; i++) {
        if (nove[i] != NULL) {
            for (int j = 0; j < c_pocet[i]; j++) {
                c_vahy[i][j] = nove[i][j];
            }
            free(nove[i]);
        }
    }
    free(nove);
    vypis_checkin(c_lety, c_sedadla, c_pocet, c_vahy, c_zaznamy); //zmeneny obsah pola
}

int main() {
    char program;
    FILE *zoznam = NULL, *checking = NULL;
    // dynamicke polia pre zoznamCK.txt (bez struktur - kazda polozka ma vlastne pole)
    char **lety = NULL, **mena = NULL, **priezviska = NULL, **datumy = NULL, **sedadla = NULL;
    int *batozina = NULL;
    int pocet = -1; //-1 = polia nie su vytvorene
    // dynamicke polia pre checkin1.txt
    char **c_lety = NULL, **c_sedadla = NULL;
    int *c_pocet = NULL;
    double **c_vahy = NULL;
    int c_zaznamy = -1;

    while (scanf(" %c", &program) == 1) {
        if (program == 'v') {
            int which_v;
            scanf("%d", &which_v);
            if (which_v == 1) {
                v1(&zoznam, &checking);
            }
            else if (which_v == 2) {
                v2(lety, mena, priezviska, datumy, sedadla, batozina, pocet,
                   c_lety, c_sedadla, c_pocet, c_vahy, c_zaznamy);
            }
            else {
                printf("V: Nespravna volba vypisu.\n");
            }
        }
        else if (program == 'h') {
            h(&zoznam);
        }
        else if (program == 'n') {
            n(&zoznam, &checking, &lety, &mena, &priezviska, &datumy, &sedadla, &batozina, &pocet,
              &c_lety, &c_sedadla, &c_pocet, &c_vahy, &c_zaznamy);
        }
        else if (program == 'q') {
            q(&lety, &mena, &priezviska, &datumy, &sedadla, &batozina, &pocet);
        }
        else if (program == 'w') {
            w(&lety, &mena, &priezviska, &datumy, &sedadla, &batozina, &pocet);
        }
        else if (program == 'e') {
            e(c_lety, c_sedadla, c_pocet, c_vahy, c_zaznamy);
        }
        else if (program == 'k') { //koniec programu
            break;
        }
    }
    // uvolnenie pamate a zatvorenie suborov na konci programu
    if (pocet >= 0) {
        uvolni_polia(&lety, &mena, &priezviska, &datumy, &sedadla, &batozina, &pocet,
                     &c_lety, &c_sedadla, &c_pocet, &c_vahy, &c_zaznamy);
    }
    if (zoznam != NULL) {
        fclose(zoznam);
    }
    if (checking != NULL) {
        fclose(checking);
    }
    return 0;
}
