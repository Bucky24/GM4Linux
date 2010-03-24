#ifndef TESTOBJH
#define TESTOBJH

#include <string>

using namespace std;

#include "Object.h"
#include "ObjectType.h"

class testobject : public Object {
public:
	testobject(int i, ObjectType *obj, float x, float y);
        void key_up();
};

#endif
