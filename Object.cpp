#include "ObjectType.h"
#include "Object.h"
#include <string>
#include "common.h"

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

Object::Object(int i, ObjectType *obj, float xx, float yy) {
	id = i;
	sprite = obj->getSprite();
        type = obj;
        x = xx;
        y = yy;
        keymaps = new keymap();
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_F1,&Object::key_F1));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_F1,&Object::key_F2));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_F1,&Object::key_F3));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_F1,&Object::key_F4));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_F1,&Object::key_F5));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_F1,&Object::key_F6));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_F1,&Object::key_F7));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_F1,&Object::key_F8));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_F1,&Object::key_F9));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_F1,&Object::key_F10));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_F1,&Object::key_F11));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_F1,&Object::key_F12));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_UP,&Object::key_up));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_DOWN,&Object::key_down));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_LEFT,&Object::key_left));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_RIGHT,&Object::key_right));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_PAGE_UP,&Object::key_page_up));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_PAGE_DOWN,&Object::key_page_down));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_HOME,&Object::key_home));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_END,&Object::key_end));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_INSERT,&Object::key_insert));
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
