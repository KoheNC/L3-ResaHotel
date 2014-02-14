/*Vide le buffer pour éviter les saisies erronées
*/
void vider_buffer();

/*Permet de saisir une chaîne au clavier, avec un nombre max de caractères,
puis vide le buffer, et remplace le '\n' de fgets par un '\0'
*/
int lire(char *chaine, int longueur);

/*Permet d'ajouter un nouvel hôtel à la BDD. Le nom du gérant est automatiquement récupéré
*/
int enregistrer_hotel(char *identifiant);

/*Permet de modifier un hotel de la BDD
*/
int modifier_hotel();

/*Permet de construire la chaine nécesaire à l'authentification
*/
int authentifier(char **identifiant);

/*Sélection des hôtels par leur nombre d'étoiles
*/
int consulter_par_etoile();

/*Sélection des hôtels par leur nom
*/
int consulter_par_nom();

/*Sélection des hôtels par leur Ville
*/
int consulter_par_ville();

/*Réservation d'un hôtel avec ses caractéristiques
*/
int reserver();

