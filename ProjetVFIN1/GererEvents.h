
#ifndef GEREREVENTS_H
#define GEREREVENTS_H

bool affichagePleinEcran;
int JeuEnCours = 1;
int done = 0;

void eventsModeJeu( SDL_Event event ) {
    int i;
    switch( event.type ) {
        // Si on veut quitter, done = 1 suffira (car celà fini la boucle)
        case SDL_QUIT:
             done = 1;
             break;
        case SDL_KEYDOWN:
             if( event.key.keysym.sym == SDLK_ESCAPE ) {
                 JeuEnCours = 0;
                 for( i=0 ; i!= GererMarios.size() ; ++i ) {
                      lesMarios[ i ].PauseChrono( true );
                      GererMarios[ i ].gauche = false;
                      GererMarios[ i ].droite = false;
                      GererMarios[ i ].haut = false;
                      GererMarios[ i ].bas = false;
                      GererMarios[ i ].tirer = false;
                 }
                 SDL_ShowCursor( SDL_ENABLE );
             } else if( event.key.keysym.sym == SDLK_LEFT ) GererMarios[ 0 ].gauche = true;
             else if( event.key.keysym.sym == SDLK_RIGHT ) GererMarios[ 0 ].droite = true;
             else if( event.key.keysym.sym == SDLK_UP ) GererMarios[ 0 ].haut = true;
             else if( event.key.keysym.sym == SDLK_DOWN ) GererMarios[ 0 ].bas = true;
             else if( event.key.keysym.sym == SDLK_SPACE ) GererMarios[ 0 ].tirer = true;
             else if( event.key.keysym.sym == SDLK_TAB ) {
                 if( affichagePleinEcran == true ) {
                     SDL_FreeSurface( screen );
                     screen = SDL_SetVideoMode( WIDTH, HEIGHT, 32, SDL_DOUBLEBUF | SDL_HWSURFACE );
                     SDL_ShowCursor( SDL_ENABLE );
                     affichagePleinEcran = false;
                 } else {
                     SDL_FreeSurface( screen );
                     screen = SDL_SetVideoMode( WIDTH, HEIGHT, 32, SDL_DOUBLEBUF | SDL_HWSURFACE | SDL_FULLSCREEN );
                     SDL_ShowCursor( SDL_DISABLE );
                     affichagePleinEcran = true;
                 }
                 if( screen == NULL ) done = 1;
                 DessinerCarte();
             } else if( event.key.keysym.sym == SDLK_r ) {
                    lesMarios[ 0 ].RetourCaseDepart();
                    for( i=0 ; i != lesEnnemis.size() ; ++i ) { lesEnnemis[ i ].Initialiser(); }
                    for( i=0 ; i != lesBoulets.size() ; ++i ) { lesBoulets[ i ].Initialiser(); }
             } else if( event.key.keysym.sym == SDLK_c ) lesMarios[ 0 ].RetourCheckPoint();
             break;
        case SDL_KEYUP:
             if( event.key.keysym.sym == SDLK_LEFT ) GererMarios[ 0 ].gauche = false;
             else if( event.key.keysym.sym == SDLK_RIGHT ) GererMarios[ 0 ].droite = false;
             else if( event.key.keysym.sym == SDLK_UP ) GererMarios[ 0 ].haut = false;
             else if( event.key.keysym.sym == SDLK_DOWN ) GererMarios[ 0 ].bas = false;
             else if( event.key.keysym.sym == SDLK_SPACE ) GererMarios[ 0 ].tirer = false;
             break;
        default:
             break;
    }
}


