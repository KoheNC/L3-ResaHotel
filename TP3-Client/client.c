#define _WIN32_WINNT 0x0601
/*
 Bear in mind that since you're telling the compiler that you're using Windows 7 here,
 you will not be able to make use of functions that are only available to versions
 prior to the one you have defined (Windows 7).
 */
#include "client.h"
#include "fonctionAjoutee.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <stddef.h>

#ifdef WIN32
//#include <winsock2.h> //Ne sert pas car l'on compile avec la lib "libws2_32.a"
#include <ws2tcpip.h>
#include <stddef.h> //Utilisé pour la définition du type "size_t"
#else
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>*/
#endif

#ifdef WIN32
#define perror(x) printf("%s : code d'erreur : %d\n", (x), WSAGetLastError())
#define close closesocket
#define socklen_t int
#endif

#define TRUE 1
#define FALSE 0
#define LONGUEUR_TAMPON 4096

/* Variables cachees */

/* le socket client */
int socketClient;
/* le tampon de reception */
char tamponClient[LONGUEUR_TAMPON];
int debutTampon;
int finTampon;
int finConnexion = FALSE;

int authentifier()
{
    char login[10], pwd[10];
    //char formatageMsg[50];
    char *retourMsg=NULL;
    char requeteSQL[100];

    vider_buffer(); //On vide le buffer pour éviter les problèmes liés aux caractères restés dedans avec les précédents choix

    printf("Veuillez entrer votre login\n");
    lire(login,10);
    printf("Veuillez entrer votre mot de passe \n");
    lire(pwd,10);
    sprintf(requeteSQL,"AUTHENT/%s/%s/END\n",login,pwd);

    if(Emission(requeteSQL)==1)
        {
            printf("DEBUG: En attente de la réception d'un message coté du serveur\n");
        retourMsg=Reception();
        if (retourMsg!=EOF)
        {
            printf("Authentification réussie. Bienvenue !\n");
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
        printf("Erreur lors de l'envoi des données au serveur. Retour au menu principal. \n");
        return 0;
        }
}

int action_gerant(int choixGerant);

int consulter_par_etoile() //ca renvoie un int ?!
    {
    int nbreEtoile;
    char formatageMsg[50];
    char *retourMsg;

    printf("Veuillez entrer le nombre d'étoiles souhaitées (max. 5:) \n");
    //fgets(nbreEtoile,1,stdin);
    scanf("%d", &nbreEtoile);
    sprintf(formatageMsg,"CONSULT_ETOILE/%d/END",nbreEtoile);

    // Pour chaque ligne validant la requête, le serveur va renvoyer une ligne, donc on affiche chaque ligne une à une
    if(Emission(formatageMsg)==1)//côté serveur on oublie pas de mettre un \n avant chaque envoi !!!!!!
        {
        do
            {
            retourMsg=Reception();
            if(strstr(retourMsg,"finFichier")==NULL)
                printf("%s",retourMsg);
            else
                {
                printf("Erreur lors de la réception des données !\n");
                return 0;
                break;
                }
            }
        while(retourMsg!=NULL);

        return 1;
        }
    else
        {
        printf("Erreur lors de la consultation des données ! \n");
        return 0;
        }
    }

int consulter_par_nom() //ca renvoie un int ?!
    {
    char formatageMsg[50];
    char *retourMsg;

    strcpy(formatageMsg,"CONSULT_NOM/END");

    // Pour chaque ligne validant la requête, le serveur va renvoyer une ligne, donc on affiche chaque ligne une à une
    if(Emission(formatageMsg)==1)//côté serveur on oublie pas de mettre un \n avant chaque envoi !!!!!!
        {
        do
            {
            retourMsg=Reception();
            if(strstr(retourMsg,"finFichier")==NULL)
                printf("%s",retourMsg);
            else
                {
                printf("Erreur lors de la réception des données !\n");
                return 0;
                break;
                }
            }
        while(retourMsg!=NULL);

        return 1;
        }
    else
        {
        printf("Erreur lors de la consultation des données ! \n");
        return 0;
        }
    }

int consulter_par_ville()//ca renvoie un int ?!
    {
    char ville[20];
    char formatageMsg[50];
    char *retourMsg=NULL;

    printf("Veuillez entrer le nom de la ville dont vous souhaitez voir les hôtels:\n");
    fgets(ville,20,stdin);
    sprintf(formatageMsg,"CONSULT_ETOILE/%20s/END",ville);

    // Pour chaque ligne validant la requête, le serveur va renvoyer une ligne, donc on affiche chaque ligne une à une
    if(Emission(formatageMsg)==1)//côté serveur on oublie pas de mettre un \n avant chaque envoi !!!!!!
        {
        do
            {
            retourMsg=Reception();
            if(strstr(retourMsg,"finFichier")==NULL)
                printf("%s",retourMsg);
            else
                {
                printf("Erreur lors de la réception des données !\n");
                return 0;
                break;
                }
            }
        while(retourMsg!=NULL);

        return 1;
        }
    else
        {
        printf("Erreur lors de la consultation des données ! \n");
        return 0;
        }
    }

int reserver()
    {
    char nomHotel[30];
    int jour=0,mois=0,annee=0;
    char formatageMsg[50];
    char *retourMsg=NULL;

    printf("Veuillez entrer le nom de l'hôtel où vous souhaitez réserver une nuitée \n");
    fgets(nomHotel,15,stdin);
    printf("Veuillez entrer la date de la nuitée souhaitée (sous le format JJ/MM/AA \n");
    scanf("%d/%d/%d",&jour,&mois,&annee);

    //CONTROLE DE LA DATE A FAIRE

    /*if((mois<1)||(mois>12))
        printf("Erreur lors de la saisie du mois, le mois indiqué n'existe pas !\n");

    if(jour<1)
        printf("Erreur lors de la saisie du jour, vous avez mis un jour égal à 0 ou négatif !\n");
    else if(jour>31)
        printf("Erreur lors de la saisie du jour, vous avez mis un jour supérieur à 31 ! \n");
    else if(((jour==31)&&(mois==2))||((jour==31)&&(mois==4))||((jour==31)&&(mois==6))||((jour==31)&&(mois==9))||((jour==31)&&(mois==11));
        printf("Le mois indiqué ne conient pas de 31ème jour !\n");

    if(annee<)
        */

    sprintf(formatageMsg,"RESERV/%d/%d/%d/END",jour,mois,annee);

    if(Emission(formatageMsg)==1)//côté serveur on oublie pas de mettre un \n avant chaque envoi !!!!!!
        {
        do
            {
            retourMsg=Reception();
            if(strstr(retourMsg,"finFichier")==NULL)
                printf("%s",retourMsg);
            else
                {
                printf("Erreur lors de la réception des données !\n");
                return 0;
                break;
                }
            }
        while(retourMsg!=NULL);

        return 1;
        }
    else
        {
        printf("Erreur lors de la consultation des données ! \n");
        return 0;
        }
    }

/* Initialisation.
 * Connexion au serveur sur la machine donnee.
 * Utilisez localhost pour un fonctionnement local.
 */
int Initialisation(char *machine) {
	return InitialisationAvecService(machine, "13214");
}

/* Initialisation.
 * Connexion au serveur sur la machine donnee et au service donne.
 * Utilisez localhost pour un fonctionnement local.
 */
int InitialisationAvecService(char *machine, char *service) {
	int n;
	struct addrinfo	hints, *res, *ressave;

	#ifdef WIN32
	WSADATA	wsaData;
	if (WSAStartup(0x202,&wsaData) == SOCKET_ERROR)
	{
		printf("WSAStartup() n'a pas fonctionne, erreur : %d\n", WSAGetLastError()) ;
		WSACleanup();
		exit(1);
	}
	memset(&hints, 0, sizeof(struct addrinfo));
    #else
	bzero(&hints, sizeof(struct addrinfo));
	#endif
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ( (n = getaddrinfo(machine, service, &hints, &res)) != 0)  {
     		fprintf(stderr, "Initialisation, erreur de getaddrinfo : %s", gai_strerror(n));
     		return 0;
	}
	ressave = res;

	do {
		socketClient = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (socketClient < 0)
			continue;	/* ignore this one */

		if (connect(socketClient, res->ai_addr, res->ai_addrlen) == 0)
			break;		/* success */

		close(socketClient);	/* ignore this one */
	} while ( (res = res->ai_next) != NULL);

	if (res == NULL) {
     		perror("Initialisation, erreur de connect.");
     		return 0;
	}

	freeaddrinfo(ressave);

	finConnexion = FALSE;

	printf("Connexion avec le serveur reussie.\n");

	return 1;
}

/* Recoit un message envoye par le serveur.
 */
char *Reception() {
	char message[LONGUEUR_TAMPON];
	int index = 0;
	int fini = FALSE;
	int retour = 0;
	int trouve = FALSE;

	if(finConnexion) {
		return NULL;
	}

	while(!fini) {
		/* on cherche dans le tampon courant */
		while((finTampon > debutTampon) && (!trouve)) {
			//fprintf(stderr, "Boucle recherche char : %c(%x), index %d debut tampon %d.\n",
			//					tamponClient[debutTampon], tamponClient[debutTampon], index, debutTampon);
			if (tamponClient[debutTampon]=='\n')
				trouve = TRUE;
			else
				message[index++] = tamponClient[debutTampon++];
		}
		/* on a trouve ? */
		if (trouve) {
			message[index++] = '\n';
			message[index] = '\0';
			debutTampon++;
			fini = TRUE;
			//fprintf(stderr, "trouve\n");
#ifdef WIN32
			return _strdup(message);
#else
			return strdup(message);
#endif
		} else {
			/* il faut en lire plus */
			debutTampon = 0;
			//fprintf(stderr, "recv\n");
			retour = recv(socketClient, tamponClient, LONGUEUR_TAMPON, 0);
			//fprintf(stderr, "retour : %d\n", retour);
			if (retour < 0) {
				perror("Reception, erreur de recv.");
				return NULL;
			} else if(retour == 0) {
				fprintf(stderr, "Reception, le serveur a ferme la connexion.\n");
				finConnexion = TRUE;
				// on n'en recevra pas plus, on renvoie ce qu'on avait ou null sinon
				if(index > 0) {
					message[index++] = '\n';
					message[index] = '\0';
#ifdef WIN32
					return _strdup(message);
#else
					return strdup(message);
#endif
				} else {
					return NULL;
				}
			} else {
				/*
				 * on a recu "retour" octets
				 */
				finTampon = retour;
			}
		}
	}
	return NULL;
}

/* Envoie un message au serveur.
 * Attention, le message doit etre termine par \n
 */
int Emission(char *message) {
	int taille;
	if(strstr(message, "\n") == NULL) {
		fprintf(stderr, "Emission, Le message n'est pas termine par \\n.\n");
	}
	taille = strlen(message);
	if (send(socketClient, message, taille,0) == -1) {
        perror("Emission, probleme lors du send.");
        return 0;
	}
	printf("Emission de %d caracteres.\n", taille+1);
	return 1;
}

/* Recoit des donnees envoyees par le serveur.
 */
int ReceptionBinaire(char *donnees, size_t tailleMax) {
	size_t dejaRecu = 0;
	int retour = 0;
	/* on commence par recopier tout ce qui reste dans le tampon
	 */
	while((finTampon > debutTampon) && (dejaRecu < tailleMax)) {
		donnees[dejaRecu] = tamponClient[debutTampon];
		dejaRecu++;
		debutTampon++;
	}
	/* si on n'est pas arrive au max
	 * on essaie de recevoir plus de donnees
	 */
	if(dejaRecu < tailleMax) {
		retour = recv(socketClient, donnees + dejaRecu, tailleMax - dejaRecu, 0);
		if(retour < 0) {
			perror("ReceptionBinaire, erreur de recv.");
			return -1;
		} else if(retour == 0) {
			fprintf(stderr, "ReceptionBinaire, le serveur a ferme la connexion.\n");
			return 0;
		} else {
			/*
			 * on a recu "retour" octets en plus
			 */
			return dejaRecu + retour;
		}
	} else {
		return dejaRecu;
	}
}

/* Envoie des donnees au serveur en precisant leur taille.
 */
int EmissionBinaire(char *donnees, size_t taille) {
	int retour = 0;
	retour = send(socketClient, donnees, taille, 0);
	if(retour == -1) {
		perror("Emission, probleme lors du send.");
		return -1;
	} else {
		return retour;
	}
}


/* Ferme la connexion.
 */
void Terminaison() {
	close(socketClient);
}
