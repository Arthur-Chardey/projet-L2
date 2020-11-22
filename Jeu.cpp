#include "Jeu.h"
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>


void initialiser(const char* titre , int largeur , int hauteur , bool fullscreen) {
SDL_Window *fenetre = NULL;
if (SDL_Init(SDL_INIT_VIDEO)!= 0){
    fprintf(stderr ,"Erreur d'initialisation : %s" , SDL_GetError());
        }
        if (fullscreen==false){
fenetre = SDL_CreateWindow( titre , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , largeur , hauteur , SDL_WINDOW_SHOWN); // creer fenetres
}
else {fenetre = SDL_CreateWindow( titre, SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , largeur , hauteur , SDL_WINDOW_FULLSCREEN); // creer fenetre en fullscreen

}
}

void exit(){
        SDL_Quit(); // Quite SDL
}

void detruirefenetre(SDL_Window* fenetre){
        SDL_DestroyWindow(fenetre); // detruit fenetre
}

void render(){
}

void update(){
}
