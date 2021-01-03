
#ifndef OUTILS_H
#define OUTILS_H

#include <fstream>
#include <string>
#include <sstream>

#include "Bases_du_dessin.h"

typedef struct ARROWS { 
   bool gauche;
   bool droite;
   bool haut;
   bool bas;
   bool tirer;
} ARROWS, *PARROWS;

// Si la case est de l'un des type demandé, alors renvoi 1, sinon, renvoi 0...
int VerifierTypeCase( int x, int y, string typeCase ) {
     int i;
     for( i=0 ; i!= typeCase.size() ; ++i ) {
          if( carte[x][y] == typeCase[i] ) return 1;
     }
     return 0;
}

string ouvrir_fichier(string nom_fichier) {
	string phrase;
	ifstream fichier(nom_fichier.c_str());
	if (!fichier) {
		cout <<"Erreur, fichier corrompu ou inexistant !\n\n";
		phrase = "Erreur, fichier corrompu ou inexistant !";
	} else {
		stringstream buffer;
		buffer << fichier.rdbuf();
		fichier.close();
		phrase = buffer.str();
	}
	return phrase;
}

// 0 pour fichier invalide
// 1 pour fichier "valide"
int fichier_valide(string nom_fichier) {
	ifstream fichier(nom_fichier.c_str());
	if (!fichier) return 0;
	else return 1;
}

void Attendre( int tpsEnMS ) {
    int startTicks = SDL_GetTicks();
    while( SDL_GetTicks() - startTicks < tpsEnMS ) {}
}

char * DoubleToChar( double nombre, char *leChar ) {
     int temp = nombre;
     char temp1[24];
     itoa( temp, temp1, 10 );
     temp = nombre*1000 - temp*1000;
     if( temp < 0 ) temp = -temp;
     char temp2[16];
     itoa( temp, temp2, 10 );
     char *renvoi = leChar;
     // Si le nombre est inférieur à 0 mais supérieur à -1 temp1 vaudra "0" alors qu'il devarit valloir "-0"
     if( -1 < nombre && nombre < 0 ) {
         strcpy( renvoi, "-" );
         strcat( renvoi, temp1 );
     } else strcpy( renvoi, temp1 );
     strcat( renvoi, "," );
     int i = strlen(temp2);
     while( i<3 ) {
         strcat( renvoi, "0" );
         ++i;
     }
     strcat( renvoi, temp2 );
     return renvoi;
}

void DegradeSurfaceVertical( SDL_Surface *screen, int origineX, int origineY, int finX, int finY, RGB couleur1, RGB couleur2 ) {
     int increment = 1;
     if( finY < origineY ) increment = -1;
     int i;
     for( i = origineY ; i != finY ; i += increment ) {
          int rouge = couleur1.r - ((couleur1.r-couleur2.r)*i)/screen->h;
          int vert = couleur1.g - ((couleur1.g-couleur2.g)*i)/screen->h;
          int bleu = couleur1.b - ((couleur1.b-couleur2.b)*i)/screen->h;
          TracerSegment( screen, origineX, i, finX, i, SDL_MapRGB( screen->format, rouge, vert, bleu ) );
     }
}

// Coordonnées du point en haut à droite de la jauge de vies
void AfficherVies( SDL_Surface *screen, int origineX, int origineY, int vies, Uint32 couleurCoeur ) {
     int i, x;
     int tailleCoeur = 16;
     int Espacement = 2;
     for( i=0 ; i<vies ; ++i ) {
          x = origineX - ( tailleCoeur*(i+1) + Espacement*i );
          TracerSegment( screen, x+2, origineY, x+4, origineY, couleurCoeur );
          TracerSegment( screen, x+11, origineY, x+13, origineY, couleurCoeur );
          TracerSegment( screen, x+1, origineY+1, x+5, origineY+1, couleurCoeur );
          TracerSegment( screen, x+10, origineY+1, x+14, origineY+1, couleurCoeur );
          TracerSegment( screen, x, origineY+2, x+6, origineY+2, couleurCoeur );
          TracerSegment( screen, x+9, origineY+2, x+15, origineY+2, couleurCoeur );
          
          TracerSegment( screen, x, origineY+3, x+15, origineY+3, couleurCoeur );
          TracerSegment( screen, x, origineY+4, x+15, origineY+4, couleurCoeur );
          TracerSegment( screen, x, origineY+5, x+15, origineY+5, couleurCoeur );
          TracerSegment( screen, x, origineY+6, x+15, origineY+6, couleurCoeur );
          TracerSegment( screen, x, origineY+7, x+15, origineY+7, couleurCoeur );
          TracerSegment( screen, x, origineY+8, x+15, origineY+8, couleurCoeur );
          TracerSegment( screen, x+1, origineY+9, x+14, origineY+9, couleurCoeur );
          TracerSegment( screen, x+3, origineY+10, x+12, origineY+10, couleurCoeur );
          TracerSegment( screen, x+5, origineY+11, x+10, origineY+11, couleurCoeur );
          TracerSegment( screen, x+6, origineY+12, x+9, origineY+12, couleurCoeur );
          TracerSegment( screen, x+6, origineY+13, x+9, origineY+13, couleurCoeur );
          TracerSegment( screen, x+7, origineY+14, x+8, origineY+14, couleurCoeur );
          TracerSegment( screen, x+7, origineY+15, x+8, origineY+15, couleurCoeur );
          
     }
}

double toDegres( double radians ) { return (double)(180.0*radians)/M_PI; }

double toRadians( double degres ) { return (double)(M_PI*degres)/180.0; }

void CerclePlein( SDL_Surface *screen, double oX, double oY, double rayon, Uint32 couleur ) {
     double incrementation = 1.0 / ( M_PI*rayon ); // 1 / demi-périmètre du cercle
     double i; // représente l'angle
     for( i=0 ; i < 180.0 ; i+=incrementation ) {
          double angleRadians = toRadians( i );
          double x = rayon * cos( angleRadians );
          double y = rayon * sin( angleRadians );
          TracerSegment( screen, oX-x, oY-y, oX+x, oY+y, couleur );
     }
}
#endif
