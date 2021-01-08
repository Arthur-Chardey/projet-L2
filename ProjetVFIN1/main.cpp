
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h> 
#include <iostream>
#include <math.h>
#include <string>
#include <vector>

using namespace std;

#include "res.h"
// Diverses outils : de dessin (dégradé), double to char*, la fonction VerifierTypeCase()...
#include "Outils.h"
// FONCTIONS pour la gestion, l'ouverture, l'affichage... de la carte du jeu
#include "Map.h"

// CLASSE pour le dessin et la gestion d'un objet Mario
#include "Classe_Mario.h"

// FONCTIONS charger la carte du niveau choisis...
#include "ChargerMap.h"

// FONCTIONS allègeant le main()
#include "GererEvents.h" 

int main( int argc, char **argv ) {
    // Mario temporaire
    Mario monMario;
    // lesMarios est déclaré dans GererVies.h qui contrôle le contact entre une flèche et un Mario, un Mario et un Ennemis...
    lesMarios.push_back( monMario );
    
    // ARROWS temporaire
    ARROWS GererMarioTemp;
    GererMarioTemp.gauche = false;
    GererMarioTemp.droite = false;
    GererMarioTemp.haut = false;
    GererMarioTemp.bas = false;
    // GererMarios est déclaré dans GererVies.h
    GererMarios.push_back( GererMarioTemp );
    
    //Déclaration des variables locales
    TTF_Font *policeMenu = NULL;
    TTF_Font *policeTemps = NULL;
    SDL_Event event;
    
    //Initialisation de SDL
    SDL_Windiw* fenetre;
    SDL_Event evenements;
    bool terminer = false;
    if( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        std::cerr << "Probleme pour initialiser SDL" << SDL_GetError() << std::endl;
        return 1;
    }
    // Initialisation de SDL_ttf
    if( TTF_Init() == -1 ) {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_Renderer* ecran;
    ecran = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
    // Mettre un titre à la fenêtre
    SDL_WM_SetCaption( "Version d'essai", NULL );
    
    // Initialsation de la variable affichagePleinEcran
    affichagePleinEcran = false;
    //Ouverture d'une surface pour l'affichage de la fenêtre
    screen = SDL_SetVideoMode( WIDTH, HEIGHT, 32, SDL_DOUBLEBUF | SDL_HWSURFACE );
    if( screen == NULL ) done = 1;
    
    // Laisser apparaître le curseur de la souris?
    if( JeuEnCours == 1 && affichagePleinEcran == true ) SDL_ShowCursor( SDL_DISABLE );
    else SDL_ShowCursor( SDL_ENABLE );
    
    // Charge les polices
    policeMenu = TTF_OpenFont( "angelina.ttf", 65 );
    policeNiv = TTF_OpenFont( "times.ttf", 16 );
    policeNivEnCours = TTF_OpenFont( "times.ttf", 16 );
    TTF_SetFontStyle( policeNivEnCours, TTF_STYLE_BOLD );
    policeTemps = TTF_OpenFont( "times.ttf", 24 );
    
    // Crée les textes pour le menu
    SDL_Surface *texteMenu [5];
    texteMenu[0] = TTF_RenderText_Blended( policeMenu, "Reprendre...", couleurBlanche );
    texteMenu[1] = TTF_RenderText_Blended( policeMenu, "Retour Case départ (R)", couleurBlanche );
    texteMenu[2] = TTF_RenderText_Blended( policeMenu, "Retour CheckPoint (C)", couleurBlanche );
    texteMenu[3] = TTF_RenderText_Blended( policeMenu, "Plein écran ?", couleurBlanche );
    texteMenu[4] = TTF_RenderText_Blended( policeMenu, "QUITTER", couleurBlanche );
    // Crée le texte affiché une fois le niveau fini
    SDL_Surface *texteMenuTemps;
    texteMenuTemps = TTF_RenderText_Blended( policeMenu, "Félicitations!", couleurBlanche );
    
    // On charge les noms des niveaux
    ChargerNomsNiveaux( "Niveaux.txt" );
    // Si l'on ne trouve aucun niveau, on met fin au programme (en empêchant le lancement de la boucle de messages while())
    if( nomsNiveaux.size() == 0 ) done = 1;
    // On charge la nouvelle carte
    ChargerCarte( 0 );
    
    // On dessine la carte
    if( JeuEnCours == true ) DessinerCarte();
    
    // On crée un Mario et le place à la case départ
    lesMarios[0].RetourCaseDepart();
    
    // Boucle generale
    while( !done ) {
        // Traiter les évènements
        while( SDL_PollEvent(&event) ) {
            // Les messages sont traiter par les fonctions ci-dessous,
            // ce n'est sans doute pas la méthode la plus esthétique
            // mais elle fonctionne tout de même et permet d'allèger le contenu de la boucle principale du programme (while())
            if( JeuEnCours == 1 ) eventsModeJeu( event );
            else if( JeuEnCours == 0 ) eventsModePause( event, texteMenu );
            else if( JeuEnCours == 2 ) eventsModeFin( event );
        }
        // On fait avancer le jeu...
        // On affiche ce qu'il faut afficher : le menu principal, le jeu...
        if( JeuEnCours == 1 ) {
            ModeJeu( policeTemps );
            // On effectue les vérifications de dernière minute
            VerifierFlechettes();
            VerifierMarioEnnemis();
            VerifierMarioBoulets();
            VerifierEnnemisBoulets();
        } else if( JeuEnCours == 0 ) ModePause( texteMenu );
        else if( JeuEnCours == 2 ) ModeFin( texteMenuTemps );
    }
    
    // Fermer les polices
    TTF_CloseFont( policeMenu );
    TTF_CloseFont( policeNiv );
    TTF_CloseFont( policeNivEnCours );
    TTF_CloseFont( policeTemps );
    // Quitter SDL_ttf
    TTF_Quit();
    
    // Libérer les surfaces
    SDL_FreeSurface( texteMenu[0] );
    SDL_FreeSurface( texteMenu[1] );
    SDL_FreeSurface( texteMenu[2] );
    SDL_FreeSurface( texteMenu[3] );
    SDL_FreeSurface( texteMenu[4] );
    SDL_FreeSurface( texteMenu[5] );
    SDL_FreeSurface( texteNomNivPrec );
    SDL_FreeSurface( texteNomNivActuel );
    SDL_FreeSurface( texteNomNivSuiv );
    SDL_FreeSurface( texteMenuTemps );
    SDL_FreeSurface( texteTemps );
    // Quitter SDL
    SDL_Quit();
    return 0;
}
