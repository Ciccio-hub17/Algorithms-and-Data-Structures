#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define input "input.txt"

#define output "output.txt"

int main(void) {
    FILE *input_file, *output_file;

    int i = 0, length = 0, flag = 0, count = 0, k = 0, n = 0;

    char line [100];

    if ((input_file = fopen (input, "r")) == NULL) {
        printf ("Errore nell'apertura del file di lettura");
        return 1;
    }
    if ((output_file = fopen (output, "w")) == NULL ) {
        printf ("Errore nell'apertura del file");
        return 2;
    }

    while ((fgets (line, sizeof (line), input_file)) != NULL) {
        length = (int) strlen (line);
        length = length - 1;
        count = 0;
        n = 0;
        for (i = 0; i < 25-n; i++)
        {
            if (i < length)
            {
                count++;
                if (isdigit(line[i]))
                {
                    fprintf (output_file, "%c", '*');
                }
                else if (strchr(".,;:!?", line[i]) && (line[i+1] != ' ') && (line[i+1] != '\n'))
                {
                    fprintf (output_file, "%c ", line[i]);
                    n++;
                    if ((line[i] == '.') || (line[i] == '!') || (line[i] == '?'))
                    {
                        flag = 1;
                    }
                }
                else if ((line[i] == '.') || (line[i] == '!') || (line[i] == '?'))
                {
                    flag = 1;
                    fprintf (output_file, "%c", line[i]);
                }
                else
                {
                    if ((flag == 1) && (isalpha(line[i])))
                    {
                        flag = 0;
                        if (islower(line[i]))
                        {
                            line[i] = (char) toupper(line[i]);
                            fprintf (output_file, "%c", line[i]);
                        }
                        else
                        {
                            fprintf (output_file, "%c", line[i]);
                        }

                    }
                    else
                    {
                        fprintf (output_file, "%c", line[i]);
                    }
                }
            }
            else
            {
                fprintf (output_file, "%c", ' ');
            }
        }
        fprintf (output_file, "| c:%d \n", count);
        k = i;
        count = 1;
        n=0;
        if (i < length)
        {
            for (i = k; i < k + 25-n; i++)
            {
                if (i < length)
                {
                    count++;
                    if (isdigit(line[i]))
                    {
                        fprintf (output_file, "%c", '*');
                    }
                    else if (strchr(".,;:!?", line[i]) && (line[i+1] != ' ') && (line[i+1] != '\n'))
                    {
                        fprintf (output_file, "%c ", line[i]);
                        n++;
                        if ((line[i] == '.') || (line[i] == '!') || (line[i] == '?'))
                        {
                            flag = 1;
                        }
                    }
                    else if (((line[i] == '.') || (line[i] == '!') || (line[i] == '?')))
                    {
                        flag = 1;
                        fprintf (output_file, "%c", line[i]);
                    }
                    else
                    {
                        if ((flag == 1) && (isalpha(line[i])))
                        {
                            flag = 0;
                            if (islower(line[i]))
                            {
                                line[i] = (char) toupper(line[i]);
                                fprintf (output_file, "%c", line[i]);
                            }
                            else if (line[i] == ' ')
                            {
                                fprintf (output_file, "%c", line[i]);
                            }
                        }
                        else
                        {
                            fprintf (output_file, "%c", line[i]);
                        }
                    }
                }
                else
                {
                    fprintf (output_file, "%c", ' ');
                }
            }
            fprintf (output_file, "| c:%d \n", count);
        }
    }
    return 0;
}