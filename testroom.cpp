#include "testroom.h"
#include "Objects.h"
#include "common.h"

// all object cpp files must include Engine
#include "Engine.h"

testroom::testroom(int i, string t, int w, int h, int sp) : Room(i,t,w,h,sp) {
        initInstances();
        create();
}

void testroom::initInstances() {
        instances.push_back(Engine::getInstance(instance_create(0,30,30)));
}
