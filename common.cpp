#include "common.h"

void draw_character(char letter, float x, float y) {
	Letter *let = Engine::currentFont->letters[letter];
	int i,j;
	for (i=x;i<x+let->width;i++) {
		
	}
}

int instance_create(unsigned int id, int x, int y) {
        int ret = noone;
        Object *inst = NULL;
        ObjectType *object= Engine::objectref[id];
	/* -- OBJECT CREATION -- */
	cout << "common.cpp instance_create " << id << endl;
        if (inst != NULL) {
                Engine::instanceref.push_back(inst);
                Engine::instances->find(id)->second->push_back(inst);
		if (Engine::currentRoom != NULL) {
			cout << "common.cpp instance_create room is not null" << endl;
			Engine::currentRoom->instances.push_back(inst);
		}
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

void draw_line(float x1, float y1, float x2, float y2) {
	glColor3f(Engine::r,Engine::g,Engine::b);
	glBegin(GL_LINES);
	glVertex3f(x1,y1,0);
	glVertex3f(x2,y2,0);
	glEnd();
	// this point needed because gl lines never draws the starting point
	glBegin(GL_POINTS);
	glVertex3f(x1,y1,0);
	glEnd();
}

void draw_line_color(float x1, float y1, float x2, float y2, float r, float g, float b) {
	glColor3f(r,g,b);
	glBegin(GL_LINES);
	glVertex3f(x1,y1,0);
	glVertex3f(x2,y2,0);
	glEnd();
	// this point needed because gl lines never draws the starting point
	glBegin(GL_POINTS);
	glVertex3f(x1,y1,0);
	glEnd();
	glColor3f(Engine::r,Engine::g,Engine::b);
}

int instance_number(int object) {
	instancemap::iterator itor = Engine::instances->find(object);
	if (itor == Engine::instances->end()) {
		return 0;
	}
	return itor->second->size();
}

int instance_find(int object, int number) {
	instancemap::iterator itor = Engine::instances->find(object);
	if (itor == Engine::instances->end()) {
		return 0;
	}
	objlist *list = itor->second;
	return list->at(number)->id;
}

void draw_set_color_rgb(int r, int g, int b) {
	Engine::r = ((float)r)/255;
	Engine::g = ((float)g)/255;
	Engine::b = ((float)b)/255;
}

void draw_point(float x, float y) {
	glColor3f(Engine::r,Engine::g,Engine::b);
	glBegin(GL_POINTS);
	glVertex2f(x,y);
	glEnd();
}

void drawText(string text, float x, float y) {
	
}
