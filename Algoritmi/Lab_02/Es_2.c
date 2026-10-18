#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>

//loro fanno la stessa cosa, solo che una ritorna e l'altra assegna
int **malloc2R (int nr, int nc, FILE* input_file);
void malloc2P (int ***mat, int nr, int nc, FILE* input_file);

void separa (int **mat, int nr, int nc, int **nere, int **bianche, int *dim);
void stampa (int *celle_nere, int *celle_bianche, int dim, int nr, int nc);
void dealloca (int *celle_nere, int *celle_bianche, int **mat, int nr);

int main (){
    //apro il file e controllo che funzioni
    FILE *input_file = fopen ("matrice.txt", "r");

    if (input_file == NULL){
        printf ("Il file non esiste\n");
        return 1;
    }

    //dichiaro le variabili e prendo i primi parametri nel file
    int nr, nc, **mat, var, *celle_nere, *celle_bianche, i, dim;
    fscanf (input_file, "%d %d", &nr, &nc);

    //scelgo come far allocare la matrice
    printf ("Come preferisci allocare la matrice? (0 con valore di ritorno, 1 come parametro)\n");
    scanf ("%d", &var);
    if (var){
        malloc2P (&mat, nr, nc, input_file);
    }
    else{
        mat = malloc2R (nr, nc, input_file);
    }

    separa (mat, nr, nc, &celle_nere, &celle_bianche, &dim);

    stampa (celle_nere, celle_bianche, dim, nr, nc);

    dealloca (celle_nere, celle_bianche, mat, nr);

    fclose (input_file);
    printf ("\n");
    return 0;
}

//lei ritorna la matrice che ha creato
int **malloc2R (int nr, int nc, FILE* input_file){
    int **mat, i, j;

    //alloco prima il vettore di puntatori a intero
    mat = (int **) malloc (nr*(sizeof (int *)));

    if (mat == NULL){
        exit (1);
    }

    for (i = 0; i < nr; i++){
        //poi i singoli vettori di interi
        mat[i] = (int *) malloc (nc*(sizeof (int)));
        if (mat[i] == NULL){
            exit (1);
        }
        //nel frattempo carico le righe che alloco
        for (j = 0; j < nc; j++){
            fscanf (input_file, "%d", &mat[i][j]);
        }
    }

    //ritorno la matrice che ho fatto
    return mat;

}

//lei invece si prende in pasto la matrice dal main (***)
void malloc2P (int ***mat, int nr, int nc, FILE* input_file){
    //creo una matrice di appoggio e faccio la stessa cosa della malloc2R
    int **m;

    int i, j;

    m = (int **) malloc (nr*sizeof (int*));

    for (i = 0; i < nr; i++){
        m[i] = (int*) malloc (nc*sizeof (int));
        for (j = 0; j < nc; j++){
            fscanf (input_file, "%d", &m[i][j]);
        }
    }

    //solo che al posto di tornare la matrice, assegno il suo indirizzo alla matrice del main
    *mat = m;

}

//guarda la matrice come una scacchiera
void separa (int **mat, int nr, int nc, int *nere[], int *bianche[], int *dim){
    int i, j, m=0, n=0, *nere_supp, *bianche_supp;

    //controllo quanti elementi ci sono nella matrice
    //se sono dispari, impongo la prima cella nera
    //e cio significa che le celle nere sono le celle bianche +1
    //invece se sono pari, sono metà e metà
    if ((nr*nc)%2 == 0){
        *dim = nr*nc/2;
        nere_supp = (int*) malloc (*dim*sizeof (int));
    }
    else{
        *dim = nr*nc/2+1;
        nere_supp = (int*) malloc (*dim*sizeof (int));
    }
    bianche_supp = (int*) malloc ((nr*nc/2)*sizeof (int));

    if (nere_supp == NULL || bianche_supp == NULL){
        exit (1);
    }

    //se siamo in posizione pari, mettile in nere, altrimenti mettile in bianche
    for (i = 0; i < nr; i++){
        for (j = 0; j < nc; j++){
            if ((i+j)%2 == 0){
                 nere_supp[m++]= mat[i][j];
            }
            else{
                 bianche_supp[n++] = mat[i][j];
            }
        }
    }

    //assegno poi i vettori agli indirizzi che mi sono preso dal main
    *nere = nere_supp;
    *bianche = bianche_supp;
}

void stampa (int *celle_nere, int *celle_bianche, int dim, int nr, int nc){
    int i;
    //stampo gli elementi
    printf ("Elementi nelle celle nere:\n");
    for (i = 0; i < dim; i++){
        printf (" %d ", celle_nere[i]);
    }
    printf ("\n\nElementi nelle celle bianche:\n");
    for (i = 0; i < nr*nc/2; i++){
        printf (" %d ", celle_bianche[i]);
    }
}

void dealloca (int *celle_nere, int *celle_bianche, int **mat, int nr){
    int i;

    //dealloco le strutture dinamiche
    free (celle_bianche);
    free (celle_nere);
    for (i = 0; i < nr; i++){
        free (mat[i]);
    }
    free (mat);
}

