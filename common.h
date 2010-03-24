#ifndef COMMONH
#define COMMONH

#include <vector>
#include "Util.h"

using namespace std;

extern int instance_create(unsigned int id, int x, int y);
extern void draw_sprite(unsigned int sprite, int offset, float x, float y);

#endif
