#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <divisione.h>
#include <dipendente.h>
#define NUM_TIP 4
#define MAX_S 10

int carattere_indice (char carattere){
    char vet[NUM_TIP] = {'o', 'a', 't', 'i'};

    for (int i = 0; i < NUM_TIP; i++){
        if (carattere == vet[i]){
            return i;
        }
    }
}



void leggi_associazioni (char *filename, divisione* div, int D, dipendente_t* dipendenti){
    FILE *input;
    if ((input = fopen(filename, "r")) == NULL){
        printf("Errore nell'apertura del file: \"%s\"", filename);
        exit(-1);
    }

    int N, i, matricola, index, mansione, j, ind_dip;
    char tipologia, sigla[MAX_S];
    dipendente_t dipendente;
    fscanf (input, "%d", &N);

    for (i = 0; i < N; i++){
        fscanf (input, "%d %c %s", &matricola, &tipologia, sigla);
        index = ricerca_divisione (div, D, sigla);
        mansione = carattere_indice (tipologia);
        dipendente = ricerca_dipendente (dipendenti, N, matricola);
        ind_dip = ricerca_indice_libero (div[index], N);
        ins_dip (div[index], mansione, ind_dip, dipendente);
    }

    int flag;

    for (i = 0; i < D; i++){
        flag = check_divisione (div[i], N);
        if (flag){
            printf ("Divisione %d pulita\n", i);
        }
        else{
            printf ("La divisione %d non rispetta i canoni minimi\n", i);
        }
    }


    
    fclose(input);
}

int main(int argc, char* argv[]){

    if (argc != 4){
        exit (-1);
    }
    
    printf("\n");
    return 0;
}