#ifndef COMMONH
#define COMMONH

#include <vector>
#include "Engine.h"
#include <iostream>

using namespace std;

extern int instance_create(unsigned int id, int x, int y);
extern void draw_sprite(unsigned int sprite, int offset, float x, float y);
extern void draw_line(int x1, int y1, int x2, int y2);
extern int instance_number(int object);
extern Object *instance_find(int object, int number);
extern void draw_set_color_rgb(int r, int g, int b);

#endif
