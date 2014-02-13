#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "serveur.h"
#define MORCEAU 8 //pour l'allocation

//Extraction de la requête, tri des variables potentielles et formulation de la requête SQL en conséquence
int extraction_requete(char *requete, char **sql, char *IDRequete)
{
    char idenRequete[15], resteRequete[1000];
    int nbreCaractere=0;
    char *p;    /*pointeur pour la liaison avec *sql passé en paramètre*/

    //On identifie le type de requête et on enlève le '/' restant à la fin
    sscanf(requete, "%[^/]/%[^END]",idenRequete,resteRequete);
    nbreCaractere=strlen(resteRequete);
    resteRequete[nbreCaractere-1]='\0';

    //On copie l'identifiant de la requête pour pouvoir le réutiliser dans le main, qui déterminera l'utilisation de Callback() ou CallbackSELECT()
    strcpy(IDRequete,idenRequete);


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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////$
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Il faut modifier la requete sql en fonction de la structure de la table car j'ai oublié de la noter.
    else if(strcmp(idenRequete,"ACTGER")==0)
        {
            printf("je suis dans actger\n\n");
            char nomHotel[100];
            char nombreEtoile[2];
            char ville[50];
            char nombreChambre[2];
            char nomGerant[100];
            char action[13];
            char finRequete[50];
            int longReqSQL=0, longNomHotel=0, longVille=0, longNomGerant=0, longNombreChambre=0,longNombreEtoile=0;
            printf("test\n\n");
            //sscanf(resteRequete, "%[^/]/%s/%[^/]%s/%[^/]%s/%[^/]%s/%[^/]%s/%[^/]%s",action,nomHotel,nombreEtoile,ville,nombreChambre,nomGerant,finRequete);
            //sscanf(requete, "%[^/]/%[^END]",idenRequete,resteRequete);
            sscanf(resteRequete, "%[^/]/%[^/]/%[^/]/%[^/]/%[^/]/%[^/]/%[^/]/",action,nomHotel,nombreEtoile,ville,nombreChambre,nomGerant,finRequete);
            printf("Action=%s\n",action);
            printf("resterequete=%s\n",resteRequete);
                longVille=strlen(ville);
                longNombreChambre=strlen(nombreChambre);
                longNomGerant=strlen(nomGerant);
                longNomHotel=strlen(nomHotel);
                longNombreEtoile=strlen(nombreEtoile);

            if(strcmp(action,"SaveNewHotel")==0)
            {
                printf("%s %s %s %s",nomHotel,nombreEtoile,ville,nombreChambre);
                char *reqSQL="INSERT INTO HOTEL WHERE (nomHotel,ville,categorie,nombreChambre,gerant) VALUES ('','','','','')";
                /*Contient la requête SQL sans les variables qui vont se rajouter dedans après*/

                printf("ceb pour la requete d'enregistrement de lhotel !\n\n");
                //On compte le nombre de caractères de la requete
                longReqSQL=strlen(reqSQL);
                longReqSQL=longReqSQL+longVille+longNombreChambre+longNomGerant+longNomHotel+longNombreEtoile;
                p=malloc(longReqSQL*MORCEAU*sizeof(char));
                sprintf(p,"INSERT INTO HOTEL WHERE (nomHotel,ville,categorie,nombreChambre,gerant) VALUES ('%s','%s','%s','%s','%s');",nomHotel,ville,nombreEtoile,nombreChambre,nomGerant);
                *sql=p;


            }
            else
            {
                char *reqSQL="UPDATE HOTEL SET ville='',categorie='',nombreChambre='',gerant='' WHERE nomHotel='' ";
                longReqSQL=strlen(reqSQL);
                longReqSQL=longReqSQL+longVille+longNombreChambre+longNomGerant+longNomHotel+longNombreEtoile;
                p=malloc(longReqSQL*MORCEAU*sizeof(char));
                sprintf(p,"UPDATE HOTEL SET ville='%s',categorie='%s',nombreChambre='%s',gerant='%s' WHERE nomHotel='%s';",ville,nombreEtoile,nombreChambre,nomGerant,nomHotel);
                *sql=p;
            }

        }
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
    return 1;
};
