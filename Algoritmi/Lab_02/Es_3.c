#include<stdio.h>
#include<string.h>
#include <stdlib.h>

//definisco le costanti per lo switch
#define ordina_per_data 0
#define ordina_per_partenza 1
#define ordina_per_arrivo 2
#define ordina_per_tratta 3
#define leggi_di_nuovo 4
#define fine 5

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

//funzioni che mi servono
void acquisizione (FILE* input_file, struttura **vet, struttura ***ord_data, struttura ***ord_partenza, struttura ***ord_arrivo, struttura ***ord_tratta, int righe);
struttura** alloca_puntatori (struttura p[], int n);
void merge_sort(int l, int r, struttura **puntatori, int (*cmp)(const struttura *a, const struttura *b), int n);
void merge (int l, int r, int m, struttura **puntatori, int (*cmp)(const struttura *a, const struttura *b), int n);
void libera_memoria(struttura *vet, struttura **ord_data, struttura **ord_partenza, struttura **ord_arrivo, struttura **ord_tratta, int n);
void stampa_risultati (struttura **p, int n);
void menu (struttura *vet, struttura** ord_data, struttura **ord_partenza, struttura **ord_arrivo, struttura **ord_tratta, int nr, FILE *input_file);

//funzioni che fanno la strcmp tra i campi della struttura che mi servono
int cmp_data(const struttura *a, const struttura *b) { 
    if (strcmp(a->data, b->data) == 0){
        return strcmp(a->ora_par, b->ora_par);
    }
    return strcmp(a->data, b->data); 
}
int cmp_partenza(const struttura *a, const struttura *b) { return strcmp(a->partenza, b->partenza); }
int cmp_arrivo(const struttura *a, const struttura *b) { return strcmp(a->arrivo, b->arrivo); }
int cmp_codice(const struttura *a, const struttura *b) { return strcmp(a->codice, b->codice); }

int main(){

    //acquisisco il file la prima volta
    FILE *input_file = fopen ("log.txt", "r");
    if (input_file == NULL){
        printf ("Errore nell'apertura del file\n");
        return 1;
    }

    //dichiaro la struttura e i vettori di ordinamento
    struttura *vet, **ord_data, **ord_partenza, **ord_arrivo, **ord_tratta;
    int nr;

    fscanf (input_file, "%d", &nr);

    //conto il numero di righe e leggo il file la prima volta
    acquisizione (input_file, &vet, &ord_data, &ord_partenza, &ord_arrivo, &ord_tratta, nr);

    menu (vet, ord_data, ord_partenza, ord_arrivo, ord_tratta, nr, input_file);

    printf ("\n");
    return 0;
}

//legge il file e alloca anche il vettore di strutture
void acquisizione (FILE* input_file, struttura **vet, struttura ***ord_data, struttura ***ord_partenza, struttura ***ord_arrivo, struttura ***ord_tratta, int righe){
    int i=0, j;
    //il vettore di strutture
    struttura *p;

    //che prima punta ad una sola struttura
    p = (struttura *) malloc (righe*sizeof(struttura));
    if (p == NULL){
        exit (1);
    }

    //man mano che leggo il file, controllo se ho raggiunto il massimo allocato, allora raddoppio
    while (fscanf (input_file, "%s %s %s %s %s %s %d", p[i].codice, p[i].partenza, p[i].arrivo, p[i].data, p[i].ora_par, p[i].ora_arrivo, &(p[i].ritardo)) > 0){
        i++;
    }

    //alloco i vettori di puntatori e li inizializzo
    *ord_data = alloca_puntatori(p, i);
    *ord_partenza = alloca_puntatori(p, i);
    *ord_arrivo = alloca_puntatori(p, i);
    *ord_tratta = alloca_puntatori(p, i);

    //passo al main
    *vet = p;
}

