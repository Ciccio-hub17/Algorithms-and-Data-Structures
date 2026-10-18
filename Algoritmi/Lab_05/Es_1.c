#include<stdio.h>
#include <stdlib.h>

#define FILENAME "att1.txt"

//struttura che mi serve per definire le singole attività
typedef struct att {
    int i; 
    int f;
    int d;
} att;

//fa il controllo tra due attività per vedere se sono compatibili
int check (att a, att b){
    if (a.i < b.f && b.i < a.f) {
        return 0;
    }
    return 1;
}

//funzione ricorsiva: pos cicla su sol, best_sol è l'ottima fino a quel momento
//*max durata massima fino a quel momento, *sum durata della sol parziale
//start per "forzare" l'ordine, *len la lunghezzza della best sol
void att_Sel_r (int pos, int *sol, int *best_sol, int N, att *V, int *max, int *sum, int start, int *len){
    int i;

    //se la somma della sol parziale trovata finora è maggiore di quella trovata in precedenza
    //questa è la migliore, allora salvala
    if (*sum > *max){
        for (i = 0; i < pos; i++){
            best_sol[i] = sol[i];
        }
        *max = *sum;
        *len = pos;
    }

    //caso base
    if (start >= N){
        return;
    }

    //se pos è diverso da 0 ci sono dei controlli aggiuntivi
    if (pos != 0){
        for (i = start; i < N; i++){
            //parto da start (che aumenta ad ogni chiamata ricorsiva)
            int control = 1;
            //ciclo sulla sol parziale fino ad adesso
            for (int j = pos-1; j >= 0 && control; j--){
                control = check (V[i], V[sol[j]]);
            }
            //se le attività sono compatibili
            if (control){
                //butta dentro sol
                sol[pos] = i;
                *sum = *sum + V[i].d;
                att_Sel_r (pos+1, sol, best_sol, N, V, max, sum, i+1, len);
                //backtracking
                *sum = *sum - V[i].d;
            }
        }
    }
    else{   //caso in cui pos = 0, quindi tutto l'insieme è valido
        for (i = 0; i < N; i++){
            *sum = *sum + V[i].d;
            sol[pos] = i;
            att_Sel_r (pos+1, sol, best_sol, N, V, max, sum, i+1, len);
            *sum = *sum - V[i].d;
        }    
    }

    return;
}

//wrapper che alloca le struttur, libera e stampa la soluzione trovata
void attSel (int N, att *V){
    int *sol = malloc (N * sizeof (att));
    int *best_sol = malloc (N*sizeof (att));
    int len = 0, max = 0, sum = 0;

    att_Sel_r (0, sol, best_sol, N, V, &max, &sum, 0, &len);
    for (int i = 0; i < len; i++){
        printf (" (%d %d) ", V[best_sol[i]].i, V[best_sol[i]].f);
    }
    printf ("\nValore massimo raggiunto: %d", max);

    free (sol);
    free (best_sol);
    return ;
}

void read_file (){

    int nr, i;

    //apro il file
    FILE *input_file;
    if ((input_file = fopen(FILENAME, "r")) == NULL){
        printf("Errore nell'apertura del file: \"%s\"", FILENAME);
        exit(-1);
    }

    //leggo il numero di righe del file
    fscanf (input_file, "%d", &nr);

    //alloco il vettore di strutture
    att *V = malloc (nr * sizeof (att));

    for (i = 0; i < nr; i++){
        fscanf (input_file, "%d %d", &V[i].i, &V[i].f);
        V[i].d = V[i].f - V[i].i;
    }

    //chiamo il wrapper
    attSel (nr, V);

    free (V);
    fclose(input_file);
    return;
}

int main(int argc, char* argv[]){
    
    read_file();

    printf("\n");
    return 0;
}