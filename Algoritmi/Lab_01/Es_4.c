#include<stdio.h>
#include<string.h>

#define scelta_data 0
#define scelta_partenza 1
#define scelta_arrivo 2
#define scelta_tratta 3
#define scelta_fine 4

//struttura con i campi del file
typedef struct {
    char codice[30];
    char partenza[30];
    char arrivo[30];
    char data[30];
    char ora_par[30];
    char ora_arrivo[30];
    int ritardo;
}struttura;


// legge il file
void leggifile (FILE* input_file, struttura vet[], int nr);
// gestisce l'ordinamento chiamando quante volte serve la funzione che ordina
int gestione_ordinamento (struttura *ord_data[], struttura *ord_partenza[], struttura *ord_arrivo[], struttura *ord_tratta[], int nr, struttura *aus[], struttura vet[]);

// ordinamento con merge sort ricorsivo
void merge_sort (int l, int r, struttura *puntatori[], struttura *aus[], int (*cmp)(const struttura *a, const struttura *b));
void merge (int l, int r, int m, struttura *puntatori[], struttura *aus[], int (*cmp)(const struttura *a, const struttura *b));

// visualizza
void visualizzazione (struttura *ord[],  int nr);

// queste funzioni vengono date come parametro al merge in modo tale da ordinare ogni volta secondo un campo diverso
int cmp_data(const struttura *a, const struttura *b) { 
    if (strcmp(a->data, b->data) == 0){
        return strcmp(a->ora_par, b->ora_arrivo);
    }
    return strcmp(a->data, b->data); 
}
int cmp_partenza(const struttura *a, const struttura *b) { return strcmp(a->partenza, b->partenza); }
int cmp_arrivo(const struttura *a, const struttura *b) { return strcmp(a->arrivo, b->arrivo); }
int cmp_codice(const struttura *a, const struttura *b) { return strcmp(a->codice, b->codice); }

// funzione main
int main (){
    FILE *input_file = fopen ("log.txt", "r");

    int nr;

    //capisco quante righe ci sono nel file
    fscanf (input_file, "%d", &nr);

    //creo un vettore di strutture
    struttura vet[nr];

    //creo tanti vettori di puntatori a struttura
    struttura *ord_data[nr];
    struttura *ord_partenza[nr];
    struttura *ord_arrivo[nr];
    struttura *ord_tratta[nr];

    //vettore ausiliario per il merge
    struttura *aus[nr];

    //inizializzo i vettori alla prima struttura
    for (int i = 0; i < nr; i++){
        ord_data[i] = &vet[i];
        ord_partenza[i] = &vet[i];
        ord_arrivo[i] = &vet[i];
        ord_tratta[i] = &vet[i];
    }

    leggifile(input_file, vet, nr);

    gestione_ordinamento(ord_data, ord_partenza, ord_arrivo, ord_tratta, nr, aus, vet);

    fclose (input_file);

    return 0;
}

void leggifile (FILE* input_file, struttura vet[], int nr){
    //legge il file iterativamente
    int i = 0;
    for (i = 0; i < nr; i++){
        fscanf (input_file, "%s %s %s %s %s %s %d", vet[i].codice, vet[i].partenza, vet[i].arrivo, vet[i].data, vet[i].ora_par, vet[i].ora_arrivo, &vet[i].ritardo);
    }
    return;
}


//chiama 4 volte il merge per ordinare in base ai campi passando un puntatore ad una funzione diversa
int gestione_ordinamento (struttura *ord_data[], struttura *ord_partenza[], struttura *ord_arrivo[], struttura *ord_tratta[], int nr, struttura *aus[], struttura vet[]){
    int scelta, flag = 1;

    while (flag){
        printf ("Come vuoi ordinare\nPremere 0 per ordinare per data\nPremere 1 per ordinare per partenza\nPremere 2 per ordinare per arrivo\nPremere 3 per ordinare per tratta\nPremere 4 per terminare\n\n");
        scanf ("%d", &scelta);
        switch (scelta){
            case scelta_data:
                merge_sort (0, nr-1, ord_data, aus, cmp_data);
                visualizzazione (ord_data, nr);
                break;
            case scelta_partenza:
                merge_sort (0, nr-1, ord_partenza, aus, cmp_partenza);
                visualizzazione (ord_partenza, nr);
                break;
            case scelta_arrivo:
                merge_sort (0, nr-1, ord_arrivo, aus, cmp_arrivo);
                visualizzazione (ord_arrivo, nr);
                break;
            case scelta_tratta:
                merge_sort (0, nr-1, ord_tratta, aus, cmp_codice);
                visualizzazione (ord_tratta, nr);
                break;
            case scelta_fine:
                flag = 0;
                break;
            default:
                printf ("Scelta errata, riprovare\n\n");
                break;
        }

    }
}

//classico merge sort ricorsivo
void merge_sort (int l, int r, struttura *puntatori[], struttura *aus[], int (*cmp)(const struttura *a, const struttura *b)){
    if (l >= r){
        return;
    }

    int m = (l+r)/2;

    merge_sort (l, m, puntatori, aus, cmp);
    merge_sort (m+1, r, puntatori, aus, cmp);
    merge (l, r, m, puntatori, aus, cmp);
}

void merge (int l, int r, int m, struttura *puntatori[], struttura *aus[], int (*cmp)(const struttura *a, const struttura *b)){
    int k = l, i = l, j = m+1;

    while (i <= m && j <= r){
        if (cmp (puntatori[i], puntatori[j]) <= 0){
            aus[k] = puntatori[i++];
        }
        else{
            aus[k] = puntatori[j++];
        }
        k++;
    }

    while (i <= m){
        aus[k++] = puntatori[i++];
    }
    while (j <= r){
        aus[k++] = puntatori[j++];
    }
    for (i = l; i <= r; i++){
        puntatori[i] = aus[i];
    }
}

void visualizzazione (struttura *ord[], int nr){
    int i;
    printf ("Ecco il vettore ordinato per parametro\n");
    for (i = 0; i < nr; i++){
        printf ("%s %s %s %s %s %s %d \n", ord[i]->codice, ord[i]->partenza, ord[i]->arrivo, ord[i]->data, ord[i]->ora_par, ord[i]->ora_arrivo, ord[i]->ritardo);
    }
}