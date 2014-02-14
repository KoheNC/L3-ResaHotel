#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "serveur.h"
#define MORCEAU 8 //pour l'allocation

//Extraction de la requête, tri des variables potentielles et formulation de la requête SQL en conséquence
int extraction_requete(char *requete, char **sql, char *IDRequete, char **identifiant)
{
    char idenRequete[15]={0}, resteRequete[1000]={0};
    char *p;    /*pointeur pour la liaison avec *sql passé en paramètre*/

    //On identifie le type de requête et on stocke le résultat dans idenRequete
    sscanf(requete, "%[^/]/%s",idenRequete,resteRequete);

    //On copie l'identifiant de la requête pour pouvoir le réutiliser dans le main, qui déterminera l'utilisation de Callback() ou CallbackSELECT()
    strcpy(IDRequete,idenRequete);

    //Comparaison du résultat et traitement
    if(strcmp(idenRequete,"AUTHENT")==0)
    {
        char login[10], mdp[10], *m;
        int longReqSQL=0, longLogin=0,longMdp=0;
        char *reqSQL="SELECT COUNT(identifiant),mdp FROM UTILISATEUR WHERE identifiant='' AND mdp='';";  /*Contient la requête SQL sans les variables qui vont se rajouter dedans après*/

        sscanf(resteRequete, "%[^/]/%s",login,mdp);

        //On compte le nombre de caractères de la requete + identifiant + mdp pour faire l'allocation nécessaire en mémoire(c'est un peu brouillon et archaïque je sais)
        longReqSQL=strlen(reqSQL);
        longLogin=strlen(login);
        longMdp=strlen(mdp);
        longReqSQL=longReqSQL+longLogin+longMdp;
        p=malloc(longReqSQL*MORCEAU*sizeof(char));

        //Puis on crée la requête et on la met dans *sql
        sprintf(p,"SELECT COUNT(identifiant),mdp FROM UTILISATEUR WHERE identifiant='%s' AND mdp='%s';",login,mdp);
        *sql=p;

        //On stocke le login dans *identifiant
        m=malloc(longLogin*MORCEAU*sizeof(char));
        strcpy(m,login);
        *identifiant=m;
    }

    else if(strcmp(idenRequete,"CONSULT_ETOILE")==0)
        {
        char finRequete[100], nbreEtoile[2];
        int longReqSQL=0;
        char *reqSQL="SELECT nomHotel,ville FROM HOTEL WHERE nbreEtoile='';";  /*Contient la requête SQL sans les variables qui vont se rajouter dedans après*/

        sscanf(resteRequete, "%[^/]/%s",nbreEtoile,finRequete);

        //On compte le nombre de caractères de la requete pour faire l'allocation nécessaire en mémoire
        longReqSQL=strlen(reqSQL);
        longReqSQL=longReqSQL+1;        /*le 1 Correspond au nbre d'étoile*/
        p=malloc(longReqSQL*MORCEAU*sizeof(char));

        //Puis on crée la requête et on la met dans *sql
        sprintf(p,"SELECT nomHotel,ville FROM HOTEL WHERE nbreEtoile='%s';",nbreEtoile);
        *sql=p;
        }

    else if(strcmp(idenRequete,"CONSULT_VILLE")==0)
        {
        char finRequete[100], nomVille[25];
        int longReqSQL=0,longVille=0;
        char *reqSQL="SELECT nomHotel,ville FROM HOTEL WHERE ville='';";  /*Contient la requête SQL sans les variables qui vont se rajouter dedans après*/

        sscanf(resteRequete, "%[^/]/%s",nomVille,finRequete);

        //On compte le nombre de caractères de la requete pour faire l'allocation nécessaire en mémoire
        longReqSQL=strlen(reqSQL);
        longVille=strlen(nomVille);
        longReqSQL=longReqSQL+longVille;
        p=malloc(longReqSQL*MORCEAU*sizeof(char));

        //Puis on crée la requête et on la met dans *sql
        sprintf(p,"SELECT nomHotel,ville FROM HOTEL WHERE ville='%s';",nomVille);
        *sql=p;
        }

    else if(strcmp(idenRequete,"CONSULT_NOM")==0)
        {
        int longReqSQL=0;
        char *reqSQL="SELECT nomHotel,ville FROM HOTEL GROUP BY ville,nomHotel;";  /*Contient la requête SQL sans les variables qui vont se rajouter dedans après*/

        longReqSQL=strlen(reqSQL);
        p=malloc(longReqSQL*MORCEAU*sizeof(char));

        //Puis on crée la requête et on la met dans *sql
        sprintf(p,"SELECT nomHotel,ville FROM HOTEL GROUP BY ville,nomHotel;");
        *sql=p;
        }

    else if(strcmp(idenRequete,"RESERVATION")==0)
        {
        char finRequete[100], date[10], nomHotel[20],nomClient[20];
        int longReqSQL=0,longNomHotel=0,longNomClient=0;
        char *reqSQL="INSERT INTO RESERVATION (nomHotel,nomClient,date) VALUES ('','','');";  /*Contient la requête SQL sans les variables qui vont se rajouter dedans après*/

        sscanf(resteRequete, "%[^/]/%s",nomHotel,finRequete);
        sscanf(finRequete, "%[^/]/%s",nomClient,date);

        //On compte le nombre de caractères de la requete pour faire l'allocation nécessaire en mémoire
        longReqSQL=strlen(reqSQL);
        longNomHotel=strlen(nomHotel);
        longNomClient=strlen(nomClient);
        longReqSQL=longReqSQL+longNomHotel+longNomClient+10;        /*le 10 Correspond à la date*/
        p=malloc(longReqSQL*MORCEAU*sizeof(char));

        //Puis on crée la requête et on la met dans *sql
        sprintf(p,"INSERT INTO RESERVATION (nomHotel,nomClient,date) VALUES ('%s','%s','%s');",nomHotel,nomClient,date);
        *sql=p;
        }
    else if(strcmp(idenRequete,"ACTGER")==0)
        {
            char nomHotel[20], nombreEtoile[2], ville[20], nombreChambre[3], nomGerant[10], action[15];
            int longReqSQL=0, longNomHotel=0, longVille=0, longNomGerant=0, longNombreChambre=0,longNombreEtoile=0;

            strcpy(nomGerant,*identifiant);

            sscanf(resteRequete, "%[^/]/%s",action,resteRequete);
            sscanf(resteRequete, "%[^/]/%s",nomHotel,resteRequete);
            sscanf(resteRequete, "%[^/]/%s",nombreEtoile,resteRequete);
            sscanf(resteRequete, "%[^/]/%s",ville,resteRequete);
            sscanf(resteRequete, "%[^/]/%s",nombreChambre,resteRequete);
            sscanf(resteRequete, "%[^/]/%s",nomGerant,resteRequete);
            printf("resteRequete après sscanf=%s\n\n",resteRequete);

            /*printf("Action=%s\n",action);
            printf("nomHotel=%s\n",nomHotel);
            printf("nbreEtoile=%s\n",nombreEtoile);
            printf("ville=%s\n",ville);
            printf("nbreChambre=%s\n\n",nombreChambre);*/
            longVille=strlen(ville);
            longNombreChambre=strlen(nombreChambre);
            longNomGerant=strlen(nomGerant);
            longNomHotel=strlen(nomHotel);
            longNombreEtoile=strlen(nombreEtoile);

            if(strcmp(action,"saveNewHotel")==0)
            {
                printf("%s %s %s %s",nomHotel,nombreEtoile,ville,nombreChambre);
                /*Contient la requête SQL sans les variables qui vont se rajouter dedans après*/

                char *reqSQL="INSERT INTO HOTEL (nomHotel,nbreEtoile,ville,nbreChambre,gerant) VALUES ('',,'',,'');";

                //On compte le nombre de caractères de la requete
                longReqSQL=strlen(reqSQL);
                longReqSQL=longReqSQL+longVille+longNombreChambre+longNomGerant+longNomHotel+longNombreEtoile;
                p=malloc(longReqSQL*MORCEAU*sizeof(char));

                printf("ceb pour la requete d'enregistrement de l'hotel !\n\n");

                sprintf(p,"INSERT INTO HOTEL (nomHotel,nbreEtoile,ville,nbreChambre,gerant) VALUES ('%s',%s,'%s',%s,'%s');",nomHotel,nombreEtoile,ville,nombreChambre,nomGerant);
                *sql=p;
            }
            else
            {
                char *reqSQL="UPDATE HOTEL SET nbreEtoile=,nbreChambre= WHERE nomHotel='' AND ville='' AND gerant='';";

                //On compte le nombre de caractères de la requete
                longReqSQL=strlen(reqSQL);
                longReqSQL=longReqSQL+longVille+longNombreChambre+longNomGerant+longNomHotel+longNombreEtoile;
                p=malloc(longReqSQL*MORCEAU*sizeof(char));

                sprintf(p,"UPDATE HOTEL SET nbreEtoile=%s,nbreChambre=%s WHERE nomHotel='%s' AND ville='%s' AND gerant='%s';",nombreEtoile,nombreChambre,nomHotel,ville,nomGerant);
                *sql=p;
            }

        }
    return 1;
};
