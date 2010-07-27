#include "testroom.h"
#include "Objects.h"
#include "common.h"

testroom::testroom(int i, string t, int w, int h, int sp) : Room(i,t,w,h,sp) {
	r = 0.82;
	g = 0.82;
	b = 0.82;
        initInstances();
}

void testroom::initInstances() {
        instance_create(obj_obj_control,30,30);
}
