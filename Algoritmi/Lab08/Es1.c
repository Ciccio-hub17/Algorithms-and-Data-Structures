#include<stdio.h>
#include <stdlib.h>

#define FILENAME "elementi.txt"

//ESERCIZIO SVOLTO CON PARADIGMA GREEDY, NON TROVA L'OTTIMO TOTALE

#define MAX_S 100
#define MD 3
#define ME 5
#define SPECIAL_DIFF 8
#define COEFF 1.5
#define DD 10
#define DP 20

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
    float ratio;
}element;

void merge_sort (int l, int r, element *val, int n, int (*cmp) (element a, element b));
void merge (int l, int m, int r, element *val, int n, int (*cmp) (element a, element b));


//confronta il rapporto valore/difficoltà e ordina in maniera decrescente
int compare_ratio (element a, element b){

    if (a.ratio > b.ratio){
        return 0;
    }
    else if (a.ratio == b.ratio){
        if (a.type != transizione){
            return 0;
        }
        return 1;
    }
    return 1;
}

int compare_value (element a, element b){

    if (a.value > b.value){
        return 0;
    }
    else if (a.value == b.value){
        if (a.type != transizione){
            return 0;
        }
        return 1;
    }
    return 1;
}

//contronta solo la difficoltà e ordina in maniera crescente
int compare_diff (element a, element b){
    if (a.difficulty < b.difficulty){
        return 0;
    }
    else if (a.difficulty == b.difficulty){
        if (a.type != transizione){
            return 0;
        }
        return 1;
    }
    return 1;
}

void create_first_layer (element **diag, element *val, int n, int *total_diff, float *max){
    int i = 0, j, current_diff_diag = 0, acroAv = 0, acroIn = 0, k = 0;
    element *acro_el = malloc (n*sizeof (element));
    for (i = 0; i < n; i++){
        if (val[i].type != transizione){
            acro_el[k++] = val[i];
        }
    }

    i = 0;

    for (j = 0; j < k && i < 1; j++){
        if (acro_el[j].type == avanti && acro_el[j].final != non_puo_essere_seguito && acro_el[j].entry == fronteIng){
            if (current_diff_diag + acro_el[j].difficulty <= DD && *total_diff + acro_el[j].difficulty <= DP){
                diag[i++] = &acro_el[j];
                *max += acro_el[j].value;
                current_diff_diag += acro_el[j].difficulty;
                *total_diff += acro_el[j].difficulty;
            }
        }
    }

    for (j = 0; j < k  && i < 2; j++){
        if (acro_el[j].type != transizione && acro_el[j].entry == diag[i-1]->exit){
            if (current_diff_diag + acro_el[j].difficulty <= DD && *total_diff + acro_el[j].difficulty <= DP){
                diag[i++] = &acro_el[j];
                *max += acro_el[j].value;
                current_diff_diag += acro_el[j].difficulty;
                *total_diff += acro_el[j].difficulty;
            }
        }
    }

    for (i = 0; i < ME && diag[i] != NULL; i++){
        printf (" %s ", diag[i]->name);
    }
    printf ("\n");

    free (acro_el);
    return;
    
}

void create_second_layer (element **diag, element *val, int n, int *total_diff, float *max){
    int k, i = 0, j, l, current_diff_diag = 0, final = 0, linkable = 0, trovato = 0;

    for (j = 0; j < n && !trovato; j++){
        if (val[j].entry == fronteIng && val[j].final != non_puo_essere_seguito && val[j].value != 0.0){
            for (k = 0; k < n && !trovato; k++){
                if (val[k].type == indietro && current_diff_diag + val[j].difficulty + val[k].difficulty <= DD && *total_diff + val[j].difficulty + val[k].difficulty <= DP){
                    trovato = 1;
                    diag[i++] = &val[j];
                    diag[i++] = &val[k];
                    *max += val[j].value + val[k].value;
                    *total_diff += val[j].difficulty + val[k].difficulty;
                }
            } 
        }
    }

    for (i = 0; i < ME && diag[i] != NULL; i++){
        printf (" %s ", diag[i]->name);
    }
    printf ("\n");

    return;
}

