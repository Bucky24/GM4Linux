#include "obj_wall.h"
#include <string>

using namespace std;

obj_wall::obj_wall(int i, ObjectType *obj, float x, float y) : Object(i,obj,x,y) {
       create();
}
