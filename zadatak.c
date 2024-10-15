#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define ERROR_OPENING_FILE 1
#define BUFFER_SIZE 1024
#define MAX_BR_BODOVA 50

typedef struct {
    char ime[50];
    char prezime[50];
    int bodovi;
}student;
int count_rows(char* filename);
int citaj(char* filename, int broj_studenata);
double racunaj_rel(int broj_bodova);

int main() {
    int redovi;


    redovi = count_rows("studenti.txt");

    printf("Datoteka ima %d redaka \n", redovi); //varijabla redovi ce nam posluziti kao broj studenata (n)
    printf("\n");

    citaj("studenti.txt", redovi);


    return 0;
}
int count_rows(char* filename) { //Brojimo redove i vracamo broj redova odnosno studenata
    FILE* fp = NULL;
    char buffer[BUFFER_SIZE];
    int row_count = 0;

    fp = fopen("studenti.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return ERROR_OPENING_FILE;
    }

    while (!feof(fp)) {
        fgets(buffer, BUFFER_SIZE, fp);
        ++row_count;

    }
    fclose(fp);



    return row_count;

}
int citaj(char* filename, int broj_studenata) { //Citanje podataka iz svakog retka
    FILE* fp = NULL;
    student* Studenti;
    int i = 0;
    //din. alokacija memorije
    Studenti = (student*)malloc(broj_studenata * sizeof(student));
    if (Studenti == NULL) {
        printf("Neuspjela alokacija memorije");
        return ERROR_OPENING_FILE;

    }


    fp = fopen("studenti.txt", "r");
    if (fp == NULL) {
        printf("Neuspjelo otvaranje datoteke.");
        return ERROR_OPENING_FILE;

    }
    double relativni;
    for (i = 0; i < broj_studenata; i++) {
        //Datoteka izgleda: ime prezime bodovi
        fscanf(fp, "%19s %19s %d", Studenti[i].ime, Studenti[i].prezime, &Studenti[i].bodovi);


    }
    printf("\n");
    for (i = 0; i < broj_studenata; i++) {
        //saljemo u f-ju racunaj_rel bodove od svakog studenta na kojeg naidemo
        relativni = racunaj_rel(Studenti[i].bodovi);
        printf("Student %d : %s %s, Broj bodova: %d, Relativni Bodovi:  %f", i + 1, Studenti[i].ime, Studenti[i].prezime, Studenti[i].bodovi, relativni);
        printf("\n");
    }

    free(Studenti); //oslobodimo din.alociran prostor
    fclose(fp); //zatvori datoteku
    return 0;


}
double racunaj_rel(int broj_bodova) {
    //prvo cemo provjeriti za svakog od studenata ima li mozda neg. broj bodova ili vise od 100% sto je nemoguce
    if (broj_bodova<0 || broj_bodova>MAX_BR_BODOVA) {
        printf("Nedozvoljen broj bodova kod studenta s %d bodova. \n", broj_bodova);
        return 0;
    }

    double relativni;
    relativni = ((double)broj_bodova / (double)MAX_BR_BODOVA) * 100;


    return relativni;
}