void create_third_layer (element **diag, element *val, int n, int *total_diff, float *max){
    int i=0, j, k = 0, trovato = 0, current_diff_diag = 0, remaning = DP - *total_diff, inserito = 0;

    if (SPECIAL_DIFF > DD){
        for (j = 0; j < n; j++){
            if (val[j].entry == fronteIng && val[j].priority == primo && current_diff_diag + val[j].difficulty <= DD && *total_diff + val[j].difficulty <= DP){
                diag[i++] = &val[j];
                *max += val[j].value;
                current_diff_diag += val[j].difficulty;
                *total_diff += val[j].difficulty;
            }
        }

        for (j = 0; j < ME && diag[j] != NULL; j++){
            printf (" %s ", diag[j]->name);
        }
        printf ("\n");
        return;
    }

    if (remaning >= SPECIAL_DIFF){
        int possible = remaning - SPECIAL_DIFF;
        for (j = 0; j < n; j++){
            if (val[j].difficulty >= SPECIAL_DIFF){
                for (k = 0; k < n; k++){
                    if (val[k].entry == fronteIng && val[k].priority == primo && val[k].difficulty <= possible && current_diff_diag + val[j].difficulty + val[k].difficulty <= DD && *total_diff + val[j].difficulty + val[k].difficulty <= DP){
                        inserito = 1;
                        diag[i++] = &val[k];
                        diag[i++] = &val[j];
                        *max += COEFF*val[j].value + val[k].value;
                        printf (" %s ", diag[0]->name);
                        printf (" %s \n", diag[1]->name);
                        return;
                    }
                }
            }
        }
        for (j = 0; j < n; j++){
            if (val[j].difficulty >= SPECIAL_DIFF && val[j].entry == fronteIng && val[j].priority == primo && val[j].difficulty <= DD && *total_diff + val[j].difficulty <= DP){
                diag[i++] = &val[j];
                *max += COEFF*val[j].value;
                printf (" %s \n", diag[0]->name);
                return;
            }
        }
        for (j = 0; j < n; j++){
            if (val[j].entry == fronteIng && val[j].priority == primo && val[j].difficulty <= DD && *total_diff + val[j].difficulty <= DP){
                diag[i++] = &val[j];
                *max += val[j].value;
                printf (" %s \n", diag[0]->name);
                return;
            }
        }

    }

    return;

}

void merge (int l, int m, int r, element *val, int n, int (*cmp) (element a, element b)){
    int i = l, k = l, j = m+1;
    element *temp = malloc (n*sizeof (element));

    while (i <= m && j <= r){

        if (cmp (val[i], val[j]) == 0){
            temp[k] = val[i++];
        }
        else{
            temp[k] = val[j++];
        }
        k++;
    }

    while (i <= m){
        temp[k++] = val[i++];
    }

    while (j <= r){
        temp[k++] = val[j++];
    }

    for (i = l; i <= r; i++){
        val[i] = temp[i];
    }

    free (temp);

    return;

}

void merge_sort (int l, int r, element *val, int n, int (*cmp) (element a, element b)){
    if (l >= r){
        return;
    }

    int m = (l+r)/2;

    merge_sort (l, m, val, n, cmp);
    merge_sort (m+1, r, val, n, cmp);
    merge (l, m, r, val, n, cmp);
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
        val_temp[i].ratio = val_temp[i].value /(float)val_temp[i].difficulty;
    }
    fclose(input);

    *val = val_temp;
    return nr;
}

void best_sol_wrapper (int n, element *val){
    element ***sol;
    sol = malloc (MD*sizeof(element**));
    for (int i = 0; i < MD; i++){
        sol[i] = malloc (ME*sizeof (element*));
        for (int j = 0; j < ME; j++){
            sol[i][j] = NULL;
        }
    }

    int total_diff = 0;
    float max = 0.0;

    /*SPiegazione scelte fatte:
    Si costruisce una diagonale alla volta usando queste forzature:
    Nella prima diagonale voglio avere due elementi acrobatici in sequenza
    Nella seconda diagonale voglio avere L'elemento acrobatico indietro
    Nella terza diagonale si cerca di mettere l'elemento con difficoltà maggiore alla fine
    in modo tale da avere un punteggio più alto
    Usando questi criteri, le soluzioni formate sono semore valide (anche se mai ottime,
    in quanto senza backtracking è impossibile valutare se una soluzione è migliore di un'altra*/

    //Per la prima diagonale ordino per rapporto

    merge_sort (0, n-1, val, n, compare_ratio);

    create_first_layer (sol[0], val, n, &total_diff, &max);

    //Per la seconda diagonale ordino per difficoltà
    merge_sort (0, n-1, val, n, compare_diff);

    create_second_layer (sol[1], val, n, &total_diff, &max);

    //Per la terza diagonale ordino per rapporto
    merge_sort (0, n-1, val, n, compare_ratio);

    create_third_layer (sol[2], val, n, &total_diff, &max);

    printf ("Valore massimo %.2f\n", max);


    for (int i = 0; i < MD; i++){
        free (sol[i]);
    }
    free (sol);

    return;
}

int main(int argc, char* argv[]){

    element *val;

    int n = read_file (&val);

    best_sol_wrapper (n, val);

    free (val);

    printf("\n");
    return 0;
}