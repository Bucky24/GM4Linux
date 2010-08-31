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
	variables = *(new map<string, Variable>());
        create();
}

void Object::create() {}

void Object::destroy() {}

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
void Object::key_any() {}

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
void Object::keyup_a() {}
void Object::keyup_b() {}
void Object::keyup_c() {}
void Object::keyup_d() {}
void Object::keyup_e() {}
void Object::keyup_f() {}
void Object::keyup_g() {}
void Object::keyup_h() {}
void Object::keyup_i() {}
void Object::keyup_j() {}
void Object::keyup_k() {}
void Object::keyup_l() {}
void Object::keyup_m() {}
void Object::keyup_n() {}
void Object::keyup_o() {}
void Object::keyup_p() {}
void Object::keyup_q() {}
void Object::keyup_r() {}
void Object::keyup_s() {}
void Object::keyup_t() {}
void Object::keyup_u() {}
void Object::keyup_v() {}
void Object::keyup_w() {}
void Object::keyup_x() {}
void Object::keyup_y() {}
void Object::keyup_z() {}
void Object::keyup_any() {}

void Object::keydown_up() {}
void Object::keydown_down() {}
void Object::keydown_left() {}
void Object::keydown_right() {}
void Object::keydown_F1() {}
void Object::keydown_F2() {}
void Object::keydown_F3() {}
void Object::keydown_F4() {}
void Object::keydown_F5() {}
void Object::keydown_F6() {}
void Object::keydown_F7() {}
void Object::keydown_F8() {}
void Object::keydown_F9() {}
void Object::keydown_F10() {}
void Object::keydown_F11() {}
void Object::keydown_F12() {}
void Object::keydown_page_down() {}
void Object::keydown_page_up() {}
void Object::keydown_home() {}
void Object::keydown_end() {}
void Object::keydown_insert() {}

void Object::mousepressed_left() {}
void Object::mousepressed_right() {}
void Object::mousepressed_middle() {}

void Object::globalmousepressed_left() {}
void Object::globalmousepressed_right() {}
void Object::globalmousepressed_middle() {}

void Object::globalmousereleased_left() {}
void Object::globalmousereleased_right() {}
void Object::globalmousereleased_middle() {}

void Object::step_begin() {}
void Object::step() {}
void Object::step_end() {}

int Object::getType() {
        return type->getId();
}

string Object::getName() {
        return type->getName();
}

bool Object::check_collision_with_object(int objectId) {
        return false;
}

void Object::collide_with(int objectId) {
        
}

bool Object::pointInside(float px, float py) {
	if (Engine::getSprite(type->getSprite()) == NULL) {
		return false;
	}
	float width = Engine::getSprite(type->getSprite())->width;
	float height = Engine::getSprite(type->getSprite())->height;

	return (px >= x && px <= x+width && py >= y && py <= y+height);
}
