#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void vider_buffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

int lire(char *chaine, int longueur)
{
    char *positionEntree = NULL; //on cherche le caractère d'entrée, \n

    if (fgets(chaine, longueur, stdin) != NULL)
    {
        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL)
            *positionEntree = '\0';
        else
            vider_buffer();
        return 1;
    }
    else
    {
        vider_buffer();
        return 0;
    }
}

