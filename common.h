#ifndef COMMONH
#define COMMONH

#include <vector>
#include "Engine.h"
#include <iostream>
#include <string>

/* -- OBJECT DEFINITIONS -- */

#define c_white 1,1,1

#define mouse_x Engine::mousex
#define mouse_y Engine::mousey

#define noone -4

#define room_width Engine::currentRoom->width
#define room_height Engine::currentRoom->height

using namespace std;

extern int instance_create(unsigned int id, int x, int y);
extern void draw_sprite(unsigned int sprite, int offset, float x, float y);
extern void draw_line(float x1, float y1, float x2, float y2);
extern int instance_number(int object);
extern int instance_find(int object, int number);
extern void draw_set_color_rgb(int r, int g, int b);
extern void draw_point(float x, float y);
extern void draw_line_color(float x1, float y1, float x2, float y2, float r, float g, float b);
extern void draw_text(string text, float x, float y);
extern void draw_rectangle(float x1, float y1, float x2, float y2);
extern void draw_rectangle_color(float x1, float y1, float x2, float y2, float r, float g, float b);
extern void Tokenize(const string& str, vector<string>& tokens, const string& delimiters);
extern int file_text_open_write(string filename);
extern void file_text_close(int handle);

#endif