void eventsModeFin( SDL_Event event ) {
    int i;
    switch( event.type ) {
        // Si on veut quitter, done = 1 suffira (car celà fini la boucle)
        case SDL_QUIT:
             done = 1;
             break;
        case SDL_MOUSEBUTTONDOWN:
             if( event.button.button == SDL_BUTTON_LEFT ) {
                 JeuEnCours = 1;
                 for( i=0 ; i!= lesMarios.size() ; ++i ) { lesMarios[ i ].PauseChrono( false ); }
                 if( affichagePleinEcran == true ) SDL_ShowCursor( SDL_DISABLE );
                 else SDL_ShowCursor( SDL_ENABLE );
                 ChargerCarte( nivActuel+1 );
                 DessinerCarte();
                 for( i=0 ; i!= lesMarios.size() ; ++i ) { lesMarios[ i ].RetourCaseDepart(); }
             }
             break;
        case SDL_KEYDOWN:
             if( event.key.keysym.sym == SDLK_ESCAPE ) {
                 JeuEnCours = 0;
                 for( i=0 ; i!= lesMarios.size() ; ++i ) { lesMarios[ i ].PauseChrono( true ); }
                 SDL_ShowCursor( SDL_ENABLE );
                 ChargerCarte( nivActuel+1 );
                 DessinerCarte();
                 for( i=0 ; i!= lesMarios.size() ; ++i ) { lesMarios[ i ].RetourCaseDepart(); }
             } else if( event.key.keysym.sym == SDLK_RETURN ) {
                 JeuEnCours = 1;
                 for( i=0 ; i!= lesMarios.size() ; ++i ) { lesMarios[ i ].PauseChrono( false ); }
                 if( affichagePleinEcran == true ) SDL_ShowCursor( SDL_DISABLE );
                 else SDL_ShowCursor( SDL_ENABLE );
                 ChargerCarte( nivActuel+1 );
                 DessinerCarte();
                 for( i=0 ; i!= lesMarios.size() ; ++i ) { lesMarios[ i ].RetourCaseDepart(); }
             } else if( event.key.keysym.sym == SDLK_TAB ) {
                 if( affichagePleinEcran == true ) {
                     SDL_FreeSurface( screen );
                     screen = SDL_SetVideoMode( WIDTH, HEIGHT, 32, SDL_DOUBLEBUF | SDL_HWSURFACE );
                     affichagePleinEcran = false;
                 } else {
                     SDL_FreeSurface( screen );
                     screen = SDL_SetVideoMode( WIDTH, HEIGHT, 32, SDL_DOUBLEBUF | SDL_HWSURFACE | SDL_FULLSCREEN );
                     affichagePleinEcran = true;
                 }
                 if( screen == NULL ) done = 1;
             }
             break;
        default:
            break;
    }
}

/*
ModeJeu()
peut gérer plusieurs Marios simultanément
*/
void ModeJeu( TTF_Font *policeTemps ) {
    /*
    Le reste de ce code permet :
    
    1 -  d'analyser la situation
    puis d'agir en fonction de celle-ci (faut-il sauter?...),
    
    2 - faire patienter le programme 20 millisecondes
    afin que le déplacement du Mario ne soit pas trop rapide.
    
    Certes, cette deuxième partie n'est pas très esthétique mais après un essai peu convainquant avec les timers
    qui demandait (enfin je n'est réussi que comme celà) de mettre Mario lesMarios[ 0 ] en variable globale
    ce qui empêchait le programme de démarrer à cause du constructeur... Sans le constructeur le programme fonctionnait
    mais il fallait appeler une fonction de Mario avant de s'en servir. ;)
    cf. http://www.siteduzero.com/tuto-3-6996-1-maitrisez-le-temps.html
    */
    int i;
    
    /* Gérer puis effacer les personnages */
    
    memset( DessinCarte, false, sizeof(DessinCarte) );
    for( i=0 ; i != lesMarios.size() ; ++i ) {
        // S'il n'y a pas de GererMarios pour ce Mario, alors il ne peut pas bouger
        if( i < GererMarios.size() ) {
            if( GererMarios[ i ].haut != GererMarios[ i ].bas ) {
                if( GererMarios[ i ].haut == true ) lesMarios[ i ].Haut();
                else lesMarios[ i ].Bas();
            }
            if( GererMarios[ i ].gauche != GererMarios[ i ].droite ) {
                if( GererMarios[ i ].gauche == true ) lesMarios[ i ].Gauche();
                else lesMarios[ i ].Droite();
            }
            if( GererMarios[ i ].gauche == GererMarios[ i ].droite && GererMarios[ i ].haut == GererMarios[ i ].bas ) lesMarios[ i ].Actualiser();
            if( GererMarios[ i ].tirer == true ) {
                lesMarios[ i ].Tirer();
                GererMarios[ i ].tirer = false;
            }
        }
        // Ceà n'empêche pas d'effacer le Mario
        // Effacer le Marios
        lesMarios[ i ].EffacerMario();
        // Par la même occasion, cette boucle nous permettra d'effacer les coeurs (indiquant les vies) précédents
        // Redessine la partie de la carte où peuvent se trouver les coeurs avnt de redessiner ces derniers
        RedessinerZoneCarte( 0, HEIGHT-16*i, screen->w, HEIGHT-16*(i+1) );
    }
    
    for( i=0 ; i != lesEnnemis.size() ; ++i ) {
         lesEnnemis[ i ].Bouger();
         lesEnnemis[ i ].Effacer();
         RedessinerZoneCarte( 0, HEIGHT-16*(lesMarios.size()+i), screen->w, HEIGHT-16*(lesMarios.size()+i+1) );
    }
    for( i=0 ; i != lesBoulets.size() ; ++i ) {
         lesBoulets[ i ].Bouger();
         lesBoulets[ i ].Effacer();
    }
    ActualiserCarte();
    
    
    // Après avoir effacer tous les points de vies, on peut redessiner les Marios et le nombre de vies restantes
    // On déclare tempsNiveau qui contiendra le status de la partie : c'est à dire fini ou non
    int tempsNiveau = -1;
    int MarioNb;
    for( i=0 ; i!= lesMarios.size() ; ++i ) {
         // Dessiner le Mario
         lesMarios[ i ].DessinerMario();
         // Afficher le nombre de vies restantes
         AfficherVies( screen, screen->w, i*16, lesMarios[ i ].NombreDeVies(), SDL_MapRGB( screen->format, 255, 62, 62 ) );
         // Si aucun Mario n'a fini le niveau,
         // On verifie si ce (nouveau) Mario a fini le niveau
         if( tempsNiveau == -1 ) {
             tempsNiveau = lesMarios[ i ].NiveauFini();
             MarioNb = i;
         }
    }
    
    for( i=0 ; i != lesEnnemis.size() ; ++i ) {
         lesEnnemis[ i ].Dessiner();
         int nbCoeurs;
         if( lesEnnemis[ i ].NBVies > 0 ) nbCoeurs = lesEnnemis[ i ].NBVies;
         else nbCoeurs = 0;
         AfficherVies( screen, screen->w, (lesMarios.size()+i)*16, nbCoeurs, SDL_MapRGB( screen->format, 62, 62, 255 ) );
    }
    for( i=0 ; i != lesBoulets.size() ; ++i ) { lesBoulets[ i ].Dessiner(); }
    
    if( tempsNiveau != -1 ) {
        JeuEnCours = 2;
        for( i=0 ; i!= GererMarios.size() ; ++i ) {
             GererMarios[ i ].gauche = false;
             GererMarios[ i ].droite = false;
             GererMarios[ i ].haut = false;
             GererMarios[ i ].bas = false;
             GererMarios[ i ].tirer = false;
        }
        char temp[24];
        char final[128];
        strcpy( final, "Joueur n°" );
        itoa( MarioNb+1, temp, 10 );
        strcat( final, temp );
        strcat( final, " : Niveau terminé en " );
        DoubleToChar( tempsNiveau/1000.0, temp );
        strcat( final, temp );
        strcat( final, " secondes..." );
        texteTemps = TTF_RenderText_Blended( policeTemps, final, couleurBlanche );
        SDL_ShowCursor( SDL_ENABLE );
    }
    SDL_UpdateRect( screen, 0, 0, 0, 0 );
    
    Attendre( 20 );
}

