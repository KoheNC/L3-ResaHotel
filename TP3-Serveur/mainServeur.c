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
    /*Variables*/
	char *message = NULL, *identifiant=NULL;
	char IDRequete[15];
	int finProgramme=FALSE;

    /*Variables SQL*/
    int rc;
    char* data = "Callback function called";
    char *sql=NULL;
    sqlite3 *db;
    char *zErrMsg = 0;
    int connectionDB;

	Initialisation();

	//Ouverture de la DB pour son utilisation dans le programme
    connectionDB = sqlite3_open("BDD_resa.db", &db);
    if(connectionDB)
    {
        fprintf(stderr, "Impossible d'ouvrir la BDD: %s\n", sqlite3_errmsg(db));
        exit(0);
    }
    else
        fprintf(stderr, "BDD ouverte avec succes !\n");

    //Création des tables de la DB*/

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
            "INSERT INTO RESERVATION (nomHotel,nomClient,date) VALUES ('Meridien','LEJEUNE','08-10-14');"\
            "INSERT INTO RESERVATION (nomHotel,nomClient,date) VALUES ('TerraNui','SADA','02-03-14');"\
            "INSERT INTO RESERVATION (nomHotel,nomClient,date) VALUES ('Ibis','Ksenia','03-04-14');"\
            "INSERT INTO RESERVATION (nomHotel,nomClient,date) VALUES ('Ibis','Salwa','02-04-14');";*/

    // Execute SQL statement
    sql="SELECT * FROM RESERVATION;";
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Operation done successfully\n");
   }


   attentClient:
    do
        {
        AttenteClient();
        G_connecte=TRUE;
        do
            {
            free(sql);
            free(message);
            message = Reception();

            if(message==NULL)
                {
                TerminaisonClient();
                goto attentClient;
                }

            extraction_requete(message,&sql,IDRequete,&identifiant);

            //Si c'est pour l'authentification on utilise CallbackCOUNT(), sinon on utilise Callback()
            if(strcmp(IDRequete,"AUTHENT")==0)
                {
                printf("Je passe par le callbackCOUNT ! ");
                rc = sqlite3_exec(db, sql, callbackCOUNT, (void*)data, &zErrMsg);
                }
            else if(strstr(IDRequete,"CONSULT")!=NULL)
                {
                printf("Je passe par le callback consult ! ");
                rc = sqlite3_exec(db, sql, callbackCONSULT, 0, &zErrMsg);
                }
            else
                {
                printf("Je passe par le callback normal ! ");
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
                    Emission("0\n");
                    }
                else
                    {
                    fprintf(stdout, "Operation SQL effectuee avec succes !\n");
                    Emission("1\n");
                    }
                }
                }while(G_connecte==TRUE);
            }while(finProgramme==FALSE);

            TerminaisonClient();
            sqlite3_close(db);
            Terminaison();

            return 0;
    }
