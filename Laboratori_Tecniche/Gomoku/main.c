#include <stdio.h>

#define nomeFile "../partita0.txt"

void leggifile (char tabella[19][19], FILE *input_file);

void gioco (char tabella[19][19]);

int controllo(char tabella[19][19], char giocatore, int x, int y);

int main(void)
{
    int i = 0, j = 0;
    char tabella [19][19];
    FILE *input_file;

    if ((input_file = fopen(nomeFile, "r")) == NULL)
    {
        printf ("Errore nella lettura del file\n");
        return 1;
    }

    leggifile(tabella, input_file);

    gioco (tabella);

    fclose (input_file);
    return 0;
}

void leggifile (char tabella[19][19], FILE *input_file)
{
    int i = 0, j = 0;

    for (i = 0; i < 19; i++)
    {
        for (j = 0; j < 19; j++)
        {
            tabella [i][j] = fgetc (input_file);
            printf (" %c ", tabella[i][j]);
        }
        printf ("\n");
        fgetc(input_file);
    }
}

void gioco (char tabella[19][19])
{
    int turno = 1, flag = 0, x = 0, y = 0, risultato = 0;
    int i = 0, j = 0;
    char giocatore = 'N';
    while (!flag)
    {
        printf ("Dammi le coordinate (x, y)\n");
        risultato = scanf ("%d %d", &x, &y);
        while (risultato != 2 || x < 1 || x > 19 || y < 1 || y > 19 || tabella[x-1][y-1] != '.')
        {
            getchar ();
            printf ("Dati non validi, riprovare\n");
            risultato = scanf ("%d %d", &x, &y);
        }
        x--; y--;
        tabella[x][y] = giocatore;

        flag = controllo (tabella, giocatore, x, y);

        if (giocatore == 'N')
        {
            giocatore = 'B';
        }
        else
        {
            giocatore = 'N';
        }

        for (i = 0; i < 19; i++)
        {
            for (j = 0; j < 19; j++)
            {
                printf (" %c ", tabella[i][j]);
            }
            printf ("\n");
        }
    }
    if (giocatore == 'B')
    {
        printf ("Partita terminata: vittoria del nero\n");
    }
    else
    {
        printf ("Partita terminata: vittoria del bianco\n");
    }
}

int controllo(char tabella[19][19], char giocatore, int x, int y)
{
    int flag = 0, conta = 1, i = x, j = y;

    //controllo le colonne
    i--;
    while (conta != 5 && tabella[i][j] == giocatore && i > 0)
    {
        if (tabella [i][j] == giocatore)
        {
            conta++;
        }
        i--;
    }
    i = x+1;
    while (conta != 5 && tabella[i][j] == giocatore && i < 19)
    {
        if (tabella [i][j] == giocatore)
        {
            conta++;
        }
        i++;
    }
    conta = 1;
    //controllo le righe
    j--;
    while (conta != 5 && tabella[i][j] == giocatore && j > 0)
    {
        if (tabella [i][j] == giocatore)
        {
            conta++;
        }
        j--;
    }
    j = y+1;
    while (conta != 5 && tabella[i][j] == giocatore && j < 19)
    {
        if (tabella [i][j] == giocatore)
        {
            conta++;
        }
        j++;
    }
    conta = 1;
    //controllo la diagonale principale
    i--; j--;
    while (conta != 5 && tabella[i][j] == giocatore && i > 0 && j > 0)
    {
        if (tabella [i][j] == giocatore)
        {
            conta++;
        }
        j--;i--;
    }
    i = x+1; j = y+1;
    while (conta != 5 && tabella[i][j] == giocatore && i < 19 && j < 19)
    {
        if (tabella [i][j] == giocatore)
        {
            conta++;
        }
        j++; i++;
    }
    conta = 1;
    //controllo la diagonale secondaria
    i = x+1; j = y-1;
    while (conta != 5 && tabella[i][j] == giocatore && i < 19 && j > 0)
    {
        if (tabella [i][j] == giocatore)
        {
            conta++;
        }
        j--; i++;
    }
    i = x-1; j = y+1;
    while (conta != 5 && tabella[i][j] == giocatore && i > 0 && j < 19)
    {
        if (tabella [i][j] == giocatore)
        {
            conta++;
        }
        j++; i--;
    }
    if (conta == 5)
    {
        flag = 1;
        return flag;
    }
    return flag;
}