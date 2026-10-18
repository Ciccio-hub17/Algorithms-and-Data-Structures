#include<stdio.h>
#include<string.h>
#include<ctype.h>

char *cercaRegexp(char *src, char *regexp);
void lettere (char *regexp, int index, int *spostamento, char *vet);
int lunghezza (char *regexp);

int main (){

    //Considero che le stringhe abbiano solo caratteri alfabetici e i metacaratteri indicati
    //Modificare queste due stringhe per fare le diverse prove
    char str[] = "Ciaotiao";
    char regexp [] = "[^C]iao";
    char *occorrenza = cercaRegexp(str, regexp);
    if (occorrenza == NULL){
        printf ("Non e' stata trovata alcuna sequenza\n");
    }
    else{
        printf ("Il primo carattere della sequenza e': %c\n", *occorrenza);
    }

    return 0;
}

char *cercaRegexp(char *src, char *regexp){
    /*la m serve per ciclare la sorgente (e tornare indietro quando serve)
    la i serve per ciclare da un carattere in poi
    la j serve per ciclare sulla stringa espressione regolare
    conta serve per capire se tutti i caratteri sono corretti
    reglen è la lunghezza dell'espressione*/
    int i = 0, j = 0, conta = 0, reglen = lunghezza(regexp), flag, m;
    //for esterno che cicla sulla parola principale
    for (m = 0; m < strlen(src) - reglen + 1 && conta < reglen; m++){
        //cosi posso fare in modo di non andare a caso per tutta la stringa
        i = m;
        flag = 1;
        //condizione che mi permette di capire se per ogni iterazione i caratteri continuano ad essere corretti
        while (flag && i < strlen(src) && conta < reglen){
            //banale controllo di lettere
            if (src[i] == regexp[j] || regexp[j] == '.'){
                i++; j++; conta++;
            }
            //se il carattere è una parentesi
            else if (regexp[j] == '['){
                int k = 0;
                //controlla se il successivo è un apice
                if (regexp[j+1] == '^'){
                    //se lo è
                    j = j + 2;
                    // metti in un vettore le lettere da evitare
                    char vet[21];
                    lettere(regexp, j, &j, vet);
                    //controlla se il carattere è presente nel vettore
                    while (vet[k] != src[i] && k < strlen(vet)){
                        k++;
                    }
                    //se sono alla fine vuol dire che non lo è
                    if (k == strlen(vet)){
                        i++; conta++; j++;
                    }
                    else{
                        //inizializza quanto necessario
                        j = 0; conta = 0; flag = 0;
                    }
                }
                else{
                    //esattamente la stessa cosa a parti invertite
                    j++;

                    char vet[21];
                    lettere(regexp, j, &j, vet);
                    while (vet[k] != src[i] && k < strlen(vet)){
                        k++;
                    }
                    if (k == strlen(vet)){
                        //inizializza quanto necessario
                        j = 0; conta = 0; flag = 0;
                    }
                    else{
                        i++; conta++; j++;
                    }
                }
            }
            //controlla se il carattere è minuscolo
            else if (regexp[j] == '\a'){
                if (islower(src[i])){
                    j++; i++; conta++;
                }
                else{
                    j = 0; conta = 0; flag = 0;
                }
            }
            //controlla se il carattere è maiuscolo
            else if (regexp[j] == '\b'){
                if (isupper(src[i])){
                    j++; i++; conta++;
                }
                else{
                    j = 0; conta = 0; flag = 0;
                }
            }
            //banalmente se il carattere è doverso da quello dell'espressione
            else{
                j = 0; conta = 0; flag = 0;
            }
        }
    }
    //se m è alla fine, allora non c'è nessuna occorrenza
    if (m == strlen (src)-reglen){
        return NULL;
    }
    //viceversa, l'occorrenza inizia dall'ultimo carattere letto dal for (decrementato di 1 perchè il for aumenta in automatico)
    else{
        return &src[m-1];
    }
}

//lui crea i vettori quando il carattere è []
//spostamento mi serve per capire di quanto incrementare j nell'altra funzione, in quanto non so quanti caratteri ci sono
void lettere (char *regexp, int index, int *spostamento, char *vet){
    int i = 0;
    while (regexp[index+i]!= ']'){
        vet[i] = regexp[index+i];
        i++;
    }
    vet[i] = '\0';
    *spostamento = *spostamento + i;
    return;
}

//calcola la lunghezza della espressione regolare togliendo tutta la roba inutile
int lunghezza (char regexp[]){
    int len = 0, i = 0;
    while (regexp[i] != '\0'){
        if (regexp[i] == '['){
            len++; i++;
            while (regexp[i]!=']'){
                i++;
            }
            i++;
        }
        else{
            len++; i++;
        }
    }
    return len;
}