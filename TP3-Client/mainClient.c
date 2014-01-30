#include <stdio.h>
#include <stdlib.h>
#include "client.h"
#include <string.h>

int main()
{
	char *message;
	int retour=0, choix=0, choixId=0, choixGerant=0, choixAffichageClient=0, choixClient=0;

    choixMenuPrincipal:
	printf("Bienvenue dans l'application ReserveHotel\n");
	printf("1: Acc�der au serveur \n");
	printf("2: Quitter");
	printf("Choix(1 ou 2):\n");
	scanf("%d",&choix);

    //Choix du menu principal
	if(choix==1){
        if ((retour=Initialisation("localhost"))==1)
            {
            printf("Vous �tes maintenant connect� au serveur \n");
            printf("Qui �tes-vous ? \n");
            printf("1: G�rant \n");
            printf("2: Client d�sirant r�server une nuit \n");
            printf("3: D�connexion \n");
            printf("Choix (1, 2 ou 3): \n");
            scanf("%d",&choixId);

            switch(choixId)
                {
                //Si c'est un g�rant
                case 1:
                    if((retour=authentifier())==1)
                        {
                        printf("Que d�sirez-vous faire ? \n");
                        printf("1: enregistrer un nouvel h�tel \n");
                        printf("2: Modifier les informations de votre h�tel \n");
                        printf("3: Retour au menu principal \n");
                        scanf("%d",&choixGerant);
                        }else
                            break;

                        switch(choixGerant)
                            {
                            case 1:
                                action
                            }

                //Si c'est un client
                case 2:
                    printf("Bienvenue cher client, que d�sirez-vous faire ? \n");
                    printf("1: Consulter la liste des h�tels \n");
                    printf("2: R�server un h�tel \n");
                    printf("3: Retour au menu principal \n");
                    printf("Choix(1,2 ou 3): \n");
                    scanf("%d",&choixClient);

                    //On prend son choix et on traite en fonction de celui-ci
                    switch(choixClient)
                        {
                        //Affichage des h�tels
                        case 1:
                            printf("Souhaitez-vous:\n");
                            printf("1: Afficher la liste des h�tels par nombre d'�toiles \n");
                            printf("2: Afficher la liste des h�tels par nom \n");
                            printf("3: Afficher la liste des h�tels par ville \n");
                            printf("4: Retour au menu pr�c�dent \n");
                            scanf("%d",&choixAffichageClient);
                            switch(choixAffichageClient)
                                {
                                case 1:
                                    consulter_par_etoile();
                                case 2:
                                    consulter_par_nom();
                                case 3:
                                    consulter_par_ville();
                                case 4:
                                    break;
                                }
                            //R�servation d'un h�tel
                        case 2:
                            reserver(); //On testera le retour directement dans la fonction, et le printf aussi tient !
                        case 3:
                            break;
                        }

                //Si on quitte l'application
                case 3:
                    if(retour==1)
                        Terminaison();     //terminaison c'est pas pour couper la connexion ?
             }
            }else
                {
                printf("�chec de la connexion\n");
                goto choixMenuPrincipal;
                }
                }
    /*else
        break;

	if(InitialisationAvecService("localhost","3128") != 1) {
		printf("Erreur d'initialisation\n");
		return 1;*/
	//}



	/*if(Emission("GET / HTTP/1.1\n")!=1) {
		printf("Erreur d'�mission\n");
		return 1;
    }

    if(Emission("Host: www.google.fr \n")!=1) {
		printf("Erreur d'�mission\n");
		return 1;
    }

    if(Emission("\n")!=1) {
		printf("Erreur d'�mission\n");
		return 1;
    }
*/
    do{
        free(message);
        message = Reception();
        if(message != NULL) {
            printf("J'ai recu: %s\n", message);
            }
        else {
            printf("Erreur de r�ception\n");
            return 1;
            break;
            }
        }while(strstr(message,"</html>")==NULL);

	Terminaison();

	return 0;
}
