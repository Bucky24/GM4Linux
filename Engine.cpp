#include "Engine.h"
#include <cstdlib>
#include "Rooms.h"

vector<ObjectType *> Engine::objectref;
vector<Image *> Engine::imageref;
vector<Object *> Engine::instanceref;
vector<Room *> Engine::roomref;
int Engine::instanceid = 0;
Room *Engine::currentRoom;
bool Engine::keys[500];
bool Engine::keyslaststep[500];
bool Engine::mouse_left_flagged;
bool Engine::mouse_left_flagged_laststep;
bool Engine::mouse_right_flagged;
bool Engine::mouse_right_flagged_laststep;
bool Engine::mouse_center_flagged;
bool Engine::mouse_center_flagged_laststep;
keymap *Engine::keymaps;

void Engine::init() {
        //refs = (references *)malloc(sizeof(struct references));
        objectref = *(new vector<ObjectType *>());
        imageref = *(new vector<Image *>());
        instanceref = *(new vector<Object *>());
        roomref = *(new vector<Room *>());
        fillObjects();
        fillImages();
        fillRooms();

        int i;
        for (i=0;i<500;i++) {
                keys[i] = false;
                keyslaststep[i] = false;
        }

        keymaps = new keymap();
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_F1,&Object::key_F1));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_F1,&Object::key_F2));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_F1,&Object::key_F3));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_F1,&Object::key_F4));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_F1,&Object::key_F5));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_F1,&Object::key_F6));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_F1,&Object::key_F7));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_F1,&Object::key_F8));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_F1,&Object::key_F9));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_F1,&Object::key_F10));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_F1,&Object::key_F11));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_F1,&Object::key_F12));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_UP,&Object::key_up));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_DOWN,&Object::key_down));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_LEFT,&Object::key_left));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_RIGHT,&Object::key_right));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_PAGE_UP,&Object::key_page_up));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_PAGE_DOWN,&Object::key_page_down));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_HOME,&Object::key_home));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_END,&Object::key_end));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_INSERT,&Object::key_insert));
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

void Engine::handleEvents() {
        vector<Object *> instances = Engine::currentRoom->getInstances();
        unsigned int i;
        int j;
        //printf("%d %d\n",button,state);
        for (i=0;i<instances.size();i++) {
                Object *inst = instances[i];
                for (i=0;i<500;j++) {
                        if (keys[j] == true) {
                                keyfunc function = (*(keymaps->find(j))).second;
                                if (function != NULL) {
                                        (inst->*function)();
                                }
                        }
                }
                /*if (keys[GLUT_KEY_F1+200] == true) {
                        inst->key_F1();
                }
                if (keys[GLUT_KEY_F2+200]) {
                        inst->key_F2();
                }
                if (keys[GLUT_KEY_F3+200]) {
                        inst->key_F3();
                }
                if (keys[GLUT_KEY_F4+200]) {
                        inst->key_F4();
                }
                if (keys[GLUT_KEY_F5+200]) {
                        inst->key_F5();
                }
                if (keys[GLUT_KEY_F6+200]) {
                        inst->key_F6();
                }
                if (keys[GLUT_KEY_F7+200]) {
                        inst->key_F7();
                }
                if (keys[GLUT_KEY_F8+200]) {
                        inst->key_F8();
                }
                if (keys[GLUT_KEY_F9+200]) {
                        inst->key_F9();
                }
                if (keys[GLUT_KEY_F10+200]) {
                        inst->key_F10();
                }
                if (keys[GLUT_KEY_F11+200]) {
                        inst->key_F11();
                }
                if (keys[GLUT_KEY_F12+200]) {
                        inst->key_F12();
                }
                if (keys[GLUT_KEY_LEFT+200]) {
                        inst->key_left();
                }
                if (keys[GLUT_KEY_UP+200]) {
                        inst->key_up();
                }
                if (keys[GLUT_KEY_RIGHT+200]) {
                        inst->key_right();
                }
                if (keys[GLUT_KEY_DOWN+200]) {
                        inst->key_down();
                }
                if (keys[GLUT_KEY_PAGE_UP+200]) {
                        inst->key_page_up();
                }
                if (keys[GLUT_KEY_PAGE_DOWN+200]) {
                        inst->key_page_down();
                }
                if (keys[GLUT_KEY_HOME+200]) {
                        inst->key_home();
                }
                if (keys[GLUT_KEY_END+200]) {
                        inst->key_end();
                }
                if (keys[GLUT_KEY_INSERT+200]) {
                        inst->key_insert();
                }*/
	}
        for (i=0;i<500;i++) {
                keyslaststep[i] = keys[i];
        }
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
