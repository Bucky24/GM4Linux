#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

int byteToInt(int n1, int n2) {
        return n1+n2*256;
}

class Letter {
public:
	Letter(int,int,char *);
	char *pixels;
	int width;
	int height;
};

Letter::Letter(int w, int h, char *p) {
	width = w;
	height = h;
	pixels = p;
}


int main(int argc, char **argv) {
	if (argc < 2) {
		cout << "Usage: makefont <input images>" << endl;
	}

	ofstream outfile;
	ifstream infile;
	char input;
	int state = 0;
	char r, g, b;
	unsigned int i,j,k,l;
	int width,height;

	for (i=1;i<argc;i++) {
		char *filename = argv[i];
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

		char image[width][height][3];

		for (j=0;j<width;j++) {
			for (k=0;k<height;k++) {
				image[j][k][0] = 255;
				image[j][k][1] = 255;
				image[j][k][2] = 255;
			}
		}

		int four = width;
		while (four % 4 != 0) four --;
		int pad = width-four;

		infile.seekg(54);
		int count = 0;
		int lines = 0;
		state = 0;
		while (infile.read(&input,1)) {
			if (state == 0) {
				r = input;
				state = 1;
			} else if (state == 1) {
				g = input;
				state = 2;
			} else if (state == 2) {
				b = input;
				state = 0;
				if (r != -1 || g != -1 || b != -1) {
					//cout << count << " == " << (width-1)*3 << " " << height-lines-1 << endl;
					image[count/3][height-lines-1][0] = r;
					image[count/3][height-lines-1][0] = g;
					image[count/3][height-lines-1][0] = b;
				}
			}
			if (count == (width)*3) {
				lines ++;
				//cout << count << " " << (count/3) << " " << lines << endl;
				count = 0;
				//cout << lines << " " << pad << " " << infile.tellg() << endl;
				for (j=0;j<pad;j++) {
					infile.read(&input,1);
				}
			}
			count ++;
			//cout << "count " << count << endl;
		}
		infile.close();
		//cout << lines << endl;

		// remove top blank lines
		int remove = 0;
		for (j=0;j<height;j++) {
			bool found = false;
			for (k=0;k<width;k++) {
				if (image[k][j][0] != -1 || image[k][j][1] != -1 || image[k][j][2] != -1) {
					found = true;
				}
			}
			if (!found) {
				remove ++;
			} else {
				break;
			}
		}

		//cout << remove << endl;
		for (j=remove;j<height;j++) {
			for (k=0;k<width;k++) {
				image[k][j-remove][0] = image[k][j][0];
				image[k][j-remove][1] = image[k][j][1];
				image[k][j-remove][2] = image[k][j][2];
			}
		}

		height -= remove;

		// remove bottom blank lines
		for (j=height-1;j>=0;j--) {
			bool found = false;
			for (k=0;k<width;k++) {
				if (image[k][j][0] != -1 || image[k][j][1] != -1 || image[k][j][2] != -1) {
					found = true;
				}
			}
			if (!found) {
				height--;
			} else {
				break;
			}
		}

		// remove left blanks
		remove = 0;
		for (j=0;j<width;j++) {
			bool found = false;
			for (k=0;k<height;k++) {
				if (image[j][k][0] != -1 || image[j][k][1] != -1 || image[j][k][2] != -1) {
					found = true;
				}
			}
			if (!found) {
				remove ++;
			} else {
				break;
			}
		}

		cout << remove << endl;
		for (j=remove;j<width;j++) {
			for (k=0;k<height;k++) {
				image[j-remove][k][0] = image[j][k][0];
				image[j-remove][k][1] = image[j][k][1];
				image[j-remove][k][2] = image[j][k][2];
			}
		}
		width -= remove;

		// remove right blanks
		remove = 0;
		for (j=width-1;j>=0;j--) {
			bool found = false;
			for (k=0;k<height;k++) {
				if (image[j][k][0] != -1 || image[j][k][1] != -1 || image[j][k][2] != -1) {
					found = true;
				}
			}
			if (!found) {
				width--;
			} else {
				break;
			}
		}

		vector<int> splits;
		
		bool inWhite = false;
		for (j=0;j<width;j++) {
			bool found = false;
			for (k=0;k<height;k++) {
				if (image[j][k][0] != -1 || image[j][k][1] != -1 || image[j][k][2] != -1) {
					found = true;
				}
			}
			if (!found) {
				if (!inWhite) {
					//cout << "pushing " << j << endl;
					splits.push_back(j);
				}
				inWhite = true;
			} else {
				if (inWhite) {
					inWhite = false;
					//cout << "pushing " << j-1 << endl;
					splits.push_back(j-1);
				}
			}
		}
		splits.push_back(width);
		splits.push_back(0);

		vector<Letter *> letters;

		int prev = 0;
		for (l=0;l<splits.size();l+=2) {
			int w = splits[l]-prev;
			char *data = (char *)malloc(sizeof(char)*w*height*3);
			for (j=0;j<height*w*3;j++) {
				data[j] = -1;
			}
			for (j=0;j<height;j++) {
				for (k=0;k<w;k++) {
					int index = (j*w+k)*3;
					data[index] = image[k+prev][j][0];
					data[index+1] = image[k+prev][j][1];
					data[index+2] = image[k+prev][j][2];
				}
			}
			Letter *let = new Letter(w,height,data);
			letters.push_back(let);
			prev = splits[l+1];
		}

		outfile.open("output");
		for (l=0;l<letters.size();l++) {
			Letter *let = letters[l];
			char *image2 = let->pixels;
			for (j=0;j<let->height;j++) {
				for (k=0;k<let->width;k++) {
					int index = (j*let->width+k)*3;
					if (image2[index] != -1 || image2[index+1] != -1 || image2[index+2] != -1) {
						outfile << "*";
					} else {
						outfile << " ";
					}
				}
				outfile << endl;
			}
			outfile << endl;
		}
		outfile.close();
	}
	//cout << "height: " << image.size() << " width: " << image[0].size() << endl;
}
