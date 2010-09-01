#ifndef SPRITESH
#define SPRITESH
#include <map>
#include <string>
using namespace std;

extern map<string,char *> spriteData;
extern map<string,int> spriteWidths;
extern map<string,int> spriteHeights;

void initSprites();

#endif
