#include<stdio.h>
#include<stdlib.h>
#include<string.h> //strlen, strcpy, strcmp - pre retazce v dynamickych poliach

/* V2: ako v1 + dynamicke polia (v 2, n, q, w, e).
   Struktury sa nesmu pouzit, preto mam pre kazdu polozku samostatne pole (ako velke[] a char_velke[] v h).
   Zaznam cislo i je vo vsetkych poliach na rovnakom indexe i.
   zoznamCK.txt: let[i], meno[i], priezvisko[i], datum[i], sedadlo[i], batozina[i]
   checkin1.txt: c_let[i], c_sedadlo[i], c_batozina[i], c_vahy[i][0..c_batozina[i]-1] */

void v(FILE **zoznam, FILE **checkin,
       char **let, char **meno_p, char **priezvisko, char **datum, char **sedadlo, int *batozina, int z_pocet,
       char **c_let, char **c_sedadlo, int *c_batozina, float **c_vahy, int c_pocet, int polia) {
    //V2: pridane parametre s dynamickymi poliami - pouziju sa vo vetve which_v == 2
    //(meno_p, lebo premenna meno[16] uz je nizsie z v1)
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
    else if (which_v == 2) { //V2: pridane - vypis z dynamickych poli
        /*po aktivovaní program zistí, či dynamické polia boli naplnené (tj. príkaz n už bol aktivovaný).
          Ak polia ešte neboli naplnené, program vypíše správu „V2: Nenaplnene polia.“*/
        if (polia == 0) {
            printf("V2: Nenaplnene polia.\n");
            return;
        }
        for (int i = 0; i < z_pocet; i++) {
            int d = strlen(datum[i]); //vek - posledne 4 cislice datumu DDMMRRRR
            vek = 2026 - ((datum[i][d-4]-'0') * 1000 + (datum[i][d-3]-'0') * 100 + (datum[i][d-2]-'0') * 10
                + (datum[i][d-1]-'0'));

            int najdeny = -1; //index v checkin poliach s rovnakym letom aj sedadlom, -1 = checkin nebol
            for (int j = 0; j < c_pocet; j++) {
                if (strcmp(c_let[j], let[i]) == 0 && strcmp(c_sedadlo[j], sedadlo[i]) == 0) {
                    najdeny = j;
                    break;
                }
            }

            printf("Oznacenie letu: %s\n", let[i]);
            printf("Meno a Priezvisko [vek]: %s %s [%d]\n", meno_p[i], priezvisko[i], vek);
            printf("Oznacenie sedadla: %c %s\n", sedadlo[i][0], sedadlo[i] + 1); //"A35" -> "A 35"
            if (najdeny == -1) {
                printf("Status: false\n");
                printf("Pocet batoziny: %d / 0\n", batozina[i]);
            }
            else {
                printf("Status: true\n");
                printf("Pocet batoziny: %d / %d", batozina[i], c_batozina[najdeny]);
                for (int k = 0; k < c_batozina[najdeny]; k++) {
                    if (k == 0) printf(" "); //medzera iba ked su nejake vahy (pri 0 kusoch nie)
                    if (k > 0) printf(","); //pri viacerých batožinách budú zátvorky oddelené čiarkou
                    printf("[%.2f]", c_vahy[najdeny][k]);
                }
                printf("\n");
            }
            printf("\n"); //(prázdny riadok)
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

void n(FILE **zoznam, FILE **checkin,
       char ***let, char ***meno, char ***priezvisko, char ***datum, char ***sedadlo, int **batozina, int *z_pocet,
       char ***c_let, char ***c_sedadlo, int **c_batozina, float ***c_vahy, int *c_pocet, int *polia) {
    /*Ak aspoň jeden zo súborov nie je otvorený (t.j. ešte nebol vykonaný príkaz ‘v 1’), táto voľba nič
      nezmení a vypíše správu „N: Neotvoreny subor.“*/
    if (*zoznam == NULL || *checkin == NULL) {
        printf("N: Neotvoreny subor.\n");
        return;
    }
    //Ak už boli polia predtým vytvorené, sú najprv korektne dealokované a potom sa vytvoria nové.
    if (*polia == 1) {
        for (int i = 0; i < *z_pocet; i++) { //najprv retazce, ktore su v poli...
            free((*let)[i]);
            free((*meno)[i]);
            free((*priezvisko)[i]);
            free((*datum)[i]);
            free((*sedadlo)[i]);
        }
        free(*let); //...a az potom samotne pole (naopak by som adresy retazcov stratil)
        free(*meno);
        free(*priezvisko);
        free(*datum);
        free(*sedadlo);
        free(*batozina);
        for (int i = 0; i < *c_pocet; i++) {
            free((*c_let)[i]);
            free((*c_sedadlo)[i]);
            free((*c_vahy)[i]);
        }
        free(*c_let);
        free(*c_sedadlo);
        free(*c_batozina);
        free(*c_vahy);
        *z_pocet = 0;
        *c_pocet = 0;
        *polia = 0;
    }

    char buffer[256];
    int pocet_z = 0, pocet_c = 0;
    //1. prechod: spočíta počet záznamov v jednotlivých txt súboroch
    /*riadok so zaznamom hladam cez strchr (najde znak '#' v retazci) a nie buffer[0] == '#',
      lebo subor ulozeny v Notepade moze mat na zaciatku 3 neviditelne bajty (BOM) pred prvym '#' */
    rewind(*zoznam);
    while (fgets(buffer, sizeof(buffer), *zoznam) != NULL) {
        if (strchr(buffer, '#') != NULL) pocet_z++; //kazdy zaznam zacina riadkom s '#'
    }
    rewind(*checkin);
    while (fgets(buffer, sizeof(buffer), *checkin) != NULL) {
        if (strchr(buffer, '#') != NULL) pocet_c++; //kazdy zaznam checkinu obsahuje '#', prazdny riadok nie
    }

    //dynamicky vytvorí polia pre jednotlivé položky podľa počtu záznamov (malloc)
    *let = malloc(pocet_z * sizeof(char *));
    *meno = malloc(pocet_z * sizeof(char *));
    *priezvisko = malloc(pocet_z * sizeof(char *));
    *datum = malloc(pocet_z * sizeof(char *));
    *sedadlo = malloc(pocet_z * sizeof(char *));
    *batozina = malloc(pocet_z * sizeof(int));
    *c_let = malloc(pocet_c * sizeof(char *));
    *c_sedadlo = malloc(pocet_c * sizeof(char *));
    *c_batozina = malloc(pocet_c * sizeof(int));
    *c_vahy = malloc(pocet_c * sizeof(float *));

    //2. prechod: do jednotlivých polí sa zapíšu jednotlivé záznamy v takom poradí, v akom sú v textovom súbore
    char slovo[30]; //sem si precitam polozku, potom ju skopirujem do pola
    int riadok = 0;
    int i = -1; //index zaznamu, pri prvom '#' bude 0
    rewind(*zoznam);
    while (fgets(buffer, sizeof(buffer), *zoznam) != NULL) {
        if (strchr(buffer, '#') != NULL) { //novy zaznam
            i++;
            riadok = 0;
            continue;
        }
        if (sscanf(buffer, "%s", slovo) != 1) {
            continue; //prazdny riadok (alebo iba medzery) preskocim - sscanf nenasiel ziadne slovo
        }
        if (i < 0) continue; //nieco pred prvym '#' - to nie je zaznam
        riadok++; //1 = let, 2 = meno, 3 = priezvisko, 4 = datum, 5 = sedadlo, 6 = batozina
        if (riadok == 1) {
            (*let)[i] = malloc(strlen(slovo) + 1); //+1 pre '\0'
            strcpy((*let)[i], slovo);
        }
        if (riadok == 2) {
            (*meno)[i] = malloc(strlen(slovo) + 1);
            strcpy((*meno)[i], slovo);
        }
        if (riadok == 3) {
            (*priezvisko)[i] = malloc(strlen(slovo) + 1);
            strcpy((*priezvisko)[i], slovo);
        }
        if (riadok == 4) {
            (*datum)[i] = malloc(strlen(slovo) + 1);
            strcpy((*datum)[i], slovo);
        }
        if (riadok == 5) {
            (*sedadlo)[i] = malloc(strlen(slovo) + 1);
            strcpy((*sedadlo)[i], slovo);
        }
        if (riadok == 6) {
            sscanf(buffer, "%d", &(*batozina)[i]);
            *z_pocet = i + 1; //zaznam je cely
        }
    }

    //checkin1.txt: IB1234#A35#2#25.20#18.15
    i = 0;
    rewind(*checkin);
    while (fgets(buffer, sizeof(buffer), *checkin) != NULL) {
        if (strchr(buffer, '#') == NULL) {
            continue; //prazdny riadok (aj iba z medzier) - nie je to zaznam, rovnako ako pri pocitani
        }
        for (int k = 0; buffer[k] != '\0'; k++) { //'#' zmenim na medzeru, potom staci obycajny sscanf
            if (buffer[k] == '#') buffer[k] = ' ';
        }
        int zac = 0; //let zacina velkym pismenom - preskocim vsetko pred nim (napr. BOM na zaciatku suboru)
        while (buffer[zac] != '\0' && !(buffer[zac] >= 'A' && buffer[zac] <= 'Z')) {
            zac++;
        }
        char c_let_temp[10] = "", c_sedadlo_temp[5] = "";
        int pocet_kusov = 0;
        sscanf(&buffer[zac], "%s %s %d", c_let_temp, c_sedadlo_temp, &pocet_kusov);

        (*c_let)[i] = malloc(strlen(c_let_temp) + 1);
        strcpy((*c_let)[i], c_let_temp);
        (*c_sedadlo)[i] = malloc(strlen(c_sedadlo_temp) + 1);
        strcpy((*c_sedadlo)[i], c_sedadlo_temp);
        (*c_batozina)[i] = pocet_kusov;
        (*c_vahy)[i] = malloc(pocet_kusov * sizeof(float)); //kazdy zaznam ma svoje pole vah
        for (int k = 0; k < pocet_kusov; k++) {
            (*c_vahy)[i][k] = 0; //keby v riadku bolo menej vah ako kusov, nezostane tam smetie
        }

        //vahy su za 3. medzerou (predtym za 3. '#'): za kazdou medzerou od tretej precitam jedno cislo
        int medzery = 0;
        int index_vahy = 0;
        for (int k = zac; buffer[k] != '\0' && index_vahy < pocet_kusov; k++) {
            if (buffer[k] == ' ') {
                medzery++;
                if (medzery >= 3) {
                    sscanf(&buffer[k+1], "%f", &(*c_vahy)[i][index_vahy]);
                    index_vahy++;
                }
            }
        }
        i++;
    }
    *c_pocet = i;
    *polia = 1; //Pri tejto voľbe program negeneruje žiaden výstup.
}

void q(char ***let, char ***meno, char ***priezvisko, char ***datum, char ***sedadlo, int **batozina,
       int *z_pocet, int polia) {
    int y;
    char novy_let[10], nove_meno[16], nove_priezvisko[26], novy_datum[10], nove_sedadlo[5];
    int nova_batozina;
    scanf("%d", &y); //ako vo v(): najprv nacitam vstup, az potom kontrolujem
    scanf("%s %s %s %s %s %d", novy_let, nove_meno, nove_priezvisko, novy_datum, nove_sedadlo, &nova_batozina);
    //(keby som kontroloval skor, main by "IB1234", "Jana"... citala po pismenach ako prikazy)
    if (polia == 0) {
        printf("Q: Polia nie su vytvorene.\n");
        return;
    }
    //Y=1 reprezentuje pozíciu pole[0]. Ak je Y väčšie ako počet záznamov, záznam sa pridá na koniec poľa.
    int pozicia = y - 1;
    if (pozicia > *z_pocet) pozicia = *z_pocet;
    if (pozicia < 0) pozicia = 0;

    //kazde pole zvacsim o 1 miesto
    *let = realloc(*let, (*z_pocet + 1) * sizeof(char *));
    *meno = realloc(*meno, (*z_pocet + 1) * sizeof(char *));
    *priezvisko = realloc(*priezvisko, (*z_pocet + 1) * sizeof(char *));
    *datum = realloc(*datum, (*z_pocet + 1) * sizeof(char *));
    *sedadlo = realloc(*sedadlo, (*z_pocet + 1) * sizeof(char *));
    *batozina = realloc(*batozina, (*z_pocet + 1) * sizeof(int));

    //vsetko od pozicie posuniem o 1 doprava (od konca, aby som si nic neprepisal)
    for (int i = *z_pocet; i > pozicia; i--) {
        (*let)[i] = (*let)[i-1];
        (*meno)[i] = (*meno)[i-1];
        (*priezvisko)[i] = (*priezvisko)[i-1];
        (*datum)[i] = (*datum)[i-1];
        (*sedadlo)[i] = (*sedadlo)[i-1];
        (*batozina)[i] = (*batozina)[i-1];
    }

    //na uvolnene miesto dam novy zaznam
    (*let)[pozicia] = malloc(strlen(novy_let) + 1);
    strcpy((*let)[pozicia], novy_let);
    (*meno)[pozicia] = malloc(strlen(nove_meno) + 1);
    strcpy((*meno)[pozicia], nove_meno);
    (*priezvisko)[pozicia] = malloc(strlen(nove_priezvisko) + 1);
    strcpy((*priezvisko)[pozicia], nove_priezvisko);
    (*datum)[pozicia] = malloc(strlen(novy_datum) + 1);
    strcpy((*datum)[pozicia], novy_datum);
    (*sedadlo)[pozicia] = malloc(strlen(nove_sedadlo) + 1);
    strcpy((*sedadlo)[pozicia], nove_sedadlo);
    (*batozina)[pozicia] = nova_batozina;
    (*z_pocet)++;
}

void w(char ***let, char ***meno, char ***priezvisko, char ***datum, char ***sedadlo, int **batozina,
       int *z_pocet, int polia) {
    char hladany_let[10];
    scanf("%s", hladany_let); //najprv nacitam, potom kontrolujem (ako v q)
    if (polia == 0) {
        printf("W: Polia nie su vytvorene.\n");
        return;
    }
    int vymazane = 0;
    for (int i = 0; i < *z_pocet; i++) {
        if (strcmp((*let)[i], hladany_let) == 0) { //tento zaznam mazem
            free((*let)[i]);
            free((*meno)[i]);
            free((*priezvisko)[i]);
            free((*datum)[i]);
            free((*sedadlo)[i]);
            for (int j = i; j < *z_pocet - 1; j++) { //vsetko za nim posuniem o 1 dolava
                (*let)[j] = (*let)[j+1];
                (*meno)[j] = (*meno)[j+1];
                (*priezvisko)[j] = (*priezvisko)[j+1];
                (*datum)[j] = (*datum)[j+1];
                (*sedadlo)[j] = (*sedadlo)[j+1];
                (*batozina)[j] = (*batozina)[j+1];
            }
            (*z_pocet)--;
            vymazane++;
            i--; //na miesto i sa posunul dalsi zaznam, aj ten musim skontrolovat
        }
    }
    //Dynamické polia udržujte tak, aby nezaberali miesto v pamäti pre nepotrebné záznamy.
    if (*z_pocet == 0) { //nezostal ziadny zaznam - polia uplne uvolnim (realloc na 0 nie je presne definovany)
        free(*let);
        free(*meno);
        free(*priezvisko);
        free(*datum);
        free(*sedadlo);
        free(*batozina);
        *let = NULL;
        *meno = NULL;
        *priezvisko = NULL;
        *datum = NULL;
        *sedadlo = NULL;
        *batozina = NULL;
    }
    else { //inak ich zmensim na presny pocet zaznamov
        *let = realloc(*let, *z_pocet * sizeof(char *));
        *meno = realloc(*meno, *z_pocet * sizeof(char *));
        *priezvisko = realloc(*priezvisko, *z_pocet * sizeof(char *));
        *datum = realloc(*datum, *z_pocet * sizeof(char *));
        *sedadlo = realloc(*sedadlo, *z_pocet * sizeof(char *));
        *batozina = realloc(*batozina, *z_pocet * sizeof(int));
    }

    printf("W: Vymazalo sa : %d zaznamov !\n", vymazane);
}

float **e(char **c_let, char **c_sedadlo, int *c_batozina, float **c_vahy, int c_pocet, int polia) {
    char hladane_sedadlo[5];
    scanf("%s", hladane_sedadlo); //najprv nacitam, potom kontrolujem (ako v q)
    if (polia == 0) {
        printf("E: Polia nie su vytvorene.\n");
        return c_vahy;
    }
    //zistí koľko batožiny sa odovzdalo pre dané sedadlo (moze byt viac zaznamov, napr. A15 je 2x)
    int spolu = 0;
    for (int i = 0; i < c_pocet; i++) {
        if (strcmp(c_sedadlo[i], hladane_sedadlo) == 0) spolu += c_batozina[i];
    }
    //pre každú batožinu bude možné zadať novú váhu z klávesnice
    float *nove_vahy = malloc(spolu * sizeof(float));
    if (spolu > 0) { //ked take sedadlo nie je, nie je co zadavat
        printf("Zadaj %d váhy: ", spolu); //presne ako v ukazke (s diakritikou)
    }
    for (int i = 0; i < spolu; i++) {
        scanf("%f", &nove_vahy[i]);
    }

    //Program najprv vypíše pôvodný obsah poľa v tvare v akom je uložený v txt súbore...
    for (int i = 0; i < c_pocet; i++) {
        printf("%s#%s#%d", c_let[i], c_sedadlo[i], c_batozina[i]);
        for (int k = 0; k < c_batozina[i]; k++) {
            printf("#%.2f", c_vahy[i][k]);
        }
        printf("\n");
    }

    //zmenim vahy pri zaznamoch s tymto sedadlom
    int index_vahy = 0;
    for (int i = 0; i < c_pocet; i++) {
        if (strcmp(c_sedadlo[i], hladane_sedadlo) == 0) {
            for (int k = 0; k < c_batozina[i]; k++) {
                c_vahy[i][k] = nove_vahy[index_vahy];
                index_vahy++;
            }
        }
    }
    free(nove_vahy);

    //...a potom zmenený obsah poľa.
    printf("\n");
    for (int i = 0; i < c_pocet; i++) {
        printf("%s#%s#%d", c_let[i], c_sedadlo[i], c_batozina[i]);
        for (int k = 0; k < c_batozina[i]; k++) {
            printf("#%.2f", c_vahy[i][k]);
        }
        printf("\n");
    }
    return c_vahy; //Funkcia vracia zmenený obsah poľa naspäť do funkcie main.
}

int main() {
    char program;
    FILE *zoznam = NULL, *checking = NULL;
    //dynamicke polia pre zoznamCK.txt
    char **let = NULL, **meno = NULL, **priezvisko = NULL, **datum = NULL, **sedadlo = NULL;
    int *batozina = NULL;
    int z_pocet = 0;
    //dynamicke polia pre checkin1.txt
    char **c_let = NULL, **c_sedadlo = NULL;
    int *c_batozina = NULL;
    float **c_vahy = NULL;
    int c_pocet = 0;
    int polia = 0; //0 = prikaz n este nebol, 1 = polia su vytvorene

    printf("Oberte fuknciu \n \nVstup v 1: informacia o letu.\nVstup v 2: vypis z dynamickych poli.\n"
           "Vstup h: histogram.\nVstup n: vytvorenie dynamickych poli.\nVstup q Y: pridanie zaznamu.\n"
           "Vstup w LET: vymazanie letu.\nVstup e SEDADLO: zmena vah batoziny.\nk - koniec\n");
    while (1) {
        if (scanf(" %c", &program) != 1) break; //vstup skoncil bez k - inak by sa posledny prikaz opakoval donekonecna
        if (program == 'v') {
            v(&zoznam, &checking, let, meno, priezvisko, datum, sedadlo, batozina, z_pocet,
              c_let, c_sedadlo, c_batozina, c_vahy, c_pocet, polia);
        }
        else if (program == 'h') {
            h(&zoznam);
        }
        else if (program == 'n') {
            n(&zoznam, &checking, &let, &meno, &priezvisko, &datum, &sedadlo, &batozina, &z_pocet,
              &c_let, &c_sedadlo, &c_batozina, &c_vahy, &c_pocet, &polia);
        }
        else if (program == 'q') { //q je teraz pridanie zaznamu, koniec je preto k
            q(&let, &meno, &priezvisko, &datum, &sedadlo, &batozina, &z_pocet, polia);
        }
        else if (program == 'w') {
            w(&let, &meno, &priezvisko, &datum, &sedadlo, &batozina, &z_pocet, polia);
        }
        else if (program == 'e') {
            c_vahy = e(c_let, c_sedadlo, c_batozina, c_vahy, c_pocet, polia);
        }
        else if (program == 'k') {
            break;
        }
        else {
            printf("Neexistujúci program. Oberte : v, h, n, q, w, e, k\n");
        }
    }

    //pred koncom uvolnim vsetku dynamicku pamat (ako v n: najprv retazce, potom polia)
    if (polia == 1) {
        for (int i = 0; i < z_pocet; i++) {
            free(let[i]);
            free(meno[i]);
            free(priezvisko[i]);
            free(datum[i]);
            free(sedadlo[i]);
        }
        free(let);
        free(meno);
        free(priezvisko);
        free(datum);
        free(sedadlo);
        free(batozina);
        for (int i = 0; i < c_pocet; i++) {
            free(c_let[i]);
            free(c_sedadlo[i]);
            free(c_vahy[i]);
        }
        free(c_let);
        free(c_sedadlo);
        free(c_batozina);
        free(c_vahy);
    }
    if (zoznam != NULL) {
        fclose(zoznam);
    }
    if (checking != NULL) {
        fclose(checking);
    }
    return 0;
}
