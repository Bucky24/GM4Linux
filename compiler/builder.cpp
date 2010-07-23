#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main(int argc, char **argv) {
	if (argc < 2) {
		cout << "Usage: builder file_name\n";
		return 0;
	}

	ifstream infile;
	infile.open(argv[1],ios::in | ios::binary);

	if (!infile.is_open()) {
		cout << "Could not open file\n";
		return 0;
	}

	infile.seekg(0);

	char input;
	int state = 0;
	string name = "";
	map<string,string> actionMap;
	while (infile.read(&input,1)) {
		//infile.seekg(1,ios_base::cur);
		if (input < 8) {
			if (state == 3 && name != "") {
				cout << name << endl;
			}
			state = input;
			cout << "new state " << state << endl;
			if (state == 3) {
				name = "";
			} else if (state == 4) {
				name = "";
				actionMap.clear();
			}
		} else {
			if (state == 3) {
				name += input;
				cout << (int)input << input << endl;
			} else if (state == 4
		}
	}
	return 0;
}