/*
ModePause()
quant à elle, affiche le menu principal
*/
void ModePause( SDL_Surface *texteMenu [5] ) {
    SDL_Rect position;
    
    SDL_FillRect( screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0) );
    
    position.x = 60;
    position.y = 60;
    SDL_BlitSurface( texteMenu[0], NULL, screen, &position );
    position.x = 125;
    position.y = 125;
    SDL_BlitSurface( texteMenu[1], NULL, screen, &position );
    position.x = 190;
    position.y = 190;
    SDL_BlitSurface( texteMenu[2], NULL, screen, &position );
    
    position.x = screen->w / 6 - texteNomNivPrec->w / 2;
    position.y = 270;
    SDL_BlitSurface( texteNomNivPrec, NULL, screen, &position );
    position.x = screen->w / 2 - texteNomNivActuel->w / 2;
    position.y = 270;
    SDL_BlitSurface( texteNomNivActuel, NULL, screen, &position );
    position.x = ( 5 * screen->w ) / 6 - texteNomNivSuiv->w / 2;
    position.y = 270;
    SDL_BlitSurface( texteNomNivSuiv, NULL, screen, &position );
    
    position.x = 320;
    position.y = 320;
    SDL_BlitSurface( texteMenu[3], NULL, screen, &position );
    position.x = ( screen->w - texteMenu[4]->w )/2;
    position.y = 450;
    SDL_BlitSurface( texteMenu[4], NULL, screen, &position );
    SDL_Flip( screen );
}

/*
ModeFin()
affiche un bilan du niveau fini (lorsqu'un niveau est terminé)
*/
void ModeFin( SDL_Surface *texteMenuTemps ) {
    SDL_Rect position;
    SDL_FillRect( screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0) );
    
    position.x = 60;
    position.y = 60;
    SDL_BlitSurface( texteMenuTemps, NULL, screen, &position );
    position.x = 90;
    position.y = 140;
    SDL_BlitSurface( texteTemps, NULL, screen, &position );
    
    SDL_Flip( screen );
}

#endif
