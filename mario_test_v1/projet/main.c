#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "constante.h"
#include "jeu.h"
#include "editeur.h"

int main(int argc, char *argv[]){
	SDL_Surface *ecran = NULL, *menu = NULL;
	SDL_Rect positionMenu;
	SDL_Event event;
	
	int continuer = 1;
	
    	SDL_Init(SDL_INIT_VIDEO);

    	SDL_WM_SetIcon(IMG_Load("obstacle.jpg"), NULL);
    	ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption("Mario test", NULL);

	menu = IMG_Load("menu.jpg");
	positionMenu.x = 0;
	positionMenu.y = 0;
	
	while (continuer){
		SDL_WaitEvent(&event);
		switch(event.type){
			case SDL_QUIT:
				continuer = 0;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_ESCAPE:
						continuer = 0;
						break;
					case SDLK_UP:
						posPerso = mario[HAUT];
						deplacerJoueur(carte, &positionJoueur, HAUT);
						break;
					case SDLK_DOWN:
						posPerso = mario[DOWN];
						deplacerJoueur(carte, &positionJoueur, BAS);
						break;
					case SDLK_RIGHT:
						posPerso = mario[RIGHT];
						deplacerJoueur(carte, &positionJoueur, DROITE);
						break;
					case SDLK_LEFT:
						posPerso = mario[LEFT];
						deplacerJoueur(carte, &positionJoueur, GAUCHE);
						break;
					case SDLK_KP1:
						jouer(ecran);
						break;
					case SDLK_KP2:
						editeur(ecran);
						break;
				}
				break;
		}
		
		SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
		SDL_BlitSurface(menu, NULL, ecran, &positionMenu);
		SDL_Flip(ecran);
	}
	
    	SDL_FreeSurface(menu);
    	SDL_Quit();

    	return EXIT_SUCCESS;
}
