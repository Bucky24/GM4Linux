#include <fstream>
#include <iostream>
#include <string>

using namespace std;

string stripStuff(string input) {
	string output = input;
	unsigned int i;
	for (i=0;i<output.size();i++) {
		if (output[i] == '\t') {
			output[i] = ' ';
		} else if (output[i] == '"') {
			output[i] = '\\';
			output.insert(i+1,"\"");
			i++;
		}
	}
	return output;
}

int main(int argc, char **argv) {
	if (argc < 2) {
		cout << "Usage: pack <filename>\n";
		return 1;
	}
	unsigned int i;
	ifstream infile;
	ofstream outfile;

	for (i=1;i<argc;i++) {
		infile.open(argv[i]);
		string outname = argv[i];
		outname += ".pack";
		outfile.open(outname.c_str());

		string line;
		while (!infile.eof()) {
			getline(infile,line);
			line = stripStuff(line);
			if (line[0] == '#' || (line[0] == '/' && line[1] == '/')) {
				line += "\\n";
			}
			outfile << line;
		}

		infile.close();
		outfile.close();
	}
	return 0;
}
