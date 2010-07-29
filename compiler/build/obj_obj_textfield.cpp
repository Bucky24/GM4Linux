#include "obj_obj_textfield.h"
#include "common.h"
obj_obj_textfield::obj_obj_textfield(int i, ObjectType *obj, float x, float y) : Object(i,obj,x,y) {
create();
}
void obj_obj_textfield::create() {
variables["width"] = 100;
variables["height"] = 100;
}
void obj_obj_textfield::draw() {
}
