#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "serveur.h"
#include "sqlite3.h"
#include "fonctionAjouteeServeur.h"
#define MORCEAU 8
#define TRUE 1
#define FALSE 0

int main() {
	char *message = NULL;
	char *codeErreur;
	char IDRequete[15];
	int finProgramme=FALSE;
    int rc;
    char* data = "Callback function called";


	codeErreur=malloc(MORCEAU*4*sizeof(char)); //On se met à 4 pour être tranquille dans l'allocation mémoire

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
        }
    else
        fprintf(stderr, "Opened database successfully\n");

    //Création des tables de la DB
    char *sql=NULL;
    //sql="DROP TABLE IF EXISTS user;";

    /*sql="DROP TABLE IF EXISTS UTILISATEUR;"\
        "DROP TABLE IF EXISTS HOTEL;"\
        "DROP TABLE IF EXISTS RESERVATION;"\
        "CREATE TABLE UTILISATEUR("\
            "identifiant   TEXT   PRIMARY KEY,"\
            "mdp     TEXT   NOT NULL);"\
        "CREATE TABLE HOTEL("\
            "nomHotel   TEXT   PRIMARY KEY,"\
            "nbreEtoile INT     NOT NULL,"\
            "ville      TEXT    NOT NULL,"\
            "nbreChambre INT    NOT NULL,"\
            "gerant     TEXT    NOT NULL,"\
            "FOREIGN KEY(gerant) REFERENCES UTILISATEUR(identifiant));"\
        "CREATE TABLE RESERVATION("\
            "nomHotel   TEXT    NOT NULL,"\
            "nomClient  TEXT    NOT NULL,"\
            "date       TEXT    NOT NULL,"\
            "PRIMARY KEY(nomHotel,nomClient,date)"\
            "FOREIGN KEY(nomHotel) REFERENCES HOTEL(nomHotel));"\
            "INSERT INTO UTILISATEUR (identifiant,mdp) VALUES ('adrien','test');"\
            "INSERT INTO UTILISATEUR (identifiant,mdp) VALUES ('brice','toto');"\
            "INSERT INTO UTILISATEUR (identifiant,mdp) VALUES ('herve','titi');"\
            "INSERT INTO HOTEL (nomHotel,nbreEtoile,ville,nbreChambre,gerant) VALUES ('Meridien',5,'Toulouse',5,'adrien');"\
            "INSERT INTO HOTEL (nomHotel,nbreEtoile,ville,nbreChambre,gerant) VALUES ('TerraNui',3,'Noumea',5,'adrien');"\
            "INSERT INTO HOTEL (nomHotel,nbreEtoile,ville,nbreChambre,gerant) VALUES ('Nouvotel',3,'Blagnac',5,'brice');"\
            "INSERT INTO HOTEL (nomHotel,nbreEtoile,ville,nbreChambre,gerant) VALUES ('Ibis',2,'Colomiers',5,'brice');"\
            "INSERT INTO HOTEL (nomHotel,nbreEtoile,ville,nbreChambre,gerant) VALUES ('Plaza',4,'Andorre',5,'herve');"\
            "INSERT INTO HOTEL (nomHotel,nbreEtoile,ville,nbreChambre,gerant) VALUES ('LeRitz',5,'Vao',5,'herve');"\
            "INSERT INTO RESERVATION (nomHotel,nomClient,date) VALUES ('Meridien','LEJEUNE','08/10/2014');"\
            "INSERT INTO RESERVATION (nomHotel,nomClient,date) VALUES ('TerraNui','SADA','02/03/2014');"\
            "INSERT INTO RESERVATION (nomHotel,nomClient,date) VALUES ('Ibis','Ksenia','03/04/2014');"\
            "INSERT INTO RESERVATION (nomHotel,nomClient,date) VALUES ('Ibis','Salwa','02/04/2014');";*/

    // Execute SQL statement
    //sql="SELECT * FROM RESERVATION;";
   /*rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Operation done successfully\n");*/
   }
   /////////////////////////////////////////////////////////////////////////




//*/

   ////////////////////////////////////////////////////////////////////////
   //sqlite3_close(db);

	while(finProgramme==FALSE)
        {
        AttenteClient();
        G_connecte=TRUE;
        do{

		int fini = 0;
		free(sql);
		free(message);

        printf("attente message du client\n");
        message = Reception();
        printf("-----------------------------------------------------------\n\n\n");
        printf("Message apres reception=%s",message);

        extraction_requete(message,&sql,IDRequete);
        printf("requeteSQL=%s\n",sql);
        //Si c'est juste du SELECT on utilise CallbackSELECT(), sinon on utilise Callback()
        if(strcmp(IDRequete,"AUTHENT")==0)
            {
            printf("Je passe par le callbackSELECT !");
            rc = sqlite3_exec(db, sql, callbackSELECT, (void*)data, &zErrMsg);
            }
        else
            {
            printf("Je passe par le callback normal !");
            rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
            }

        if(strcmp(IDRequete,"CLOSE_SOCKET")==0)
                G_connecte=FALSE;
        else
            {
            if( rc != SQLITE_OK )
                {
                fprintf(stderr, "SQL error: %s\n", zErrMsg);
                sqlite3_free(zErrMsg);
                }
            else
                fprintf(stdout, "Operation done successfully\n");
            }


        printf("--------------------------\n");
        if(message != NULL)
            {
            printf("J'ai recu: %s\n", message);
            free(message);
            }

//////////////////////////////////////////////////////////////
        printf("--------------------------\n");

		/*while(!fini) {
			message = Reception();

			//Si on reçoit un pointeur vide c'est que le client a coupé la connexion

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

            }while(G_connecte==TRUE);
        }
		TerminaisonClient();
		sqlite3_close(db);

	return 0;
}
