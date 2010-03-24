#include "testobject.h"
#include <string>
#include "Util.h"

using namespace std;

testobject::testobject(int i, ObjectType *obj, float x, float y) : Object(i,obj,x,y) {
       create();
}

void testobject::key_up() {
        y -= 5;
}
