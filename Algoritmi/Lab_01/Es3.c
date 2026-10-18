#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//durante l'esecuzione allungare il per vedere bene tutti gli output

#define stampa 4
#define data 3
#define codice 0
#define partenza 1
#define arrivo 2
#define ricerca 5
#define fine 6

#define NUM_CAMPI 7
#define MAX_S 30
#define MAX_FILE 1000

void leggi_file (FILE *input_file, char struttura[][NUM_CAMPI][MAX_S]);
int leggicomando (char stringa[]);
void menu (char struttura[][NUM_CAMPI][MAX_S], int indici[], int nr);
void merge_sort(char struttura[][NUM_CAMPI][MAX_S], int indici[], int l, int r, int parametro);
void merge (char struttura[][NUM_CAMPI][MAX_S], int indici[], int l, int r, int m, int parametro);
void stampa_log (char struttura[][NUM_CAMPI][MAX_S], int nr);
void ricerca_lineare (char struttura[][NUM_CAMPI][MAX_S], int nr, char stringa[], int parametro);
void ricerca_dicotomica (char struttura[][NUM_CAMPI][MAX_S], int l, int r, char stringa[], int indici[], int nr, int parametro);
void visualizza (int nr, char struttura[][NUM_CAMPI][MAX_S], int indici[]);

int main(void){
    //leggo il file
    FILE *input_file;

    int nr = 0;

    //controllo se il file non è vuoto
    if ((input_file = fopen ("log.txt", "r")) == NULL)
    {
        printf ("Errore nell'apertura del file \n");
        return 1;
    }

    //capisco quante righe ci sono nel file
    fscanf (input_file, " %d ", &nr);

    char struttura [MAX_FILE][NUM_CAMPI][MAX_S];    //matrice di stringhe (la terza dim è quindi dovuta al fatto che gli elementi della mat sono stringhe)
    int indici[MAX_FILE];   //Uso un vettore di indici per gestire le righe quando faccio l'ordinamento

    leggi_file(input_file, struttura);

    menu (struttura, indici, nr);
    
    fclose(input_file);

    printf ("\n");
    return 0;
}


void leggi_file (FILE *input_file, char struttura[][NUM_CAMPI][MAX_S]){
    int i = 0;

    //salvo le info che mi servono dentro la struttura
    while (fscanf (input_file, " %s %s %s %s %s %s %s ", struttura[i][codice], struttura[i][partenza], struttura[i][arrivo], struttura[i][data], struttura[i][4], struttura[i][5], struttura[i][6]) == NUM_CAMPI)
    {
        i++;
    }

}

