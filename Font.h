#ifndef FONTH
#define FONTH

#include <map>
#include <vector>

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
	Font(const char *);
	map<char,Letter *> *letters;
	void create(const char *);
	int widthOf(char);
	vector<char> *chars;
};

#endif
