#include<stdio.h>
#include <stdlib.h>
#include<string.h>
//Si Usa il principio della moltiplicazione

#define MAX_S 255

typedef struct {char **scelte; int n_scelte; } livello;

void readfile_allocation (livello **val, char ***sol, int *dim){
    FILE *input_file = fopen ("brani.txt", "r");
    if (input_file == NULL){
        exit (1);
    }

    livello *val_tmp;
    char **sol_tmp;
    int i, j;
    fscanf (input_file, "%d", dim);

    val_tmp = (livello *) malloc ((*dim)*sizeof (livello));

    sol_tmp = (char **) malloc ((*dim)*sizeof(char *));
    for (i = 0; i < *dim; i++){
        sol_tmp[i] = (char *) malloc (MAX_S * sizeof (char));
    }

    for (i = 0; i < *dim; i++){
        fscanf (input_file, "%d", &val_tmp[i].n_scelte);
        val_tmp[i].scelte = (char **) malloc (val_tmp[i].n_scelte * sizeof (char *));
        for (j = 0; j < val_tmp[i].n_scelte; j++){
            val_tmp[i].scelte[j] = (char *) malloc (MAX_S * sizeof (char));
        }
        for (j = 0; j < val_tmp[i].n_scelte; j++){
            fscanf (input_file, "%s", val_tmp[i].scelte[j]);
        }
    }

    fclose (input_file);

    *val = val_tmp;
    *sol = sol_tmp;
}

int search_solutions (char **sol, livello *val, int n, int cnt, int pos){
    if (pos >= n){
        for (int i = 0; i < n; i++){
            printf ("%s\n", sol[i]);
        }
        printf ("\n");
        return cnt+1;
    }
    for (int i = 0; i < val[pos].n_scelte; i++){
        strcpy (sol[pos], val[pos].scelte[i]);
        cnt = search_solutions (sol, val, n, cnt, pos+1);
    }
    return cnt;
}

void deallocation (livello *val, char **sol, int dim){
    int i, j;
    for (i = 0; i < dim; i++){
        for (j = 0; j < val[i].n_scelte; j++){
            free (val[i].scelte[j]);
        }
        free (val[i].scelte);
        free (sol[i]);
    }
    free (val);
    free (sol);
}

int main (){
    livello *val;
    char **sol;
    int dim;
    
    readfile_allocation (&val, &sol, &dim);

    int cnt = search_solutions (sol, val, dim, 0, 0);

    printf ("Numero di playlist possibili: %d", cnt);
    
    deallocation (val, sol, dim);

    printf ("\n");
    return 0;
}