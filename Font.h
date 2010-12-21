#ifndef FONTH
#define FONTH

#include <map>
#include <vector>
#include "Image.h"

using namespace std;

class Font {
public:
	Font(const char *);
	map<char,Image *> *letters;
	void create(const char *);
	int widthOf(char);
	int heightOf(char);
	vector<char> *chars;
};

#endif
