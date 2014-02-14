/*Vide le buffer pour �viter les saisies erron�es
*/
void vider_buffer();

/*Permet de saisir une cha�ne au clavier, avec un nombre max de caract�res,
puis vide le buffer, et remplace le '\n' de fgets par un '\0'
*/
int lire(char *chaine, int longueur);

/*Permet d'ajouter un nouvel h�tel � la BDD. Le nom du g�rant est automatiquement r�cup�r�
*/
int enregistrer_hotel(char *identifiant);

/*Permet de modifier un hotel de la BDD
*/
int modifier_hotel();

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

