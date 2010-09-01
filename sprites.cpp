#include "sprites.h"

map<string,char *> spriteData;
map<string,int> spriteWidths;
map<string,int> spriteHeights;

void initSprites() {
	spriteData = *(new map<string,char *>());
	spriteWidths = *(new map<string,int>());
	spriteHeights = *(new map<string,int>());
/* -- SPRITE DATA -- */
}
