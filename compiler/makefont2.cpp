#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

class Image {
public:
	char *pixels;
	int width;
	int height;
	Image(char *, int, int);
};

Image::Image(char *p, int w, int h) {
	pixels = p;
	width = w;
	height = h;
}

Image *loadImage(char *);

int main(int argc, char **argv) {
	if (argv < 4) {
		cout << "Usage: makefont2 <bitmap> width height" << endl;
		return 1;
	}

	int letterWidth = atoi(argv[2]);
	int letterHeight = atoi(argv[3]);

	char letters[75][letterHeight][letterWidth];

	Image *image = loadImage(argv[1]);

	return 0;
}

Image *loadImage(char *filename) {
	infile.open(argv[i],ios::in | ios::binary);
	infile.seekg(18);
	char in1, in2;
	int i1, i2;
	infile.read(&in1,1);
	infile.read(&in2,1);
	i1 = in1;
	if (i1 < 0) i1 = 256+i1;
	i2 = in2;	
	//cout << i1 << " " << i2 << endl;
	width = byteToInt(i1,i2);

	infile.seekg(22);
	infile.read(&in1,1);
	infile.read(&in2,1);
	i1 = in1;
	if (i1 < 0) i1 = 256+i1;
	i2 = in2;	
	//cout << i1 << " " << i2 << endl;
	height = byteToInt(i1,i2);

	//cout << width << " " << height << endl;

	//cout << "allocating image memory of " << width << "x" << height << "x3" <<  endl;
	char image[width][height][3];
	//cout << "generating image map " << endl;

	for (j=0;j<width;j++) {
		for (k=0;k<height;k++) {
			//cout << j <<  " " << k << endl;
			image[j][k][0] = 255;
			image[j][k][1] = 255;
			image[j][k][2] = 255;
		}
	}

	int four = width;
	while (four % 4 != 0) four --;
	int pad = width-four;

	//cout << "four: " << four << endl;

	infile.seekg(54);
	int count = 0;
	int lines = 0;
	state = 0;
	while (infile.read(&input,1)) {
		if (state == 0) {
			b = input;
			state = 1;
		} else if (state == 1) {
			g = input;
			state = 2;
		} else if (state == 2) {
			r = input;
			state = 0;
			if (r != -1 || g != -1 || b != -1) {
				//cout << infile.tellg() << " " << count/3 << "," << height-lines-1 << " " << (int)r << "," << (int)g << "," << (int)b << endl;
				image[count/3][height-lines-1][0] = r;
				image[count/3][height-lines-1][1] = g;
				image[count/3][height-lines-1][2] = b;
			}
		}
		if (count == (width)*3-1) {
			lines ++;
			//cout << count << " " << (count/3) << " " << lines << endl;
			count = -1;
			//cout << lines << " " << pad << " " << infile.tellg() << endl;
			for (j=0;j<pad;j++) {
				infile.read(&input,1);
				//cout <<"pad " << (int)input << endl;
			}
		}
		count ++;
		//cout << "count " << count << endl;
	}
	infile.close();

	Image *im = new Image(image,width,height);
	return im;
}
