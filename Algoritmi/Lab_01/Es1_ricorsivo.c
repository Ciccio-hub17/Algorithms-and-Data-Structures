#include <stdio.h>
#include <ctype.h>

char *cercaRegexp (char *src, char *regexp);

int main (){

    char str[] = "Ciaotiao";
    char regexp[] = "[^C]iao";
    char *occorrenza;
    int k = 0, flag = 0;
    //while che mi permette di ciclare o fino alla fine della stringa o fino a quando non si trova un'occorrenza
    while (*(str+k) != '\0' && !flag){
        occorrenza = cercaRegexp(str+k, regexp);
        //se il carattere ritornato è diverso da null, allora ha trovato un'occorrenza e può uscire
        if (occorrenza != NULL){
            flag = 1;
        }
        k++;
    }
    
    if (occorrenza != NULL){
        printf ("Il carattere e': %c\n\n", *occorrenza);
    }
    else{
        printf ("Nessuna occorrenza trovata!\n\n");
    }
    return 0;
}

char * cercaRegexp (char *src, char *regexp){
    //se hai finito l'espressione, è stata trovata un'occorrenza
    if (*regexp == '\0') {return src;}

    //se ha finito la stringa sorgente, allora vuol dire che non c'è occorrenza
    if (*src == '\0') {return NULL;}

    //vedi se il carattere matcha oppure se c'è un punto
    if (*src == *regexp || *regexp == '.') {
            //se il valore ritornato da una eventuale precedente chiamata ricorsiva non è null, allora continua
            if (cercaRegexp(src+1, regexp+1) != NULL){
                //ritorno il rispettivo carattere
                return src;
            }
    }
    
    //controllo sul carattere maiuscolo
    if ((*regexp == '\a') && (islower(*src))){
        if (cercaRegexp(src+1, regexp+1) != NULL){
                return src;
            }
    }

    //controllo sul carattere minuscolo
    if (*regexp == '\b' && isupper(*src)){
        if (cercaRegexp(src+1, regexp+1) != NULL){
                return src;
            }
    }

    //se trovi una parentesi
    if (*regexp == '['){
        int flag=1;
        regexp++;
        //se trovi un apice
        if (*regexp == '^'){
            regexp++;
            //fai un ciclo fino a quando non trovi la parentes chiusa
            while (*regexp != ']'){
                //se c'è un carattere che non va bene modifica il flag
                if (*regexp == *src){
                    flag = 0;
                }
                regexp++;
            }
        }
        //altrimenti
        else{
            flag = 0;
            while (*regexp != ']'){
                //appena trovi un carattere che va bene cambia il flag
                if (*regexp == *src){
                    flag=1;
                }
                regexp++;
            }
        }

        //se flag è ancora == 1, allora continua nella ricorsione
        if (flag){
            if (cercaRegexp(src+1, regexp+1) != NULL){
                return src;
            }
        }
    }
    //altrimenti, se non è stato trovato alcun match, ritorna null e riparti dal while, dal carattere successivo
    return NULL;
}