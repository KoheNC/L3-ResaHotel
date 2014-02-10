#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "serveur.h"

//Extraction de la requête, tri des variables potentielles et formulation de la requête SQL en conséquence
int extraction_requete(char *requete, char *sql)
{
    char login[10], mdp[10];
    char idenRequete[15], resteRequete[1000];
    //char *idenRequete=NULL, *resteRequete=NULL;
    int nbreCaractere=0;

    //On identifie le type de requête
    sscanf(requete, "%[^/]/%[^END]",idenRequete,resteRequete);

    printf("DEBUG: requete=%s \n", requete);
    printf("DEBUG: idenRequete=%s\n",idenRequete);
    printf("DEBUG: resteRequete=%s\n",resteRequete);

    //On enlève le '/' restant à la fin
    nbreCaractere=strlen(resteRequete);
    resteRequete[nbreCaractere-1]='\0';


   /* char messagedetest[100];
    sprintf(messagedetest,"test message, resterequete=%s",resteRequete);
    printf("%s",messagedetest);*/

    if(strcmp(idenRequete,"AUTHENT")==0)
        {
        printf("ceb pour l'authent\n");
        sscanf(resteRequete, "%[^/]/%s",login,mdp);

        printf("DEBUG: login=%s \n", login);
        printf("DEBUG: mdp=%s \n", mdp);
char *messagetest=NULL;
        sprintf(messagetest,"test %s",login);
        printf("%s",messagetest);
        //sprintf(sql,"SELECT  identifiant=%s AND pwd=%s",login,mdp);
        //printf("\n");
        //printf("sql=%s",sql);

        }










    else if(strcmp(idenRequete,"CONSULT_ETOILE")==0)
        printf("ceb pour l'étoile\n");




    Emission("1\n");


    return 1;
};
