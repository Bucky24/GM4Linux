#include "common.h"

int instance_create(unsigned int id, int x, int y) {
        int ret = noone;
        if (id == 0) {
        	testobject *inst = new testobject(Engine::instanceid,Engine::objectref[id],x,y);
                Engine::instanceref.push_back(inst);
                ret = Engine::instanceid;
                Engine::instanceid++;
        }
        return ret;
}

void draw_sprite(unsigned int sprite, int offset, float x, float y) {
        if (sprite >= Engine::imageref.size()) {
                return;
        }
        Engine::imageref[sprite]->draw(x,y);
}
