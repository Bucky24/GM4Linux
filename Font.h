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
	Font(char *);
	map<char,Letter *> letters;
	void create(const char *);
};

#endif
