#include <fstream>
#include <vector>
#include <iostream>
#include <cstdlib>

using namespace std;

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

int byteToInt(int n1, int n2) {
        return n1+n2*256;
}

int main(int argc, char **argv) {
	if (argc < 4) {
		cout << "Usage: makefont2 <bitmap> width height" << endl;
		return 1;
	}

	int i,j,k,l;

	int letterWidth = atoi(argv[2]);
	int letterHeight = atoi(argv[3]);

	Image *image = loadImage(argv[1]);

	int letterCount = image->width/letterWidth;

	char letters[letterCount][letterHeight][letterWidth][3];

	cout << letterCount << " letters." << endl;

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

	if (letterCount > letterVec.size()) {
		letterCount = letterVec.size();
	}

	for (i=0;i<letterCount;i++) {
		cout << "loading " << letterVec[i] << " " << i << endl;
		for (k=0;k<letterHeight;k++) {
			for (j=0;j<letterWidth;j++) {
				letters[i][k][j][0] = image->pixels[(i*letterWidth+j)*letterHeight*3+k*3+0];
				letters[i][k][j][1] = image->pixels[(i*letterWidth+j)*letterHeight*3+k*3+1];
				letters[i][k][j][2] = image->pixels[(i*letterWidth+j)*letterHeight*3+k*3+2];
				cout << (int)letters[i][k][j][0] << " " << (int)letters[i][k][j][1] << " " << (int)letters[i][k][j][2] << " " << (i*letterWidth+j)*letterHeight*3+k*3 << " " << j << " " << k << endl;
			}
		}
	}

	//cout << "loading complete " << endl;

	string outname = argv[1];
	vector<string> toks;
	Tokenize(outname,toks,".");
	outname = toks[0];
	outname += ".font";

	ofstream outfile;
	outfile.open(outname.c_str(), ios::out | ios::binary);
	for (l=0;l<letterCount;l++) {

		cout << "saving " << letterVec[l] << endl;
		//cout << l << endl;
		char c;
		//c = let->width;
		c = letterWidth;
		outfile.write(&c,1);
		//c = let->;
		c = letterHeight;
		outfile.write(&c,1);
		c = letterVec[l];
		outfile.write(&c,1);
		for (j=0;j<letterHeight;j++) {
			for (k=0;k<letterWidth;k++) {
				c = letters[l][j][k][0];
				outfile.write(&c,1);
				c = letters[l][j][k][1];
				outfile.write(&c,1);
				c = letters[l][j][k][2];
				outfile.write(&c,1);
			}
		}
	}
	outfile.close();

	return 0;
}

Image *loadImage(char *filename) {
	ifstream infile;
	infile.open(filename,ios::in | ios::binary);
	char in1, in2;
	infile.seekg(28);
	infile.read(&in1,1);
	if (in1 != 24) {
		cout << "Image is not a 24-bit bitmap. Cannot load" << endl;
		exit(0);
	}
	infile.seekg(18);
	int i1, i2;
	infile.read(&in1,1);
	infile.read(&in2,1);
	i1 = in1;
	if (i1 < 0) i1 = 256+i1;
	i2 = in2;
	//cout << i1 << " " << i2 << endl;
	int width = byteToInt(i1,i2);
	int j,k;

	infile.seekg(22);
	infile.read(&in1,1);
	infile.read(&in2,1);
	i1 = in1;
	if (i1 < 0) i1 = 256+i1;
	i2 = in2;	
	//cout << i1 << " " << i2 << endl;
	int height = byteToInt(i1,i2);

	//cout << width << " " << height << endl;

	//cout << "allocating image memory of " << width << "x" << height << "x3" <<  endl;
	char *image = (char *)malloc(sizeof(char)*width*height*3);
	//cout << "generating image map " << endl;

	for (j=0;j<width;j++) {
		for (k=0;k<height;k++) {
			//cout << j <<  " " << k << " " << j*height*3+k*3+0 <<  endl;
			image[j*height*3+k*3+0] = 255;
			image[j*height*3+k*3+1] = 255;
			image[j*height*3+k*3+2] = 255;
		}
	}

	int four = width;
	while (four % 4 != 0) four --;
	int pad = width-four;

	//cout << "four: " << four << endl;

	infile.seekg(54);
	int count = 0;
	int lines = 0;
	int state = 0;
	char input;

	char r,g,b;

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
				cout << infile.tellg() << " " << count/3 << "," << lines << " " << (int)r << "," << (int)g << "," << (int)b << " " << (count/3)*height*3+(lines)*3 << endl;
				image[(count/3)*height*3+(lines)*3+0] = r;
				image[(count/3)*height*3+(lines)*3+1] = g;
				image[(count/3)*height*3+(lines)*3+2] = b;
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
