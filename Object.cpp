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

int Object::getType() {
        return type->getId();
}

string Object::getName() {
        return type->getName();
}
