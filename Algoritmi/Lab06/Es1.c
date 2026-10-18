#include<stdio.h>
#include <stdlib.h>

#define FILENAME "att3.txt"

typedef struct activity {
    int start;
    int end;
    int d;
} activity;


//funzione che ritorna il risultato per capire se due attività si sovrappongono
int control (activity act1, activity act2){
    int flag = 1;

    if (act1.start < act2.end && act2.start < act1.end){
        return !flag;
    }
    return flag;
}

int read_file (activity **val){

    int nr, i;
    activity *val_temp;

    FILE *input_file;
    if ((input_file = fopen(FILENAME, "r")) == NULL){
        printf("Errore nell'apertura del file: \"%s\"", FILENAME);
        exit(-1);
    }
    
    fscanf (input_file, "%d", &nr);

    //vettore temporaneo per allocare la struttura dati
    val_temp = malloc (nr*sizeof (activity));

    for (i = 0; i < nr; i++){
        fscanf (input_file, "%d %d", &(val_temp[i].start), &(val_temp[i].end));
        val_temp[i].d = val_temp[i].end - val_temp[i].start;
    }

    *val = val_temp;

    fclose(input_file);
    return nr;
}


//funzione che mi serve per ordinare il vettore in ordine di start crescenti
void merge (activity *val, int l, int r, int c, int n){
    int i = l, j = c+1, k = l;
    activity *val_temp = malloc (n*sizeof (activity));

    int start1, start2;

    while (i <= c && j <= r){
        start1 = val[i].start; start2 = val[j].start; 
        if (start1 <= start2){
            val_temp[k] = val[i++];
        }
        else{
            val_temp[k] = val[j++];
        }
        k++;
    }

    while (i <= c){
        val_temp[k++] = val[i++];
    }
    while (j <= r){
        val_temp[k++] = val[j++];
    }

    for (i = l; i < r; i++){
        val[i] = val_temp[i];
    }

    free (val_temp);
    return;
}


//è un merge_sort classico
void sort_struct (activity *val, int l, int r, int n){
    if (l >= r){
        return ;
    }

    int c = (l+r)/2;

    sort_struct (val, l, c, n);
    sort_struct (val, c+1, r, n);
    merge (val, l, r, c, n);
}


//vede il vettore last e capisce qual è il valore massimo al suo interno
void calculate_best_sol (activity *val, int *pos, int *last, int n){
    int max = 0, index = -1;
    int i;
    for (i = 0; i < n; i++){
        if (last[i] > max){
            max = last[i];
            index = i;
        }
    }

    printf ("Soluzione massima con durata %d\n", max);
    while (index != -1){
        printf ("( %d %d ) ", val[index].start, val[index].end);
        index = pos[index];
    }
    printf ("\n");
    return;
}

//usando la programmazione dinamica 
void pd (activity *val, int n){
    int *pos = malloc (n*sizeof (int));
    int *last = malloc (n * sizeof(int));

    int i, j, maxd = 0, index = 0;

    for (i = 0; i < n; i++){
        pos[0] = -1; last[i] = val[i].d;
        maxd = 0; index = -1;
        for (j = 0; j < i; j++){
            if (control (val[j], val[i]) && (last[j] > maxd)){
                maxd = last[j];
                index = j;
            }
        }
        pos[i] = index; last[i] += maxd;
    }

    calculate_best_sol (val, pos, last, n);

    free (pos); free (last);
    return;
}

int main(int argc, char* argv[]){

    activity *val;

    int nr = read_file (&val);

    sort_struct (val, 0, nr-1, nr);

    pd (val, nr);
    
    free (val);

    printf("\n");
    return 0;
}