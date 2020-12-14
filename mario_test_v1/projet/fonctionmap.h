#include <sdl/sdl.h>

typedef unsigned char tileindex;

typedef struct
{
	SDL_Rect R;
	int plein;
} TileProp;

typedef struct
{
	int LARGEUR_TILE,HAUTEUR_TILE;
	int nbtilesX,nbtilesY;
	TileProp* props;
	tileindex** schema;
	int largeur_monde,hauteur_monde;
	SDL_Surface* tileset;

} Map;

Map* ChargerMap(const char* fic);
int AfficherMap(Map* m,SDL_Surface* screen);
int LibererMap(Map* m);
