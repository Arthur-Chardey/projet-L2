
#ifndef map_h
#define map_h

// Couleurs du ciel
RGB couleur1fond(200,100,255);

// Couleurs des briques
RGB c1Type1(255,207,64);
RGB c2Type1(128,64,0);

// Case ciel
void CaseType0( int xCase, int yCase ) { DegradeSurfaceVertical( screen, xCase*CASE_X, yCase*CASE_Y, (xCase+1)*CASE_X - 1, (yCase+1)*CASE_Y, couleur1fond, couleur2fond ); }

// Case bloc de pierre
void CaseType1( int xCase, int yCase ) {
     int xDep = xCase*CASE_X;
     int xArr = (xCase+1)*CASE_X - 1; // -1  car (xCase+1)*CASE_X appartient à la case à droite
     int yDep = yCase*CASE_Y;
     int yArr = (yCase+1)*CASE_Y;
     //RectanglePlein( screen, xDep, yDep, xArr, yArr, SDL_MapRGB( screen->format, 255, 207, 64 ) );
     DegradeSurfaceVertical( screen, xDep, yDep, xArr, yArr, c1Type1, c2Type1 );
     Uint32 couleurJointage = SDL_MapRGB( screen->format, 50, 50, 50 );
     TracerSegment( screen, xDep, yDep, xArr, yDep, couleurJointage );
     TracerSegment( screen, xDep, (yDep+yArr)/2, xArr, (yDep+yArr)/2, couleurJointage );
     TracerSegment( screen, (xDep+xArr)/2, yDep, (xDep+xArr)/2, (yDep+yArr)/2, couleurJointage );
     TracerSegment( screen, xDep, (yDep+yArr)/2, xDep, yArr, couleurJointage );
}

// Case départ
void CaseDepart( int xCase, int yCase ) {
     CaseType0( xCase, yCase );
     
     int xDep = xCase*CASE_X;
     int xArr = (xCase+1)*CASE_X - 1; // -1  car (xCase+1)*CASE_X appartient à la case à droite
     int yDep = yCase*CASE_Y;
     int yArr = (yCase+1)*CASE_Y;
     RectanglePlein( screen, xDep, yDep-((yDep-yArr)*7)/8, xArr, yArr, SDL_MapRGB( screen->format, 255, 125, 125 ) );
     
}

// Case d'arrivée
void CaseArrivee( int xCase, int yCase ) {
     CaseType0( xCase, yCase );
     
     int xDep = xCase*CASE_X;
     int xArr = (xCase+1)*CASE_X - 1; // -1  car (xCase+1)*CASE_X appartient à la case à droite
     int yDep = yCase*CASE_Y;
     int yArr = (yCase+1)*CASE_Y;
     RectanglePlein( screen, (xDep+xArr)/2 - 2, yDep, (xDep+xArr)/2 + 2, yArr, SDL_MapRGB( screen->format, 0, 0, 0 ) );
     RectanglePlein( screen, (xDep+xArr)/2 + 2, yDep+2, xArr, (yDep+yArr)/2, SDL_MapRGB( screen->format, 125, 0, 125 ) );
     RectanglePlein( screen, xDep, yDep-((yDep-yArr)*7)/8, xArr, yArr, SDL_MapRGB( screen->format, 255, 255, 0 ) );
}

// Redessine ou dessine la carte de A à Z (intégralement)
void DessinerCarte() {
     int x, y;
     for( x=0; x!=NB_CASES_X ; ++x ) {
          for( y=0; y!=NB_CASES_Y ; ++y ) {
               if( carte[x][y] == '1' ) CaseType1(x,y);
               else if( carte[x][y] == '2' ) CaseType2(x,y);
               else if( carte[x][y] == 'D' ) CaseDepart(x,y);
               else if( carte[x][y] == 'A' ) CaseArrivee(x,y);
               else if( carte[x][y] == 'C' || carte[x][y] == 'c' ) CaseCheckPoint(x,y);
               else CaseType0(x,y);
          }
     }
}

// Conserve les coordonnées des zones à redessiner
// L'intérêt de conserver ces données est qu'il sera impossible de redessiner deux fois la même zone
// ce sera donc un gain de rapidité non négligeable...
void RedessinerZoneCarte( int origineX, int origineY, int finX, int finY ) {
     // Vérifications et ajustements des données à la taille de la fenêtre
     if( origineX < 0 ) origineX = 0;
     else if( origineX > WIDTH-1 ) origineX = WIDTH-1;
     if( origineY < 0 ) origineY = 0;
     else if( origineY > HEIGHT-1 ) origineY = HEIGHT-1;
     if( finX < 0 ) finX = 0;
     else if( finX > WIDTH-1 ) finX = WIDTH-1;
     if( finY < 0 ) finY = 0;
     else if( finY > HEIGHT-1 ) finY = HEIGHT-1;
     
     int caseX1 = origineX/CASE_X;
     int caseY1 = (HEIGHT-origineY)/CASE_Y;
     int caseX2 = finX/CASE_X;
     int caseY2 = (HEIGHT-finY)/CASE_Y;
     int incrementX = 1;
     int incrementY = 1;
     if( caseX1 > caseX2 ) incrementX = -1;
     if( caseY1 > caseY2 ) incrementY = -1;
     int x, y;
     for( x=caseX1; x!=caseX2+incrementX ; x += incrementX ) {
          for( y=caseY1; y!=caseY2+incrementY ; y += incrementY ) {
               DessinCarte[x][y] = true;
          }
     }
}

// Redessine les zones necessaires choisi grâce à la fonction RedessinerZoneCarte(...)
void ActualiserCarte() {
     int x, y;
     for( x=0; x!=NB_CASES_X ; ++x ) {
          for( y=0; y!=NB_CASES_Y ; ++y ) {
               if( DessinCarte[x][y] == true ) {
                   if( carte[x][y] == '1' ) CaseType1(x,y);
                   else if( carte[x][y] == '2' ) CaseType2(x,y);
                   else if( carte[x][y] == 'D' ) CaseDepart(x,y);
                   else if( carte[x][y] == 'A' ) CaseArrivee(x,y);
                   else if( carte[x][y] == 'C' || carte[x][y] == 'c' ) CaseCheckPoint(x,y);
                   else CaseType0(x,y);
               }
          }
     }
}

void ChargerNomsNiveaux( string nom_fichier ) {
    // Vider le vector contenant le noms des fichiers de niveaux sur lesquelq jouer
    while( nomsNiveaux.size() != 0 ) { nomsNiveaux.erase( nomsNiveaux.begin() ); }
    // Ouverture du fichier
    string contenu_fichier = ouvrir_fichier( nom_fichier );
    int i;
    int size = contenu_fichier.size();
    string temp = "";
    // Actualisation du contenu du vector contenant les noms des fichiers de niveaux
    for( i=0 ; i!=size ; ++i ) {
         if( contenu_fichier[ i ] == '\n' ) {
             if( temp.size() > 0 && fichier_valide( temp ) == 1 ) nomsNiveaux.push_back( temp );
             temp = "";
         } else temp += contenu_fichier[ i ];
    }
}

#endif
