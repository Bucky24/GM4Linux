#ifndef OBJECTH
#define OBJECTH

#include <string>
#include <map>
#include "Image.h"
#include "Variable.h"

using namespace std;

class Variables {
public:
	Variables();
	map<string,Variable> vars;
	Variable &operator[](string key);
};

class Object {
public:
	Object(int i, float x, float y);
	virtual void create();
	virtual void destroy();
	virtual void draw();

        virtual void key_up();
        virtual void key_down();
        virtual void key_left();
        virtual void key_right();
        virtual void key_F1();
        virtual void key_F2();
        virtual void key_F3();
        virtual void key_F4();
        virtual void key_F5();
        virtual void key_F6();
        virtual void key_F7();
        virtual void key_F8();
        virtual void key_F9();
        virtual void key_F10();
        virtual void key_F11();
        virtual void key_F12();
        virtual void key_page_down();
        virtual void key_page_up();
        virtual void key_home();
        virtual void key_end();
        virtual void key_insert();
	virtual void key_enter();
	virtual void key_backspace();

	virtual void key_a();
	virtual void key_b();
	virtual void key_c();
	virtual void key_d();
	virtual void key_e();
	virtual void key_f();
	virtual void key_g();
	virtual void key_h();
	virtual void key_i();
	virtual void key_j();
	virtual void key_k();
	virtual void key_l();
	virtual void key_m();
	virtual void key_n();
	virtual void key_o();
	virtual void key_p();
	virtual void key_q();
	virtual void key_r();
	virtual void key_s();
	virtual void key_t();
	virtual void key_u();
	virtual void key_v();
	virtual void key_w();
	virtual void key_x();
	virtual void key_y();
	virtual void key_z();
	virtual void key_any();

	virtual void keyup_up();
        virtual void keyup_down();
        virtual void keyup_left();
        virtual void keyup_right();
        virtual void keyup_F1();
        virtual void keyup_F2();
        virtual void keyup_F3();
        virtual void keyup_F4();
        virtual void keyup_F5();
        virtual void keyup_F6();
        virtual void keyup_F7();
        virtual void keyup_F8();
        virtual void keyup_F9();
        virtual void keyup_F10();
        virtual void keyup_F11();
        virtual void keyup_F12();
        virtual void keyup_page_down();
        virtual void keyup_page_up();
        virtual void keyup_home();
        virtual void keyup_end();
        virtual void keyup_insert();

	virtual void keyup_a();
	virtual void keyup_b();
	virtual void keyup_c();
	virtual void keyup_d();
	virtual void keyup_e();
	virtual void keyup_f();
	virtual void keyup_g();
	virtual void keyup_h();
	virtual void keyup_i();
	virtual void keyup_j();
	virtual void keyup_k();
	virtual void keyup_l();
	virtual void keyup_m();
	virtual void keyup_n();
	virtual void keyup_o();
	virtual void keyup_p();
	virtual void keyup_q();
	virtual void keyup_r();
	virtual void keyup_s();
	virtual void keyup_t();
	virtual void keyup_u();
	virtual void keyup_v();
	virtual void keyup_w();
	virtual void keyup_x();
	virtual void keyup_y();
	virtual void keyup_z();
	virtual void keyup_any();

        virtual void keydown_up();
        virtual void keydown_down();
        virtual void keydown_left();
        virtual void keydown_right();
        virtual void keydown_F1();
        virtual void keydown_F2();
        virtual void keydown_F3();
        virtual void keydown_F4();
        virtual void keydown_F5();
        virtual void keydown_F6();
        virtual void keydown_F7();
        virtual void keydown_F8();
        virtual void keydown_F9();
        virtual void keydown_F10();
        virtual void keydown_F11();
        virtual void keydown_F12();
        virtual void keydown_page_down();
        virtual void keydown_page_up();
        virtual void keydown_home();
        virtual void keydown_end();
        virtual void keydown_insert();

	virtual void mousepressed_left();
	virtual void mousepressed_right();
	virtual void mousepressed_middle();

	virtual void globalmousepressed_left();
	virtual void globalmousepressed_right();
	virtual void globalmousepressed_middle();

	virtual void globalmousereleased_left();
	virtual void globalmousereleased_right();
	virtual void globalmousereleased_middle();

        virtual void step_begin();
        virtual void step();
        virtual void step_end();

	string getName();
	int getId() {return id;}
	int getSprite() {return sprite;}

        bool check_collision_with_object(Object *object);
        virtual void collide_with(int objectId);

	int id;
	int sprite;
        float x;
        float y;
	int objectId;

	string name;

	Variables variables;

	bool pointInside(float x, float y);
};

#endif
