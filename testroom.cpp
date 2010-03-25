#include "testroom.h"
#include "Objects.h"
#include "Util.h"
#include "common.h"

testroom::testroom(int i, string t, int w, int h, int sp) : Room(i,t,w,h,sp) {
        initInstances();
        create();
}

void testroom::initInstances() {
        instances.push_back(Util::getInstance(instance_create(0,30,30)));
}

void testroom::create() {

}