//restituisce un vettore di puntatori a struttura allocato dinamicamente
struttura** alloca_puntatori (struttura p[], int n){
    //vettore di appoggio
    struttura **vettore;
    int i;

    //p stavolta è la struttura
    vettore = (struttura **) malloc (n*sizeof (struttura*));
    for (i = 0; i < n; i++){
        vettore[i] = &p[i];
    }
    return vettore;
}

void menu (struttura *vet, struttura** ord_data, struttura **ord_partenza, struttura **ord_arrivo, struttura **ord_tratta, int nr, FILE *input_file){
    int scelta, flag = 1;
    char nome_file [50];
    //faccio lo switch
    while (flag){
        //Menu
        printf ("\nPremere 0, 1, 2 o 3 per ordinare rispettivamente per\ndata, partenza, arrivo o tratta;\nPremere 4 per leggere un nuovo file\n Premere 5 per terminare l'esecuzione\n");
        scanf ("%d", &scelta);
        switch (scelta){
            //casi autoesplicativi
            case ordina_per_data:
                merge_sort (0, nr-1, ord_data, cmp_data, nr);
                stampa_risultati (ord_data, nr);
                break;
            case ordina_per_partenza:
                merge_sort (0, nr-1, ord_partenza, cmp_partenza, nr);
                stampa_risultati (ord_partenza, nr);
                break;
            case ordina_per_arrivo:
                merge_sort (0, nr-1, ord_arrivo, cmp_arrivo, nr);
                stampa_risultati (ord_arrivo, nr);
                break;
            case ordina_per_tratta:
                merge_sort (0, nr-1, ord_tratta, cmp_codice, nr);
                stampa_risultati (ord_tratta, nr);
                break;
            case leggi_di_nuovo:
                //qui prima libero la memoria dinamica allocata in precedenza e poi alloco quella nuova
                libera_memoria (vet, ord_data, ord_partenza, ord_arrivo, ord_tratta, nr);
                fclose(input_file);
                printf ("Dammi il nome del nuovo file\n");
                scanf ("%s", nome_file);
                input_file = fopen (nome_file, "r");
                if (input_file == NULL){
                    printf ("File non trovato\n");
                }
                else{
                    fscanf (input_file, "%d", &nr);
                    acquisizione (input_file, &vet, &ord_data, &ord_partenza, &ord_arrivo, &ord_tratta, nr);
                }
                fclose (input_file);
                break;
            case fine:
                flag = 0;
                break;
            default:
                printf ("Scelta errata, riprovare\n");
                break;
        }
    }
}

//merge sort ricorsivo per ordinare
void merge_sort(int l, int r, struttura **puntatori, int (*cmp)(const struttura *a, const struttura *b), int n){
    if (l >= r){
        return;
    }

    int c = (l+r)/2;
    merge_sort (l, c, puntatori, cmp, n);
    merge_sort (c+1, r, puntatori, cmp, n);
    merge (l, r, c, puntatori, cmp, n);
}

void merge (int l, int r, int m, struttura **puntatori, int (*cmp)(const struttura *a, const struttura *b), int n){
    int i = l, j = m+1, k = l;
    struttura *aus[n];

    while (i <= m && j <= r){
        if (cmp (puntatori[i], puntatori[j])<=0){
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

//libero la memoria prima di leggere un nuovo file
void libera_memoria(struttura *vet, struttura **ord_data, struttura **ord_partenza, struttura **ord_arrivo, struttura **ord_tratta, int n){
    free (vet);
    free (ord_data);
    free (ord_partenza);
    free (ord_arrivo);
    free (ord_tratta);
}

//stampa i risultati dopo aver ordinato
void stampa_risultati (struttura **p, int n){
    int i;
    for (i = 0; i < n; i++){
        printf ("\n %s %s %s %s %s %s %d \n", p[i]->codice, p[i]->partenza, p[i]->arrivo, p[i]->data, p[i]->ora_par, p[i]->ora_arrivo, p[i]->ritardo);
    }
}