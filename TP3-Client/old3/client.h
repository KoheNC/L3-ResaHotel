#ifndef __CLIENT_H__
#define __CLIENT_H__
#include <stddef.h> //Utilis� pour la d�finition du type "size_t"

/* Initialisation.
 * Connexion au serveur sur la machine donnee.
 * Utilisez localhost pour un fonctionnement local.
 * renvoie 1 si �a c'est bien pass� 0 sinon
 */
int Initialisation(char *machine);

/* Initialisation.
 * Connexion au serveur sur la machine donnee et au service donne.
 * Utilisez localhost pour un fonctionnement local.
 * renvoie 1 si �a c'est bien pass� 0 sinon
 */
int InitialisationAvecService(char *machine, char *service);

/* Recoit un message envoye par le serveur.
 * retourne le message ou NULL en cas d'erreur.
 * Note : il faut liberer la memoire apres traitement.
 */
char *Reception();

/* Envoie un message au serveur.
 * Attention, le message doit etre termine par \n
 * renvoie 1 si �a c'est bien pass� 0 sinon
 */
int Emission(char *message);

/* Recoit des donnees envoyees par le serveur.
 * renvoie le nombre d'octets re�us, 0 si la connexion est ferm�e,
 * un nombre n�gatif en cas d'erreur
 */
int ReceptionBinaire(char *donnees, size_t tailleMax);

/* Envoie des donn�es au serveur en pr�cisant leur taille.
 * renvoie le nombre d'octets envoy�s, 0 si la connexion est ferm�e,
 * un nombre n�gatif en cas d'erreur
 */
int EmissionBinaire(char *donnees, size_t taille);

/* Ferme la connexion.
 */
void Terminaison();

/*Permet de construire la chaine n�cesaire � l'authentification
*/
int authentifier(char **identifiant);

/*S�lection des h�tels par leur nombre d'�toiles
*/
int consulter_par_etoile();

/*S�lection des h�tels par leur nom
*/
int consulter_par_nom();

/*S�lection des h�tels par leur Ville
*/
int consulter_par_ville();

/*R�servation d'un h�tel avec ses caract�ristiques
*/
int reserver();

/*
Envoi du choix du g�rant au serveur pour le traitement
*/
int actionGerant(int choixGerant);
void clean_stdin(void);

int enregistrer_hotel();
int modifier_hotel();
#endif
