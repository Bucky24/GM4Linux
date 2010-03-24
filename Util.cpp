#include "Util.h"
#include <cstdlib>
#include "Rooms.h"

vector<ObjectType *> Util::objectref;
vector<Image *> Util::imageref;
vector<Object *> Util::instanceref;
vector<Room *> Util::roomref;
int Util::instanceid = 0;
Room *Util::currentRoom;
void Util::init() {
        //refs = (references *)malloc(sizeof(struct references));
        objectref = *(new vector<ObjectType *>());
        imageref = *(new vector<Image *>());
        instanceref = *(new vector<Object *>());
        roomref = *(new vector<Room *>());
        fillObjects();
        fillImages();
        fillRooms();
}

void Util::fillObjects() {
        //ObjectType *derp = new ObjectType(0,"object0",0);
        //objectref.push_back(derp);
        objectref.push_back(new ObjectType(0,"Object0",0));
}

void Util::fillImages() {
        imageref.push_back(new Image((char *)"vtr.bmp",64,64,IMAGE_FILE));
}

void Util::fillRooms() {
        roomref.push_back(new testroom(0,"testroom",800,600));

        currentRoom = roomref[0];
}

ObjectType *Util::getObject(unsigned int id) {
        if (id >= objectref.size()) {
                return NULL;
        }
        return objectref[id];
}

Object *Util::getInstance(unsigned int id) {
        if (id >= instanceref.size()) {
                return NULL;
        }
        return instanceref[id];
}

Image *Util::getSprite(unsigned int id) {
        if (id >= imageref.size()) {
                return NULL;
        }
        return imageref[id];
}

Room *Util::getRoom(unsigned int id) {
        if (id >= roomref.size()) {
                return NULL;
        }
        return roomref[id];
}
