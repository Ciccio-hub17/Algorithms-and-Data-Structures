#include<stdio.h>
#include<stdlib.h>
#include <time.h>

#define FILENAME "test_set.txt"

#define NUM_STONES 4
#define zaffiro 0
#define rubino 1
#define topazio 2
#define smeraldo 3

//Uso questa matrice per "forzare" qual è la prossima pietra da mettere dopo averne messa una
int mat_next [][2] = {{zaffiro, rubino}, {topazio, smeraldo}, {rubino, zaffiro}, {topazio, smeraldo}};

//stringa che mi serve per stampare in maniera più leggibile
char index_to_stone[] = "zrts\0";

//lei si prende in input: POS: cicla sulla soluzione; *sol e *best_sol autoesplicativi
//*len: lunghezza best_sol; *current_value: valore della collana che sto provando adesso;
//*max_value: il valore dell'ottimo trovato fino a quel momento
//*value: valore di ogni singola pietra
//nStones e *stones: somma degli elemento del vettore stones e quante pietre ci sono
//max_val_disp: valore massimo possibile (stones[i]*value[i])
//*nz e *ns: numero di zaffiri e smeraldi
//max_rip: numero massimo di ripetizioni possibile
void recursive_function (int pos, int *sol, int *best_sol, int *len, int *current_value, int *max_value, int *value, int nStones, int *stones, int max_val_disp, int *nz, int *ns, int max_rip){
    int i, j, count;
    //controllo se nella soluione parziale ci sono più zaffiri che smeraldi, se è cosi, taglia il ramo
    if (*nz > *ns){
        return;
    }

    //se trovo una collana valida che ha un valore superiore a un ottimo che avevo trovato in precedenza
    //aggiorna l'ottimo e la lunghezza di esso
    if (*current_value > *max_value){
        *max_value = *current_value;
        for (i = 0; i < pos; i++){
            best_sol[i] = sol[i];
        }
        *len = pos;
    }

    //se con il valore della collana + il valore rimasto non riesco a raggiungere il massimo
    //non ha senso continuare questo ramo, quindi taglialo (pruning)
    int residue_value = 0;
    for (i = 0; i < NUM_STONES; i++){
        residue_value += stones[i]*value[i];
    }
    if (residue_value + *current_value < *max_value){
        return;
    }

    //caso base
    if (pos >= nStones || *max_value >= max_val_disp){
        return;
    }

    //devo fare la distinzione tra pos == 0 e != 0 perche ho da controllare la ripetizione delle pietre
    if (pos != 0){
        for (j = 0; j < 2; j++){    //ciclo che prova a mettere le due possibili pietre successive dalla matrice
            sol[pos] = mat_next[sol[pos-1]][j]; //provo ad inserire la pietra guardando quella prima
            i = pos-1; count = 1;
            while (i >= 0 && sol[i] == sol[pos]){   //controllo che mi serve per capire se la pietra ha superato la soglia massima di ripetizioni consecutive
                count++;
                i--;                
            }
            if (count <= max_rip && stones[sol[pos]] > 0){  //se la pietra si può inserire
                stones[sol[pos]]--;
                //segnati se è uno zaffiro o uno smeraldo
                if (sol[pos] == zaffiro){
                    (*nz)++;
                }
                if (sol[pos] == smeraldo){
                    (*ns)++;
                }
                *current_value = *current_value + value[sol[pos]];  //aggiorna il valore
                //prova a continuare la soluzione
                recursive_function (pos+1, sol, best_sol, len, current_value, max_value, value, nStones, stones, max_val_disp, nz, ns, max_rip);
                //qui faccio backtracking
                stones[sol[pos]]++;
                *current_value = *current_value - value[sol[pos]];
                if (sol[pos] == zaffiro){
                    (*nz)--;
                }
                if (sol[pos] == smeraldo){
                    (*ns)--;
                }
            }
        }
    }
    else{
        //qui invece metto la prima pietra, quindi prova ad esplorare tutte e 4 le possibilità
        for (i = 0; i < NUM_STONES; i++){
            //si opera allo stesso modo di prima
            sol[pos] = i;
            if (stones[i] > 0){
                stones[sol[pos]]--;
                if (sol[pos] == zaffiro){
                    (*nz)++;
                }
                if (sol[pos] == smeraldo){
                    (*ns)++;
                }
                *current_value = *current_value + value[sol[pos]];
                recursive_function (pos+1, sol, best_sol, len, current_value, max_value, value, nStones, stones, max_val_disp, nz, ns, max_rip);
                stones[sol[pos]]++;
                *current_value = *current_value - value[sol[pos]];
                if (sol[pos] == zaffiro){
                    (*nz)--;
                }
                if (sol[pos] == smeraldo){
                    (*ns)--;
                }

            }
        }
    }

    return;
}

void calculate_max_value_necklace (int nStones, int max_rip, int max_val, int *stones, int *value){

    //iniziaizzo la soluzione (che inizialmente può essere massima, e quella migliore)
    int len = 0, i, max_necklace_value = 0, necklace_value = 0, nz = 0, ns = 0;
    int *sol = malloc (nStones*sizeof (int));
    int *best_sol = malloc (nStones*sizeof (int));
    recursive_function (0, sol, best_sol, &len, &necklace_value, &max_necklace_value, value, nStones, stones, max_val, &nz, &ns, max_rip);
    for (i = 0; i < len; i++){  //stampo la migliore
        printf (" %c ", index_to_stone[best_sol[i]]);
    }
    printf ("(Valore collana %d, lunghezza %d gemma/e)", max_necklace_value, len);
    printf ("\n");
    free (sol);
    free(best_sol);
    return ;
}

void read_file (){

    int nr, i;

    FILE *input_file;   //leggo il file
    if ((input_file = fopen(FILENAME, "r")) == NULL){
        printf("Errore nell'apertura del file: \"%s\"", FILENAME);
        exit(-1);
    }
    
    fscanf (input_file, "%d", &nr); //leggo le righe

    //inizializzo il vettore che mi dice quante pietre ci sono e il valore di ogni pietra
    int *stones = malloc (NUM_STONES*sizeof (int)), *value = malloc (NUM_STONES*sizeof (int)), max_rip, max_val, nstones;

    //calcolo l'ottimo per ogni riga
    for (i = 0; i < nr; i++){
        max_val = 0;
        nstones = 0;
        for (int j = 0; j < NUM_STONES; j++){
            fscanf (input_file, "%d", &stones[j]);
        }
        for (int j = 0; j < NUM_STONES; j++){
            fscanf (input_file, "%d", &value[j]);
            nstones += stones[j];
        }
        for (int j = 0; j < NUM_STONES; j++){
            max_val += stones[j]*value[j];
        }

        fscanf (input_file, "%d", &max_rip);
        printf ("\nRiga %d: ", i+1);
        calculate_max_value_necklace (nstones, max_rip, max_val, stones, value);
    }

    //libero la memoria
    free (stones); 
    free (value);

    fclose(input_file);
    return;
}

int main(int argc, char* argv[]){
    
    clock_t inizio = clock ();

    read_file ();

    clock_t fine = clock ();

    printf ("%.2f secondi", (float)(fine-inizio) / CLOCKS_PER_SEC);
    //calcolo il tempo necessario all'esecuzione per vedere quanto è efficiente

    
    printf("\n");
    return 0;
}