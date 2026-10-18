#include<stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include<string.h>

#define DIM_CODICE 6
#define DIM_DATA 11
#define MAX_STR 50
#define NUM_CAMPI 7

#define insert_keyboard 0
#define insert_file 1
#define search_code 2
#define extract_code 3
#define extract_dates 4
#define print_on_file 5
#define terminate 6

typedef struct node node_t, *link;

typedef struct item {   //il campo valore di ogni nodo è una struttura
    char codice[DIM_CODICE];
    char nome [MAX_STR];
    char cognome [MAX_STR];
    char data_nascita [DIM_DATA];
    char via [MAX_STR];
    char citta[MAX_STR];
    int cap;
}item;

struct node{    //ogni nodo è fatto cosi
    item val;
    link next;
};

link newNode (link next, item val){
    link x = malloc (sizeof (node_t));  //alloco la memoria che mi serve
    if (x == NULL){
        return NULL;
    }
    x->val = val;   //inserisco il nodo nuovo
    x->next = next;
    return x;
}

void de_alloc (link h){
    link t;
    while (h != NULL){
        t = h;
        h = h->next;
        free (t);
    }
}

void visualization (link h){
    link x;
    int i;
    for (x = h, i = 1; x != NULL; x = x->next, i++){
        printf ("Nodo %d: ", i);
        printf ("%s %s %s %s %s %s %d\n", x->val.codice, x->val.nome, x->val.cognome, x->val.data_nascita, x->val.via, x->val.citta, x->val.cap);
    }
}

int strcmpData (char data1[], char data2[]){    //fa la strcmp tra due date
    //mi creo due variabili di appoggio
    char data1_appoggio[DIM_DATA], data2_appoggio[DIM_DATA];
    //metto gli slash dove necessario
    data1_appoggio[4] = '/'; data1_appoggio[7] = '/'; data2_appoggio[4] = '/'; data2_appoggio[7] = '/';
    int i, j;
    //qui ho 3 for che leggono rispettivamente l'anno il mese e il giorno e traslano nella posizione corretta
    for (i = DIM_DATA-1-4, j = 0; i < DIM_DATA-1; i++, j++){
        data1_appoggio[j] = data1[i];
        data2_appoggio[j] = data2[i];
    }
    for (i = DIM_DATA-1-7, j = 5; i < DIM_DATA-1-5; i++, j++){
        data1_appoggio[j] = data1[i];
        data2_appoggio[j] = data2[i];
    }
    for (i = 0, j = 8; i < DIM_DATA-1-8; i++, j++){
        data1_appoggio[j] = data1[i];
        data2_appoggio[j] = data2[i];
    }
    data1_appoggio[DIM_DATA-1] = '\0';
    data2_appoggio[DIM_DATA-1] = '\0';

    //adesso posso trattare la data come stringa e fare una banale strcmp
    return strcmp (data1_appoggio, data2_appoggio);

}

int validInputCode (char code[]){   //fa tutti i controlli del caso per capire se un codice è scritto in maniera corretta
    //ritorna 0 quando è scritto bene e viceversa
    int i, len, result = 0;
    if (code[0] != 'A'){
        return !result;
    }
    else{
        len = strlen(code);
        if (len < DIM_CODICE-1){
            return !result;
        }
        for (i = 1; i < len; i++){
            if (!isdigit(code[i])){
                return !result;
            }
        }
    }
    return result;
}

int validInputDate (char date[]){   //vede se una data è scritta bene
    int i, result = 0;

    if (strlen(date) != DIM_DATA-1 || date[2] != '/' || date[5] != '/'){
        return !result;
    }
    else{   //controllo se gli altri caratteri sono tutti numeri
        for (i = 0; i < 2; i++){
            if (!isdigit (date[i])){
                return !result;
            }
        }
        for (i = 3; i < 5; i++){
            if (!isdigit (date[i])){
                return !result;
            }
        }
        for (i = 6; i < 10; i++){
            if (!isdigit (date[i])){
                return !result;
            }
        }
    }
    return result;
}

item ItemSetVoid (){    //crea l'elemento vuoto
    item vuoto;
    vuoto.codice[0] = '\0';
    vuoto.nome[0] = '\0';
    vuoto.cognome[0] = '\0';
    vuoto.data_nascita[0] = '\0';
    vuoto.via[0] = '\0';
    vuoto.citta[0] = '\0';
    vuoto.cap = -1;
    return vuoto;
}

link sortListIns (link h, item val){    //inserisci l'elemento in lista ordinata (per data)
    link current, prevoius;
    if (h == NULL || strcmpData((h->val).data_nascita, val.data_nascita) < 0){
        return newNode (h, val);
    }

    for (current = h->next, prevoius = h; current != NULL && strcmpData(val.data_nascita, (current->val).data_nascita) < 0; prevoius = current, current = current->next);

    prevoius->next = newNode (current, val);
    return h;

}

