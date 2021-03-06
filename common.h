#ifndef COMMONH
#define COMMONH

#include <vector>
#include "Engine.h"
#include <iostream>
#include <string>

#include "specialDefs.h"

#define c_white 1,1,1

#define mouse_x Engine::mousex
#define mouse_y Engine::mousey

#define noone -4

#define room_width Engine::currentRoom->width
#define room_height Engine::currentRoom->height

#define keyboard_string Engine::keyboardString

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
extern void draw_text(Variable *text, float x, float y);
extern void draw_rectangle(float x1, float y1, float x2, float y2);
extern void draw_rectangle_color(float x1, float y1, float x2, float y2, float r, float g, float b);
extern void Tokenize(const string& str, vector<string>& tokens, const string& delimiters);
extern int file_text_open_write(string filename);
extern void file_text_close(int handle);
extern void file_text_write_string(int handle, string data);
extern int ds_list_create();
extern void ds_list_add(Variable &id, Variable &value);
extern void ds_list_add(Variable &id, const char*value);
extern void ds_list_add(Variable &id, int value);
extern Variable &ds_list_find_value(int id, int pos);
extern int ds_list_size(int id);
extern int round(Variable *);
extern Variable &string_char_at(Variable &str, unsigned int pos);
extern Variable &string_length(Variable &str);
extern Variable &string_copy(Variable &, int, int);
extern void file_text_writeln(int handle);
extern Variable &stringInt(Variable &);
extern int file_text_open_read(string filename);
extern string file_text_read_string(int handle);
extern void file_text_readln(int handle);
extern bool file_text_eof(int handle);
extern int string_width(string);

#endif
