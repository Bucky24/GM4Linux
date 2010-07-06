#include <fstream>
#include <iostream>

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
	while (infile.read(&input,1)) {
		infile.seekg(1,ios_base::cur);
		cout << (int)input << input << endl;
	}

	return 0;
}
