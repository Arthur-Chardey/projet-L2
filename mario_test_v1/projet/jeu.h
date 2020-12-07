#include "constante.h"
void jouer(SDL_Surface* ecran);
SDL_Surface *mario[4] = {NULL};
SDL_Surface *mur = NULL, *caisse = NULL, *objectif = NULL, *marioActuel = NULL;
SDL_Rect position, positionJoueur;
SDL_Event event;

SDL_BlitSurface(marioActuel, NULL, ecran, &position);

int continuer = 1, objectifsRestants = 0, i = 0, j = 0;
int carte[NB_BLOCKS_LARGEUR][NB_BLOCKS_HAUTEUR] = {0};
