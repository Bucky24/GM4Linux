#include "ObjectType.h"
#include "Object.h"
#include <string>
#include "Util.h"
#include "common.h"

using namespace std;

Object::Object(int i, ObjectType *obj, float xx, float yy) {
	id = i;
	sprite = obj->getSprite();
        type = obj;
        x = xx;
        y = yy;
}

void Object::create() {

}

void Object::destroy() {

}

void Object::draw() {
	if (sprite != noone) {
                draw_sprite(sprite,0,x,y);
	}
}

void Object::key_up() {

}

void Object::key_down() {

}

void Object::key_left() {

}

void Object::key_right() {

}

void Object::key_F1() {

}

void Object::key_F2() {

}

void Object::key_F3() {

}

void Object::key_F4() {

}

void Object::key_F5() {

}

void Object::key_F6() {

}

void Object::key_F7() {

}

void Object::key_F8() {

}

void Object::key_F9() {

}

void Object::key_F10() {

}

void Object::key_F11() {

}

void Object::key_F12() {

}

void Object::key_page_down() {

}

void Object::key_page_up() {

}

void Object::key_home() {

}

void Object::key_end() {

}

void Object::key_insert() {

}

int Object::getType() {
        return type->getId();
}

string Object::getName() {
        return type->getName();
}
