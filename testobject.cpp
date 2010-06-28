#include "testobject.h"
#include <string>
#include "common.h"

using namespace std;

testobject::testobject(int i, ObjectType *obj, float x, float y) : Object(i,obj,x,y) {
       create();
}

void testobject::key_up() {
        y -= 5;
}

void testobject::key_down() {
	y += 5;
}

void testobject::key_left() {
	x -= 5;
}

void testobject::key_right() {
	x += 5;
}

void testobject::step() {
       //y += 1;
}

void testobject::draw() {
	int i;
	Object *obj;
	for (i=0;i<instance_number(0);i++) {
		obj = instance_find(0,i);
		if (obj != this) {
			draw_line(x,y,obj->x,obj->y);
			cout << x << " " << y << " " << obj->x << " " << obj->y << endl;
		}
	}
}

void testobject::collide_with(int objectid) {
        
}
