#include <fstream>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>

using namespace std;

int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

int main(int argc, char **argv) {
	if (argc < 2) {
		cout << "Usage: archive <file name>\n";
		return 1;
	}
	unsigned int i,j;
	ifstream infile;
	ofstream outfile;
	string outName = argv[1];
	string outPathH = outName + ".h";
	string outPathCpp = outName + ".cpp";

	outfile.open(outPathH.c_str());

	vector<string> files;
	getdir(".",files);

	outfile << "#ifndef " << outName << "H\n";
	outfile << "#define " << outName << "H\n";
	outfile << "#include <map>\n";
	outfile << "#include <string>\n";
	outfile << "using namespace std;\n";
	outfile << "extern map<string,string *> files;\n";

	for (i=0;i<files.size();i++) {
		string file = files[i];
		if (file.find(".pack") != string::npos) {
			char tmp[200];
			int length = file.copy(tmp,file.size()-5);
			tmp[length] = 0;
			string strName = tmp;
			for (j=0;j<strName.size();j++) {
				if (strName[j] == '.') {
					strName[j] = '_';
				}
			}
			outfile << "extern string " << strName << ";\n";
		}
	}
	outfile << "void initFiles();\n";

	outfile << "#endif\n";
	outfile.close();
	outfile.open(outPathCpp.c_str());
	outfile << "#include \"" << outPathH << "\"\n";
	outfile << "map<string,string *> files;\n";
	for (i=0;i<files.size();i++) {
		string file = files[i];
		if (file.find(".pack") != string::npos) {
			char tmp[200];
			int length = file.copy(tmp,file.size()-5);
			tmp[length] = 0;
			string strName = tmp;
			for (j=0;j<strName.size();j++) {
				if (strName[j] == '.') {
					strName[j] = '_';
				}
			}
			outfile << "string " << strName << ";\n";
		}
	}
	outfile << "void initFiles() {\n";
	outfile << "files = *(new map<string,string *>());\n";

	for (i=0;i<files.size();i++) {
		string file = files[i];
		//cout << file << endl;
		if (file.find(".pack") != string::npos) {
			infile.open(file.c_str());
			string line;
			char tmp[200];
			int length = file.copy(tmp,file.size()-5);
			tmp[length] = 0;
			string strName = tmp;
			for (j=0;j<strName.size();j++) {
				if (strName[j] == '.') {
					strName[j] = '_';
				}
			}
			//cout << strName << endl;
			outfile << strName << " = \"";
			while (!infile.eof()) {
				getline(infile,line);
				//cout << line;
				outfile << line;
			}
			outfile << "\";\n";
			outfile << "files.insert(pair<string,string*>(\"" << strName << "\",&" << strName << "));\n";
			infile.close();
			remove(file.c_str());
		}

	}
	outfile << "}\n";

	outfile.close();
	return 0;
}
