#include <fstream>
#include <cstdlib>
#include <iostream>

#include "Font.h"

using namespace std;

Font::Font(const char *filename) {
	cout << "font.cpp font creating new font " << filename << endl;
	ifstream infile;
	infile.open(filename, ios::in | ios::binary);
	char c;
	Letter *letter;
	char w,h,ch;
	int i,j;
	letters = *(new map<char, Letter *>());
	while (infile.read(&c,1)) {
		w = c;
		infile.read(&h,1);
		infile.read(&ch,1);
		char *p = (char *)malloc(sizeof(char)*w*h*3);
		cout << "font.cpp font reading in " << (int)ch << " with size of " << (int)w << "," << (int)h << endl;
		for (i=0;i<h;i++) {
			for (j=0;j<w;j++) {
				int index = (i*w+j)*3;
				infile.read(&p[index],1);
				infile.read(&p[index+1],1);
				infile.read(&p[index+2],1);
			}
		}
		letter = new Letter(w,h,p);
		letters.insert(pair<char,Letter *>(ch,letter));
	}
	cout << "font.cpp font finished loading of font " << endl;
}

Letter::Letter(int w, int h, char *pix) {
	width = w;
	height = h;
	pixels = pix;
}

int Font::widthOf(char c) {
	if (letters[c] != NULL) {
		return letters[c]->width;
	}
	return 0;
}
