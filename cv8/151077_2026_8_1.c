#include <stdio.h>

#define POCET 10

typedef struct {
    char meno[101];      // meno a priezvisko: max 100 znakov + '\0'
    char ulica[101];     // ulica: max 100 znakov + '\0'
    char psc[7];         // PSC v tvare "811 01": 6 znakov + '\0'
    char telefon[16];    // napr. "+421901234567"
} OSOBA;

int main() {
    // staticke pole pre 10 osob, naplnene priamo pri deklaracii
    OSOBA osoby[POCET] = {
        {"Jan Novak",          "Hlavna 12",        "811 01", "+421901111111"},
        {"Peter Horvath",      "Obchodna 5",       "811 06", "+421902222222"},
        {"Maria Kovacova",     "Mlynska dolina 1", "842 48", "+421903333333"},
        {"Eva Vargova",        "Stefanikova 20",   "811 05", "+421904444444"},
        {"Martin Toth",        "Kosicka 7",        "821 08", "+421905555555"},
        {"Lucia Balazova",     "Ruzinovska 33",    "821 02", "+421906666666"},
        {"Tomas Szabo",        "Racianska 44",     "831 02", "+421907777777"},
        {"Zuzana Molnarova",   "Pekna cesta 2",    "831 52", "+421908888888"},
        {"Michal Kral",        "Dunajska 9",       "811 08", "+421909999999"},
        {"Katarina Lukacova",  "Namestie SNP 1",   "811 01", "+421910000000"}
    };

    printf("%-3s %-22s %-20s %-8s %s\n", "#", "Meno a priezvisko", "Ulica", "PSC", "Telefon");
    printf("--------------------------------------------------------------------------\n");

    for (int i = 0; i < POCET; i++) {
        printf("%-3d %-22s %-20s %-8s %s\n",
               i + 1, osoby[i].meno, osoby[i].ulica, osoby[i].psc, osoby[i].telefon);
    }

    return 0;
}
