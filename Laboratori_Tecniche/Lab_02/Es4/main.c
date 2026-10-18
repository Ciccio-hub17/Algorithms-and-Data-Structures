#include <stdio.h>
#include <ctype.h>

void codifica (FILE *input, FILE *output);

void decodifica (FILE *input, FILE *output);

int main(void) {
    FILE *to_read_code, *to_write_code, *to_read_decode, *to_write_decode;

    char choice = ' ';

    if ((to_read_code = fopen ("input.txt", "r")) == NULL) {
        printf ("Errore nell'apertura del file");
        return 1;
    }
    if ((to_read_decode = fopen ("input1.txt", "r")) == NULL) {
        printf ("Errore nell'apertura del file");
        return 2;
    }
    if ((to_write_code = fopen ("output.txt", "w")) == NULL) {
        printf ("Errore nell'apertura del file");
        return 3;
    }
    if ((to_write_decode = fopen ("output1.txt", "w")) == NULL) {
        printf ("Errore nell'apertura del file");
        return 4;
    }

    printf ("Vuoi codificare (C) o decodificare (D)?");

    scanf ("%c", &choice);
    getchar ();

    if (choice == 'C') {
        codifica (to_read_code, to_write_code);
    }
    else {
        decodifica(to_read_decode, to_write_decode);
    }

    return 0;
}

void codifica (FILE *input, FILE *output) {

    int k = 0, h = 0, toPrint = 0;

    char previous, ch;

    previous = fgetc (input);
    fprintf (output, "%c", previous);

    k = 0;

    while ((ch = fgetc (input)) != EOF) {
        if (isdigit(ch)) {
            toPrint = ((int) ch - '0' + k) % 10 + '0';
            k = (k + 1) % 10;
            fprintf (output, "%c", (char) toPrint);
        }
        else if (isalpha(ch)) {
            if (isalpha(previous)) {
                if (isupper(previous)) {
                    h = previous - 'A';
                }
                else {
                    h = previous - 'a';
                }

                if (isupper(ch))
                {
                    toPrint = (ch - 'A' + h) % 26 + 'A';
                }
                else
                {
                    toPrint = (ch - 'a' + h) % 26 + 'a';
                }
                fprintf (output, "%c", (char) toPrint);
            }
            else {
                toPrint = ch;
                fprintf (output, "%c", toPrint);
            }
        }
        else {
            toPrint = ch;
            fprintf (output, "%c", toPrint);
        }
        previous = (char) toPrint;
    }
}

void decodifica (FILE *input, FILE *output)
{
    int k = 0, h = 0, toPrint = 0;

    char previous, ch;

    previous = fgetc (input);
    fprintf (output, "%c", previous);

    k = 0;

    while ((ch = fgetc (input)) != EOF) {
        if (isdigit(ch)) {
            toPrint = ((int) ch - '0' - k + 10) % 10 + '0';
            k = (k + 1) % 10;
            fprintf (output, "%c", (char) toPrint);
        }
        else if (isalpha(ch)) {
            if (isalpha(previous)) {
                if (isupper(previous)) {
                    h = previous - 'A';
                }
                else {
                    h = previous - 'a';
                }

                if (isupper(ch))
                {
                    toPrint = (ch - 'A' - h + 26) % 26 + 'A';
                }
                else
                {
                    toPrint = (ch - 'a' - h + 26) % 26 + 'a';
                }
                fprintf (output, "%c", (char) toPrint);
            }
            else {
                toPrint = ch;
                fprintf (output, "%c", toPrint);
            }
        }
        else {
            toPrint = ch;
            fprintf (output, "%c", toPrint);
        }
        previous = (char) toPrint;
    }
}