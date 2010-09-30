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
	letters = new map<char, Letter *>();
	chars = new vector<char>();
	while (infile.read(&c,1)) {
		w = c;
		infile.read(&h,1);
		infile.read(&ch,1);
		chars->push_back(ch);
		char *p = (char *)malloc(sizeof(char)*w*h*3);
		cout << "font.cpp font reading in " << (int)ch << " with size of " << (int)w << "," << (int)h << endl;
		for (i=0;i<h;i++) {
			for (j=0;j<w;j++) {
				int index = (i*w+j)*3;
				infile.read(&p[index],1);
				infile.read(&p[index+1],1);
				infile.read(&p[index+2],1);
				/*int r = p[index];
				if (r < 0) r += 256;
				int g = p[index+1];
				if (g < 0) g += 256;
				int b = p[index+2];
				if (b < 0) b += 256;
				cout << r << " " << g << " " << b << endl;*/
			}
		}
		letter = new Letter(w,h,p);
		letters->insert(pair<char,Letter *>(ch,letter));
	}
	cout << "font.cpp font finished loading of font " << endl;
}

Letter::Letter(int w, int h, char *pix) {
	width = w;
	height = h;
	pixels = pix;
}

int Font::widthOf(char c) {
	if (letters->find(c) != letters->end()) {
		return letters->find(c)->second->width;
	}
	return 0;
}
