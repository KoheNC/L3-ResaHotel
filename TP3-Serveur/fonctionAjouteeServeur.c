#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "serveur.h"
#define MORCEAU 8 //pour l'allocation

//Extraction de la requ�te, tri des variables potentielles et formulation de la requ�te SQL en cons�quence
int extraction_requete(char *requete, char **sql)
{
    char login[10], mdp[10];
    char idenRequete[15], resteRequete[1000];
    int nbreCaractere=0;
    char *p;    /*pointeur pour la liaison avec *sql pass� en param�tre*/

    //On identifie le type de requ�te et on enl�ve le '/' restant � la fin
    sscanf(requete, "%[^/]/%[^END]",idenRequete,resteRequete);
    nbreCaractere=strlen(resteRequete);
    resteRequete[nbreCaractere-1]='\0';

    //Comparaison du r�sultat et traitement
    if(strcmp(idenRequete,"AUTHENT")==0)
        {
        int longReqSQL=0, longLogin=0,longMdp=0;
        char *reqSQL="SELECT utilisateur,mdp FROM UTILISATEUR WHERE identifiant= AND mdp=;";  /*Contient la requ�te SQL sans les variables qui vont se rajouter dedans apr�s*/

        printf("ceb pour l'authent\n");
        sscanf(resteRequete, "%[^/]/%s",login,mdp);

        //On compte le nombre de caract�res de la requete + identifiant + mdp pour faire l'allocation n�cessaire en m�moire(c'est un peu brouillon et archa�que je sais)

        longReqSQL=strlen(reqSQL);
        longLogin=strlen(login);
        longMdp=strlen(mdp);
        longReqSQL=longReqSQL+longLogin+longMdp;
        p=malloc(longReqSQL*MORCEAU*sizeof(char));

        //Puis on cr�e la requ�te et on la fout dans *sql
        sprintf(p,"SELECT utilisateur,mdp FROM UTILISATEUR WHERE identifiant=%s AND mdp=%s;",login,mdp);
        *sql=p;
        }


    else if(strcmp(idenRequete,"CONSULT_ETOILE")==0)
        printf("ceb pour l'�toile\n");




    Emission("1\n");


    return 1;
};
