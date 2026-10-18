#include <stdio.h>
#include <string.h>
#include <ctype.h>

int controlli (int i, int flag, char pre_char, char line[100]);

int main(void)
{
    FILE *input_file;

    char line [50], pre_char;

    int parentesi_aperte = 0, flag = 0, i = 0, length = 0, count = 0;

    if ((input_file = fopen ("C:/Users/franc/Desktop/Uni/Secondo_Semestre/Tecniche_di_programmazione/Laboratori/Lab_03/Es2/expr.txt", "r")) == NULL)
    {
        printf ("Errore nell'apertura del file\n");
        return 1;
    }

    while (fgets (line, sizeof (line), input_file))
    {
        parentesi_aperte = 0;
        count++;
        i = 2;
        flag = 0;
        length = (int) strlen (line);
        if (line[0] == ')')
        {
            flag = 11;
        }
        else if (line[0] == '(')
        {
            parentesi_aperte++;
        }
        if (line[1] == ')' && parentesi_aperte == 0)
        {
            flag = 11;
        }
        else if (line[1] == '(')
        {
            parentesi_aperte++;
        }

        while ((i < length) && flag == 0)
        {
            if (line[i] != ' ')
            {
                if (line[i-1] != ' ')
                {
                    pre_char = line[i-1];
                }
                else
                {
                    pre_char = line[i-2];
                }
            }
            else
            {
                pre_char = line[i-1];
            }
            if (line[i] == '(')
            {
                parentesi_aperte++;
            }

            flag = controlli (i, flag, pre_char, line);

            if (line[i] == ')')
            {
                parentesi_aperte--;
            }

            if (parentesi_aperte < 0)
            {
                flag = 11;
            }

            i++;
        }
        if (i == length && strchr("+-*/%", pre_char) && line[i-1] == '\n')
        {
            flag = 11;
        }

        if (flag == 11)
        {
            printf ("Errore nella lettura di un operando (espressione %d)\n", count);
        }
        else if (flag == 10)
        {
            printf ("Errore nella lettura di un numero (espressione %d)\n", count);
        }
        else if (parentesi_aperte != 0)
        {
            printf ("Errore nella lettura di un operando (espressione %d)\n", count);
        }

    }

    return 0;
}

int controlli (int i, int flag, char pre_char, char line[100])
{
    //(3 + 2) / 7
    if ((isdigit(line[i])) && (line[i-1] == ' ') && (isdigit(line[i-2])))
    {
        flag = 10;
    }
    else if ((((line[i] == '(') || (isdigit(line[i]))) && ((pre_char != '(') && (!strchr("+-*/%", pre_char)))))
    {
        if (!isdigit(line[i-1]))
        {
            flag = 10;
        }
    }
    else if (line[i] == ')' && ((pre_char != ')') && (!isdigit(pre_char))))
    {
        flag = 11;
    }
    else if (strchr("+-*/%", line[i]) && ((pre_char != ')') && (!isdigit(pre_char))))
    {
        flag = 11;
    }

    return flag;
}