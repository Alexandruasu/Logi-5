//164 5 Satalla Alexandru
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int verificare_per_col_lin(int tabla[5][5], int perechile[5][5])
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (tabla[i][j] != 0)
            {
                for (int k = j + 1; k < 5; k++)
                {
                    if (tabla[i][j] == tabla[i][k])
                    {
                        return 0;
                    }
                }
                for (int k = i + 1; k < 5; k++)
                {
                    if (tabla[i][j] == tabla[k][j])
                    {
                        return 0;
                    }
                }
                for (int z = 0; z < 5; z++)
                {
                    for (int v = 0; v < 5; v++)
                    {
                        if (z != i || v != j)
                        {
                            if (perechile[i][j] == perechile[z][v] && tabla[i][j] == tabla[z][v])
                            {
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }
    
    return 1;
}


int verifica_linia(int linia, int numar, int tabla[5][5])
{
    for (int i = 0; i < 5; i++)
    {
        if (tabla[linia][i] == numar)
        {
            return 0;
        }
    }
    return 1;
}

int verifica_coloana(int coloana, int numar, int tabla[5][5])
{
    for (int i = 0; i < 5; i++)
    {
        if (tabla[i][coloana] == numar)
        {
            return 0;
        }
    }
    return 1;
}

int verifica_perechea(int linia, int coloana, int numar, int perechile[5][5], int tabla[5][5])
{
    int pereche = perechile[linia][coloana];
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (perechile[i][j] == pereche && tabla[i][j] == numar)
            {
                return 0;
            }
        }
    }
    return 1;
}

int validarea(int linia, int coloana, int numar, int perechile[5][5], int tabla[5][5])
{
    if (!verifica_linia(linia, numar, tabla) || !verifica_coloana(coloana, numar, tabla) || !verifica_perechea(linia, coloana, numar, perechile, tabla))
    {
        return 0;
    }
    return 1;
}

int solutia(int linia, int coloana, int perechile[5][5], int tabla[5][5])
{
    if (coloana == 5)
    {
        coloana = 0;
        linia++;
        if (linia == 5)
        {
            return 1;
        }
    }
    if (tabla[linia][coloana] != 0)
    {
        return solutia(linia, coloana+1, perechile, tabla);
    }
    for (int numar = 1; numar <= 5; numar++)
    {
        if (validarea(linia, coloana, numar, perechile, tabla))
        {
            tabla[linia][coloana] = numar;
            if (solutia(linia, coloana+1, perechile, tabla))
            {
                return 1;
            }
            tabla[linia][coloana] = 0;
        }
    }
    return 0;
}

void afisare_tabla(int tabla[5][5],int perechile[5][5])
{
    printf("\n");
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if(perechile[i][j]==1)
                printf("\e[0;41m%d ", tabla[i][j]);
            if(perechile[i][j]==2)
                printf("\e[0;42m%d ", tabla[i][j]);
            if(perechile[i][j]==3)
                printf("\e[0;46m%d ", tabla[i][j]);
            if(perechile[i][j]==4)
                printf("\e[0;43m%d ", tabla[i][j]);
            if(perechile[i][j]==5)
                printf("\e[0;45m%d ", tabla[i][j]);
            printf("\e[0m");
        }
        printf("\n");
    }
    printf("\n");
}
void proceseaza_fisier(char *input_nume_fisier)
{
    FILE *f = fopen(input_nume_fisier, "r");
    if (f == NULL)
    {
        fprintf(stderr, "deschiderea fisierului a esuat %s\n", input_nume_fisier);
        exit(EXIT_FAILURE);
    }
    int i, j, tabla[5][5], perechile[5][5], verificare[5][5];
    for (i = 0; i < 5; i++)
        for (j = 0; j < 5; j++)
            fscanf(f, "%d", &tabla[i][j]);
    for (i = 0; i < 5; i++)
        for (j = 0; j < 5; j++)
            fscanf(f, "%d", &perechile[i][j]);
    for (i = 0; i < 5; i++)
        for (j = 0; j < 5; j++)
            fscanf(f, "%d", &verificare[i][j]);
    fclose(f);
    if(!verificare_per_col_lin(tabla,perechile))
    {
        printf("Tabla incorecta!\n");
        exit(EXIT_FAILURE);
    }
    if (solutia(0, 0, perechile, tabla))
    {
        printf("Solutia:");
        afisare_tabla(tabla,perechile);
    }
    else
    {
        printf("Nu s-a gasit o solutie!\n");
    }
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            assert(tabla[i][j]==verificare[i][j]);
}
int main()
{
    proceseaza_fisier("date1.in");
    proceseaza_fisier("date2.in");
    proceseaza_fisier("date3.in");

}
