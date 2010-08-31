#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cassert>

using namespace std;

void writeBitmapData(string, ofstream &);

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

void writeString(ofstream &out, const char *str, int count) {
	int i;
	for (i=0;i<count;i++) {
		char c = str[i];
		out.write(&c,1);
		//out.seekp(1,ios_base::cur);
	}
	//char c = 10;
	//out.write(&c,1);
	//out.seekp(1,ios_base::cur);
}

int main(int argc, char **argv) {

	if (argc < 2) {
		cout << "Usage: compiler file_name" << endl;
		return 0;
	}

	//unsigned int i;

	ofstream outfile;
	ifstream infile;

	string gamefile = argv[1];
	gamefile += ".gam";
	infile.open(gamefile.c_str());

	if (!infile.is_open()) {
		cout << "Unable to open file for reading\n";
		return 0;
	}

	string datfile = argv[1];
	datfile += ".dat";
	outfile.open(datfile.c_str(),ios::out | ios::binary);
	
	if (!outfile.is_open()) {
		cout << "Unable to open file for writing\n";
	}

	string line;
	int state = 0; // 0=none, 1=sprites, 2=objects, 3=object, 4=object action, 5=rooms, 6=room, 7=room instances, 8=fonts
	int secondState = 0;

	string objectName;
	int objectSprite;
	string spriteName;
	string r,g,b;
	while (!infile.eof()) {
		getline(infile,line);
		// cut off newline
		if (state == 0 && line == "[sprites]") {
			state = 1;
			secondState = 0;
			char s = (char)state;
			outfile.write(&s,1);
			//outfile.seekp(1,ios_base::cur);
		} else if (state == 0 && line == "[objects]") {
			state = 2;
			secondState = 0;
			char s = (char)state;
			outfile.write(&s,1);
			//outfile.seekp(1,ios_base::cur);
		} else if (state == 0 && line == "[rooms]") {
			state = 5;
			secondState = 0;
			char s = (char)state;
			outfile.write(&s,1);
			//outfile.seekp(1,ios_base::cur);
		} else if (state == 1 && line == "[/sprites]") {
			state = 0;
			secondState = 0;
			char s = (char)state;
			outfile.write(&s,1);
			//outfile.seekp(1,ios_base::cur);
		} else if (state == 2 && line == "[/objects]") {
			state = 0;
			secondState = 0;
			char s = (char)state;
			outfile.write(&s,1);
			//outfile.seekp(1,ios_base::cur);
		} else if (state == 5 && line == "[/rooms]") {
			state = 0;
			secondState = 0;
			char s = (char)state;
			outfile.write(&s,1);
			//outfile.seekp(1,ios_base::cur);
		} else if (state == 2 && line == "[object]") {
			state = 3;
			secondState = 0;
			objectName = "";
			objectSprite = 0;
			char s = (char)state;
			outfile.write(&s,1);
			//outfile.seekp(1,ios_base::cur);
		} else if (state == 5 && line == "[room]") {
			state = 6;
			secondState = 0;
			char s = (char)state;
			outfile.write(&s,1);
			//outfile.seekp(1,ios_base::cur);
		} else if (state == 3 && line == "[/object]") {
			state = 2;
			secondState = 0;
			char s = (char)state;
			outfile.write(&s,1);
			//outfile.seekp(1,ios_base::cur);
		} else if (state == 6 && line == "[/room]") {
			state = 5;
			secondState = 0;
			char s = (char)state;
			outfile.write(&s,1);
			//outfile.seekp(1,ios_base::cur);
		} else if (state == 3 && line == "[action]") {
			state = 4;
			secondState = 0;
			char s = (char)state;
			outfile.write(&s,1);
			//outfile.seekp(1,ios_base::cur);
		} else if (state == 4 && line == "[/action]") {
			state = 3;
			secondState = 0;
			char s = (char)state;
			outfile.write(&s,1);
			//outfile.seekp(1,ios_base::cur);
		} else if (state == 6 && line == "[instances]") {
			state = 7;
			secondState = 0;
			char s = (char)state;
			outfile.write(&s,1);
			//outfile.seekp(1,ios_base::cur);
		} else if (state == 7 && line == "[/instances]") {
			state = 6;
			secondState = 0;
			char s = (char)state;
			outfile.write(&s,1);
			//outfile.seekp(1,ios_base::cur);
		} else if (state == 0 && line == "[fonts]") {
			state = 8;
			char s = (char)state;
			outfile.write(&s,1);
		} else if (state == 8 && line == "[/fonts]") {
			state = 0;
			char s = (char)state;
			outfile.write(&s,1);
		} else {
			if (state == 1) {
				spriteName = line;
				writeBitmapData(spriteName,outfile);
			} else if (state == 3) {
				if (secondState == 0) {
					objectName = line;
					secondState = 1;
					writeString(outfile,objectName.c_str(),objectName.size());
				} else if (secondState == 1) {
					objectSprite = atoi(line.c_str());
					char s = (char)objectSprite;
					outfile.write(&s,1);
					//outfile.seekp(1,ios_base::cur);
				}
			} else if (state == 4) {
				line += "\n";
				writeString(outfile,line.c_str(),line.size());
			} else if (state == 6) {
				if (secondState == 0) {
					objectName = line;
					writeString(outfile,line.c_str(),line.size());
					char s = '\n';
					outfile.write(&s,1);
					secondState = 1;
				} else if (secondState == 1) {
					writeString(outfile,line.c_str(),line.size());
					char s = '\n';
					outfile.write(&s,1);
					secondState = 2;
				} else if (secondState == 2) {
					writeString(outfile,line.c_str(),line.size());
					char s = '\n';
					outfile.write(&s,1);
					secondState = 3;
				}
			} else if (state == 7) {
				writeString(outfile,line.c_str(),line.size());
				char s = '\n';
				outfile.write(&s,1);
			} else if (state == 8) {
				writeString(outfile,line.c_str(),line.size());
				char s = '\n';
				outfile.write(&s,1);
			}
		}
		//cout << state << " " << line << endl;
	}

	infile.close();
	outfile.close();
	
	return 0;
}


