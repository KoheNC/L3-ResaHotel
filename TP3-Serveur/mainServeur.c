#include <stdio.h>
#include <stdlib.h>
#include "serveur.h"
#include "sqlite3.h"

int main() {
	char *message = NULL;
	char *nomFichier[50]={};

	Initialisation();

	//Ouverture de la DB pour son utilisation dans le programme
    sqlite3 *db;
    char *zErrMsg = 0;
    int connectionDB;

    connectionDB = sqlite3_open("BDD_resa.db", &db);

    if(connectionDB)
        {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
        }else
            fprintf(stderr, "Opened database successfully\n");

    //

	while(1)
        {
		int fini = 0;

		AttenteClient();
        message = Reception();
		/*while(!fini) {
			message = Reception();

			if(message != NULL) {
				printf("J'ai recu: %s\n", message);
				free(message);

				if(Emission("Test de message serveur.\n")!=1) {
					printf("Erreur d'emission\n");
				}
			} else {
				fini = 1;
			}
		}*/

		TerminaisonClient();
        }

	return 0;
}
