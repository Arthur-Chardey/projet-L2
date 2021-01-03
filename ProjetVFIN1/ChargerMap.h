
#ifndef CHARGERCARTE_H
#define CHARGERCARTE_H

// Charge la carte spécifié par fichier_nb
void ChargerCarte( int fichier_nb ) {
     // Vider les vectors contenant les Ennemis et Boulets
     while( lesEnnemis.size() != 0 ) { lesEnnemis.erase( lesEnnemis.begin() ); }
     while( lesBoulets.size() != 0 ) { lesBoulets.erase( lesBoulets.begin() ); }
     
     if( fichier_nb < 0 ) fichier_nb = nomsNiveaux.size() - 1;
     if( fichier_nb > nomsNiveaux.size() - 1 ) fichier_nb = 0;
     
     nivActuel = fichier_nb;
     string contenu_fichier = ouvrir_fichier( nomsNiveaux[ fichier_nb ]/*nom_fichier*/ );
     int i;
     int size = contenu_fichier.size();
     int x = 0;
     int y = 0;
     memset( carte, '0', sizeof(carte) );
     for( i=0 ; i != size ; ++i ) {
          char temp = contenu_fichier[i];
          if( temp == '\n' || temp == '\r' || temp == '+' ) {
              ++y;
              x = 0;
          } else {
               if( temp == 'm' ) {
                   temp = '0';
                   if( x < NB_CASES_X && y < NB_CASES_Y ) {
                       Ennemis EnnemisTemp( x * CASE_X, HEIGHT - ( ( y + 1 )* CASE_Y ), 1 );
                       lesEnnemis.push_back( EnnemisTemp );
                   }
               } else if( temp == 'M' ) {
                   temp = '0';
                   if( x < NB_CASES_X && y < NB_CASES_Y ) {
                       if( i+1 < size ) {
                           ++i;
                           char NB_viesTemp[16];
                           memset( NB_viesTemp, 0, sizeof(NB_viesTemp) );
                           NB_viesTemp[ 0 ] = contenu_fichier[i];
                           Ennemis EnnemisTemp( x * CASE_X, HEIGHT - ( ( y + 1 )* CASE_Y ), atoi(NB_viesTemp)+1 );
                           lesEnnemis.push_back( EnnemisTemp );
                       } else {
                           Ennemis EnnemisTemp( x * CASE_X, HEIGHT - ( ( y + 1 )* CASE_Y ), 1 );
                           lesEnnemis.push_back( EnnemisTemp );
                       }
                   }
               } else if( temp == '<' ) {
                   temp = '0';
                   if( x < NB_CASES_X && y < NB_CASES_Y ) {
                       Boulet leBouletTemp( x * CASE_X, HEIGHT - ( ( y + 1 )* CASE_Y ), -2 );
                       lesBoulets.push_back( leBouletTemp );
                   }
               } else if( temp == '>' ) {
                   temp = '0';
                   if( x < NB_CASES_X && y < NB_CASES_Y ) {
                       Boulet leBouletTemp( x * CASE_X, HEIGHT - ( ( y + 1 )* CASE_Y ), 2 );
                       lesBoulets.push_back( leBouletTemp );
                   }
               } else if( temp != '0' && temp != '1' && temp != '2' && temp != 'D' && temp != 'A' && temp != 'C' && temp != 'c' ) temp = '0';
               if( x < NB_CASES_X && y < NB_CASES_Y ) carte[x][y] = temp;
               ++x;
          }
          if( y >= NB_CASES_Y ) break;
     }
     int temp = fichier_nb - 1;
     if( temp < 0 ) temp = nomsNiveaux.size() - 1;
     niv_precedent = nomsNiveaux[ temp ];
     niv_actuel = nomsNiveaux[ nivActuel ];
     niv_suivant = nomsNiveaux[ fichier_nb ];
     temp = fichier_nb + 1;
     if( temp > nomsNiveaux.size() - 1 ) temp = 0;
     niv_suivant = nomsNiveaux[ temp ];
     
     texteNomNivPrec = TTF_RenderText_Blended( policeNiv, niv_precedent.c_str(), couleurBlanche );
     texteNomNivActuel = TTF_RenderText_Blended( policeNivEnCours, niv_actuel.c_str(), couleurJaune );
     texteNomNivSuiv = TTF_RenderText_Blended( policeNiv, niv_suivant.c_str(), couleurBlanche );
}

#endif
