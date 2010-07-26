#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
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
	int objectCount = 0;
	// common.h
	string objectDefinitions = "";
	// engine.cpp
	string objectTypes = "";
	// common.cpp
	string objectCreation = "";
	// Makefile
	string extraFiles = "";
	// Objects.h
	string objectIncludes = "";
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
					outfile << "class " << className << " : public Object {\npublic:\n" << className << "(int, ObjectType *, float, float);\n";
					map<string,string>::iterator itor;
					for (itor=actionMap.begin();itor!=actionMap.end();itor++) {
						outfile << "void " << itor->first << "();\n";
					}
					outfile << "};\n#endif\n";
					outfile.close();
					buildH = true;
					extraFiles += objectFileName + " ";
				} else {
					cout << "Can't open " << objectFileName << " for some reason or another\n";
				}
				objectFileName = className + ".cpp";
				outfile.open(objectFileName.c_str());
				if (outfile.is_open()) {
					outfile << "#include \"" << className << ".h\"\n";
					outfile << "#include \"common.h\"\n"; 
					outfile << className << "::" << className << "(int i, ObjectType *obj, float x, float y) : Object(i,obj,x,y) {\ncreate();\n}\n";
					map<string,string>::iterator itor;
					for (itor=actionMap.begin();itor!=actionMap.end();itor++) {
						outfile << "void " << className << "::" << itor->first << "() {\n";
						outfile << itor->second;
						outfile << "}\n";
					}
					outfile.close();
					buildCpp = true;
					extraFiles += objectFileName + " ";
				} else {
					cout << "Can't open " << objectFileName << "for some reason or another\n";
				}

				if (!buildH || !buildCpp) {
					cout << "Could not write " << objectName << ".\n";
					return 1;
				}
				stringstream out;
				out << objectCount;
				string count = out.str();

				objectDefinitions += "#define " + objectName + " " + count + "\n";

				objectTypes += "objectref.push_back(new ObjectType(" + count + ",\"" + objectName + "\",-4));\n";

				objectCreation += "if (id == " + objectName + ") {\ninst = new " + className + "(Engine::instanceid,object,x,y);\n}\n";

				objectIncludes += "\n#include \"" + className + ".h\"\n";

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

	// begin output of files.
	map<string,string*>::iterator itor;
	for (itor=files.begin();itor!=files.end();itor++) {
		string fileName = itor->first;
		for (i=0;i<fileName.size();i++) {
			if (fileName[i] == '_') {
				fileName[i] = '.';
			}
		}
		outfile.open(fileName.c_str());
		if (outfile.is_open()) {
			string output = *(itor->second);
			// now insert certain sections of code
			if (output.find("/* -- OBJECT DEFINITIONS -- */") != string::npos) {
				output.replace(output.find("/* -- OBJECT DEFINITIONS -- */"),30,objectDefinitions);
			}
			if (output.find("/* -- CREATE OBJECT TYPES -- */") != string::npos) {
				output.replace(output.find("/* -- CREATE OBJECT TYPES -- */"),31,objectTypes);
			}
			if (output.find("/* -- OBJECT CREATION -- */") != string::npos) {
				output.replace(output.find("/* -- OBJECT CREATION -- */"),27,objectCreation);
			}
			if (output.find("EXTRA_FILES = ") != string::npos) {
				output.replace(output.find("EXTRA_FILES = "),14,"EXTRA_FILES = "+extraFiles+"\n");
			}
			if (output.find("/* -- OBJECT INCLUDES -- */") != string::npos) {
				output.replace(output.find("/* -- OBJECT INCLUDES -- */"),27,objectIncludes);
			}
			outfile << output;
			outfile.close();
		} else {
			cout << "Can't open " << itor->first << "for some reason or another\n";
			return 1;
		}
	}	

	return 0;
}
