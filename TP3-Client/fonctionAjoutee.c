#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"
#define MORCEAU 8
#define TRUE 1
#define FALSE 0

void vider_buffer()
    {
    int c = 0;
    while (c != '\n' && c != EOF)
        c = getchar();
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


int authentifier(char **identifiant)
    {
    char login[10], pwd[10],*p;
    char *retourMsg=NULL,*comparaison="1";
    char requeteSQL[100];
    int longLogin=0;

    vider_buffer(); //On vide le buffer pour éviter les problèmes liés aux caractères restés dedans avec les précédents choix
    free(retourMsg);

    printf("Veuillez entrer votre login\n");
    lire(login,10);
    printf("\nVeuillez entrer votre mot de passe \n");
    lire(pwd,10);
    sprintf(requeteSQL,"AUTHENT/%s/%s\n",login,pwd);

    if(Emission(requeteSQL)==1)
        {
        retourMsg=Reception();

        if (*retourMsg==*comparaison)
            {
            longLogin=strlen(login);
            p=malloc(longLogin*MORCEAU*sizeof(char));
            strcpy(p,login);
            *identifiant=p;
            printf("\nAuthentification reussie. Bienvenue %s !\n",login);
            return 1;
        }
        else
            {
            printf("Erreur: Login et/ou mot de passe incorrect(s). Retour au menu principal.\n");
            return 0;
            }
        }
    else
        {
        printf("Erreur lors de l'envoi des donnees au serveur. Retour au menu principal. \n");
        return 0;
        }
    }

int enregistrer_hotel(char *identifiant)
    {
    char requeteSQL[200], nomHotel[20], nombreEtoile[2], ville[20], nombreChambre[3], nomGerant[10];
    char *retourMsg=NULL,*comparaison="1";

    //On récupère l'identifiant en paramètre obtenu grâce à l'authentification
    strcpy(nomGerant,identifiant);

    //On prend les variables pour créer la requête
    vider_buffer();
    printf("Veuillez saisir le nom de l'hotel :\n");
    lire(nomHotel,20);
    printf("Veuillez saisir le nombre d'etoile de votre etoile :\n");
    lire(nombreEtoile,2);
    printf("Veuillez saisir le nom de la ville où se trouve l'hotel :\n");
    lire(ville,20);
    printf("Veuillez saisir le nombre de chambre disponible de votre etoile :\n");
    lire(nombreChambre,3);
    sprintf(requeteSQL,"ACTGER/saveNewHotel/%s/%s/%s/%s/%s\n",nomHotel,nombreEtoile,ville,nombreChambre,nomGerant);

    if(Emission(requeteSQL)==1)
    {
        retourMsg=Reception();

        if (*retourMsg==*comparaison)
            {
            printf("\n\nVotre hotel a ete enregistre avec succes !!!\n\n");
            printf("Retour au menu principal...\n\n");
            return 1;
            }
        else
            {
            printf("Erreur lors de l'enregistrement. Votre hotel n'a pas ete enregistre.......\n\n");
            printf("Retour au menu principal...\n\n");
            return 0;
            }
    }
    else
        {
        printf("Erreur lors de l'envoi des données au serveur. Retour au menu principal.\n");
        return 0;
        }
    }

int modifier_hotel(char *identifiant)
    {

    char requeteSQL[200], nomHotel[20], nombreEtoile[2], nombreChambre[3], nomGerant[10],ville[20];
    char *retourMsg=NULL,*comparaison="1";
    int choix=0, retour=0;

    //On récupère l'identifiant en paramètre obtenu grâce à l'authentification
    strcpy(nomGerant,identifiant);

    vider_buffer();
    printf("Veuillez saisir le nom de l'hotel dont vous souhaitez modifier les informations:\n");
    lire(nomHotel,20);
    printf("\nVeuillez saisir le nom de la ville ou se trouve l'hotel a modifier:\n");
    lire(ville,20);

    do
        {
        printf("\nL'hotel dont vous desirez changer les informations est: %s\n\n",nomHotel);
        printf("Souhaitez-vous :\n");
        printf(" 1 : Modifier le nombre de chambre que vous mettez a disposition.\n");
        printf(" 2 : Modifier le nombre d'etoiles de l'hotel.\n");
        printf(" 3 : Terminer et appliquer les modifications.\n");


        do
            {
            retour=scanf("%d",&choix);
            if(retour!=1)
            {
                printf("Choix incorrect. Veuillez reentrer votre choix:\n");
            }
            }while(retour!=1);

        if(choix==1)
        {
            printf("\nVeuillez saisir le nouveau nombre de chambres a disposition de votre hotel:\n");
            vider_buffer();
            lire(nombreChambre,3);
            printf("\nVous avez saisi: %s\n\n",nombreChambre);
        }
        if(choix==2)
        {
            printf("\nVeuillez saisir la nouvelle categorie de votre hotel (nombre d'etoiles) :\n");
            vider_buffer();
            lire(nombreEtoile,3);
            printf("\nVous avez saisi: %s\n\n",nombreEtoile);
        }
    }while(choix!=3);

    sprintf(requeteSQL,"ACTGER/editHotel/%s/%s/%s/%s/%s\n",nomHotel,nombreEtoile,ville,nombreChambre,nomGerant);

    if(Emission(requeteSQL)==1)
    {
        retourMsg=Reception();

        if (*retourMsg==*comparaison)
            {
            printf("\nVotre hotel a ete modifie avec succes !!!\n\n");
            printf("Retour au menu principal...\n\n");
            return 1;
            }
        else
            {
            printf("Erreur lors de la modification. Votre hotel n'a pas ete modifie.......\n\n");
            printf("Retour au menu principal...\n\n");
            return 0;
            }
    }
    else
        {
        printf("Erreur lors de l'envoi des données au serveur. Retour au menu principal.\n");
        return 0;
        }
    }

int consulter_par_etoile()
    {
    char requeteSQL[100],colonne[100],valeur[100],reste[100],nbreColRep[5];;
    char etoile[2];
    char *retourMsg=NULL;
    int finBoucle=FALSE,retour;

    vider_buffer();

    printf("\nVeuillez entrer le nombre d'etoiles souhaitees pour votre recherche:\n");
    lire(etoile,2);

    sprintf(requeteSQL,"CONSULT_ETOILE/%s\n",etoile);

    if(Emission(requeteSQL)==1)
        {
        printf("*****************************************\n");
        printf("\nListe des hotel avec %s etoiles:\n\n",etoile);
        do
        {
            retourMsg=Reception();
            sscanf(retourMsg,"%[^/]/%s",colonne,reste);
            sscanf(reste,"%[^/]/%s",valeur,nbreColRep);

            if(colonne[0]=='1')
                {
                    finBoucle=TRUE;
                    retour=1;
                }
            else if(colonne[0]=='0')
                {
                    printf("Erreur lors de la reception des donnees du serveur. Retour au menu principal.\n");
                    finBoucle=TRUE;
                    retour=0;
                }
            else
                {
                    printf("%s = %s\n", colonne,valeur);
                }
        }while(finBoucle==FALSE);
        }
    else
        {
        printf("Erreur lors de l'envoi des donnees au serveur. Retour au menu principal. \n");
        retour=0;
        }
    return retour;
}

int consulter_par_nom()
    {
    char requeteSQL[100],colonne[100],valeur[100],reste[100],nbreColRep[5];
    char *retourMsg=NULL;
    int finBoucle=FALSE,retour=0;

    vider_buffer();
    strcpy(requeteSQL,"CONSULT_NOM/END\n");

    if(Emission(requeteSQL)==1)
        {
            printf("*****************************************\n");
            printf("Liste des hotels et de leur ville:\n");
            do
            {
                retourMsg=Reception();
                sscanf(retourMsg,"%[^/]/%s",colonne,reste);
                sscanf(reste,"%[^/]/%s",valeur,nbreColRep);

                if(colonne[0]=='1')
                    {
                        finBoucle=TRUE;
                        retour=1;
                    }
                else if(colonne[0]=='0')
                    {
                        printf("Erreur lors de la reception des donnees du serveur. Retour au menu principal.\n");
                        finBoucle=TRUE;
                        retour=0;
                    }
                else
                    {
                        printf("%s = %s\n", colonne,valeur);
                    }

            }while(finBoucle==FALSE);
        }
    else
        {
        printf("Erreur lors de l'envoi des donnees au serveur. Retour au menu principal. \n");
        retour=0;
        }
    return retour;
    }

int consulter_par_ville()
    {
    char requeteSQL[100],colonne[100],valeur[100],reste[100],nbreColRep[5];
    char ville[20];
    char *retourMsg=NULL;
    int finBoucle=FALSE,retour;

    vider_buffer();
    printf("Veuillez entrer le nom de la ville dont vous souhaitez voir les hotels:\n");
    lire(ville,20);

    sprintf(requeteSQL,"CONSULT_VILLE/%s\n",ville);

    if(Emission(requeteSQL)==1)
        {
            printf("*****************************************\n");
            printf("Liste des hotel situes dans la ville: %s\n",ville);
            do
            {
                retourMsg=Reception();
                sscanf(retourMsg,"%[^/]/%s",colonne,reste);
                sscanf(reste,"%[^/]/%s",valeur,nbreColRep);

                if(colonne[0]=='1')
                    {
                        finBoucle=TRUE;
                        retour=1;
                    }
                else if(colonne[0]=='0')
                    {
                        printf("Erreur lors de la reception des donnees du serveur. Retour au menu principal.\n");
                        finBoucle=TRUE;
                        retour=0;
                    }
                else
                    {
                        printf("%s = %s\n", colonne,valeur);
                    }

            }while(finBoucle==FALSE);
        }
    else
        {
        printf("Erreur lors de l'envoi des donnees au serveur. Retour au menu principal. \n");
        retour=0;
        }
    return retour;
    }

int reserver()
    {
    char nomHotel[30],date[100],requeteSQL[100],nomClient[20];
    int jour=0,mois=0,annee=0;
    int longueur_mois[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    char *comparaison="1", *retourMsg=NULL;

    vider_buffer();
    printf("Veuillez entrer le nom de l'hotel ou vous souhaitez reserver une nuitee\n\n");
    lire(nomHotel,20);
    printf("\nVeuillez entrer la date de la nuitee souhaitee (sous le format JJ-MM-AA \n");
    lire(date,10);
    sscanf(date, "%d-%d-%d", &jour, &mois, &annee);

    while(((mois<1)||(mois>12))|| ((jour < 1)||(jour > longueur_mois[mois]))||(annee<14))
    {
        printf("Erreur. La date saisie est incorrecte !\n");
        printf("Veuillez entrer la date de la nuitee souhaitee (sous le format JJ-MM-AA \n");
        lire(date,10);
        sscanf(date, "%d-%d-%d", &jour, &mois, &annee);
    }

    printf("\nVeuillez entrer votre nom: \n");
    lire(nomClient,20);

    sprintf(requeteSQL,"RESERVATION/%s/%s/%d-%d-%d\n",nomHotel,nomClient,jour,mois,annee);

    if(Emission(requeteSQL)==1)
    {
        retourMsg=Reception();

        if (*retourMsg==*comparaison)
            {
            printf("\n\nVotre reservation a ete enregistre avec succes !!!\n\n");
            printf("Retour au menu principal...\n\n");
            return 1;
            }
        else
            {
            printf("Erreur lors de l'enregistrement. Votre reservation n'a pas ete enregistre.......\n\n");
            printf("Retour au menu principal...\n\n");
            return 0;
            }
    }
    else
        {
        printf("Erreur lors de l'envoi des données au serveur. Retour au menu principal.\n");
        return 0;
        }
    }
