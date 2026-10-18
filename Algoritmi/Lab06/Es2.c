#include <stdio.h>
#include <stdlib.h>

#define zaffiro 0
#define rubino 1
#define topazio 2
#define smeraldo 3
#define TYPES_STONES 4

#define FILENAME "hard_test_set.txt"


//quattro funzioni ricorsive identiche che si chiamano in maniera incrociata
int fZ (int nz, int nr, int nt, int ns, int *****mat_m);
int fR (int nz, int nr, int nt, int ns, int *****mat_m);
int fT (int nz, int nr, int nt, int ns, int *****mat_m);
int fS (int nz, int nr, int nt, int ns, int *****mat_m);

//wrapper
int wrapper_recursive_functions (int nz, int nr, int nt, int ns, int *****mat_m, int *c){
    int max_vet[TYPES_STONES], true_max;

    //calcolo il massimo iniziando con una pietra diversa
    max_vet[zaffiro] = fZ (nz, nr, nt, ns, mat_m);
    max_vet[rubino] = fR (nz, nr, nt, ns, mat_m);
    max_vet[topazio] = fT (nz, nr, nt, ns, mat_m);
    max_vet[smeraldo] = fS (nz, nr, nt, ns, mat_m);

    //calcola il migliore
    true_max = max_vet[zaffiro];
    *c = zaffiro;
    for (int i = 1; i < TYPES_STONES; i++){
        if (max_vet[i] > true_max){
            true_max = max_vet[i];
            //salvo l'indice
            *c = i;
        }
    }
    //ritorna
    return true_max;
}

void read_file_and_calculate (){
    int nrighe, i, j, stones, nz, nr, nt, ns, max, z, r, t, s, stone;
    //matrice della memoization
    int *****mat_m = (int*****) malloc (TYPES_STONES*sizeof (int****));
    
    FILE *input;
    if ((input = fopen(FILENAME, "r")) == NULL){
        printf("Errore nell'apertura del file: \"%s\"", FILENAME);
        exit(-1);
    }
    
    fscanf (input, "%d", &nrighe);

    for (i = 0; i < nrighe; i++){
        fscanf (input, "%d %d %d %d", &nz, &nr, &nt, &ns);

        //allocazione
        for (j = 0; j < TYPES_STONES; j++){
            mat_m[j] = (int****) malloc ((nz+1)*sizeof (int***));
            if (mat_m[j] == NULL){
                exit (1);
            }
            for (z = 0; z < nz+1; z++){
                mat_m[j][z] = (int***) malloc ((nr+1)*sizeof (int**));
                if (mat_m[j][z] == NULL){
                    exit (1);
                }
                for (r = 0; r < nr+1; r++){
                    mat_m[j][z][r] = (int**) malloc ((nt+1) * sizeof (int*));
                    if (mat_m[j][z][r] == NULL){
                        exit (1);
                    }
                    for (t = 0; t < nt+1; t++){
                        mat_m [j][z][r][t] = (int*) malloc ((ns+1) * sizeof (int));
                        if (mat_m[j][z][r][t] == NULL){
                            exit (1);
                        }
                        for (s = 0; s < ns+1; s++){
                            //inizializzazione
                            mat_m [j][z][r][t][s] = -1;
                        }
                    }
                }
            }
        }

        max = wrapper_recursive_functions (nz, nr, nt, ns, mat_m, &stone);
        printf ("Lunghezza massima possibile per riga %d: %d (pietra iniziale: %d)\n", i+1, max, stone);
        
        //libera
        for (j = 0; j < TYPES_STONES; j++){
            for (z = 0; z < nz+1; z++){
                for (r = 0; r < nr+1; r++){
                    for (t = 0; t < nt+1; t++){
                        free (mat_m [j][z][r][t]);
                    }
                    free (mat_m[j][z][r]);
                }
                free (mat_m[j][z]);
            }
            free (mat_m[j]);
        }
        
    }
    
    free (mat_m);
    fclose(input);
    return;
}

//ne commento una sola, tanto sono analoghe
int fZ (int nz, int nr, int nt, int ns, int *****mat_m){

    //se il pezzo dell matrice è gia occupato, non ricorrere e ritorna il massimo fino a quel momento
    if (mat_m[zaffiro][nz][nr][nt][ns] != -1){
        return mat_m[zaffiro][nz][nr][nt][ns];
    }
    //caso base
    if (nz == 0){
        return 0;
    }

    //usa le regole per comporre la collana
    int max1 = fZ (nz-1, nr, nt, ns, mat_m);
    int max2 = fR (nz-1, nr, nt, ns, mat_m);

    //vedi quale è migliore e fai memoization
    if (max1 >= max2){
        mat_m[zaffiro][nz][nr][nt][ns] = 1+max1; 
        return 1+max1;
    }
    mat_m[zaffiro][nz][nr][nt][ns] = 1+max2; 
    return 1+max2;
}

int fR (int nz, int nr, int nt, int ns, int *****mat_m){

    if (mat_m[rubino][nz][nr][nt][ns] != -1){
        return mat_m[rubino][nz][nr][nt][ns];
    }
    if (nr == 0){
        return 0;
    }

    int max1 = fS (nz, nr-1, nt, ns, mat_m);
    int max2 = fT (nz, nr-1, nt, ns, mat_m);
    if (max1 >= max2){
        mat_m[rubino][nz][nr][nt][ns] = 1+max1;
        return 1+max1;
    }
    mat_m[rubino][nz][nr][nt][ns] = 1+max2;
    return 1+max2;
}

int fT (int nz, int nr, int nt, int ns, int *****mat_m){
    
    if (mat_m[topazio][nz][nr][nt][ns] != -1){
        return mat_m[topazio][nz][nr][nt][ns];
    }

    if (nt == 0){
        return 0;
    }
    
    int max1 = fZ (nz, nr, nt-1, ns, mat_m);
    int max2 = fR (nz, nr, nt-1, ns, mat_m);
    if (max1 >= max2){
        mat_m[topazio][nz][nr][nt][ns] = 1+max1;
        return 1+max1;
    }
    mat_m[topazio][nz][nr][nt][ns] = 1+max2;
    return 1+max2;
}

int fS (int nz, int nr, int nt, int ns, int *****mat_m){
    
    if (mat_m[smeraldo][nz][nr][nt][ns] != -1){
        return mat_m[smeraldo][nz][nr][nt][ns];
    }

    if (ns == 0){
        return 0;
    }
    
    int max1 = fS (nz, nr, nt, ns-1, mat_m);
    int max2 = fT (nz, nr, nt, ns-1, mat_m);
    if (max1 >= max2){
        mat_m[smeraldo][nz][nr][nt][ns] = 1+max1;
        return 1+max1;
    }
    mat_m[smeraldo][nz][nr][nt][ns] = 1+max2;
    return 1+max2;
}


int main(int argc, char* argv[]){
    
    read_file_and_calculate ();

    printf("\n");
    return 0;
}