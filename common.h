#ifndef COMMONH
#define COMMONH

#include <vector>
#include "Engine.h"
#include <iostream>

/* -- OBJECT DEFINITIONS -- */
#define obj_testobject 0
#define obj_obj_control 2

using namespace std;

extern int instance_create(unsigned int id, int x, int y);
extern void draw_sprite(unsigned int sprite, int offset, float x, float y);
extern void draw_line(float x1, float y1, float x2, float y2);
extern int instance_number(int object);
extern Object *instance_find(int object, int number);
extern void draw_set_color_rgb(int r, int g, int b);
extern void draw_point(float x, float y);

#endif
