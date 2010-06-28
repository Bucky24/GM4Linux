#ifndef TESTOBJH
#define TESTOBJH

#include <string>

using namespace std;

#include "Object.h"
#include "ObjectType.h"

class testobject : public Object {
public:
	testobject(int i, ObjectType *obj, float x, float y);
        void key_up();
	void key_down();
        void key_left();
        void key_right();
        void step();
        void draw();

        void collide_with(int instanceId);
	void collide_with_obj_wall();
};

#endif
