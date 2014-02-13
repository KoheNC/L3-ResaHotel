#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "serveur.h"
#define MORCEAU 8 //pour l'allocation

//Extraction de la requête, tri des variables potentielles et formulation de la requête SQL en conséquence
int extraction_requete(char *requete, char **sql)
    {
    char idenRequete[15], resteRequete[1000];
    int nbreCaractere=0;
    char *p;    /*pointeur pour la liaison avec *sql passé en paramètre*/

    //On identifie le type de requête et on enlève le '/' restant à la fin
    sscanf(requete, "%[^/]/%[^END]",idenRequete,resteRequete);
    nbreCaractere=strlen(resteRequete);
    resteRequete[nbreCaractere-1]='\0';

    //Comparaison du résultat et traitement
    if(strcmp(idenRequete,"AUTHENT")==0)
        {
        char login[10], mdp[10];
        int longReqSQL=0, longLogin=0,longMdp=0;
        char *reqSQL="SELECT COUNT(identifiant),mdp FROM UTILISATEUR WHERE identifiant='' AND mdp='';";  /*Contient la requête SQL sans les variables qui vont se rajouter dedans après*/

        printf("ceb pour l'authent\n");
        sscanf(resteRequete, "%[^/]/%s",login,mdp);

        //On compte le nombre de caractères de la requete + identifiant + mdp pour faire l'allocation nécessaire en mémoire(c'est un peu brouillon et archaïque je sais)

        longReqSQL=strlen(reqSQL);
        longLogin=strlen(login);
        longMdp=strlen(mdp);
        longReqSQL=longReqSQL+longLogin+longMdp;
        p=malloc(longReqSQL*MORCEAU*sizeof(char));

        //Puis on crée la requête et on la fout dans *sql
        sprintf(p,"SELECT COUNT(identifiant),mdp FROM UTILISATEUR WHERE identifiant='%s' AND mdp='%s';",login,mdp);
        *sql=p;
        }

    else if(strcmp(idenRequete,"CONSULT_ETOILE")==0)
        {
        char finRequete[100], nbreEtoile[2];
        int longReqSQL=0;
        char *reqSQL="SELECT nomHotel,ville FROM HOTEL WHERE nbreEtoile='';";  /*Contient la requête SQL sans les variables qui vont se rajouter dedans après*/

        printf("ceb pour l'étoile\n");
        sscanf(resteRequete, "%[^/]/%s",nbreEtoile,finRequete);
        printf("DEBUG: nbreEtoile=%s\n",nbreEtoile);
        printf("DEBUG: finRequete=%s\n",finRequete);

        //On compte le nombre de caractères de la requete + identifiant + mdp pour faire l'allocation nécessaire en mémoire(c'est un peu brouillon et archaïque je sais)

        longReqSQL=strlen(reqSQL);
        longReqSQL=longReqSQL+1;        /*le 1 Correspond au nbre d'étoile*/
        p=malloc(longReqSQL*MORCEAU*sizeof(char));

        //Puis on crée la requête et on la fout dans *sql
        sprintf(p,"SELECT nomHotel,ville FROM HOTEL WHERE nbreEtoile='%s';",nbreEtoile);
        *sql=p;
        }

    else if(strcmp(idenRequete,"CONSULT_VILLE")==0)
        {
        char finRequete[100], nomVille[25];
        int longReqSQL=0,longVille=0;
        char *reqSQL="SELECT nomHotel,ville FROM HOTEL WHERE ville='';";  /*Contient la requête SQL sans les variables qui vont se rajouter dedans après*/

        printf("ceb pour la ville !\n\n");
        sscanf(resteRequete, "%[^/]/%s",nomVille,finRequete);
        printf("DEBUG: nomVille=%s\n",nomVille);
        printf("DEBUG: finRequete=%s\n",finRequete);

        //On compte le nombre de caractères de la requete + identifiant + mdp pour faire l'allocation nécessaire en mémoire(c'est un peu brouillon et archaïque je sais)

        longReqSQL=strlen(reqSQL);
        longVille=strlen(nomVille);
        longReqSQL=longReqSQL+longVille;
        p=malloc(longReqSQL*MORCEAU*sizeof(char));

        //Puis on crée la requête et on la fout dans *sql
        sprintf(p,"SELECT nomHotel,ville FROM HOTEL WHERE ville='%s';",nomVille);
        *sql=p;
        }

    else if(strcmp(idenRequete,"CONSULT_NOM")==0)
        {
        int longReqSQL=0;
        char *reqSQL="SELECT nomHotel,ville FROM HOTEL GROUP BY ville,nomHotel;";  /*Contient la requête SQL sans les variables qui vont se rajouter dedans après*/

        printf("ceb pour le nom !\n\n");

        //On compte le nombre de caractères de la requete + identifiant + mdp pour faire l'allocation nécessaire en mémoire(c'est un peu brouillon et archaïque je sais)

        longReqSQL=strlen(reqSQL);

        p=malloc(longReqSQL*MORCEAU*sizeof(char));

        //Puis on crée la requête et on la fout dans *sql
        sprintf(p,"SELECT nomHotel,ville FROM HOTEL GROUP BY ville,nomHotel;");
        *sql=p;
        }

    else if(strcmp(idenRequete,"ACTGER")==0)
        {
        char *reqSQL="UPDATE HOTEL SET nbreChambre = WHERE nomHotel='' AND ville='' AND Gerant ='';";
        int longReqSQL=0,longChambre=0, longVille=0 ,longHotel=0,longGerant=0;
        char nomDELHotel[25], nomVille[25], nomGerant[10], nbreChambre[3];

	       //On compte le nombre de caractÃ¨res de la requete + identifiant + mdp pour faire l'allocation nÃ©cessaire en mÃ©moire(c'est un peu brouillon et archaÃ¯que je sais)
        printf("ceb pour l'act ger !\n\n");

        //sscanf(resteRequete, "%[^/]/%s",nomVille,finRequete);

        printf("DEBUG: nomVille=%s\n",nomVille);
       // printf("DEBUG: finRequete=%s\n",finRequete);

        //On compte le nombre de caractères de la requete + identifiant + mdp pour faire l'allocation nécessaire en mémoire(c'est un peu brouillon et archaïque je sais)

       // strcpy(nomGerant,identifiant); il sera dans la requete
        longReqSQL=strlen(reqSQL);
        longChambre=strlen(nbreChambre);
        longVille=strlen(nomVille);
        longHotel=strlen(nomDELHotel);
        longGerant=strlen(nomGerant);
        longReqSQL=longReqSQL+longChambre+longVille+longHotel+nomGerant;

        //nomGerant= identifiant;

        p=malloc(longReqSQL*MORCEAU*sizeof(char));

        //Puis on crée la requête et on la fout dans *sql
        sprintf(p,"UPDATE HOTEL SET nbreChambre =%s  WHERE nomHotel='%s' AND ville='%s' AND Gerant ='%s';",nbreChambre,nomDELHotel,nomVille, nomGerant);
 	    *sql=p;
        }

return 1;
}
