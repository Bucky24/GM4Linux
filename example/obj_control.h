#ifndef OBJ_CONTROLH
#define OBJ_CONTROLH

#include "Object.h"
#include "ObjectType.h"

class obj_control : public Object {
public:
	obj_control(int i, ObjectType *obj, float x, float y);
	void globalmousepressed_left();
};

#endif
