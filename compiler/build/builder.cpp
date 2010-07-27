#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include "files.h"

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

	// 0=none, 1=sprites, 2=objects, 3=object, 4=object action, 5=rooms, 6=room, 7=room instances

	char input;
	int state = 0;
	string objectName = "";
	string actionName = "";
	string roomName = "";
	map<string,string> actionMap;
	bool readName = false;
	bool readColors = false;
	string code = "";
	int objectCount = 0;
	vector<string> instances;
	string roomColors = "";
	string instanceString = "";
	// common.h
	string objectDefinitions = "";
	// engine.cpp
	string objectTypes = "";
	string createRooms = "";
	// common.cpp
	string objectCreation = "";
	// Makefile
	string extraFiles = "";
	// Objects.h
	string objectIncludes = "";
	// Rooms.h
	string roomIncludes = "";
	while (infile.read(&input,1)) {
		//infile.seekg(1,ios_base::cur);
		if (input < 8) {
			if (state == 6 && instanceString != "") {
				instances.push_back(instanceString);
				instanceString = "";
			} else if (state == 4 && actionName != "") {
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
				readName = false;
			} else if (state == 5 && roomName != "") {
				cout << "creating new room!" << endl;
				bool buildH = false;
				bool buildCpp = false;
				string className = roomName;

				string fileName = className + ".h";
				outfile.open(fileName.c_str());
				if (outfile.is_open()) {
					outfile << "#ifndef " << className << "HFILE\n";
					outfile << "#define " << className << "HFILE\n";
					outfile << "#include \"Room.h\"\n"; 
					outfile << "class " << className << " : public Room {\npublic:\n" << className << "(int i, string t, int w, int h, int sp=30);\nvoid initInstances();\n};\n";
					outfile << "#endif\n";
					buildH = true;
				} else {
					cout << "Couldn't open " << fileName << " for some reason\n";
				}
				outfile.close();
				fileName = className + ".cpp";
				outfile.open(fileName.c_str());
				if (outfile.is_open()) {
					vector<string> temptoks;
					Tokenize(roomColors,temptoks,",");
					outfile << "#include \"" << className << ".h\"\n";
					outfile << "#include \"Objects.h\"\n";
					outfile << "#include \"common.h\"\n";
					outfile << className << "::" << className << "(int i, string t, int w, int h, int sp) : Room(i,t,w,h,sp) {\nr=" << temptoks[0] << ";\ng=" << temptoks[1] << ";\nb=" << temptoks[2] << ";\ninitInstances();\n}\n";
					outfile << "void " << className << "::initInstances() {\n";
					for (i=0;i<instances.size();i++) {
						temptoks.clear();
						Tokenize(instances[i],temptoks,",");
						outfile << "instance_create(" << temptoks[0] << "," << temptoks[1] << "," << temptoks[2] << ");\n";
					}
					outfile << "}\n";
					buildCpp = true;
				} else {
					cout << "Couldn't open " << fileName << " for some reason\n";
				}
				roomName = "";
				roomColors = "";
				instances.clear();
				readName = false;
				readColors = false;
				outfile.close();
				roomIncludes += "#include \"" + className + ".h\"\n";
				extraFiles += className + ".h " + className + ".cpp ";
				createRooms += "Engine::roomref.push_back(new " + className + "(0,\"" + roomName + "\",800,600));";
			} else if (state == 7) {
				instanceString = "";
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
			} else if (state == 6) {
				if (!readName) {
					if (input == '\n') {
						readName = true;
					} else {
						roomName += input;
					}
				} else if (!readColors) {
					if (input == '\n') {
						readColors = true;
					} else {
						roomColors += input;
					}
				}
			} else if (state == 7) {
				if (input == '\n') {
					if (instanceString != "") {
						instances.push_back(instanceString);
					}
					instanceString = "";
				} else {
					instanceString += input;
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
			if (output.find("/* -- ROOM INCLUDES -- */") != string::npos) {
				output.replace(output.find("/* -- ROOM INCLUDES -- */"),25,roomIncludes);
			}
			if (output.find("/* -- CREATE ROOMS -- */") != string::npos) {
				output.replace(output.find("/* -- CREATE ROOMS -- */"),25,createRooms);
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
