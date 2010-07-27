#include "Room.h"
#include <iostream>

using namespace std;

Room::Room(int i, string t, int w, int h, int sp) {
        id = i;
        title = t;
        width = w;
        height = h;
        speed = sp;
        instances = *(new vector<Object *>());
}

void Room::initInstances() {

}

void Room::create() {

}

void Room::draw() {
        unsigned int i;
        for (i=0;i<instances.size();i++) {
		if (instances[i] != NULL) {
                	instances[i]->draw();
		}
        }
}
