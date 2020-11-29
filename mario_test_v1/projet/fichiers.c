#include "constante.h"
if(!chargerNiveau(carte))
	exit(EXIT_FAILURE);
	
	
for (i = 0; i < NB_BLOCKS_LARGEUR; i++){
	for (j = 0; j < NB_BLOCKS_HAUTEUR; j++){
		if (carte[i][j] == MARIO){ //la case sur laquelle va se trouver le perso
			positionJoueur.x = i;
			positionJoueur.y = j;
			carte[i][j] = VIDE;
		}
	}
}