void menu (char struttura[][NUM_CAMPI][MAX_S], int indici[], int nr){
    char stringa_cercare[MAX_S]; //stringa che mi serve per la partenza o il codice quando l'utente sceglie la ricerca
    int flag = 1;   //mi serve per far continuare il while nel menu
    int scelta_ricerca; // mi serve per cappire che tipo di ricerca ha scelto l'utente (dicotomica o lineare)
    int codice_partenza; // mi serve per capire se vuole ordinare per codice o per partenza

    //while che gestisce lo switch fino a quando non si scrive la parola "fine"
    while (flag){

        //inizializzo il vettore di indici per ordinare in modo diverso ogni volta
        for (int i = 0; i < nr; i++){
            indici[i] = i;
        }

        printf ("Dimmi cosa vuoi fare: inserire una di queste parole\nstampa\n\n(Ordina per:)\ndata\ncodice\npartenza\narrivo\n\nricerca\n\nfine\n\n");
        char comando [MAX_S];
        //uso i define che ho creato per "convertire la stringa in numeri"
        scanf ("%s", comando); 
        int scelta = leggicomando (comando);

        switch (scelta){
        case stampa:
            //funzione che stampa su schermo o sul file
            stampa_log (struttura, nr);
            break;
        //d'ora in poi sono tutti ordinamenti+stampe
        case data:
            merge_sort (struttura, indici, 0, nr-1, data);
            visualizza (nr, struttura, indici);
            break;
        case codice:
            merge_sort (struttura, indici, 0, nr-1, codice);
            visualizza (nr, struttura, indici);
            break;
        case partenza:
            merge_sort (struttura, indici, 0, nr-1, partenza);
            visualizza (nr, struttura, indici);
            break;
        case arrivo:
            merge_sort (struttura, indici, 0, nr-1, arrivo);
            visualizza (nr, struttura, indici);
            break;
        //implemento una funzione di ricerca lineare e dicotomica
        case ricerca:
            printf ("Ricerca per codice o stazione di partenza (0 o 1)?\n");
            scanf ("%d", &codice_partenza);

            printf ("0 se vuoi usare la ricerca lineare, 1 se vuoi usare la ricerca dicotomica\n");
            scanf ("%d", &scelta_ricerca);

            printf ("Dammi la stringa (o il prefisso) che stai cercando\n");
            scanf ("%s", stringa_cercare);

            if (scelta_ricerca){
                //ordino per partenza o per codice in base alla scelta dell'utente
                if (codice_partenza) { merge_sort (struttura, indici, 0, nr-1, partenza); }
                else { merge_sort (struttura, indici, 0, nr-1, codice); }

                ricerca_dicotomica(struttura, 0, nr-1, stringa_cercare, indici, nr, codice_partenza);
            }
            else{
                ricerca_lineare(struttura, nr, stringa_cercare, codice_partenza);
            }

            printf ("\n");
            break;
        case fine:
            flag = 0;
            printf ("Arrivederci\n\n");
            break;
        default:
            printf ("Comando non valido, riprovare\n\n");
            break;
        }
    }
}

int leggicomando (char stringa[]){
    //c è intero che diventerà il rappresentante della richiesta fatta dall'utente
    int c = 0;
    for (int i = 0; i < strlen (stringa); i++){
        stringa[i] = tolower (stringa[i]);
    }
    
    char tabella[NUM_CAMPI][MAX_S] = {"codice", "partenza", "arrivo", "data", "stampa", "ricerca", "fine"};

    //controllo se c == alla fine oppure se c'è una corrispondenza
    while (strcmp(stringa, tabella[c]) != 0 && c <= fine)
    {
        c++;
    }
    return c;
}

//merge sort fatto usando una funzione ricorsiva
void merge_sort(char struttura[][NUM_CAMPI][MAX_S], int indici[], int l, int r, int parametro){
    if (l >= r){
        return;
    }
    int m = (l+r)/2;
    merge_sort(struttura, indici, l, m, parametro);
    merge_sort(struttura, indici, m+1, r, parametro);
    merge (struttura, indici, l, r, m, parametro);
}

//parametro mi permette di capire quale campo della struttura devo andare a controllare
//ordino il vettore di indici e poi stampo in base a quello
void merge (char struttura[][NUM_CAMPI][MAX_S], int indici[], int l, int r, int m, int parametro){
    int i = l, j = m+1, k = l;
    int aus[MAX_FILE];

    while (i <= m && j <= r){
        //caso speciale nel caso in cui si abbia la stessa data, allora controllo l'ora
        if (strcmp (struttura[indici[i]][parametro], struttura[indici[j]][parametro]) == 0 && parametro == data){
            if (strcmp (struttura[indici[i]][parametro+1], struttura[indici[j]][parametro+1]) <= 0){
                aus[k] = indici[i++];
            }
            else{
                aus[k] = indici[j++];
            }
        }
        else if(strcmp (struttura[indici[i]][parametro], struttura[indici[j]][parametro]) <= 0){
            aus[k] = indici[i++];
        }
        else{
            aus[k] = indici[j++];
        }
        k++;
    }

    while (i <= m){
        aus[k++] = indici[i++];
    }

    while (j <= r){
        aus[k++] = indici[j++];
    }

    for (k = l; k <= r; k++){
        indici[k] = aus[k];
    }
}

