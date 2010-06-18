#include "common.h"

int instance_create(unsigned int id, int x, int y) {
        int ret = noone;
        Object *inst = NULL;
        ObjectType *object= Engine::objectref[id];
        if (id == 0) {
        	inst = new testobject(Engine::instanceid,object,x,y);
        } else if (id == 1) {
        	inst = new obj_wall(Engine::instanceid,object,x,y);
        }
        if (inst != NULL) {
                Engine::instanceref.push_back(inst);
                Engine::instances->find(id)->second->push_back(inst);
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

void draw_line(int x1, int y1, int x2, int y2) {
        glColor3f(255,255,255);
	glBegin(GL_LINES);
	glVertex2f(x1,y1);
	glVertex2f(x2,y2);
	glEnd();
        glColor3f(0,0,0);
}
