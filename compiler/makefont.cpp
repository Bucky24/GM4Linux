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

void Tokenize(const string& str,
                      vector<string>& tokens,
                      const string& delimiters = " ")
{
    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}

int main(int argc, char **argv) {
	if (argc < 2) {
		//cout << "Usage: makefont <input images>" << endl;
	}

	ofstream outfile;
	ifstream infile;
	char input;
	int state = 0;
	unsigned char r, g, b;
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
		//cout << lines << endl;

		// print
		for (j=0;j<height;j++) {
			for (k=0;k<width;k++) {
				if (image[k][j][0] != -1 || image[k][j][1] != -1 || image[k][j][2] != -1) {
					//cout << "*";
				} else {
					//cout << " ";
				}
			}
			//cout << endl;
		}
		// end print

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

		//cout << remove << endl;
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

		int avgw=0,avgh=0;

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

					//cout << "l: " << l << " " << k << "," << j << " " << (int)(unsigned char)image[k+prev][j][0] << "," << (int)(unsigned char)image[k+prev][j][1] << "," << (int)(unsigned char)image[k+prev][j][2] << endl;
				}
			}
			Letter *let = new Letter(w,height,data);
			letters.push_back(let);
			prev = splits[l+1];
			avgw += w;
			avgh += height;
			//cout << endl << endl;
		}

		avgw /= splits.size();
		avgh /= splits.size();

		avgh = height;
		avgw = 6;

		// add in the space
		char *data = (char *)malloc(sizeof(char)*avgw*avgh*3);
		for (j=0;j<avgh*avgw*3;j++) {
			data[j] = -1;
		}
		for (j=0;j<avgh;j++) {
			for (k=0;k<avgw;k++) {
				int index = (j*avgw+k)*3;
				data[index] = 255;
				data[index+1] = 255;
				data[index+2] = 255;
			}
		}
		Letter *let = new Letter(avgw,avgh,data);
		letters.push_back(let);

		// now format for font thingy
		// first byte is width
		// second is height
		// third is the ASCII value of the character
		// then letter data
		// then next height, width, data, ect
		// letters in the following order a-zA-z

		vector<char> letterVec;
		letterVec.push_back('a');
		letterVec.push_back('b');
		letterVec.push_back('c');
		letterVec.push_back('d');
		letterVec.push_back('e');
		letterVec.push_back('f');
		letterVec.push_back('g');
		letterVec.push_back('h');
		letterVec.push_back('i');
		letterVec.push_back('j');
		letterVec.push_back('k');
		letterVec.push_back('l');
		letterVec.push_back('m');
		letterVec.push_back('n');
		letterVec.push_back('o');
		letterVec.push_back('p');
		letterVec.push_back('q');
		letterVec.push_back('r');
		letterVec.push_back('s');
		letterVec.push_back('t');
		letterVec.push_back('u');
		letterVec.push_back('v');
		letterVec.push_back('w');
		letterVec.push_back('x');
		letterVec.push_back('y');
		letterVec.push_back('z');
		letterVec.push_back('A');
		letterVec.push_back('B');
		letterVec.push_back('C');
		letterVec.push_back('D');
		letterVec.push_back('E');
		letterVec.push_back('F');
		letterVec.push_back('G');
		letterVec.push_back('H');
		letterVec.push_back('I');
		letterVec.push_back('J');
		letterVec.push_back('K');
		letterVec.push_back('L');
		letterVec.push_back('M');
		letterVec.push_back('N');
		letterVec.push_back('O');
		letterVec.push_back('P');
		letterVec.push_back('Q');
		letterVec.push_back('R');
		letterVec.push_back('S');
		letterVec.push_back('T');
		letterVec.push_back('U');
		letterVec.push_back('V');
		letterVec.push_back('W');
		letterVec.push_back('X');
		letterVec.push_back('Y');
		letterVec.push_back('Z');
		letterVec.push_back('1');
		letterVec.push_back('2');
		letterVec.push_back('3');
		letterVec.push_back('4');
		letterVec.push_back('5');
		letterVec.push_back('6');
		letterVec.push_back('7');
		letterVec.push_back('8');
		letterVec.push_back('9');
		letterVec.push_back('0');
		letterVec.push_back('[');
		letterVec.push_back(']');
		letterVec.push_back('/');
		letterVec.push_back('-');
		letterVec.push_back('+');
		letterVec.push_back('=');
		letterVec.push_back('(');
		letterVec.push_back(')');
		letterVec.push_back(',');
		letterVec.push_back('.');
		letterVec.push_back(';');
		letterVec.push_back('*');
		letterVec.push_back(' ');

		// get output name
		string outname = argv[i];
		vector<string> toks;
		Tokenize(outname,toks,".");
		outname = toks[0];
		outname += ".font";

		outfile.open(outname.c_str(), ios::out | ios::binary);
		for (l=0;l<1/*letters.size()*/;l++) {
			//cout << l << endl;
			Letter *let = letters[l];
			char *image2 = let->pixels;
			char c;
			//c = let->width;
			c = 32;
			outfile.write(&c,1);
			//c = let->height;
			c = 32;
			outfile.write(&c,1);
			c = letterVec[l];
			outfile.write(&c,1);
			//cout << "wrote '" << c << "'" <<  endl;
			for (j=0;j<let->height;j++) {
				for (k=0;k<let->width;k++) {
					int index = (j*let->width+k)*3;
					c = image2[index];
					outfile.write(&c,1);
					c = image2[index+1];
					outfile.write(&c,1);
					c = image2[index+2];
					outfile.write(&c,1);
					//if (letterVec[l] == 'A') {
					//	//cout << k << "," << j << " " << (int)(unsigned char)image2[index] << "," << (int)(unsigned char)image2[index+1] << "," << (int)(unsigned char)image2[index+2] << endl;
					//}
				}
			}
		}
		outfile.close();
	}
	//cout << "height: " << image.size() << " width: " << image[0].size() << endl;
}