void stampa_log (char struttura[][NUM_CAMPI][MAX_S], int nr){
    int scelta;
    printf ("Scegliere 0 per stampare a schermo, scegliere 1 per stampare su file\n");
    scanf ("%d", &scelta);
    if (scelta == 1){
        //apro un file in scrittura e scrivo su quello
        FILE* f_w = fopen ("logW.txt", "w");
        for (int i = 0; i < nr; i++){
            for (int j = 0; j < NUM_CAMPI; j++){
                fprintf (f_w, " %s ", struttura[i][j]);
            }
            fprintf (f_w, "\n");
        }
        fclose (f_w);
        printf ("Scrittura su file effettuata\n\n");
    }
    else{
        for (int i = 0; i < nr; i++){
            for (int j = 0; j < NUM_CAMPI; j++){
                printf (" %s ", struttura[i][j]);
            }
            printf ("\n");
        }
    }
    printf ("\n");
}

void ricerca_lineare (char struttura[][NUM_CAMPI][MAX_S], int nr, char stringa[], int parametro){
    //banale ricerca lineare con un ciclo
    int flag = 0;
    for (int i = 0; i < nr; i++){
        if (strstr(struttura[i][parametro], stringa) == struttura[i][parametro]){
            flag = 1;
            printf ("%s %s %s %s %s %s %s\n", struttura[i][codice], struttura[i][partenza], struttura[i][arrivo], struttura[i][data], struttura[i][4], struttura[i][5], struttura[i][6]);
            //controllo se il parametro è 0 o 1
            if (!parametro) { break; }
        }
    }
    printf ("\n");
    if (!flag){
        printf ("Nessuna occorrenza trovata\n\n");
    }
}

//ricerca dicotomica un po particolre in quanto di norma la ricerca dicotomica
//torna un solo elemento, mentre io vorrei stampare tutte le corrispodnenze (solo quando cerco per partenza)
//allora appena ne trovo una, controllo se ce n'è qualcuna accanto a quella trovata
void ricerca_dicotomica (char struttura[][NUM_CAMPI][MAX_S], int l, int r, char stringa[], int indici[], int nr, int parametro){
    if (l >= r){
        printf ("Elemento non trovato\n");
        return;
    }
    int c = (l+r)/2;
    if (strstr (struttura[indici[c]][parametro], stringa) == struttura[indici[c]][parametro]){

        printf ("%s %s %s %s %s %s %s\n", struttura[c][codice], struttura[c][partenza], struttura[c][arrivo], struttura[c][data], struttura[c][4], struttura[c][5], struttura[c][6]);

        if (parametro){
            int i = c-1, j = c+1;
            while ( i >= 0 && strstr (struttura[indici[i]][partenza], stringa) == struttura[indici[i]][partenza]){
                printf ("%s %s %s %s %s %s %s\n", struttura[i][codice], struttura[i][partenza], struttura[i][arrivo], struttura[i][data], struttura[i][4], struttura[i][5], struttura[i][6]);
                i--;
            }

            while (j < nr && strstr (struttura[indici[j]][partenza], stringa) == struttura[indici[j]][partenza]){
                printf ("%s %s %s %s %s %s %s\n", struttura[j][codice], struttura[j][partenza], struttura[j][arrivo], struttura[j][data], struttura[j][4], struttura[j][5], struttura[j][6]);
                j++;
            }
        }
        return;
    }
    else if (strcmp (stringa, struttura[indici[c]][parametro]) <= 0){
        ricerca_dicotomica (struttura, l, c, stringa, indici, nr, parametro);
    }
    else{
        ricerca_dicotomica (struttura, c+1, r, stringa, indici, nr, parametro);
    }
    return ;
}

void visualizza (int nr, char struttura[][NUM_CAMPI][MAX_S], int indici[]){
    //visualizzo la struttura ordinata attraverso il vettore di indici
    for (int i = 0; i < nr; i++){
        for (int j = 0; j < NUM_CAMPI; j++){
            printf (" %s ", struttura[indici[i]][j]);
        }
        printf ("\n");
    }
}