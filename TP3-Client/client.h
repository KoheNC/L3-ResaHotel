#ifndef __CLIENT_H__
#define __CLIENT_H__
#include <stddef.h> //UtilisÈ pour la dÈfinition du type "size_t"

/* Initialisation.
 * Connexion au serveur sur la machine donnee.
 * Utilisez localhost pour un fonctionnement local.
 * renvoie 1 si ça c'est bien passé 0 sinon
 */
int Initialisation(char *machine);

/* Initialisation.
 * Connexion au serveur sur la machine donnee et au service donne.
 * Utilisez localhost pour un fonctionnement local.
 * renvoie 1 si ça c'est bien passé 0 sinon
 */
int InitialisationAvecService(char *machine, char *service);

/* Recoit un message envoye par le serveur.
 * retourne le message ou NULL en cas d'erreur.
 * Note : il faut liberer la memoire apres traitement.
 */
char *Reception();

/* Envoie un message au serveur.
 * Attention, le message doit etre termine par \n
 * renvoie 1 si ça c'est bien passé 0 sinon
 */
int Emission(char *message);

/* Recoit des donnees envoyees par le serveur.
 * renvoie le nombre d'octets reçus, 0 si la connexion est fermée,
 * un nombre négatif en cas d'erreur
 */
int ReceptionBinaire(char *donnees, size_t tailleMax);

/* Envoie des données au serveur en précisant leur taille.
 * renvoie le nombre d'octets envoyés, 0 si la connexion est fermée,
 * un nombre négatif en cas d'erreur
 */
int EmissionBinaire(char *donnees, size_t taille);

/* Ferme la connexion.
 */
void Terminaison();

/*Permet de construire la chaine nÈcesaire ‡ l'authentification
*/
int authentifier(char **identifiant);

/*SÈlection des hÙtels par leur nombre d'Ètoiles
*/
int consulter_par_etoile();

/*SÈlection des hÙtels par leur nom
*/
int consulter_par_nom();

/*SÈlection des hÙtels par leur Ville
*/
int consulter_par_ville();

/*RÈservation d'un hÙtel avec ses caractÈristiques
*/
int reserver();

/*
Envoi du choix du gÈrant au serveur pour le traitement
*/
int actionGerant(int choixGerant);
void clean_stdin(void);

int enregistrer_hotel();
int modifier_hotel();
#endif
