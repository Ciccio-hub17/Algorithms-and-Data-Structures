#include<stdio.h>
#include<stdlib.h>

#define FILENAME "grafo.txt"

void leggifile (int *num_vert, int *num_archi, int ***archi, int **vertici){

    int **archi_temp, *vert_temp, i, pos = 0, j, flag;  //creo le variabili temporanee 
    FILE *input_file = fopen (FILENAME, "r");   //apro il file
    if (input_file == NULL){
        printf ("File non trovato, uscita\n");  //controllo se esiste
        exit (1);
    }

    fscanf (input_file, "%d %d", num_vert, num_archi); //leggo il numero di vertici e di archi

    //alloco dinamicamente le strutture che mi servono
    vert_temp = (int*) malloc (*num_archi * sizeof (int));

    archi_temp = (int**) malloc (*num_vert * sizeof (int*));  
    for (i = 0; i < *num_archi; i++){
        archi_temp[i] = (int*) malloc (2*sizeof (int));
    }

    //leggo effettivamente il file
    for (i = 0; i < *num_archi; i++){
        fscanf (input_file, "%d %d", &archi_temp[i][0], &archi_temp[i][1]);
        flag = 1;
        //controllo se ciò che ho letto è, già presente nel vettore dei vertici
        for (j = 0; j < pos && flag; j++){
            if (archi_temp[i][0] == vert_temp[j]){
                flag = 0;
            }
        }
        if (flag){
            vert_temp[pos++] = archi_temp[i][0];
        }
        flag = 1;
        for (j = 0; j < pos && flag; j++){
            if (archi_temp[i][1] == vert_temp[j]){
                flag = 0;
            }
        }
        if (flag){
            vert_temp[pos++] = archi_temp[i][1];
        }
    }

    //ritorno al main 
    *archi = archi_temp;
    *vertici = vert_temp;

    return;
}

int control (int *sol, int **archi, int pos, int num_archi){
    int i, j, flag = 1;
    //ciclo PER OGNI ARCO
    for (i = 0; i < num_archi && flag; i++){
            flag = 0;   //assumo che la soluzione non va bene
            //Questo for serve per comprendere se ogni arco è coperto da almeno 1 dei nodi della soluzione
            for (j = 0; j < pos && !flag; j++){
                if (sol[j] == archi[i][0] || sol[j] == archi[i][1]){
                    //se effettivamente c'è un arco che non è coperto, cambia il flag
                    flag = 1;
                }
                
            }
        }
    return flag;
}

//un powerset ricorsivo con una flag di controllo per vedere se la soluzione è valida
int vertex_cover (int *sol, int *vert, int **archi, int pos, int num_vert, int num_archi, int cnt, int start){
    if (start >= num_vert){
        int flag = control (sol, archi, pos, num_archi);
        if (flag == 0 || pos == 0){
            return cnt;
        }
        else{
            printf ("(");
            for (int i = 0; i < pos; i++){
                printf (" %d ", sol[i]);
            }
            printf (")\n\n");
        }

        return cnt+1;
    }
    for (int i = start; i < num_vert; i++){
        sol[pos] = vert[i];
        cnt = vertex_cover (sol, vert, archi, pos+1, num_vert, num_archi, cnt, i+1);
    }
    cnt = vertex_cover (sol, vert, archi, pos, num_vert, num_archi, cnt, num_vert);
    return cnt;
}

//libera la memoria precedentemente allocata
void free_memory (int **archi, int *vertici, int num_archi, int *sol){
    free (vertici);
    for (int i = 0; i < num_archi; i++){
        free (archi[i]);
    }
    free (archi);
    free (sol);
    return ;
}

int main (){

    int num_vert, num_archi, **archi, *vertici;

    leggifile (&num_vert, &num_archi, &archi, &vertici);

    int *sol = malloc (num_vert * sizeof(int));

    printf ("Elenco dei vertex cover del grafo:\n\n");
    int cnt = vertex_cover (sol, vertici, archi, 0, num_vert, num_archi, 0, 0);
    printf ("\nI vertex cover sono %d\n", cnt);

    free_memory (archi, vertici, num_archi, sol);

    printf ("\n");
    return 0;
}