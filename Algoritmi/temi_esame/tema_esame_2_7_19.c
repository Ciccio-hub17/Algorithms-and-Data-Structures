#include<stdio.h>
#include<stdlib.h>
#define MAX 300

int **read_matrix (char *filename, int *V, int *pop);

/*Formato libero proposto:
Prima riga: dist_max
Seconda riga: stazMin numero di stazioni poisizionate
seguono stazMin righe con gli indici della città in cui la stazione è posizionata
*/

int check_valid (int **madj, int V, int dist_max, int *staz, int num_staz){
    int i, j, flag;
    for (i = 0; i < V; i++){
        flag = 0;
        for (j = 0; j < num_staz && !flag; j++){
            if (madj[i][staz[j]] <= dist_max){
                flag = 1;
            }
        }
        if (flag == 0){
            return 0;
        }
    }
    return 1;
    
}

void fun_ob_1 (int *sol, int pos, int dist_max, int **madj, int V, int *flag, int *min_staz, int start, int k){

    int i, j;
    if (*flag == 0) return;

    if (pos >= k && check_valid (madj, V, dist_max, sol, pos)){
        *flag = 0;
        *min_staz = pos;
        return;
    }
    if (pos >= k){
        return;
    }

    for (i = start; i < V && *flag; i++){
        sol[pos] = i;
        fun_ob_1 (sol, pos+1, dist_max, madj, V, flag, min_staz, i+1, k);
    }
    return;
}

void fun_ob_1_w (int V, int **madj, int dist_max, int *staz, int num_staz){
    int min_staz = 0, *sol = calloc (V, sizeof(int)), flag = 1;

    //Richiesta 1
    int valid = check_valid (madj, V, dist_max, staz, num_staz);
    if (valid){
        for (int i = 0; i <= num_staz && flag; i++){
            fun_ob_1 (sol, 0, dist_max, madj, V, &flag, &min_staz, 0, i);
        }
    }
    if (min_staz == num_staz && valid){
        printf ("La soluzione letta è ottima\n");
    }
    else{
        printf ("La soluzione letta non rispetta la funzione obiettivo 1\n");
    }

    min_staz = 0; for (int i = 0; i < V; i++) sol[i] = 0; flag = 1;

    //Richiesta 2
    for (int i = 0; i < V && flag; i++){
        fun_ob_1 (sol, 0, dist_max, madj, V, &flag, &min_staz, 0, i);
    }

    printf ("Soluzione ottima con %d stazioni posizionate nelle seguenti città\n", min_staz);
}

void fun_ob_2 (int *sol, int numStaz, int *pop, int *stazComune, int V, int *min, int **madj, int *dist, int *numStazDistMin, int start){
    int i, j, min_i = MAX, m;

    if (numStaz <= 0){
        int cur_val = 0;
        for (i = 0; i < V; i++){
            dist[i] = MAX;
        }
        for (i = 0; i < V; i++){
            if (sol[i] != 0){
                for (j = 0; j < V; j++){
                    if (madj[i][j] < dist[j]){
                        dist[j] = madj[i][j];
                        numStazDistMin[j] = sol[i];
                    }
                }
            }
        }

        for (i = 0; i < V; i++){
            cur_val += pop[i]*dist[i]/numStazDistMin[i];
        }
        
        if (cur_val < *min){
            *min = cur_val;
        }
        return;
    }

    for (i = start; i < V; i++){
        if (stazComune[i] != 0){
            sol[i]++;
            stazComune[i]--;

            fun_ob_2 (sol, numStaz-1, pop, stazComune, V, min, madj, dist, numStazDistMin, i);
            
            sol[i]--;
            stazComune[i]++;
        }
    }
    return;
}

void fun_ob_2_w (int numStaz, int *stazComune, int *pop, int V, int **madj){
    int *sol = calloc (V, sizeof (int)), min = MAX, *dist = malloc (V*sizeof(int)), *numStazDistMin = malloc (V*sizeof(int));
    
    fun_ob_2 (sol, numStaz, pop, stazComune, V, &min, madj, dist, numStazDistMin, 0);
    printf ("Soluzione minima trovata con %d stazioni posizionate nelle seguenti città\n", numStaz);
}

int main(int argc, char* argv[]){
    
    printf("\n");
    return 0;
}