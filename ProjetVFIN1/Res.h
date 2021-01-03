#ifndef RES_H
#define RES_H

const int Largeur = 1920;
const int Hauteur = 1080;

const int NbCasesX = 25;
const int NbCasesY = 20;

const int CaseX = Largeur/NbCasesX;
const int CaseY = Hauteur/NbCasesY;

SDL_Color couleurBlanche = { 255, 255, 255 };
SDL_Color couleurJaune = { 255, 255, 0 };

SDL_Surface *screen = NULL;
SDL_Surface *texteNomNivPrec = NULL;
SDL_Surface *texteNomNivActuel = NULL;
SDL_Surface *texteNomNivSuiv = NULL;
SDL_Surface *texteTemps = NULL;

TTF_Font *policeNiv = NULL;
TTF_Font *policeNivEnCours = NULL;

char Map[NbCasesX+1][NbCasesY+1];
bool DessinMap[NbCasesX+1][NbCasesY+1];
string niv_precedent;
string niv_actuel;
string niv_suivant;

vector <string> nomsNiveaux;
int nivActuel = 0;

#endif
