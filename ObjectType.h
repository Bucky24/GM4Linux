#ifndef OBJECTTYPEH
#define OBJECTTYPEH

#include <string>

using namespace std;

class ObjectType {
public:
	ObjectType(int i,string s, int im);

	string getName() {return name;}
	int getId() {return id;}
	int getSprite() {return sprite;}
private:
	string name;
	int id;
	int sprite;
};

#endif