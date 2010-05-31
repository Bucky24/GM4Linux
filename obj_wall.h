#ifndef WALLOBJH
#define WALLOBJH

#include <string>

using namespace std;

#include "Object.h"
#include "ObjectType.h"

class obj_wall : public Object {
public:
	obj_wall(int i, ObjectType *obj, float x, float y);
};

#endif
