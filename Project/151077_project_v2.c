#include<stdio.h>
#include<stdlib.h>
#include<string.h> //strlen, strcpy, strcmp - pre retazce v dynamickych poliach

/* V2: ako v1 + dynamicke polia (v 2, n, q, w, e).
   Struktury sa nesmu pouzit, preto mam pre kazdu polozku samostatne pole (ako velke[] a char_velke[] v h).
   Zaznam cislo i je vo vsetkych poliach na rovnakom indexe i.
   zoznamCK.txt: let[i], meno[i], priezvisko[i], datum[i], sedadlo[i], batozina[i]
   checkin1.txt: c_let[i], c_sedadlo[i], c_batozina[i], c_vahy[i][0..c_batozina[i]-1] */

/* V2: v2() je napisana az za h (poradie: v1, h, v 2, n, q, w, e), ale v() ju vola uz tu,
   preto ju tu iba ohlasim (prototyp) - kompilator potom vie, ze taka funkcia existuje */
void v2(char **let, char **meno, char **priezvisko, char **datum, char **sedadlo, int *batozina, int z_pocet,
        char **c_let, char **c_sedadlo, int *c_batozina, float **c_vahy, int c_pocet, int polia);

void v(FILE **zoznam, FILE **checkin,
       char **let, char **meno_p, char **priezvisko, char **datum, char **sedadlo, int *batozina, int z_pocet,
       char **c_let, char **c_sedadlo, int *c_batozina, float **c_vahy, int c_pocet, int polia) {
    //V2: pridane parametre s dynamickymi poliami - v() ich iba posunie do v2()
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
        v2(let, meno_p, priezvisko, datum, sedadlo, batozina, z_pocet,
           c_let, c_sedadlo, c_batozina, c_vahy, c_pocet, polia);
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

void v2(char **let, char **meno, char **priezvisko, char **datum, char **sedadlo, int *batozina, int z_pocet,
        char **c_let, char **c_sedadlo, int *c_batozina, float **c_vahy, int c_pocet, int polia) {
    /*po aktivovaní program zistí, či dynamické polia boli naplnené (tj. príkaz n už bol aktivovaný).
      Ak polia ešte neboli naplnené, program vypíše správu „V2: Nenaplnene polia.“*/
    if (polia == 0) {
        printf("V2: Nenaplnene polia.\n");
        return;
    }
    for (int i = 0; i < z_pocet; i++) {
        int d = strlen(datum[i]); //vek ako vo v1 - posledne 4 cislice datumu
        int vek = 2026 - ((datum[i][d-4]-'0') * 1000 + (datum[i][d-3]-'0') * 100 + (datum[i][d-2]-'0') * 10
            + (datum[i][d-1]-'0'));

        int najdeny = -1; //index v checkin poliach s rovnakym letom aj sedadlom, -1 = checkin nebol
        for (int j = 0; j < c_pocet; j++) {
            if (strcmp(c_let[j], let[i]) == 0 && strcmp(c_sedadlo[j], sedadlo[i]) == 0) {
                najdeny = j;
                break;
            }
        }

        printf("Oznacenie letu: %s\n", let[i]);
        printf("Meno a Priezvisko [vek]: %s %s [%d]\n", meno[i], priezvisko[i], vek);
        printf("Oznacenie sedadla: %c %s\n", sedadlo[i][0], sedadlo[i] + 1); //"A35" -> "A 35"
        if (najdeny == -1) {
            printf("Status: false\n");
            printf("Pocet batoziny: %d / 0\n", batozina[i]);
        }
        else {
            printf("Status: true\n");
            printf("Pocet batoziny: %d / %d ", batozina[i], c_batozina[najdeny]);
            for (int k = 0; k < c_batozina[najdeny]; k++) {
                if (k > 0) printf(","); //pri viacerých batožinách budú zátvorky oddelené čiarkou
                printf("[%.2f]", c_vahy[najdeny][k]);
            }
            printf("\n");
        }
        printf("\n"); //(prázdny riadok)
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
        for (int i = 0; i < *z_pocet; i++) { //najprv kazdy retazec...
            free((*let)[i]);
            free((*meno)[i]);
            free((*priezvisko)[i]);
            free((*datum)[i]);
            free((*sedadlo)[i]);
        }
        free(*let); //...potom samotne polia
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
    rewind(*zoznam);
    while (fgets(buffer, sizeof(buffer), *zoznam) != NULL) {
        if (buffer[0] == '#') pocet_z++; //kazdy zaznam zacina '#'
    }
    rewind(*checkin);
    while (fgets(buffer, sizeof(buffer), *checkin) != NULL) {
        if (buffer[0] != '\n' && buffer[0] != '\r' && buffer[0] != '\0') pocet_c++; //1 riadok = 1 zaznam
    }

    //dynamicky vytvorí polia pre jednotlivé položky podľa počtu záznamov (malloc)
    *let = malloc((pocet_z + 1) * sizeof(char *)); //+1 aby som nerobil malloc(0) ked je subor prazdny
    *meno = malloc((pocet_z + 1) * sizeof(char *));
    *priezvisko = malloc((pocet_z + 1) * sizeof(char *));
    *datum = malloc((pocet_z + 1) * sizeof(char *));
    *sedadlo = malloc((pocet_z + 1) * sizeof(char *));
    *batozina = malloc((pocet_z + 1) * sizeof(int));
    *c_let = malloc((pocet_c + 1) * sizeof(char *));
    *c_sedadlo = malloc((pocet_c + 1) * sizeof(char *));
    *c_batozina = malloc((pocet_c + 1) * sizeof(int));
    *c_vahy = malloc((pocet_c + 1) * sizeof(float *));
    if (*let == NULL || *meno == NULL || *priezvisko == NULL || *datum == NULL || *sedadlo == NULL ||
        *batozina == NULL || *c_let == NULL || *c_sedadlo == NULL || *c_batozina == NULL || *c_vahy == NULL) {
        return;
    }

    //2. prechod: do jednotlivých polí sa zapíšu jednotlivé záznamy v takom poradí, v akom sú v textovom súbore
    char slovo[30]; //sem si najprv precitam polozku, potom ju skopirujem do pola presne tak dlhu ako je
    int riadok = 0;
    int i = -1; //index zaznamu, pri prvom '#' bude 0
    rewind(*zoznam);
    while (fgets(buffer, sizeof(buffer), *zoznam) != NULL) {
        if (buffer[0] == '\n' || buffer[0] == '\r' || buffer[0] == '\0') {
            continue;
        }
        if (buffer[0] == '#') { //novy zaznam
            i++;
            riadok = 0;
            continue;
        }
        if (i < 0 || i >= pocet_z) continue;
        riadok++; //rovnake cislovanie ako vo v1: 1 let ... 6 batozina
        if (riadok == 6) {
            sscanf(buffer, "%d", &(*batozina)[i]);
            *z_pocet = i + 1; //zaznam je cely
            continue;
        }
        sscanf(buffer, "%29s", slovo);
        char *novy = malloc(strlen(slovo) + 1); //+1 pre '\0'
        if (novy == NULL) continue;
        strcpy(novy, slovo);
        if (riadok == 1) (*let)[i] = novy;
        else if (riadok == 2) (*meno)[i] = novy;
        else if (riadok == 3) (*priezvisko)[i] = novy;
        else if (riadok == 4) (*datum)[i] = novy;
        else if (riadok == 5) (*sedadlo)[i] = novy;
        else free(novy); //riadok navyse - nepotrebujem ho
    }

    //checkin1.txt: IB1234#A35#2#25.20#18.15
    i = 0;
    rewind(*checkin);
    while (fgets(buffer, sizeof(buffer), *checkin) != NULL && i < pocet_c) {
        if (buffer[0] == '\n' || buffer[0] == '\r' || buffer[0] == '\0') {
            continue;
        }
        for (int k = 0; buffer[k] != '\0'; k++) { //'#' zmenim na medzeru, potom staci obycajny sscanf
            if (buffer[k] == '#') buffer[k] = ' ';
        }
        char c_let_temp[10], c_sedadlo_temp[5];
        int pocet_kusov = 0;
        sscanf(buffer, "%9s %4s %d", c_let_temp, c_sedadlo_temp, &pocet_kusov);

        (*c_let)[i] = malloc(strlen(c_let_temp) + 1);
        (*c_sedadlo)[i] = malloc(strlen(c_sedadlo_temp) + 1);
        (*c_vahy)[i] = malloc((pocet_kusov + 1) * sizeof(float)); //pre kazdy zaznam pole vah
        if ((*c_let)[i] == NULL || (*c_sedadlo)[i] == NULL || (*c_vahy)[i] == NULL) break;
        strcpy((*c_let)[i], c_let_temp);
        strcpy((*c_sedadlo)[i], c_sedadlo_temp);
        (*c_batozina)[i] = pocet_kusov;

        //vahy su za 3. medzerou (predtym za 3. '#'): za kazdou medzerou od tretej precitam jedno cislo
        int medzery = 0;
        int index_vahy = 0;
        for (int k = 0; buffer[k] != '\0' && index_vahy < pocet_kusov; k++) {
            if (buffer[k] == ' ') {
                medzery++;
                if (medzery >= 3) {
                    sscanf(&buffer[k+1], "%f", &(*c_vahy)[i][index_vahy]);
                    index_vahy++;
                }
            }
        }
        i++;
        *c_pocet = i;
    }
    *polia = 1; //Pri tejto voľbe program negeneruje žiaden výstup.
}

void q(char ***let, char ***meno, char ***priezvisko, char ***datum, char ***sedadlo, int **batozina,
       int *z_pocet, int polia) {
    int y;
    char novy_let[10], nove_meno[16], nove_priezvisko[26], novy_datum[10], nove_sedadlo[5];
    int nova_batozina;
    /* udaje precitam este pred kontrolou - inak by "IB1234", "Jana"... zostali vo vstupe
       a main by ich bral ako dalsie prikazy (I, J, ...) */
    scanf("%d", &y);
    scanf("%9s %15s %25s %9s %4s %d", novy_let, nove_meno, nove_priezvisko, novy_datum, nove_sedadlo,
        &nova_batozina);
    if (polia == 0) {
        printf("Q: Polia nie su vytvorene.\n");
        return;
    }
    //Y=1 reprezentuje pozíciu pole[0]. Ak je Y väčšie ako počet záznamov, záznam sa pridá na koniec poľa.
    int pozicia = y - 1;
    if (pozicia > *z_pocet) pozicia = *z_pocet;
    if (pozicia < 0) pozicia = 0;

    //kazde pole zvacsim o 1 (realloc cez temp ako v 4_3)
    char **temp;
    temp = realloc(*let, (*z_pocet + 1) * sizeof(char *));
    if (temp == NULL) return;
    *let = temp;
    temp = realloc(*meno, (*z_pocet + 1) * sizeof(char *));
    if (temp == NULL) return;
    *meno = temp;
    temp = realloc(*priezvisko, (*z_pocet + 1) * sizeof(char *));
    if (temp == NULL) return;
    *priezvisko = temp;
    temp = realloc(*datum, (*z_pocet + 1) * sizeof(char *));
    if (temp == NULL) return;
    *datum = temp;
    temp = realloc(*sedadlo, (*z_pocet + 1) * sizeof(char *));
    if (temp == NULL) return;
    *sedadlo = temp;
    int *temp_int = realloc(*batozina, (*z_pocet + 1) * sizeof(int));
    if (temp_int == NULL) return;
    *batozina = temp_int;

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
    (*meno)[pozicia] = malloc(strlen(nove_meno) + 1);
    (*priezvisko)[pozicia] = malloc(strlen(nove_priezvisko) + 1);
    (*datum)[pozicia] = malloc(strlen(novy_datum) + 1);
    (*sedadlo)[pozicia] = malloc(strlen(nove_sedadlo) + 1);
    strcpy((*let)[pozicia], novy_let);
    strcpy((*meno)[pozicia], nove_meno);
    strcpy((*priezvisko)[pozicia], nove_priezvisko);
    strcpy((*datum)[pozicia], novy_datum);
    strcpy((*sedadlo)[pozicia], nove_sedadlo);
    (*batozina)[pozicia] = nova_batozina;
    (*z_pocet)++;
}

void w(char ***let, char ***meno, char ***priezvisko, char ***datum, char ***sedadlo, int **batozina,
       int *z_pocet, int polia) {
    char hladany_let[10];
    scanf("%9s", hladany_let);
    if (polia == 0) {
        printf("W: Polia nie su vytvorene.\n");
        return;
    }
    int vymazane = 0;
    int novy_pocet = 0; //kam dam dalsi zaznam, ktory nechavam
    for (int i = 0; i < *z_pocet; i++) {
        if (strcmp((*let)[i], hladany_let) == 0) { //tento zaznam mazem
            free((*let)[i]);
            free((*meno)[i]);
            free((*priezvisko)[i]);
            free((*datum)[i]);
            free((*sedadlo)[i]);
            vymazane++;
        }
        else { //tento nechavam, posuniem ho dopredu na miesto vymazanych
            (*let)[novy_pocet] = (*let)[i];
            (*meno)[novy_pocet] = (*meno)[i];
            (*priezvisko)[novy_pocet] = (*priezvisko)[i];
            (*datum)[novy_pocet] = (*datum)[i];
            (*sedadlo)[novy_pocet] = (*sedadlo)[i];
            (*batozina)[novy_pocet] = (*batozina)[i];
            novy_pocet++;
        }
    }
    *z_pocet = novy_pocet;

    //Dynamické polia udržujte tak, aby nezaberali miesto v pamäti pre nepotrebné záznamy.
    //(+1 aby realloc nikdy nedostal 0 - pri 0 zaznamoch zostane 1 prazdne miesto)
    char **temp;
    temp = realloc(*let, (novy_pocet + 1) * sizeof(char *));
    if (temp != NULL) *let = temp;
    temp = realloc(*meno, (novy_pocet + 1) * sizeof(char *));
    if (temp != NULL) *meno = temp;
    temp = realloc(*priezvisko, (novy_pocet + 1) * sizeof(char *));
    if (temp != NULL) *priezvisko = temp;
    temp = realloc(*datum, (novy_pocet + 1) * sizeof(char *));
    if (temp != NULL) *datum = temp;
    temp = realloc(*sedadlo, (novy_pocet + 1) * sizeof(char *));
    if (temp != NULL) *sedadlo = temp;
    int *temp_int = realloc(*batozina, (novy_pocet + 1) * sizeof(int));
    if (temp_int != NULL) *batozina = temp_int;

    printf("W: Vymazalo sa : %d zaznamov !\n", vymazane);
}

float **e(char **c_let, char **c_sedadlo, int *c_batozina, float **c_vahy, int c_pocet, int polia) {
    char hladane_sedadlo[5];
    scanf("%4s", hladane_sedadlo);
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
    float *nove_vahy = malloc((spolu + 1) * sizeof(float));
    if (nove_vahy == NULL) return c_vahy;
    printf("Zadaj %d váhy: ", spolu); //presne ako v ukazke (s diakritikou)
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
        if (scanf(" %c", &program) != 1) break; //ked vstup skonci (EOF), inak by sa cyklus nikdy nezastavil
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

    //pred koncom uvolnim vsetku dynamicku pamat (ako v n)
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
