#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include "files.h"
#include <cstdlib>

using namespace std;

class Object {
public:
	Object(string, map<string,string> *,int,int/*,string*/);
	string name;
	map<string,string> *actionMap;
	int sprite;
	int objectId;
	//string parent;
};

Object::Object(string n, map<string,string> *a, int s, int id/*, string p*/) {
	name = n;
	actionMap = a;
	sprite = s;
	objectId = id;
	//parent = p;
}

class Room {
public:
	Room(string, string, string, vector<string> *);
	string name;
	string colors;
	string size;
	vector<string> *instances;
};

Room::Room(string n, string c, string s, vector<string> *i) {
	name = n;
	colors = c;
	size = s;
	instances = i;
}

class Sprite {
public:
	Sprite(string, vector<char> *, float, float);
	string name;
	vector<char> *data;
	float width;
	float height;
};

Sprite::Sprite(string n, vector<char> *d, float w, float h) {
	name = n;
	data = d;
	width = w;
	height = h;
}

void buildReserved(vector<string> &);
bool isReserved(string word, vector<string> &vec);
string processCode(string code, vector<string>);

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

	unsigned int i, j,k,l;

	initFiles();

	infile.seekg(0);

	// 0=none, 1=sprites, 2=objects, 3=object, 4=object action, 5=rooms, 6=room, 7=room instances, 8=font

	char input;
	int state = 0;
	string objectName = "";
	string actionName = "";
	//string objectParent = "";
	string roomName = "";
	map<string,string> *actionMap = new map<string,string>;
	int objectSprite = -1;
	int objectId = -1;
	bool readName = false;
	bool readColors = false;
	string code = "";
	int objectCount = 0;
	vector<string> *instances = new vector<string>;
	string roomColors = "";
	string instanceString = "";
	string roomSize = "";
	bool readSize = false;
	string fontString = "";
	bool readSprite = false;
	bool readId = false;
	// common.h
	string objectDefinitions = "";
	// engine.cpp
	string objectTypes = "";
	string createRooms = "";
	string instanceMap = "";
	string createFonts = "string fontName;";
	string createImages = "";
	// common.cpp
	string objectCreation = "";
	// Makefile
	string extraFiles = "";
	// Objects.h
	string objectIncludes = "";
	// Rooms.h
	string roomIncludes = "";
	// sprites.cpp
	string spriteFileData = "";

	vector<Object *> objects;
	vector<Room *> rooms;
	vector<string> fonts;
	vector<Sprite *> sprites;
	
	vector<string> reserved;
	buildReserved(reserved);

	vector<char> spriteData;

	char data, data2;

	while (infile.read(&input,1)) {

		//infile.seekg(1,ios_base::cur);
		if (input < 9) {
			if (state == 6 && instanceString != "") {
				instances->push_back(instanceString);
				instanceString = "";
			} else if (state == 4 && actionName != "") {
				
				actionMap->insert(pair<string,string>(actionName,code));
			}
			state = input;
			//cout << "new state " << state << endl;
			if (state == 1) {
				spriteData = *(new vector<char>());
				
				while (infile.read(&data,1)) {
					if (data == 0) break;
					string name = "";
					while (true) {
						if (data == 0) break;
						name += data;
						//cout << name << " " << data << endl;
						infile.read(&data,1);
					}
					//cout << "here?" << endl;
					vector<char> *tempData = new vector<char>();
					//cout << "here " << endl;
					infile.read(&data,1);
					infile.read(&data2,1);
					int width = data*256+data2;
					infile.read(&data,1);
					infile.read(&data2,1);
					int height = data*256+data2;
					//cout << width*height*3+4 << endl;
					for (i=0;i<width*height*3;i++) {
						infile.read(&data,1);
						tempData->push_back(data);
					}
					Sprite *sprite = new Sprite(name,tempData,width,height);
					sprites.push_back(sprite);
				}
				state = 0;
			} else if (state == 4) {
				actionName = "";
				code = "";
				readName = false;
			} else if (state == 2 && objectName != "") {
				//cout << "new object" << endl;
				Object *obj = new Object(objectName,actionMap,objectSprite,objectId/*,objectParent*/);
				objects.push_back(obj);				

				objectName = "";
				//objectParent = "";
				actionMap = new map<string,string>();
				objectSprite = -1;
				objectId = 2;
				readName = false;
				readSprite = false;
				readId = false;
			} else if (state == 5 && roomName != "") {
				//cout << "new room" << endl;
				Room *rm = new Room(roomName,roomColors,roomSize,instances);
				rooms.push_back(rm);	
				roomName = "";
				roomColors = "";
				instances = new vector<string>();
				readName = false;
				readColors = false;
				readSize = false;
				roomSize = "";
			} else if (state == 7) {
				instanceString = "";
			}
		} else {
			if (state == 1) {
				spriteData.push_back(input);
			} else if (state == 3) {
				char input2;
				while (input != '\n') {
					objectName += input;
					infile.read(&input,1);
				}

				infile.read(&input,1);
				infile.read(&input2,1);
				objectSprite = input*256+input2;

				infile.read(&input,1);
				infile.read(&input2,1);
				objectId = input*256+input2;

				/*infile.read(&input,1);
				while (input != '\n') {
					objectParent += input;
					infile.read(&input,1);
				}*/
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
				//cout << (char)input << endl;
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
				} else if (!readSize) {
					if (input == '\n') {
						readSize = true;
					} else {
						roomSize += input;
					}
				}
			} else if (state == 7) {
				if (input == '\n') {
					if (instanceString != "") {
						instances->push_back(instanceString);
					}
					instanceString = "";
				} else {
					instanceString += input;
				}
			} else if (state == 8) {
				//cout << input << endl;
				if (input == '\n') {
					if (fontString != "") {
						//cout << "found font " << fontString << endl;
						fonts.push_back(fontString);
					}
					fontString = "";
				} else {
					fontString += input;
				}
			}
		}
	}

	// add object and room names to reserved list

	for (i=0;i<objects.size();i++) {
		reserved.push_back(objects[i]->name);
	}
	for (i=0;i<rooms.size();i++) {
		reserved.push_back(rooms[i]->name);
	}
	for (i=0;i<sprites.size();i++) {
		reserved.push_back(sprites[i]->name);
	}

	for (i=0;i<objects.size();i++) {
		objectName = objects[i]->name;
		actionMap = objects[i]->actionMap;
		objectSprite = objects[i]->sprite;
		objectId = objects[i]->objectId;
		//objectParent = objects[i]->parent;
		cout << "object " << objectName << endl;// << "<=" << objectParent << endl;
		bool buildH = false;
		bool buildCpp = false;
		string className = "obj_" + objectName;
		string objectFileName = className + ".h";
		outfile.open(objectFileName.c_str());
		if (outfile.is_open()) {
			outfile << "#ifndef " << objectName << "HFILE\n";
			outfile << "#define " << objectName << "HFILE\n";
			outfile << "#include \"Object.h\"\n";
			outfile << "class " << className << " : public Object {\npublic:\n" << className << "(int, float, float);\n";
			map<string,string>::iterator itor;
			for (itor=actionMap->begin();itor!=actionMap->end();itor++) {
				outfile << "void " << itor->first << "();\n";
			}
			outfile << "};\n#endif\n";
			outfile.close();
			buildH = true;
			//extraFiles += objectFileName + " ";
		} else {
			cout << "Can't open " << objectFileName << " for some reason or another\n";
		}
		objectFileName = className + ".cpp";
		outfile.open(objectFileName.c_str());
		if (outfile.is_open()) {
			outfile << "#include \"" << className << ".h\"\n";
			outfile << "#include \"common.h\"\n"; 
			outfile << className << "::" << className << "(int i, float x, float y) : Object(i,x,y) {\nname=\"" << objectName << "\";\nsprite=" << objectSprite << ";\nobjectId=" << objectId << ";\ncreate();\n}\n";
			map<string,string>::iterator itor;
			for (itor=actionMap->begin();itor!=actionMap->end();itor++) {
				string code = itor->second;
				code = processCode(code,reserved);
				outfile << "void " << className << "::" << itor->first << "() {\n";
				outfile << code;
				outfile << "}\n";
			}
			outfile.close();
			buildCpp = true;
			//extraFiles += objectFileName + " ";
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

		//objectTypes += "objectref.push_back(new ObjectType(" + count + ",\"" + objectName + "\",-4));\n";

		objectCreation += "if (id == " + objectName + ") {\ninst = new " + className + "(Engine::instanceid,x,y);\n}\n";

		objectIncludes += "\n#include \"" + className + ".h\"\n";

		extraFiles += className + ".h " + className + ".cpp ";

		//cout << "extras: " << extraFiles << endl;

		instanceMap += "instances->insert(pair<int,objlist *>(" + count + ",new objlist()));\n";

		objectCount ++;
	}
	
	for (i=0;i<rooms.size();i++) {
		roomName = rooms[i]->name;
		roomColors = rooms[i]->colors;
		instances = rooms[i]->instances;
		roomSize = rooms[i]->size;
		cout << "room " << roomName << endl;
		bool buildH = false;
		bool buildCpp = false;
		string className = "rm_" + roomName;

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
			outfile << className << "::" << className << "(int i, string t, int w, int h, int sp) : Room(i,t,w,h,sp) {\nr=" << temptoks[0] << ";\ng=" << temptoks[1] << ";\nb=" << temptoks[2] << ";\n}\n";
			outfile << "void " << className << "::initInstances() {\n";
			for (i=0;i<instances->size();i++) {
				temptoks.clear();
				Tokenize(instances->at(i),temptoks,",");
				outfile << "instance_create(" << temptoks[0] << "," << temptoks[1] << "," << temptoks[2] << ");\n";
			}
			outfile << "}\n";
			buildCpp = true;
		} else {
			cout << "Couldn't open " << fileName << " for some reason\n";
		}
		outfile.close();
		roomIncludes += "#include \"" + className + ".h\"\n";
		extraFiles += className + ".h " + className + ".cpp ";

		vector<string> temptoks;
		Tokenize(roomSize,temptoks,",");
		createRooms += "Engine::roomref.push_back(new " + className + "(0,\"" + roomName + "\"," + temptoks[0] + "," + temptoks[1] + "));";
	}

	for (i=0;i<fonts.size();i++) {
		string font = fonts[i];
		cout << "font " << font << endl;
		createFonts += "fontName = \"" + font + ".font\";Engine::fonts.push_back(new Font(fontName.c_str()));\n";
	}

	for (i=0;i<sprites.size();i++) {
		Sprite *sprite = sprites[i];
		cout << "sprite " << sprite->name << endl;

		char w[6];
		char h[6];
		sprintf(w,"%d",(int)sprite->width);
		sprintf(h,"%d",(int)sprite->height);
		//cout << sprite->width << " " << w << endl;
		spriteFileData += "spriteWidths.insert(pair<string,int>(\"" + sprite->name + "\"," + w + "));";
		spriteFileData += "spriteHeights.insert(pair<string,int>(\"" + sprite->name + "\"," + h + "));";
		spriteFileData += "char *" + sprite->name + " = (char *)malloc(sizeof(char)*3*" + w + "*" + h + ");";
		
		for (j=0;j<sprite->data->size();j++) {
			char d[3];
			int dat = (int)sprite->data->at(j);
			if (dat == -1) dat = 255;
			sprintf(d,"%d",dat);
			char derp[6];
			sprintf(derp,"%d",j);
			//spriteFileData += d;
			spriteFileData += sprite->name + "[" + derp + "] = " + d + ";";
			if (j != sprite->data->size()-1) {
			}
		}

		spriteFileData += "spriteData.insert(pair<string,char *>(\"" + sprite->name + "\"," + sprite->name + "));";

		//createImages += "Engine::imageref.push_back(new Image(sprites.find(\"" + sprite->name + "\")->second,widths.find(\"" + sprite->name + "\")->second,heights.find(\"" + sprite->name + "\")->second));";
		createImages += "Engine::imageref.push_back(new Image(spriteData[\"" + sprite->name + "\"],spriteWidths[\"" + sprite->name + "\"],spriteHeights[\"" + sprite->name + "\"]));";
	}

	//cout << spriteFileData << endl;

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
			//if (output.find("/* -- CREATE OBJECT TYPES -- */") != string::npos) {
			//	output.replace(output.find("/* -- CREATE OBJECT TYPES -- */"),31,objectTypes);
			//}
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
				output.replace(output.find("/* -- CREATE ROOMS -- */"),24,createRooms);
			}
			if (output.find("/* -- INSTANCE MAP -- */") != string::npos) {
				output.replace(output.find("/* -- INSTANCE MAP -- */"),24,instanceMap);
			}
			if (output.find("/* -- CREATE FONTS -- */") != string::npos) {
				output.replace(output.find("/* -- CREATE FONTS -- */"),24,createFonts);
			}
			if (output.find("/* -- SPRITE DATA -- */") != string::npos) {
				output.replace(output.find("/* -- SPRITE DATA -- */"),23,spriteFileData);
			}
			if (output.find("/* -- CREATE IMAGES -- */") != string::npos) {
				output.replace(output.find("/* -- CREATE IMAGES -- */"),25,createImages);
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

void buildReserved(vector<string> &ret) {
	ret.push_back("for");
	ret.push_back("if");
	ret.push_back("this");
	ret.push_back("endl");
	ret.push_back("cout");
	ret.push_back("instance_create");
	ret.push_back("draw_sprite");
	ret.push_back("draw_line");
	ret.push_back("instance_number");
	ret.push_back("instance_find");
	ret.push_back("draw_set_color_rgb");
	ret.push_back("draw_point");
	ret.push_back("draw_line_color");
	ret.push_back("draw_text");
	ret.push_back("mouse_x");
	ret.push_back("mouse_y");
	ret.push_back("draw_rectangle");
	ret.push_back("c_white");
	ret.push_back("else");
	ret.push_back("room_width");
	ret.push_back("room_height");
	ret.push_back("draw_rectangle_color");
	ret.push_back("ds_list_create");
	ret.push_back("ds_list_add");
	ret.push_back("ds_list_find_value");
	ret.push_back("ds_list_size");
	ret.push_back("round");
	ret.push_back("string_length");
	ret.push_back("string_char_at");
	ret.push_back("file_text_write_string");
	ret.push_back("file_text_open_write");
	ret.push_back("file_text_close");
	ret.push_back("string_copy");
	ret.push_back("file_text_writeln");
	ret.push_back("stringInt");
	ret.push_back("file_text_open_read");
	ret.push_back("file_text_read_string");
	ret.push_back("file_text_readln");
	ret.push_back("file_text_eof");
	ret.push_back("while");
}

bool isReserved(string word, vector<string> &vec) {
	int i;
	for (i=0;i<vec.size();i++ ) {
		if (vec[i] == word) {
			return true;
		}
	}
	return false;
}

string processCode(string code, vector<string> reserved) {
	int i,j;
	// do code processing
	vector<string> toks;
	Tokenize(code,toks,"\n");
	code = "";
	for (i=0;i<toks.size();i++) {
		string tmp = toks[i];
		string variable = "";
		bool inVariable = false;
		int varPos = 0;
		bool inQuotes = false;
		//cout << "\tbegin line" << endl;
		for (j=0;j<tmp.size();j++) {
			//cout << j << " " << tmp[j] << " " << inVariable << " " << inQuotes << endl;
			if (tmp[j] == 92) { // '\'
				//cout << "found \\ at " << j << " on " << tmp << endl;
				tmp.insert(j,"\\");
				j++;
			}
			if (!inVariable) {
				if (isalpha(tmp[j]) && !inQuotes) {
					//cout << "new var " << variable << endl;
					inVariable = true;
					varPos = j;
					//j--;
					//cout << j << endl;
					variable = tmp[j];
				}
			} else {
				if (isalnum(tmp[j]) || tmp[j] == '.' || tmp[j] == '_') {
					variable += tmp[j];
				} else {
					if (variable != "") {
						//cout << "running " << variable << endl;
						if (variable == "string") {
							tmp.replace(varPos,variable.size(),"stringInt");
							variable = "stringInt";
							j += 3;
						}
						if (!isReserved(variable,reserved)) {
							//cout << variable << " found" << endl;
							//vector<string> toks2;
							//Tokenize(variable,toks2,".");
							//if (toks2.size() > 1) {
							//	cout << "builder.cpp todo: multi-object variable name" << endl;
							//} else {
								//cout << varPos << " " << variable.size() << endl;
								tmp.replace(varPos,variable.size(),"variables[\"" + variable + "\"]");
								j += 13;
							//}
						} else {
							//cout << "reserved" << endl;
							//j += variable.size();
						}
					}
					inVariable = false;
					varPos = 0;
					variable = "";
				}
			}
			if (tmp[j] == '"') {
				//cout << "quote! " << j << " " << tmp[j] << "\n";
				inQuotes = !inQuotes;
			}
		}
		code += tmp + "\n";
	}
	//cout << "processed code" << endl;
	return code;
}
