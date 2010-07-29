#ifndef FONTH
#define FONTH

#include <map>

using namespace std;

class Letter {
public:
	Letter(int,int,char *);
	int width;
	int height;
	char *pixels;
};

class Font {
public:
	Font(char *filename);
	Font(string filename);
	map<char,Letter *> letters;
};

#endif
