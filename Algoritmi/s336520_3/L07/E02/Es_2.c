#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include <time.h>

#define FILENAME "elementi.txt"

#define MAX_S 100
#define MD 3
#define ME 5
#define SPECIAL_DIFF 8
#define COEFF 1.5
#define DD 12
#define DP 28

typedef enum {transizione, indietro, avanti} tipologia;
typedef enum {spalleIng, fronteIng}ingresso;
typedef enum {spalleUsc, fronteUsc}uscita;
typedef enum {primo, preceduto}precedenza;
typedef enum {puo_essere_seguito, non_puo_essere_seguito}finale;

typedef struct element_s {
    char name[MAX_S];
    int type;
    int entry;
    int exit;
    int priority;
    int final;
    float value;
    int difficulty;
}element;

float caculate_max_diag_value (element ***all_diags, int n){
    float max = 0;
    for (int i = 0; i < n; i++){
        float diag_value = 0.0;
        for (int j = 0; j < ME && all_diags[i][j] != NULL; j++){
            diag_value += all_diags[i][j]->value;
        }
        if (diag_value > max){
            max = diag_value;
        }
    }
    return max;

}

int calculate_allocation (int n){
    int i;
    int count = 0;
    for (i = 1; i <= ME; i++){
        count += pow (n, i);
    }
    return count;
}

int evaluate_diag (element **diag){
    int i, acro = 0, current_diff = 0;

    for (i = 0; i < ME && diag[i] != NULL; i++){
        current_diff += diag[i]->difficulty;
        if (i != 0 && diag[i-1]->final == non_puo_essere_seguito){
            return 0;
        }
        if (diag[i]->type != transizione){
            acro = 1;
        }
    }
    if (current_diff > DD){
        return 0;
    }

    if (!acro){
        return 0;
    }
    return 1;
}

int control_best(element ***sol, float *total, int diff){
    int i, j, flagAvanti=0, flagIndietro=0, sequenza = 0;
    if (diff > DP){
        return 0;
    }

    for (int i = 0; i < MD; i++){
        for (int j = 0; j <ME && sol[i][j] != NULL; j++){
            if (sol[i][j]->type == avanti){
                flagAvanti = 1;
            }
            if (sol[i][j]->type == indietro){
                flagIndietro = 1;
            }
            if (j > 0 && sol[i][j]->type != transizione && sol[i][j-1]->type != transizione){
                sequenza = 1;
            }
        }
    }

    for (int i = 0; i < MD-1; i++){
        for (int j = 0; j < ME && sol[i][j] != NULL; j++){
            *total += sol[i][j]->value;
        }
    }
    int k = ME-1;
    while (sol[MD-1][k] == NULL){
        k--;
    }
    if (sol[MD-1][k]->difficulty >= SPECIAL_DIFF){
        float value_third_diag = 0.0;
        for (int j = 0; j < ME && sol[MD-1][j] != NULL; j++){
            value_third_diag += sol[MD-1][j]->value;
        } 
        *total += COEFF*value_third_diag;
    }
    else{
        for (int j = 0; j < ME && sol[MD-1][j] != NULL; j++){
            *total += sol[MD-1][j]->value;
        }
    }

    if (!flagAvanti){
        return 0;
    }
    if (!flagIndietro){
        return 0;
    }
    if (!sequenza){
        return 0;
    }
    return 1;
}

int evaluate_element (int pos, element **diag){
    if (pos == 0){
        if (diag[pos]->priority == primo && diag[pos]->entry == fronteIng){
            return 1;
        }
        return 0;
    }
    if (diag[pos-1]->exit == diag[pos]->entry){
        return 1;
    }
    return 0;
}

//carica gli elementi in un vettore di struct
int read_file (element **val){

    element *val_temp;
    int nr;

    FILE *input;
    if ((input = fopen(FILENAME, "r")) == NULL){
        printf("Errore nell'apertura del file: \"%s\"", FILENAME);
        exit(-1);
    }
    
    fscanf (input, "%d", &nr);

    val_temp = malloc (nr*sizeof (element));

    for (int i = 0; i < nr; i++){
        fscanf (input, "%s %d %d %d %d %d %f %d", val_temp[i].name, &(val_temp[i].type), &(val_temp[i].entry), &(val_temp[i].exit), &(val_temp[i].priority), &(val_temp[i].final), &(val_temp[i].value), &(val_temp[i].difficulty));
    }
    fclose(input);

    *val = val_temp;
    return nr;
}

