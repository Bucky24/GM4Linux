#include "common.h"

int instance_create(unsigned int id, int x, int y) {
        int ret = noone;
        if (id == 0) {
        	testobject *inst = new testobject(Util::instanceid,Util::objectref[id],x,y);
                Util::instanceref.push_back(inst);
                ret = Util::instanceid;
                Util::instanceid++;
        }
        return ret;
}

void draw_sprite(unsigned int sprite, int offset, float x, float y) {
        if (sprite >= Util::imageref.size()) {
                return;
        }
        Util::imageref[sprite]->draw(x,y);
}
