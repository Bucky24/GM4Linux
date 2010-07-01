#include "testroom.h"
#include "Objects.h"
#include "common.h"

// all object cpp files must include Engine
#include "Engine.h"

testroom::testroom(int i, string t, int w, int h, int sp) : Room(i,t,w,h,sp) {
	r = 0.82;
	g = 0.82;
	b = 0.82;
        initInstances();
        create();
}

void testroom::initInstances() {
        instances.push_back(Engine::getInstance(instance_create(2,30,30)));
}