link leggiAnagrafica (link h){  //legge un file
    printf ("Dammi il nome del file\n");
    int flag = 1;
    char nome_file [50];
    link x;
    scanf ("%s", nome_file);
    FILE *input_file = fopen (nome_file, "r");
    if (input_file == NULL){
        printf ("Errore nella lettura del file, riprovare \n");
        return h;
    }

    item val;

    //leggo il file
    while (fscanf (input_file, "%s %s %s %s %s %s %d", val.codice, val.nome, val.cognome, val.data_nascita, val.via, val.citta, &val.cap) == NUM_CAMPI){
        flag = 0;
        for (x = h; x != NULL && !flag; x=x->next){
            if (strcmp (val.codice, (x->val).codice) == 0){
                printf ("Elemento già presente nella lista, il record con codice %s viene ignorato", val.codice);
                flag = 1;
                break;
            }
        }
        if (!flag){
            h = sortListIns (h, val);
        }
    }
    fclose (input_file);
    return h;
}

link newData (link h){
    item val;
    link x;
    int flag = 1, i, len, exist = 0;

    printf ("Inserire il codice (del tipo AXXXX, con X compreso tra 0 e 9)\n");
    while (flag){   //while che controlla se il codice è scritto bene
        if (scanf ("%5s", val.codice) == 1){
            flag = validInputCode (val.codice);
        }
        else{
            printf ("Input errato, riprovare\n");
            getchar ();
        }
        
        if (flag){
            printf ("Input errato, riprovare\n");
            getchar ();
        }
        else{
            for (x = h; x != NULL; x = x->next){
                if (strcmp (x->val.codice, val.codice) == 0){
                    printf ("Comando già presente nella lista, riprovare\n");
                    flag = 1;
                    break;
                }
            }
        }
    }

    while (getchar() != '\n');

    printf ("Inserire il nome\n");
    scanf("%s", val.nome);

    printf ("Inserire il cognome\n");
    scanf ("%s", val.cognome);

    printf ("Inserire la data di nascita (GG/MM/AAAA)\n");
    flag = 1;
    while (flag){   //while che vede se la data è scritta bene
        scanf ("%10s", val.data_nascita);
        flag = validInputDate (val.data_nascita);
        if (flag){
            printf ("Comando errato, riprovare\n");
            getchar ();
        }
    }

    printf ("Inserire la via\n");
    scanf("%s", val.via);

    while (getchar () != '\n');
    printf ("Inserire la citta\n");
    scanf("%s", val.citta);

    printf ("Inserire il cap\n");
    while (scanf("%d", &val.cap) != 1){
        printf ("Comando errato, riprovare\n");
        getchar ();
    }

    return sortListIns (h, val);
}

link srcListCode (link h){
    int flag = 1, i, len;
    char code [DIM_CODICE];
    link x;

    printf ("Inserire il codice (del tipo AXXXX, con X compreso tra 0 e 9)\n");
    while (flag){
        scanf ("%s", code);
        flag = validInputCode (code);
        if (flag){
            printf ("Riprovare, comando errato\n");
            getchar ();
        }
    }

    for (x = h; x != NULL; x = x->next){
        if (strcmp ((x->val).codice, code) == 0){
            return x;
        }
    }
    return NULL;
}

item extraction_code(link *h){
    link current, previous, t;
    item val;

    int flag = 1, i;
    char code [DIM_CODICE];

    printf ("Inserire il codice (del tipo AXXXX, con X compreso tra 0 e 9)\n");
    while (flag){   //controllo se il codice è scritto bene
        if (scanf ("%5s", code) == 1){
            flag = validInputCode (code);
        }
        else{
            printf ("Input errato, riprovare\n");
            getchar();
        }
        
        if (flag){
            printf ("Input errato, riprovare\n");
            getchar();
        }
    }

    if (*h != NULL && strcmp (((*h)->val).codice, code) == 0){
        t = (*h);
        val = (*h)->val;
        (*h) = (*h)->next;
        free (t);
        return val;
    }
    if (*h != NULL){
        for (current = (*h)->next, previous = *h; current != NULL; previous = current, current = current->next){
            if (strcmp ((current->val).codice, code) == 0){
                previous->next = current->next;
                val = current->val;
                t = current;
                free (t);
                return val;
            }
        }
    }
    return ItemSetVoid();
}

