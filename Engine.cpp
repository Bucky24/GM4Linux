#include "Engine.h"
#include <cstdlib>
#include "Rooms.h"

vector<ObjectType *> Engine::objectref;
vector<Image *> Engine::imageref;
vector<Object *> Engine::instanceref;
vector<Room *> Engine::roomref;
int Engine::instanceid = 0;
Room *Engine::currentRoom;
void Engine::init() {
        //refs = (references *)malloc(sizeof(struct references));
        objectref = *(new vector<ObjectType *>());
        imageref = *(new vector<Image *>());
        instanceref = *(new vector<Object *>());
        roomref = *(new vector<Room *>());
        fillObjects();
        fillImages();
        fillRooms();
}

void Engine::fillObjects() {
        //ObjectType *derp = new ObjectType(0,"object0",0);
        //objectref.push_back(derp);
        objectref.push_back(new ObjectType(0,"Object0",0));
}

void Engine::fillImages() {
        imageref.push_back(new Image((char *)"vtr.bmp",64,64,IMAGE_FILE));
}

void Engine::fillRooms() {
        roomref.push_back(new testroom(0,"testroom",800,600));

        currentRoom = roomref[0];
}

ObjectType *Engine::getObject(unsigned int id) {
        if (id >= objectref.size()) {
                return NULL;
        }
        return objectref[id];
}

Object *Engine::getInstance(unsigned int id) {
        if (id >= instanceref.size()) {
                return NULL;
        }
        return instanceref[id];
}

Image *Engine::getSprite(unsigned int id) {
        if (id >= imageref.size()) {
                return NULL;
        }
        return imageref[id];
}

Room *Engine::getRoom(unsigned int id) {
        if (id >= roomref.size()) {
                return NULL;
        }
        return roomref[id];
}
