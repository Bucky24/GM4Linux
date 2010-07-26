#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "files.h"

using namespace std;

int main(int argc, char **argv) {
	if (argc < 2) {
		cout << "Usage: builder file_name\n";
		return 0;
	}

	ifstream infile;
	infile.open(argv[1],ios::in | ios::binary);

	ofstream outfile;

	if (!infile.is_open()) {
		cout << "Could not open file\n";
		return 0;
	}

	unsigned int i;

	initFiles();

	infile.seekg(0);

	char input;
	int state = 0;
	string objectName = "";
	string actionName = "";
	map<string,string> actionMap;
	bool readName = false;
	string code = "";
	string objectCount = 0;
	// common.h
	string objectDefinitions = "";
	// engine.cpp
	string objectTypes = "";
	// common.cpp
	string objectCreation = "";
	while (infile.read(&input,1)) {
		//infile.seekg(1,ios_base::cur);
		if (input < 8) {
			if (state == 3 && objectName != "") {
				cout << objectName << endl;
			} else if (state == 4 && actionName != "") {
				cout << actionName << endl;
				cout << code;
				actionMap.insert(pair<string,string>(actionName,code));
			}
			state = input;
			cout << "new state " << state << endl;
			if (state == 4) {
				actionName = "";
				code = "";
				readName = false;
			} else if (state == 2 && objectName != "") {
				cout << "creating new object\n";
				bool buildH = false;
				bool buildCpp = false;
				string className = "obj_" + objectName;
				string objectFileName = className + ".h";
				outfile.open(objectFileName.c_str());
				if (outfile.is_open()) {
					outfile << "#ifndef " << objectName << "HFILE\n";
					outfile << "#define " << objectName << "HFILE\n";
					outfile << "#include \"Object.h\"\n";
					outfile << "class " << className << " : public Object {\npublic:\n" << objectName << "(int, ObjectType *, float, float);\n";
					map<string,string>::iterator itor;
					for (itor=actionMap.begin();itor!=actionMap.end();itor++) {
						outfile << "void " << itor->first << "();\n";
					}
					outfile << "};\n#endif\n";
					outfile.close();
					buildH = true;
				} else {
					cout << "Can't open " << objectFileName << " for some reason or another\n";
				}
				objectFileName = className + ".cpp";
				outfile.open(objectFileName.c_str());
				if (outfile.is_open()) {
					outfile << "#include \"" << className << ".h\"\n";
					outfile << className << "::" << className << "(int i, ObjectType *obj, float x, float y) : Object(i,obj,x,y) {\ncreate();\n}\n";
					map<string,string>::iterator itor;
					for (itor=actionMap.begin();itor!=actionMap.end();itor++) {
						outfile << "void " << className << "::" << itor->first << "() {\n";
						outfile << itor->second;
						outfile << "}\n";
					}
					outfile.close();
					buildCpp = true;
				} else {
					cout << "Can't open " << objectFileName << "for some reason or another\n";
				}

				if (!buildH || !buildCpp) {
					cout << "Could not write " << objectName << ".\n";
					return 1;
				}
				objectDefinitions += "#define " << objectName << " " << objectCount << "\n";

				objectTypes += "objectref.push_back(new ObjectType(" << objectCount << "," << objectName << ",-4));\n";

				objectCreation += "if (id == " << objectName << ") {\ninst = new " << className << "(Engine::instanceid,object,x,y);\n}\n";

				objectCount ++;
				
				objectName = "";
				actionMap.clear();
			}
		} else {
			if (state == 3) {
				objectName += input;
				//cout << (int)input << input << endl;
			} else if (state == 4) {
				if (!readName) {
					if (input == '\n') {
						readName = true;
					} else {
						actionName += input; 
					}
				} else {
					code += input;
				}
			}
		}
	}
	return 0;
}
