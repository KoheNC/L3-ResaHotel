#include <stdio.h>
#include <stdlib.h>

int main()
{
    char login[10], pwd[10];
    char formatageMsg[20],envoiMessage[50];
    printf("Veuillez entrer votre login\n");
    scanf("%10s",login);
    printf("Veuillez entrer votre mot de passe\n");
    scanf("%10s",pwd);
/*
    strcpy(formatageMsg,'AUTHENT/');
    strcat(formatageMsg,login);

    formatageMsg=login+"/"+pwd+"/END";
    */
    sprintf(formatageMsg,"AUTHENT/%s/%s/END\n",login,pwd);
    printf("%s",formatageMsg);
}
