#include <fstream>
#include <cstdlib>

#include "Font.h"

using namespace std;

Font::Font(string filename) {
	create(filename.c_str());
}

Font::Font(char *filename) {
	create(filename);
}

void create(char *filename) {
	ifstream infile;
	infile.open(filename, ios::in | ios::binary);
	char c;
	Letter *letter;
	char w,h,ch;
	int i,j;
	while (infile.read(&c,1)) {
		w = c;
		infile.read(&h,1);
		infile.read(&ch,1);
		char *p = (char *)malloc(sizeof(char)*w*h*3);
		for (i=0;i<h;i++) {
			for (j=0;j<w;j++) {
				int index = (h*w+w)*3;
				infile.read(&p[index],1);
				infile.read(&p[index+1],1);
				infile.read(&p[index+2],1);
			}
		}
		letter = new Letter(w,h,p);
		letters.insert(pair<char,Letter *>(ch,letter));
	}
}

Letter::Letter(int w, int h, char *pix) {
	width = w;
	height = h;
	pixels = pix;
}
