#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "serveur.h"
#include "sqlite3.h"
#include "fonctionAjouteeServeur.h"


int main() {
	char *message = NULL;

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
            "INSERT INTO UTILISATEUR (identifiant,mdp)"\
            "VALUES ('adrien','test');";*/

    /*/ Execute SQL statement
    int rc;
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Records created successfully\n");
   }*/
   /////////////////////////////////////////////////////////////////////////
   //* Create SQL statement
   //char *sql=NULL;
   int rc;
   //sql = "SELECT login from user where login='paul';";

   printf("%s\n",sql);

   char* data = "Callback function called";


//*/

   ////////////////////////////////////////////////////////////////////////
   //sqlite3_close(db);

	while(1)
        {
		int fini = 0;

		AttenteClient();
        printf("DEBUG: message avant réception=%s\n",message);
        message = Reception();
        printf("DEBUG: message après réception=%s\n",message);

        extraction_requete(message,&sql);
        printf("DEBUG: SQL=%s\n",sql);

        /////////////////////////////////////////////////////////////////////
        /* Execute SQL statement*/
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Operation done successfully\n");
      printf("%d",rc);//c'est pas rc qu'il faut check, mais ce que renvoie callback !!
   }
//////////////////////////////////////////*//////////////////////////////////////
        printf("DEBUG: Après extraction:\n\n");
		while(!fini) {
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
		}



		TerminaisonClient();
		sqlite3_close(db);
        }

	return 0;
}
