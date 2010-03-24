#ifndef OBJECTH
#define OBJECTH

#include <string>

using namespace std;

#include "Image.h"
#include "ObjectType.h"

class Object {
public:
	Object(int i, ObjectType *obj, float x, float y);
	virtual void create();
	virtual void destroy();
	virtual void draw();

        virtual void key_up();
        virtual void key_down();

	string getName();
	int getId() {return id;}
	int getSprite() {return sprite;}
        int getType();
protected:
	int id;
	int sprite;
        float x;
        float y;
        ObjectType *type;
};

#endif
