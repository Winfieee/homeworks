#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* V2: ako v1 + dynamicke polia (v 2, n, q, w, e).
   Struktury sa nesmu pouzit, preto mam pre kazdu polozku samostatne pole (ako velke[] a char_velke[] v h).
   Zaznam cislo i je vo vsetkych poliach na rovnakom indexe i.
   zoznamCK.txt: oznac_letov[i], mena[i], priezviska[i], datumy[i], sedadla[i], batoziny[i]
   checkin1.txt: registered_oznac_letov[i], registered_sedadla[i], registered_batoziny[i], vahy_batoziny[i][0..registered_batoziny[i]-1] */

void v(FILE **zoznam, FILE **checkin,
       char **oznac_letov, char **mena, char **priezviska, char **datumy, char **sedadla, int *batoziny, int pocet_pasaz,
       char **registered_oznac_letov, char **registered_sedadla, int *registered_batoziny, float **vahy_batoziny, int pocet_registered, int polia) {
    //V2: pridane parametre s dynamickymi poliami - pouziju sa vo vetve which_v == 2
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
    else if (which_v == 2) {
        if (polia == 0) { //po aktivovaní program zistí, či dynamické polia boli naplnené
            //Ak polia ešte neboli naplnené, program vypíše správu „V2: Nenaplnene polia
            printf("V2: Nenaplnene polia.\n");
            return;
        }
        for (int i = 0; i < pocet_pasaz; i++) {
            int datum_length = strlen(datumy[i]); //vek - posledne 4 cislice datumu DDMMRRRR
            vek = 2026 - ((datumy[i][datum_length-4]-'0') * 1000 + (datumy[i][datum_length-3]-'0') * 100 + (datumy[i][datum_length-2]-'0') * 10
                + (datumy[i][datum_length-1]-'0'));

            int najdeny = -1; //index v checkin poliach s rovnakym letom aj sedadlom, -1 = checkin nebol
            for (int j = 0; j < pocet_registered; j++) {
                if (strcmp(registered_oznac_letov[j], oznac_letov[i]) == 0 && strcmp(registered_sedadla[j], sedadla[i]) == 0) {
                    najdeny = j;
                    break;
                }
            }

            printf("Oznacenie letu: %s\n", oznac_letov[i]);
            printf("Meno a Priezvisko [vek]: %s %s [%d]\n", mena[i], priezviska[i], vek);
            printf("Oznacenie sedadla: %c %s\n", sedadla[i][0], sedadla[i] + 1); //"A35" -> "A 35"
            if (najdeny == -1) {
                printf("Status: false\n");
                printf("Pocet batoziny: %d / 0\n", batoziny[i]);
            }
            else {
                printf("Status: true\n");
                printf("Pocet batoziny: %d / %d", batoziny[i], registered_batoziny[najdeny]);
                for (int k = 0; k < registered_batoziny[najdeny]; k++) {
                    if (k == 0) printf(" "); //medzera iba ked su nejake vahy (pri 0 kusoch nie)
                    if (k > 0) printf(","); //pri viacerých batožinách budú zátvorky oddelené čiarkou
                    printf("[%.2f]", vahy_batoziny[najdeny][k]);
                }
                printf("\n");
            }
            printf("\n");
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
       char ***oznac_letov, char ***mena, char ***priezviska, char ***datumy, char ***sedadla, int **batoziny, int *pocet_pasaz,
       char ***registered_pocet_letov, char ***registered_sedadla, int **registered_batoziny, float ***bahy_batoziny, int *pocet_registered, int *polia) {
    if (*zoznam == NULL || *checkin == NULL) { //Ak aspoň jeden zo súborov nie je otvorený
        //voľba nič nezmení a vypíše správu „N: Neotvoreny subor.“
        printf("N: Neotvoreny subor.\n");
        return;
    }
    //Ak už boli polia predtým vytvorené, sú najprv korektne dealokované a potom sa vytvoria nové.
    if (*polia == 1) {
        for (int i = 0; i < *pocet_pasaz; i++) { //najprv retazce, ktore je v poli...
            free((*oznac_letov)[i]);
            free((*mena)[i]);
            free((*priezviska)[i]);
            free((*datumy)[i]);
            free((*sedadla)[i]);
        }
        free(*oznac_letov); //...a az potom samotne pole (v inom pripade som by adresy retazcev stratil)
        free(*mena);
        free(*priezviska);
        free(*datumy);
        free(*sedadla);
        free(*batoziny);
        for (int i = 0; i < *pocet_registered; i++) {
            free((*registered_pocet_letov)[i]);
            free((*registered_sedadla)[i]);
            free((*bahy_batoziny)[i]);
        }
        free(*registered_pocet_letov);
        free(*registered_sedadla);
        free(*registered_batoziny);
        free(*bahy_batoziny);
        *pocet_pasaz = 0;
        *pocet_registered = 0;
        *polia = 0;
    }

    char buffer[27]; //ak som urobil vo v1
    char c_buffer[69]; /*najdlhsi riadok checkinu: oznac_letov 6 + #, sedadla 3 + #, kusy 1 + #,
                         9 vah po 5 znakov (XX.XX) + # = 7 + 4 + 2 + 9*6 = 67, + '\n' + '\0' = 69 */
    int zoznamCK_rozmier = 0, checkin1_rozmier = 0;
    //1. prechod: spočíta počet záznamov v jednotlivých txt súboroch
    rewind(*zoznam);
    while (fgets(buffer, sizeof(buffer), *zoznam) != NULL) {
        if (buffer[0] == '#') zoznamCK_rozmier++; //kazdy zaznam zacina '#'
    }
    rewind(*checkin);
    while (fgets(c_buffer, sizeof(c_buffer), *checkin) != NULL) {
        if (c_buffer[0] != '\n' && c_buffer[0] != '\r' && c_buffer[0] != '\0') checkin1_rozmier++; //pre kazdy riadok mame zaznam
    }

    //dynamicky vytvorí polia pre jednotlivé položky podľa počtu záznamov v txt súboroch
    *oznac_letov = malloc(zoznamCK_rozmier * sizeof(char *));
    *mena = malloc(zoznamCK_rozmier * sizeof(char *));
    *priezviska = malloc(zoznamCK_rozmier * sizeof(char *));
    *datumy = malloc(zoznamCK_rozmier * sizeof(char *));
    *sedadla = malloc(zoznamCK_rozmier * sizeof(char *));
    *batoziny = malloc(zoznamCK_rozmier * sizeof(int));
    *registered_pocet_letov = malloc(checkin1_rozmier * sizeof(char *));
    *registered_sedadla = malloc(checkin1_rozmier * sizeof(char *));
    *registered_batoziny = malloc(checkin1_rozmier * sizeof(int));
    *bahy_batoziny = malloc(checkin1_rozmier * sizeof(float *));

    //2. prechod: do jednotlivých polí sa zapíšu jednotlivé záznamy v takom poradí, v akom sú v textovom súbore
    char slovo[26]; //tu scitam element a potom ho skopirujem do pola (najdlhsia: priezvisko 25 + 1 pre '\0')
    int riadok = 0;
    int i = -1; //index zaznamu, pri prvom '#' bude 0
    rewind(*zoznam);
    while (fgets(buffer, sizeof(buffer), *zoznam) != NULL) {
        if (buffer[0] == '\n' || buffer[0] == '\r' || buffer[0] == '\0') {
            continue; //prazdny riadok preskocim
        }
        if (buffer[0] == '#') { //novy zaznam
            i++;
            riadok = 0;
            continue;
        }
        riadok++; //1 = oznac_letov, 2 = mena, 3 = priezviska, 4 = datum, 5 = sedadla, 6 = batoziny
        if (riadok == 1) {
            sscanf(buffer, "%s", slovo);
            (*oznac_letov)[i] = malloc(strlen(slovo) + 1); //+1 pre '\0'
            strcpy((*oznac_letov)[i], slovo);
        }
        if (riadok == 2) {
            sscanf(buffer, "%s", slovo);
            (*mena)[i] = malloc(strlen(slovo) + 1);
            strcpy((*mena)[i], slovo);
        }
        if (riadok == 3) {
            sscanf(buffer, "%s", slovo);
            (*priezviska)[i] = malloc(strlen(slovo) + 1);
            strcpy((*priezviska)[i], slovo);
        }
        if (riadok == 4) {
            sscanf(buffer, "%s", slovo);
            (*datumy)[i] = malloc(strlen(slovo) + 1);
            strcpy((*datumy)[i], slovo);
        }
        if (riadok == 5) {
            sscanf(buffer, "%s", slovo);
            (*sedadla)[i] = malloc(strlen(slovo) + 1);
            strcpy((*sedadla)[i], slovo);
        }
        if (riadok == 6) {
            sscanf(buffer, "%d", &(*batoziny)[i]);
            *pocet_pasaz = i + 1; //zaznam je cely
        }
    }

    i = 0;
    rewind(*checkin);
    while (fgets(c_buffer, sizeof(c_buffer), *checkin) != NULL) {
        if (c_buffer[0] == '\n' || c_buffer[0] == '\r' || c_buffer[0] == '\0') {
            continue;
        }
        for (int k = 0; c_buffer[k] != '\0'; k++) { //'#' zmenim na medzeru, tedi staci len sscanf
            if (c_buffer[k] == '#') c_buffer[k] = ' ';
        }
        char c_let_temp[7], c_sedadlo_temp[4]; //oznac_letov 6 + 1, sedadlo 3 + 1 pre '\0'
        int pocet_kusov;
        sscanf(c_buffer, "%s %s %d", c_let_temp, c_sedadlo_temp, &pocet_kusov);

        (*registered_pocet_letov)[i] = malloc(strlen(c_let_temp) + 1);
        strcpy((*registered_pocet_letov)[i], c_let_temp);
        (*registered_sedadla)[i] = malloc(strlen(c_sedadlo_temp) + 1);
        strcpy((*registered_sedadla)[i], c_sedadlo_temp);
        (*registered_batoziny)[i] = pocet_kusov;
        (*bahy_batoziny)[i] = malloc(pocet_kusov * sizeof(float)); //kazdy zaznam ma svoje pole vah

        //vahy su za 3 medzerou (predtym za 3 '#'): za kazdou medzerou od tretej precitam jedno cislo
        int medzery = 0;
        int index_vahy = 0;
        for (int k = 0; c_buffer[k] != '\0' && index_vahy < pocet_kusov; k++) {
            if (c_buffer[k] == ' ') {
                medzery++;
                if (medzery >= 3) {
                    sscanf(&c_buffer[k+1], "%f", &(*bahy_batoziny)[i][index_vahy]);
                    index_vahy++;
                }
            }
        }
        i++;
    }
    *pocet_registered = i;
    *polia = 1; //Pri tejto voľbe program negeneruje žiaden výstup.
}

void q(char ***oznacenia_letov, char ***mena, char ***priezviska, char ***datumy, char ***sedadlo, int **pocet_batozin,
        int *pocet_elementov_zoznamu, int polia) {
    int y;
    char novy_let[7], nove_meno[16], nove_priezvisko[26], novy_datum[9], nove_sedadlo[4]; //podla formatu + 1 pre '\0'
    int nova_batozina;
    scanf("%d", &y); //po aktivovaní program načíta celé číslo Y z klávesnice
    scanf("%s %s %s %s %s %d", novy_let, nove_meno, nove_priezvisko, novy_datum, nove_sedadlo, &nova_batozina);
    //Dáta sa budú načítavať z klávesnice vo formáte súboru zoznamCK.txt
    if (polia == 0) {
        //Ak dynamické polia nie sú vytvorené, vypíše sa správa „Q: Polia nie suvytvorene.“
        printf("Q: Polia nie su vytvorene.\n");
        return;
    }
    //Y=1 reprezentuje pozíciu pole[0]. Ak Y je väčšie ako počet záznamov, záznam sa pridá na koniec poľa.
    int pozicia = y - 1;
    if (pozicia > *pocet_elementov_zoznamu) pozicia = *pocet_elementov_zoznamu;
    if (pozicia < 0) pozicia = 0;

    //kazde pole zvacsim o 1 miesto
    *oznacenia_letov = realloc(*oznacenia_letov, (*pocet_elementov_zoznamu + 1) * sizeof(char *));
    *mena = realloc(*mena, (*pocet_elementov_zoznamu + 1) * sizeof(char *));
    *priezviska = realloc(*priezviska, (*pocet_elementov_zoznamu + 1) * sizeof(char *));
    *datumy = realloc(*datumy, (*pocet_elementov_zoznamu + 1) * sizeof(char *));
    *sedadlo = realloc(*sedadlo, (*pocet_elementov_zoznamu + 1) * sizeof(char *));
    *pocet_batozin = realloc(*pocet_batozin, (*pocet_elementov_zoznamu + 1) * sizeof(int));

    //vsetko od pozicie posuniem o 1 doprava (od konca, aby som si nic neprepisal)
    for (int i = *pocet_elementov_zoznamu; i > pozicia; i--) {
        (*oznacenia_letov)[i] = (*oznacenia_letov)[i-1];
        (*mena)[i] = (*mena)[i-1];
        (*priezviska)[i] = (*priezviska)[i-1];
        (*datumy)[i] = (*datumy)[i-1];
        (*sedadlo)[i] = (*sedadlo)[i-1];
        (*pocet_batozin)[i] = (*pocet_batozin)[i-1];
    }

    //na uvolnene miesto zapisem novy zaznam
    (*oznacenia_letov)[pozicia] = malloc(strlen(novy_let) + 1);
    strcpy((*oznacenia_letov)[pozicia], novy_let);
    (*mena)[pozicia] = malloc(strlen(nove_meno) + 1);
    strcpy((*mena)[pozicia], nove_meno);
    (*priezviska)[pozicia] = malloc(strlen(nove_priezvisko) + 1);
    strcpy((*priezviska)[pozicia], nove_priezvisko);
    (*datumy)[pozicia] = malloc(strlen(novy_datum) + 1);
    strcpy((*datumy)[pozicia], novy_datum);
    (*sedadlo)[pozicia] = malloc(strlen(nove_sedadlo) + 1);
    strcpy((*sedadlo)[pozicia], nove_sedadlo);
    (*pocet_batozin)[pozicia] = nova_batozina;
    (*pocet_elementov_zoznamu)++;
}

void w(char ***oznac_letov, char ***mena, char ***priezviska, char ***datumy, char ***sedadla, int **pocet_batozin,
       int *pocet_elementov_zaznamu, int polia) {
    char oznacenie_letu[7]; //oznacenie_leta 6 + 1 pre '\0'
    scanf("%s", oznacenie_letu); //po aktivovaní program načíta Označenie letu z klávesnice
    if (polia == 0) {
        printf("W: Polia nie su vytvorene.\n");
        return;
    }
    int pocet_vymazenych_zaznamov = 0;
    for (int i = 0; i < *pocet_elementov_zaznamu; i++) {
        if (strcmp((*oznac_letov)[i], oznacenie_letu) == 0) { //tento zaznam odlozim
            free((*oznac_letov)[i]);
            free((*mena)[i]);
            free((*priezviska)[i]);
            free((*datumy)[i]);
            free((*sedadla)[i]);
            for (int j = i; j < *pocet_elementov_zaznamu - 1; j++) { //vsetko za nim posuniem na 1 dolava
                (*oznac_letov)[j] = (*oznac_letov)[j+1];
                (*mena)[j] = (*mena)[j+1];
                (*priezviska)[j] = (*priezviska)[j+1];
                (*datumy)[j] = (*datumy)[j+1];
                (*sedadla)[j] = (*sedadla)[j+1];
                (*pocet_batozin)[j] = (*pocet_batozin)[j+1];
            }
            (*pocet_elementov_zaznamu)--;
            pocet_vymazenych_zaznamov++;
            i--; //na miesto i sa posunul dalsi zaznam, aj ten musim skontrolovat
        }
    }
    //Dynamické polia udržujte tak, aby nezaberali miesto v pamäti pre nepotrebné záznamy.
    *oznac_letov = realloc(*oznac_letov, *pocet_elementov_zaznamu * sizeof(char *));
    *mena = realloc(*mena, *pocet_elementov_zaznamu * sizeof(char *));
    *priezviska = realloc(*priezviska, *pocet_elementov_zaznamu * sizeof(char *));
    *datumy = realloc(*datumy, *pocet_elementov_zaznamu * sizeof(char *));
    *sedadla = realloc(*sedadla, *pocet_elementov_zaznamu * sizeof(char *));
    *pocet_batozin = realloc(*pocet_batozin, *pocet_elementov_zaznamu * sizeof(int));

    printf("W: Vymazalo sa : %d zaznamov !\n", pocet_vymazenych_zaznamov);
}

float **e(char **checkin_oznac_letu, char **checkin_sedadla, int *checkin_pocet_batozin, float **checkin_vahy, int checkin_pocet_registarii, int polia) {
    char hladane_sedadlo[4]; //sedadlo 3 + 1 pre '\0'
    scanf("%s", hladane_sedadlo);
    if (polia == 0) {
        printf("E: Polia nie su vytvorene.\n");
        return checkin_vahy;
    }
    //Následne sa zistí koľko batožiny sa odovzdalo pre dané sedadlo
    int spolu = 0;
    for (int i = 0; i < checkin_pocet_registarii; i++) {
        if (strcmp(checkin_sedadla[i], hladane_sedadlo) == 0) spolu += checkin_pocet_batozin[i];
    }
    //pre každú batožinu bude možné zadať novú váhu z klávesnice
    float *nove_vahy = malloc(spolu * sizeof(float));
    if (spolu > 0) { //ked take sedadlo nie existuje, nie mame co zadavat
        printf("Zadaj %d váhy: ", spolu);
    }
    for (int i = 0; i < spolu; i++) {
        scanf("%f", &nove_vahy[i]);
    }
    //Program najprv vypíše pôvodný obsah poľa v tvare v akom je uložený v txt súbore
    for (int i = 0; i < checkin_pocet_registarii; i++) {
        printf("%s#%s#%d", checkin_oznac_letu[i], checkin_sedadla[i], checkin_pocet_batozin[i]);
        for (int k = 0; k < checkin_pocet_batozin[i]; k++) {
            printf("#%.2f", checkin_vahy[i][k]);
        }
        printf("\n");
    }
    //zmenim vahy pri zaznamoch s tymto sedadlom
    int index_vahy = 0;
    for (int i = 0; i < checkin_pocet_registarii; i++) {
        if (strcmp(checkin_sedadla[i], hladane_sedadlo) == 0) {
            for (int k = 0; k < checkin_pocet_batozin[i]; k++) {
                checkin_vahy[i][k] = nove_vahy[index_vahy];
                index_vahy++;
            }
        }
    }
    free(nove_vahy);
    //...a potom zmenený obsah poľa.
    printf("\n");
    for (int i = 0; i < checkin_pocet_registarii; i++) {
        printf("%s#%s#%d", checkin_oznac_letu[i], checkin_sedadla[i], checkin_pocet_batozin[i]);
        for (int k = 0; k < checkin_pocet_batozin[i]; k++) {
            printf("#%.2f", checkin_vahy[i][k]);
        }
        printf("\n");
    }
    return checkin_vahy; //Funkcia vracia zmenený obsah poľa naspäť do funkcie main.
}

int main() {
    char program;
    FILE *zoznam = NULL, *checking = NULL;
    char **oznac_letov = NULL, **mena = NULL, **priezviska = NULL, **datumy = NULL, **sedadla = NULL;
    int *batoziny = NULL;
    int pocet_pasaz = 0;
    char **registered_oznac_letov = NULL, **registered_sedadla = NULL;
    int *registered_batoziny = NULL;
    float **vahy_batoziny = NULL;
    int pocet_registered = 0;
    int polia = 0; //0 = prikaz n este nebol, 1 = polia su vytvorene

    printf("Oberte fuknciu \n \nVstup v 1: informacia o letu.\nVstup v 2: vypis z dynamickych poli.\n"
           "Vstup h: histogram.\nVstup n: vytvorenie dynamickych poli.\nVstup q Y: pridanie zaznamu.\n"
           "Vstup w LET: vymazanie letu.\nVstup e SEDADLO: zmena vah batoziny.\nk - koniec\n");
    while (1) {
        scanf(" %c", &program);
        if (program == 'v') {
            v(&zoznam, &checking, oznac_letov, mena, priezviska, datumy, sedadla, batoziny, pocet_pasaz,
              registered_oznac_letov, registered_sedadla, registered_batoziny, vahy_batoziny, pocet_registered, polia);
        }
        else if (program == 'h') {
            h(&zoznam);
        }
        else if (program == 'n') {
            n(&zoznam, &checking, &oznac_letov, &mena, &priezviska, &datumy, &sedadla, &batoziny, &pocet_pasaz,
              &registered_oznac_letov, &registered_sedadla, &registered_batoziny, &vahy_batoziny, &pocet_registered, &polia);
        }
        else if (program == 'q') { //q je teraz pridanie zaznamu, koniec je preto k
            q(&oznac_letov, &mena, &priezviska, &datumy, &sedadla, &batoziny, &pocet_pasaz, polia);
        }
        else if (program == 'w') {
            w(&oznac_letov, &mena, &priezviska, &datumy, &sedadla, &batoziny, &pocet_pasaz, polia);
        }
        else if (program == 'e') {
            vahy_batoziny = e(registered_oznac_letov, registered_sedadla, registered_batoziny, vahy_batoziny, pocet_registered, polia);
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
        for (int i = 0; i < pocet_pasaz; i++) {
            free(oznac_letov[i]);
            free(mena[i]);
            free(priezviska[i]);
            free(datumy[i]);
            free(sedadla[i]);
        }
        free(oznac_letov);
        free(mena);
        free(priezviska);
        free(datumy);
        free(sedadla);
        free(batoziny);
        for (int i = 0; i < pocet_registered; i++) {
            free(registered_oznac_letov[i]);
            free(registered_sedadla[i]);
            free(vahy_batoziny[i]);
        }
        free(registered_oznac_letov);
        free(registered_sedadla);
        free(registered_batoziny);
        free(vahy_batoziny);
    }
    if (zoznam != NULL) {
        fclose(zoznam);
    }
    if (checking != NULL) {
        fclose(checking);
    }
    return 0;
}
