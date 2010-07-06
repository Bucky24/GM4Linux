#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

void writeString(ofstream &out, const char *str, int count) {
	int i;
	for (i=0;i<count;i++) {
		char c = str[i];
		out.write(&c,1);
		out.seekp(1,ios_base::cur);
	}
	char c = 10;
	out.write(&c,1);
	out.seekp(1,ios_base::cur);
}

int main(int argc, char **argv) {

	if (argc < 2) {
		cout << "Usage: compiler file_name" << endl;
		return 0;
	}

	unsigned int i;

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
	int state = 0; // 0=none, 1=sprites, 2=objects, 3=object, 4=object action, 5=rooms, 6=room, 7=room instances
	int secondState = 0;

	string objectName;
	int objectSprite;
	vector< vector<string> *> actions;
	while (!infile.eof()) {
		getline(infile,line);
		if (state == 0 && line == "[sprites]") {
			state = 1;
			secondState = 0;
			char s = (char)state;
			outfile.write(&s,1);
			outfile.seekp(1,ios_base::cur);
		} else if (state == 0 && line == "[objects]") {
			state = 2;
			secondState = 0;
			char s = (char)state;
			outfile.write(&s,1);
			outfile.seekp(1,ios_base::cur);
		} else if (state == 0 && line == "[rooms]") {
			state = 5;
			secondState = 0;
			char s = (char)state;
			outfile.write(&s,1);
			outfile.seekp(1,ios_base::cur);
		} else if (state == 1 && line == "[/sprites]") {
			state = 0;
			secondState = 0;
			char s = (char)state;
			outfile.write(&s,1);
			outfile.seekp(1,ios_base::cur);
		} else if (state == 2 && line == "[/objects]") {
			state = 0;
			secondState = 0;
			char s = (char)state;
			outfile.write(&s,1);
			outfile.seekp(1,ios_base::cur);
		} else if (state == 5 && line == "[/rooms]") {
			state = 0;
			secondState = 0;
			char s = (char)state;
			outfile.write(&s,1);
			outfile.seekp(1,ios_base::cur);
		} else if (state == 2 && line == "[object]") {
			state = 3;
			secondState = 0;
			objectName = "";
			objectSprite = 0;
			for (i=0;i<actions.size();i++) {
				delete actions[i];
			}
			actions.clear();
			char s = (char)state;
			outfile.write(&s,1);
			outfile.seekp(1,ios_base::cur);
		} else if (state == 5 && line == "[room]") {
			state = 6;
			secondState = 0;
			char s = (char)state;
			outfile.write(&s,1);
			outfile.seekp(1,ios_base::cur);
		} else if (state == 3 && line == "[/object]") {
			state = 2;
			secondState = 0;
			cout << objectName << endl;
			writeString(outfile,objectName.c_str(),objectName.size());
			char s = (char)objectSprite;
			outfile.write(&s,1);
			outfile.seekp(1,ios_base::cur);
			s = (char)state;
			outfile.write(&s,1);
			outfile.seekp(1,ios_base::cur);
		} else if (state == 6 && line == "[/room]") {
			state = 5;
			secondState = 0;
			char s = (char)state;
			outfile.write(&s,1);
			outfile.seekp(1,ios_base::cur);
		} else if (state == 3 && line == "[action]") {
			state = 4;
			secondState = 0;
			actions.push_back(new vector<string>);
			char s = (char)state;
			outfile.write(&s,1);
			outfile.seekp(1,ios_base::cur);
		} else if (state == 4 && line == "[/action]") {
			state = 3;
			secondState = 0;
			char s = (char)state;
			outfile.write(&s,1);
			outfile.seekp(1,ios_base::cur);
		} else if (state == 6 && line == "[instances]") {
			state = 7;
			secondState = 0;
			char s = (char)state;
			outfile.write(&s,1);
			outfile.seekp(1,ios_base::cur);
		} else if (state == 7 && line == "[/instances]") {
			state = 6;
			secondState = 0;
			char s = (char)state;
			outfile.write(&s,1);
			outfile.seekp(1,ios_base::cur);
		} else {
			if (state == 3) {
				if (secondState == 0) {
					objectName = line;
					secondState = 1;
				} else if (secondState == 1) {
					objectSprite = atoi(line.c_str());
				}
			} else if (state == 4) {
				actions[actions.size()-1]->push_back(line);
			}
		}
		cout << state << " " << line << endl;
	}

	infile.close();
	outfile.close();
	
	return 0;
}
