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

void Object::key_up() {}
void Object::key_down() {}
void Object::key_left() {}
void Object::key_right() {}
void Object::key_F1() {}
void Object::key_F2() {}
void Object::key_F3() {}
void Object::key_F4() {}
void Object::key_F5() {}
void Object::key_F6() {}
void Object::key_F7() {}
void Object::key_F8() {}
void Object::key_F9() {}
void Object::key_F10() {}
void Object::key_F11() {}
void Object::key_F12() {}
void Object::key_page_down() {}
void Object::key_page_up() {}
void Object::key_home() {}
void Object::key_end() {}
void Object::key_insert() {}
void Object::key_a() {}
void Object::key_b() {}
void Object::key_c() {}
void Object::key_d() {}
void Object::key_e() {}
void Object::key_f() {}
void Object::key_g() {}
void Object::key_h() {}
void Object::key_i() {}
void Object::key_j() {}
void Object::key_k() {}
void Object::key_l() {}
void Object::key_m() {}
void Object::key_n() {}
void Object::key_o() {}
void Object::key_p() {}
void Object::key_q() {}
void Object::key_r() {}
void Object::key_s() {}
void Object::key_t() {}
void Object::key_u() {}
void Object::key_v() {}
void Object::key_w() {}
void Object::key_x() {}
void Object::key_y() {}
void Object::key_z() {}

void Object::keyup_up() {}
void Object::keyup_down() {}
void Object::keyup_left() {}
void Object::keyup_right() {}
void Object::keyup_F1() {}
void Object::keyup_F2() {}
void Object::keyup_F3() {}
void Object::keyup_F4() {}
void Object::keyup_F5() {}
void Object::keyup_F6() {}
void Object::keyup_F7() {}
void Object::keyup_F8() {}
void Object::keyup_F9() {}
void Object::keyup_F10() {}
void Object::keyup_F11() {}
void Object::keyup_F12() {}
void Object::keyup_page_down() {}
void Object::keyup_page_up() {}
void Object::keyup_home() {}
void Object::keyup_end() {}
void Object::keyup_insert() {}

int Object::getType() {
        return type->getId();
}

string Object::getName() {
        return type->getName();
}
