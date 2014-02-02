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
        }
    else
        fprintf(stderr, "Opened database successfully\n");

    /*/Création des tables de la DB
    char *sql;
    sql="DROP TABLE IF EXISTS user;"\
        "DROP TABLE IF EXISTS hotel;"\
        "DROP TABLE IF EXISTS reservation;"\
        "CREATE TABLE user("\
            "login   TEXT   PRIMARY KEY,"\
            "pwd     TEXT   NOT NULL);"\
            "INSERT INTO user (login,pwd)"\
            "VALUES ('adrien','test');";

    /* Execute SQL statement
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
   char *sql;
   int rc;
   sql = "SELECT login from user where login='paul';";
   char* data = "Callback function called";

   /* Execute SQL statement*/
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Operation done successfully\n");
      printf("%d",rc);//c'est pas rc qu'il faut check, mais ce que renvoie callback !!
   }
//*/

   ////////////////////////////////////////////////////////////////////////
   //sqlite3_close(db);

	while(1)
        {
		int fini = 0;

		AttenteClient();
		     printf("DEBUG: message=%s\n",message);
        message = Reception();
        printf("DEBUG: message=%s\n",message);
        extraction_requete(message);
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
		sqlite3_close(db);
        }

	return 0;
}