void listFilePrint (link h){

    int flag = 0;

    char file_name[50];
    printf ("Dammi il nome del file\n");
    scanf ("%s", file_name);

    FILE *input_file = fopen (file_name, "w");
    if (input_file == NULL){
        printf ("Errore nella lettura del file\n");
        return;
    }

    link x;
    for (x = h; x != NULL; x = x->next){
        fprintf (input_file, "%s %s %s %s %s %s %d\n", (x->val).codice, (x->val).nome, (x->val).cognome, (x->val).data_nascita, (x->val).via, (x->val).citta, (x->val).cap);
        flag = 1;

    }
    if (flag){
        printf ("Stampa sul file chiamato %s effettuata\n", file_name);
    }
    else{
        printf ("La lista è vuota\n");
    }
    fclose (input_file);
    return;
}

void give_date (char date1[], char date2[]){

    int flag = 1;

    printf ("Dammi le due date\n");

    while (flag){
        printf ("Data 1: ");
        scanf ("%s", date1);
        flag = validInputDate (date1);
        if (flag){
            printf ("Comando errato, riprovare\n");
        }
    }
    flag = 1;
    while (flag){
        printf ("Data 2: ");
        scanf ("%s", date2);
        flag = validInputDate (date2);
        if (flag){
            printf ("Comando errato, riprovare\n");
        }
    }

}

link src_first_date (char date[], link h){
    link current, previous;
    for (current = h, previous = NULL; current != NULL && strcmpData (date, (current->val).data_nascita) < 0; previous = current, current = current->next);
    return previous;
}

item extraction_date (link *current, link *previous){
    link t;
    item val = (*current)->val;
    (*previous)->next = (*current)->next;
    t = *current;
    (*current) = (*current)->next;
    free (t);
    return val;
}

void menu (link h){
    int flag = 1, choice;   //flag gestisce il while dello switch, choice lo switch stesso
    link x, p;      //x sarebbe un puntatore al nodo corrente, p a quello precedente
    item val;       //struttura che mi serve per visualizzare dopo le estrazioni
    char date1[DIM_DATA], date2[DIM_DATA], date_temp[DIM_DATA]; //stringhe necessarie per l'estrazione tra date

    while (flag){
        printf ("Premere\n0: Inserire un nuovo dato nella lista da tastiera\n1: Leggere il file dell'anagrafica\n2: Ricercare un record per codice\n3: Cancellare (con estrazione) un record previa ricerca per codice\n4: Estrarre tutti i dati che sono compresi tra due date inserite da tastiera\n5: Stampa su file\n6: Terminare il programma\n\n");
        while (scanf ("%d", &choice) != 1){
            printf ("Comando errato, riprovare\n");  //controllo se l'input è corretto
            getchar ();
        }
        switch (choice){
            case insert_keyboard:   //inserimento di un nuovo dato da testiera
                h = newData (h);
                visualization (h);
                break;
            case insert_file:   //lettura di nuovi dati da file
                h = leggiAnagrafica (h);
                visualization (h);
                break;
            case search_code:   //ricerca per codice
                x = srcListCode(h);
                if (x == NULL){
                    printf ("Elemento non trovato\n");
                }
                else{
                    printf ("%s %s %s %s %s %s %d\n", (x->val).codice, (x->val).nome, (x->val).cognome, (x->val).data_nascita, (x->val).via, (x->val).citta, (x->val).cap);
                }
                visualization (h);
                break;
            case extract_code:  //estrazione per codice
                val = extraction_code (&h);
                if (val.cap == -1){
                    printf ("Non è presente questo elemento nella lista\n");
                }
                else{
                    printf ("%s %s %s %s %s %s %d\n", val.codice, val.nome, val.cognome, val.data_nascita, val.via, val.citta, val.cap);
                }
                visualization (h);
                break;
            case extract_dates: //estrazione di tutti gli elementi tra due date date in input
                give_date (date1, date2);

                if (strcmpData (date1, date2) < 0){
                    strcpy (date_temp, date1);
                    strcpy (date1, date2);
                    strcpy (date2, date_temp);
                }

                p = src_first_date (date1, h);
                if (p->next == NULL){
                    printf ("Non c'è nessun elemento tra queste due date\n");
                }
                else{
                    for (x = p->next; x != NULL && strcmpData (date2, (x->val).data_nascita) < 0;){
                        val = extraction_date (&x, &p);
                        printf ("%s %s %s %s %s %s %d\n", val.codice, val.nome, val.cognome, val.data_nascita, val.via, val.citta, val.cap);
                    }
                }
                visualization (h);
                break;
            case print_on_file: //stampa su file
                listFilePrint(h);
                visualization (h);
                break;
            case terminate:
                flag = 0;
                de_alloc(h);
                printf ("Arrivederci\n");
                break;
            default:
                printf ("Comando errato\n");
                break;
        }
    }
}

int main (){

    //inizializzo lista vuota
    link head = NULL;
    
    //faccio il menu
    menu (head);

    printf ("\n");
    return 0;
}