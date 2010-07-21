#include "obj_control.h"
#include "common.h"
#include <iostream>

using namespace std;

obj_control::obj_control(int i, ObjectType *type, float x, float y) : Object(i,type,x,y) {
	create();
}

void obj_control::globalmousepressed_left() {
	instance_create(0,Engine::mouse_x,Engine::mouse_y);
}
