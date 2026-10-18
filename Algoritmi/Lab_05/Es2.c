#include<stdio.h>
#include <stdlib.h>

#define TILES "tiles.txt"
#define BOARD "board.txt"
#define NOT_ROT 0
#define ROT 1

//struttura che ha dentro due vettori, rispettivamente le due posizioni sono i colori/valori dei due tubi
typedef struct tiles {
    char colour[2];
    int value [2];
}tiles;

void free_mem (tiles *vet, int **sol, int *mark, int *rot, int nr){
    free (vet);
    free (mark);
    free (rot);
    for (int i = 0; i < nr; i++){
        free (sol[i]);
    }
    free (sol);
    return ;
}

//funzione che copia la sol nella best sol (viene chiamata quando il massimo della soluzione
//corrente è maggiore del massimo trovato in precedenza)
void copy_solution (int **sol, int **best_sol, int nr, int nc, int *best_rot, int n_tiles, int *rot_vet){
    for (int i = 0; i < nr; i++){
        for (int j = 0; j < nc; j++){
            best_sol[i][j] = sol[i][j];
        }
    }
    for (int i = 0; i < n_tiles; i++){
        best_rot[i] = rot_vet[i];
    }

    return;
}

//serve per calcolare il valore della soluzione corrente
//quindi cambia tutti i valori del vettore di rotazione (ruota tutte le caselle)
void rotate_vector (int *rot_vet, int n_tiles){
    for (int i = 0; i < n_tiles; i++){
        rot_vet[i] = !rot_vet[i];
    }
    return;
}

//calcola il valore di una soluzione
int calculate_value (int nr, int nc, int **sol, tiles *val, int *rot_vet, int *mark, int n_tiles){
    int i, j, flag = 1, max = 0, card0, card1;
    //ciclo sulla soluzione (una matrice di interi che fanno da indici)
    for (i = 0; i < nr; i++){
        //per ogni riga assumo ceh tutti i colori siano uguali
        flag = 1;
        for (j = 1; j < nc && flag; j++){
            //mi segno l'indice corrente e quello precedente
            card0 = sol[i][j];
            card1 = sol[i][j-1];
            //appena trovo che sono diversi, esco, perchè tanto la riga non è valida
            if (val[card0].colour[rot_vet[card0]] != val[card1].colour[rot_vet[card1]]){
                flag = 0;
            }
        }
        //se invece è valida, conta
        if (flag){
            for (j = 0; j < nc; j++){
                max += val[sol[i][j]].value[rot_vet[sol[i][j]]];
            }
        }
    }

    //ruota tutte le caselle per contare le colonne
    rotate_vector (rot_vet, n_tiles);
    //fai l stessa cosa di prima a par3ti invertite
    for (j = 0; j < nc; j++){
        flag = 1;
        for (i = 1; i < nr && flag; i++){
            card0 = sol[i][j];
            card1 = sol[i-1][j];
            if (val[card0].colour[rot_vet[card0]] != val[card1].colour[rot_vet[card1]]){
                flag = 0;
            }
        }
        if (flag){
            for (i = 0; i < nr; i++){
                max += val[sol[i][j]].value[rot_vet[sol[i][j]]];
            }
        }
    }
    rotate_vector (rot_vet, n_tiles);

    return max;
}

void calculate_best_board_r (int n_tiles, int **sol, int **best_sol, int *max, tiles *val, int *rot_vet, int *mark, int n_tiles_max, int nr, int nc, int posr, int posc, int *best_rot){
    int i, j;

    //caso terminale
    if (n_tiles <= 0){
        //calcola il valore della soluzione corrente
        int current = calculate_value (nr, nc, sol, val, rot_vet, mark, n_tiles_max);
        //se la soluzione corrente vale più del massimo finora
        if (current > *max){
            //copia la soluzione
            copy_solution (sol, best_sol, nr, nc, best_rot, n_tiles_max, rot_vet);
            //aggiorna il massimo
            *max = current;
        }
        return;
    }
    //while che serve per spostarsi fino a quando non si trova una casella libera
    while (posr < nr && sol[posr][posc] != -1){
        if (posc == nc-1){
            posr++;
            posc = 0;
        }
        else{
            posc++;
        }
    }

    //cicla sul vettore val 
    for (i = 0; i < n_tiles_max; i++){
        //se la tessera è disponibile e la casella è vuota, allora inserisci
        if (mark[i] == 0){
            mark[i] = 1;    //segna che è stata presa
            sol[posr][posc] = i;    //inserisci nella soluzione
            n_tiles--;  //diminuisci il numero di tessere ancora disponibili

            //devo fare un if perche se mi trovo nell'ultimo elemento della riga devo andare al primo di quella successiva
            if (posc == nc-1){
                calculate_best_board_r (n_tiles, sol, best_sol, max, val, rot_vet, mark, n_tiles_max, nr, nc, posr+1, 0, best_rot);
            }
            else{
                calculate_best_board_r (n_tiles, sol, best_sol, max, val, rot_vet, mark, n_tiles_max, nr, nc, posr, posc+1, best_rot);
            }

            //dopo aver vautato il primo ramo, valuta lo stesso ma con la tessera ruotata
            rot_vet[i] = !rot_vet[i];
            if (posc == nc-1){
                calculate_best_board_r (n_tiles, sol, best_sol, max, val, rot_vet, mark, n_tiles_max, nr, nc, posr+1, 0, best_rot);
            }
            else{
                calculate_best_board_r (n_tiles, sol, best_sol, max, val, rot_vet, mark, n_tiles_max, nr, nc, posr, posc+1, best_rot);
            }
            //fai backtracking
            rot_vet[i] = !rot_vet[i];
            n_tiles++;
            mark[i] = 0;
            sol[posr][posc] = -1;
        }
    }

    return ;

}