namespace {
	//Converts a four-character array to an integer, using little-endian form
	int toInt(const char* bytes) {
		return (int)(((unsigned char)bytes[3] << 24) |
					 ((unsigned char)bytes[2] << 16) |
					 ((unsigned char)bytes[1] << 8) |
					 (unsigned char)bytes[0]);
	}
	
	//Converts a two-character array to a short, using little-endian form
	short toShort(const char* bytes) {
		return (short)(((unsigned char)bytes[1] << 8) |
					   (unsigned char)bytes[0]);
	}
	
	//Reads the next four bytes as an integer, using little-endian form
	int readInt(ifstream &input) {
		char buffer[4];
		input.read(buffer, 4);
		return toInt(buffer);
	}
	
	//Reads the next two bytes as a short, using little-endian form
	short readShort(ifstream &input) {
		char buffer[2];
		input.read(buffer, 2);
		return toShort(buffer);
	}
	
	//Just like auto_ptr, but for arrays
	template<class T>
	class auto_array {
		private:
			T* array;
			mutable bool isReleased;
		public:
			explicit auto_array(T* array_ = NULL) :
				array(array_), isReleased(false) {
			}
			
			auto_array(const auto_array<T> &aarray) {
				array = aarray.array;
				isReleased = aarray.isReleased;
				aarray.isReleased = true;
			}
			
			~auto_array() {
				if (!isReleased && array != NULL) {
					delete[] array;
				}
			}
			
			T* get() const {
				return array;
			}
			
			T &operator*() const {
				return *array;
			}
			
			void operator=(const auto_array<T> &aarray) {
				if (!isReleased && array != NULL) {
					delete[] array;
				}
				array = aarray.array;
				isReleased = aarray.isReleased;
				aarray.isReleased = true;
			}
			
			T* operator->() const {
				return array;
			}
			
			T* release() {
				isReleased = true;
				return array;
			}
			
			void reset(T* array_ = NULL) {
				if (!isReleased && array != NULL) {
					delete[] array;
				}
				array = array_;
			}
			
			T* operator+(int i) {
				return array + i;
			}
			
			T &operator[](int i) {
				return array[i];
			}
	};
}

void writeBitmapData(string filename, ofstream &output) {
	ifstream input;
	input.open(filename.c_str(), ifstream::binary);
	assert(!input.fail() || !"Could not find file");
	char buffer[2];
	input.read(buffer, 2);
	assert((buffer[0] == 'B' && buffer[1] == 'M') || !"Not a bitmap file");
	input.ignore(8);
	int dataOffset = readInt(input);
	
	//Read the header
	int headerSize = readInt(input);
	int width;
	int height;
	switch(headerSize) {
		case 40:
			//V3
			width = readInt(input);
			height = readInt(input);
			input.ignore(2);
			assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
			assert(readShort(input) == 0 || !"Image is compressed");
			break;
		case 12:
			//OS/2 V1
			width = readShort(input);
			height = readShort(input);
			input.ignore(2);
			assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
			break;
		case 64:
			//OS/2 V2
			assert(!"Can't load OS/2 V2 bitmaps");
			break;
		case 108:
			//Windows V4
			assert(!"Can't load Windows V4 bitmaps");
			break;
		case 124:
			//Windows V5
			assert(!"Can't load Windows V5 bitmaps");
			break;
		default:
			assert(!"Unknown bitmap format");
	}
	
	//Read the data
	int bytesPerRow = ((width * 3 + 3) / 4) * 4 - (width * 3 % 4);
	int size = bytesPerRow * height;
	auto_array<char> pixels(new char[size]);
	input.seekg(dataOffset, ios_base::beg);
	input.read(pixels.get(), size);
	
	//Get the data into the right format
	auto_array<char> pixels2(new char[width * height * 3]);
	for(int y = 0; y < height; y++) {
		for(int x = 0; x < width; x++) {
			for(int c = 0; c < 3; c++) {
				pixels2[3 * (width * y + x) + c] =
					pixels[bytesPerRow * y + 3 * x + (2 - c)];
			}
		}
	}
	
	input.close();
	char *myPixels = pixels2.release();

	writeString(output,filename.c_str(),filename.size());
	char tmp = 0;
	output.write(&tmp,1);
	char byte1 = width/256;
	char byte2 = width-(((int)byte1)*256);
	output.write(&byte1,1);
	output.write(&byte2,1);
	byte1 = height/256;
	byte2 = height-(((int)byte1)*256);
	output.write(&byte1,1);
	output.write(&byte2,1);

	output.write(myPixels,width*height*3);
}
