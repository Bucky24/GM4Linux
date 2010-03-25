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
        virtual void key_left();
        virtual void key_right();
        virtual void key_F1();
        virtual void key_F2();
        virtual void key_F3();
        virtual void key_F4();
        virtual void key_F5();
        virtual void key_F6();
        virtual void key_F7();
        virtual void key_F8();
        virtual void key_F9();
        virtual void key_F10();
        virtual void key_F11();
        virtual void key_F12();
        virtual void key_page_down();
        virtual void key_page_up();
        virtual void key_home();
        virtual void key_end();
        virtual void key_insert();

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
