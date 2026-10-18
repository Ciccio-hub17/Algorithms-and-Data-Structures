#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int comprimi (FILE *source, FILE *compressed) {

    char line [256];
    int i, count, numChar = 0, length;

    while (fgets(line, sizeof(line), source) != NULL) {
        length = strlen (line);
        i = 0;
        count = 1;
        while (i < length) {
            if (line [i] == line [i+1]) {
                count++;
                i++;
                while ((line [i] == line[i+1]) && (count <= 9)) {
                    count++;
                    i++;
                }

                fprintf (compressed, "%c$%d", line[i-1], count-1);
                numChar = numChar + 3;
                count = 1;
                i++;
            }
            else {
                count = 1;
                fprintf (compressed, "%c", line[i]);
                i++;
                numChar++;
            }
        }
        fprintf (compressed, "\n");
    }
    return numChar;
}

int decomprimi (FILE *compressed, FILE *decompressed) {
    char line [256], previous;

    int length, i, numChar, repeat, j;

    while (fgets(line, sizeof(line), compressed) != NULL) {
        length = strlen (line);

        i = 0;
        while (i < length) {
            if (line[i] != '$') {
                fprintf (decompressed, "%c", line[i]);
                numChar++;
                i++;
            }
            else {
                repeat =  line[i+1] - '0';
                previous = line[i-1];
                j = 0;
                while (j < repeat) {
                    fprintf (decompressed, "%c", previous);
                    j++;
                    numChar++;
                }
                i++;
                i++;
            }
        }

        fprintf (decompressed, "\n");
    }
    return numChar;
}

int main(void) {
    FILE *source, *compressed, *decompressed, *compressedR;
    char choice;
    int result;

    if ((source = fopen("sorgente.txt", "r")) == NULL) {
        printf ("Errore nell'apertura del file\n");
        return 1;
    }
    if ((compressed = fopen("compresso.txt", "w")) == NULL) {
        printf ("Errore nell'apertura del file\n");
        return 2;
    }
    if ((decompressed = fopen ("decompresso.txt", "w")) == NULL) {
        printf ("Errore nell'apertura del file\n");
        return 3;
    }
    if ((compressedR = fopen ("compresso1.txt", "r")) == NULL) {
        printf ("Errore nell'apertura del file\n");
        return 4;
    }

    printf ("Preferisci decodificare (D) o codificare (C)?\n");

    choice = getchar();
    getchar ();

    if (choice == 'C') {
        result = comprimi (source, compressed);
    }
    else {
        result = decomprimi (compressedR, decompressed);
    }

    fclose (compressed);
    fclose (decompressed);
    fclose (compressedR);
    fclose (source);


    return 0;
}