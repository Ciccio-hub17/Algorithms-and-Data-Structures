#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "divisione.h"
#include "dipendente.h"

#define MAX_SIGLA 10
#define NUM_TIP 4
#define PARAM_PER_TIP 3

typedef struct divisione_s {
    char sigla[MAX_SIGLA];
    int mat[NUM_TIP][PARAM_PER_TIP];
    dipendente_t **dipendenti_assegnati;
    int *mansioni_assegnate;
}divisione_t;

divisione_t divisioni_init (int N){
    divisione_t div;
    div.dipendenti_assegnati = malloc (N*sizeof (dipendente_t));
    div.mansioni_assegnate = calloc (N, sizeof (int));
    for (int i = 0; i < N; i++){
        div.dipendenti_assegnati[i] = NULL;
    }
    for (int i = 0; i < NUM_TIP; i++){
        for (int j = 0; j < PARAM_PER_TIP; j++){
            div.mat[i][j] = 0;
        }
    }
    
    return div;
}

void free_divisione (divisione_t div){
    free (div.dipendenti_assegnati);
    free (div.mansioni_assegnate);
    return;
}

divisione inserimento_divisione (){
    divisione div;
    printf ("Dammi la sigla\n");
    scanf ("%s", div->sigla);
    printf ("Riempi la matrice delle divisioni con i rispettivi parametri (4*3)\n");
    for (int i = 0; i < NUM_TIP; i++){
        for (int j = 0; j < PARAM_PER_TIP; j++){
            scanf ("%d", &div->mat[i][j]);
        }
    }
    return div;
}

void inserimento_dipendente (divisione div, int N){
    int i;
    dipendente_t dipendente;
    scanf ("%d %s %s %d %d %d %d", &dipendente.matricola, dipendente.nome, dipendente.cognome, &dipendente.competenze[0], &dipendente.competenze[1], &dipendente.competenze[2], &dipendente.competenze[3]);
    for (i = 0; i < N && div->dipendenti_assegnati[i] != NULL; i++);

    if (i < N) {
        div->dipendenti_assegnati[i] = &dipendente;
        scanf ("%d", &div->mansioni_assegnate[i]);
    }
    else printf ("Divisione piena\n");

    return;
}

void file_print (FILE *input, divisione div,  int N){
    int i, j, m;
    fprintf (input, "%s\n", div->sigla);
    for (j = 0; j < NUM_TIP; j++){
        for (m = 0; m < PARAM_PER_TIP; m++){
            fprintf (input, " %d ", div->mat[j][m]);
        }
        fprintf (input, "\n");
    }
    for (i = 0; i < N; i++){
        if (div->dipendenti_assegnati[i] != NULL){
            fprintf ("%d %s %s %d\n", div->dipendenti_assegnati[i]->matricola, div->dipendenti_assegnati[i]->nome, div->mansioni_assegnate[i]);
        }
    }
    return;
}

int ricerca_divisione (divisione* div, int D, char *sigla){
    int i;
    for (i = 0; i < D; i++){
        if (strcmp (div[i]->sigla, sigla) == 0){
            return i;
        }
    }
}

int ricerca_indice_libero (divisione div, int N){
    for (int i = 0; i < N; i++){
        if (div->dipendenti_assegnati != NULL){
            return i;
        }
    }
}

void ins_dip (divisione div, int mansione, int indice_libero, dipendente_t dip){
    div->dipendenti_assegnati[indice_libero] = &dip;
    div->mansioni_assegnate[indice_libero] = mansione;
    return;
}

int check_divisione (divisione div, int N){
    int count[4] = {0};
    int somma[4] = {0};
    for (int i = 0; i < N; i++){
        if (div->dipendenti_assegnati[i] != NULL){
            count[div->mansioni_assegnate[i]]++;
            somma[div->mansioni_assegnate[i]] += div->dipendenti_assegnati[i]->competenze[div->mansioni_assegnate[i]];
        }
    }

    int i;
    for (i = 0; i < NUM_TIP; i++){
        if (count[i] < div->mat[i][0]){
            return 0;
        }
        if (somma[i] < div->mat[i][1]){
            return 0;
        }
    }

    return 1;

}

float delta_avg (divisione *div, int D, int N){
    int i, j;
    int somma[4] = {0};
    int somma_tot = 0;
    for (i = 0; i < D; i++){
        for (j = 0; j < N; j++){
            if (div[i]->dipendenti_assegnati[j] != NULL){
                somma[div[i]->mansioni_assegnate[j]] += div[i]->dipendenti_assegnati[j]->competenze[div[i]->mansioni_assegnate[j]]; 
            }
        }
        for (j = 0; j < NUM_TIP; j++){
            somma_tot += abs (div[i]->mat[j][2]-somma[j]);
        }
    }

    return (somma_tot/D);
}
