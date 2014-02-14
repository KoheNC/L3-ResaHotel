#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"
#include "fonctionAjoutee.h"


int main()
{
	char *identifiant=NULL; //*message,
	int retour=0, retourPrincipal=0,choix=0, choixId=0, choixGerant=0, choixAffichageClient=0, choixClient=0;

    L_choixMenuPrincipal:
	printf("\nBienvenue dans l'application ReserveHotel\n\n");
	printf("1: Acceder au serveur \n");
	printf("2: Quitter\n\n");
	printf("Choix(1 ou 2):\n");
	scanf("%d",&choix);

    //Choix du menu principal
	if(choix==1)
        {
        if ((retour=Initialisation("localhost"))==1)
            {
            do
            {
                    vider_buffer();
                    printf("Vous etes maintenant connecte au serveur \n");

                    L_choixConnecte:
                    printf("*****************************************\n");
                    printf("\n\nQui etes-vous ? \n\n");
                    printf("1: Gerant \n");
                    printf("2: Client desirant reserver une nuit \n");
                    printf("3: Deconnexion \n\n");
                    printf("Choix (1, 2 ou 3): \n");
                    retourPrincipal=scanf("%d",&choixId);
            }while(retourPrincipal!=1);

            switch(choixId)
                {
                //Si c'est un gérant
                case 1:
                    if((retour=authentifier(&identifiant))==1)
                        {
                        printf("Que désirez-vous faire ? \n\n");
                        printf("1: Enregistrer un nouvel hotel \n");
                        printf("2: Modifier les informations de votre hotel \n");
                        printf("3: Retour au menu principal (Vous serez desauthentifie)\n");
                        printf("\nChoix (1, 2 ou 3): \n");
                        scanf("%d",&choixGerant);
                        }else
                            {
                            printf("Echec de la connexion, retour au menu principal...\n");
                            goto L_choixMenuPrincipal;
                            };
                        switch(choixGerant)
                            {
                            case 1:
                                enregistrer_hotel(identifiant);
                                goto L_choixConnecte;
                            case 2:
                                modifier_hotel(identifiant);
                            case 3:
                                free(identifiant);
                                goto L_choixConnecte;
                            }

                //Si c'est un client
                case 2:
                    vider_buffer();
                    printf("\nBienvenue cher client, que desirez-vous faire ? \n");
                    printf("1: Consulter la liste des hotels \n");
                    printf("2: Reserver un hotel \n");
                    printf("3: Retour au menu principal \n\n");
                    printf("Choix(1,2 ou 3): \n");
                    scanf("%d",&choixClient);

                    //On prend son choix et on traite en fonction de celui-ci
                    switch(choixClient)
                        {
                        //Affichage des hôtels
                        case 1:
                            printf("\nSouhaitez-vous:\n\n");
                            printf("1: Afficher la liste des hotels par nombre d'etoiles \n");
                            printf("2: Afficher la liste des hotels par nom \n");
                            printf("3: Afficher la liste des hotels par ville \n");
                            printf("4: Retour au menu precedent \n");
                            scanf("%d",&choixAffichageClient);
                            switch(choixAffichageClient)
                                {
                                case 1:
                                    consulter_par_etoile();
                                    printf("Retour au menu principal...\n");
                                    break;
                                case 2:
                                    consulter_par_nom();
                                    printf("Retour au menu principal...\n");
                                    break;
                                case 3:
                                    consulter_par_ville();
                                    printf("Retour au menu principal...\n");
                                    break;
                                case 4:
                                    break;
                                }
                            break;
                        //Réservation d'un hôtel
                        case 2:
                            reserver();
                            break;
                        case 3:
                            break;
                        }
                    goto L_choixConnecte;
                //Si on quitte l'application
                case 3:
                    Terminaison();
                }
            }
            else
                {
                printf("Echec de la connexion\n");
                goto L_choixMenuPrincipal;
                }
        }
    else
        Terminaison();

	return 1;
}
