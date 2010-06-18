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
        draw_line(0,0,200,200);
}

void testobject::collide_with(int objectid) {
        
}
