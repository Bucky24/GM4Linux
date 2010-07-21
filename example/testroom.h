#ifndef TESTROOMH
#define TESTROOMH

#include "Room.h"

class testroom : public Room {
public:
        testroom(int i, string t, int w, int h, int sp=30);
        void initInstances();
};

#endif
