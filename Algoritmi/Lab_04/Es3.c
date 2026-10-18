#include<stdio.h>
#include<stdlib.h>
#include <time.h>

#define FILENAME "hard_test_set.txt"

#define LEN_VET 4
#define zaffiro 0
#define rubino 1
#define topazio 2
#define smeraldo 3
//Uso questa matrice per "forzare" qual è la prossima pietra da mettere dopo averne messa una
int mat_next [][2] = {{zaffiro, rubino}, {smeraldo, topazio}, {zaffiro, rubino}, {smeraldo, topazio}};


//filtri e strategie di pruning fatte in precedenza

/*int filter (int k, int *sol, int *stones){

    int *check_dim = calloc (LEN_VET, sizeof(int));
    check_dim[sol[k-1]]++;
    for (int i = 0; i < k-1; i++){
        check_dim[sol[i]]++;
        if ((sol[i] == zaffiro || sol[i] == topazio) && (sol[i+1] != zaffiro && sol[i+1] != rubino)){
            free (check_dim);
            return 0;
        }
        if ((sol[i] == rubino || sol[i] == smeraldo) && (sol[i+1] != smeraldo && sol[i+1] != topazio)){
            free (check_dim);
            return 0;
        }
    }
    
    for (int i = 0; i < LEN_VET; i++){
        if (check_dim[i] > stones[i]){
            free(check_dim);
            return 0;
        }
    }
    free (check_dim);
    return 1;
}*/

/*int pruning (int *sol, int pos){
    int i;
    for (int i = 1; i <= pos; i++){
        if ((sol[i] == zaffiro || sol[i] == rubino) && (sol[i-1] != zaffiro && sol[i-1] != topazio)){
            return 0;
        }
        if ((sol[i] == topazio || sol[i] == smeraldo) && (sol[i-1] != smeraldo && sol[i-1] != rubino)){
            return 0;
        }
    }
    return 1;
}*/

int disp_rep (int *sol, int *k, int pos, int *stones, int nStones, int *best_sol){

    int i;

    //se ho una lunghezza maggiore di quella massima trovata prima, aggiorna l'ottimo
    if (pos > *k){
        *k = pos;
        for (i = 0; i < *k; i++){
            best_sol[i] = sol[i];
        }
    }

    //se il numero di pietre rimaste più quelle nella soluzione è minore del massimo trovato prima, 
    //allora taglia il ramo
    int remaning = 0;
    for (i = 0; i < LEN_VET; i++){
        remaning += stones[i];
    }
    if (pos + remaning <= *k) { 
        return *k; 
    }

    //caso base
    if (pos >= nStones){
        return *k;
    }

    //distinguo i casi per "forzare" la soluzione mettendo le pietre giuste
    if (pos != 0){
        for (i = 0; i < 2; i++){
            int j = mat_next[sol[pos-1]][i];
                if (stones[j] > 0){
                    if (j == zaffiro || j == smeraldo){
                        int cnt = 0;
                        for (; stones[j] > 0; pos++, stones[j]--){
                            sol[pos] = j;
                            cnt++;
                        }
                        disp_rep (sol, k, pos, stones, nStones, best_sol);
                        for (; cnt > 0; pos--, stones[j]++, cnt--);
                    }
                    else{
                        sol[pos] = j;
                        stones[j]--;
                        disp_rep (sol, k, pos+1, stones, nStones, best_sol);
                        stones[j]++;    //backtracking
                    }
                }
        }
    }
    else {
        for (i = 0; i < LEN_VET; i++){
            if (stones[i] > 0){
                sol[pos] = i;
                stones[i]--;
                disp_rep (sol, k, pos+1, stones, nStones, best_sol);
                stones[i]++;
            }
        }
    }

    return *k;
    
}

void max_necklace (int total_stones, int *stones){
    int *sol, *best_sol, k = 0;
    sol = malloc (total_stones*sizeof(int));
    best_sol = malloc (total_stones*sizeof (int));
    k = disp_rep (sol, &k, 0, stones, total_stones, best_sol);
    for (int j = 0; j < k; j++){    //stampo la soluzione
        printf (" %d ", best_sol[j]);
    }
    printf (" len (%d)\n", k);       
    free (sol);
    free (best_sol);
    return;
}

void read_file (){

    int i;

    //leggo il file
    FILE *input;
    if ((input = fopen(FILENAME, "r")) == NULL){
        printf("Errore nell'apertura del file: \"%s\"", FILENAME);
        exit(-1);
    }

    int nLines, *Stones = malloc (LEN_VET*sizeof(int)), somma;

    fscanf (input, "%d", &nLines);

    for (i = 0; i < nLines; i++){   //per ogni riga calcolo la soluzione con più pietre
        fscanf (input, "%d %d %d %d", &Stones[0],  &Stones[1], &Stones[2], &Stones[3]);
        somma = Stones[0] + Stones[1] + Stones[2] + Stones[3];
        printf ("Riga %d: ", i+1);
        max_necklace (somma, Stones);
    }
    free (Stones);

    fclose(input);
    return;
}

int main (){
    
    read_file();

    printf ("\n");
    return 0;
}