void fill_all_diags (int n, element ***all_diags, int pos, int *matrix_line, int k, element *val, element **tmp_diag){
    if (pos >= k){
        if (evaluate_diag(tmp_diag)){
            for (int j = 0; j < pos; j++){
                all_diags[*matrix_line][j] = tmp_diag[j];
            }
            (*matrix_line)++;
        }
        return;
    }

    for (int i = 0; i < n; i++){
        tmp_diag[pos] = &val[i];
        if (evaluate_element (pos, tmp_diag)){
            fill_all_diags (n, all_diags, pos+1, matrix_line, k, val, tmp_diag);
        }
        tmp_diag[pos] = NULL;
        
    }

    return;
}

void calculate_best_solution (element ***best_sol, element ***sol, int n, int pos, float *max, element ***all_diags, int diff_until_now, float max_diag_value){
    if (pos >= MD){
        float totValue = 0.0;
        if (control_best (sol, &totValue, diff_until_now) && totValue > *max){
            for (int i = 0; i < MD; i++){
                for (int j = 0; j < ME; j++){
                    best_sol[i][j] = sol[i][j];
                }
            }
            *max = totValue;
        }

        return;
    }

    float current_value = 0;
    for (int i = 0; i < pos; i++){
        for (int j = 0; j < ME && sol[i][j] != NULL; j++){
            current_value += sol[i][j]->value;
        }
    }
    if (current_value +(MD-pos+1)*max_diag_value <= *max){
        return;
    }

    for (int i = 0; i < n; i++){
        sol[pos] = all_diags[i];

        for (int j = 0; j < ME && sol[pos][j] != NULL; j++){
            diff_until_now += sol[pos][j]->difficulty;
        }
        if (diff_until_now <= DP){
            calculate_best_solution (best_sol, sol, n, pos+1, max, all_diags, diff_until_now, max_diag_value);
        }

        for (int j = 0; j < ME && sol[pos][j] != NULL; j++){
            diff_until_now -= sol[pos][j]->difficulty;
        }
        sol[pos] = NULL;
    }
    return;
}

int wrapper_solution (int n, element *val, element ***all_diags, int count){
    element ***sol, ***best_sol;
    sol = malloc (MD*sizeof (element**));
    best_sol = malloc (MD*sizeof (element**));
    for (int i = 0; i < MD; i++){
        sol[i] = malloc (ME*sizeof (element *));
        best_sol[i] = malloc (ME*sizeof (element *));
        for (int j = 0; j < ME; j++){
            sol[i][j] = NULL;
            best_sol[i][j] = NULL;
        }
    }

    int matrix_line = 0;
    element **tmp_diag = malloc (ME*sizeof (element *));
    for (int i = 0; i < ME; i++){
        tmp_diag[i] = NULL;
    }

    for (int i = 1; i <= ME; i++){
        fill_all_diags (n, all_diags, 0, &matrix_line, i, val, tmp_diag);
    }

    all_diags = realloc (all_diags, matrix_line*sizeof (element **));

    float max = 0.0;

    float max_diag_value = caculate_max_diag_value (all_diags, matrix_line);

    printf ("Calcolo della soluzione migliore in corso...\n\n");

    calculate_best_solution (best_sol, sol, matrix_line, 0, &max, all_diags, 0, max_diag_value);

    printf ("Valore massimo %.2f\n", max);
    for (int i = 0; i < MD; i++){
        printf ("Diagonale %d:", i+1);
        for (int j = 0; j < ME && best_sol[i][j] != NULL; j++){
            printf (" %s ", best_sol[i][j]->name);
        }
        printf ("\n");
    }


    for (int i = 0; i < MD; i++){
        free(sol[i]);
        free (best_sol[i]);
    }
    free (sol);
    free (best_sol);
    free (tmp_diag);
    return matrix_line;
}

int main(int argc, char* argv[]){

    element *val;

    int n = read_file (&val);

    int count = calculate_allocation (n);

    element ***all_diags;

    all_diags = malloc (count*sizeof (element**));
    for (int i = 0; i < count; i++){
        all_diags[i] = malloc (ME * sizeof (element*));
        for (int j = 0; j < ME; j++){
            all_diags[i][j] = NULL;
        }
    }

    int new_count = wrapper_solution (n, val, all_diags, count);

    for (int i = 0; i < new_count; i++){
        free (all_diags[i]);
    }
    free (all_diags);

    free (val);
    
    printf("\n");
    return 0;
}