//wrapper della funzione ricorsiva, serve per allocare, stampare e distruggere la best sol
void calculate_best_board_wrapper (int n_tiles, int nr, int nc, int **sol, tiles *val, int *rot_vet, int *mark){
    int i, j, n_tiles_remaning = n_tiles;
    int **best_sol = malloc (nr*sizeof (int*)), max = 0;
    for (i = 0; i < nr; i++){
        best_sol[i] = (int*) malloc (nc*sizeof(int));
    }
    int *best_rot = calloc (n_tiles, sizeof (int));

    for (i = 0; i < nr; i++){
        for (j = 0; j < nc; j++){
            if (sol[i][j] > -1){
                n_tiles_remaning--;
            }
        }
    }

    calculate_best_board_r (n_tiles_remaning, sol, best_sol, &max, val, rot_vet, mark, n_tiles, nr, nc, 0, 0, best_rot);

    printf ("Soluzione ottima:\n\n");
    printf ("Calcolo per righe\n");
    for (i = 0; i < nr; i++){
        for (j = 0; j < nc; j++){
            printf (" %c%d", val[best_sol[i][j]].colour[best_rot[best_sol[i][j]]], val[best_sol[i][j]].value[best_rot[best_sol[i][j]]]);
        }
        printf ("\n");
    }

    printf ("Calcolo per colonne\n");
    rotate_vector (best_rot, n_tiles);
    for (i = 0; i < nr; i++){
        for (j = 0; j < nc; j++){
            printf (" %c%d", val[best_sol[i][j]].colour[best_rot[best_sol[i][j]]], val[best_sol[i][j]].value[best_rot[best_sol[i][j]]]);
        }
        printf ("\n");
    }
    printf ("Massimo trovato: %d", max);
    rotate_vector (best_rot, n_tiles);

    for (i = 0; i < nr; i++){
        free (best_sol[i]);
    }
    free (best_sol);
    free (best_rot);
    return;
}

int read_tiles (tiles **vet, int **rot_vet, int **mark){

    //un vettore temporaneo per val
    tiles *temp_vet;

    int n_tiles, i, *rot_vet_temp, *mark_temp;

    FILE *input_file;
    if ((input_file = fopen(TILES, "r")) == NULL){
        printf("Errore nell'apertura del file: \"%s\"", TILES);
        exit(-1);
    }

    //leggo il numero di tessere
    fscanf (input_file, "%d", &n_tiles);

    //alloco il vettore val, il vettore di rotazione e il vettore di presenza
    temp_vet = (tiles*) malloc (n_tiles*sizeof (tiles));
    rot_vet_temp = (int *) calloc (n_tiles, sizeof (int));
    mark_temp = (int *) calloc (n_tiles, sizeof (int));

    //inizalizzo il vettore val
    for (i = 0; i < n_tiles; i++){
        fscanf (input_file, "%*c %*d %*c %*d");
        fscanf (input_file, "%c %d %c %d", &(temp_vet[i].colour[0]), &(temp_vet[i].value[0]), &(temp_vet[i].colour[1]), &(temp_vet[i].value[1]));
    }
    
    fclose(input_file);

    //ritorno dei puntatori al main
    *vet = temp_vet;
    *rot_vet = rot_vet_temp;
    *mark = mark_temp;

    //ritorno il numero di tessere
    return n_tiles;
}

void read_board (int *nr, int *nc, int ***sol, tiles *val, int *rot_vet, int *mark){

    int **sol_temp, i, j, card, rotation;

    FILE *input_file;
    if ((input_file = fopen(BOARD, "r")) == NULL){
        printf("Errore nell'apertura del file: \"%s\"", BOARD);
        exit(-1);
    }
    
    //leggo le dimensioni del campo da gioco
    fscanf (input_file, "%d %d", nr, nc);
    //cosi da poter allocare la soluzione
    sol_temp = (int**) malloc (*nr * sizeof (int*));
    for (i = 0; i < *nr; i++){
        sol_temp[i] = (int*) malloc (*nc*sizeof (int));
    }

    //leggo il campo da gioco
    for (i = 0; i < *nr; i++){
        for (j = 0; j < *nc; j++){
            fscanf (input_file, "%d/%d ", &card, &rotation);
            //se la casella non è vuota
            if (card > -1){
                sol_temp[i][j] = card;
                rot_vet[card] = rotation;
                mark[card] = 1;

            }
            else{
                //altrimenti fai che sia vuota
                sol_temp[i][j] = card;
            }
        }
    }

    fclose(input_file);

    //ritorno al main il puntatore del vettore soluzione
    *sol = sol_temp;
    return;
}

int main(int argc, char* argv[]){
    
    tiles *vet_tiles;
    int nr, nc, n_tiles, **mat_sol, *rot_vet, *mark;

    n_tiles = read_tiles (&vet_tiles, &rot_vet, &mark);

    read_board (&nr, &nc, &mat_sol, vet_tiles, rot_vet, mark);

    calculate_best_board_wrapper (n_tiles, nr, nc, mat_sol, vet_tiles, rot_vet, mark);

    printf("\n");
    return 0;
}