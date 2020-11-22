#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
class Jeu{

Jeu();
void initialiser(const char titre , int largeur , int hauteur , bool fullscreen);
void exit();
void detruirefenetre(SDL_Window* fenetre);
void update();
void render();

};

#endif // JEU_H_INCLUDED
