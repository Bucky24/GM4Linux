#include "Engine.h"
#include <cstdlib>
#include "Rooms.h"

vector<ObjectType *> Engine::objectref;
vector<Image *> Engine::imageref;
vector<Object *> Engine::instanceref;
vector<Room *> Engine::roomref;
int Engine::instanceid = 0;
Room *Engine::currentRoom;
keyhitmap *Engine::keys;
keyhitmap *Engine::keyslaststep;
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

        /*int i;
        for (i=0;i<500;i++) {
                keys[i] = false;
                keyslaststep[i] = false;
        }*/

        mouse_left_flagged = false;
        mouse_left_flagged_laststep = false;
        mouse_right_flagged = false;
        mouse_right_flagged_laststep = false;
        mouse_center_flagged = false;
        mouse_center_flagged_laststep = false;

        keys = new keyhitmap();
        keyslaststep = new keyhitmap();
        keymaps = new keymap();

        generateKeyMaps();
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
        //int j;
        //printf("%d %d\n",button,state);
        for (i=0;i<instances.size();i++) {
                Object *inst = instances[i];
                keyhitmap::iterator itor = keys->begin();
                while (itor != keys->end()) {
                        bool val = (*itor).second;
                        int id = (*itor).first;
                        if (val == true) {
                                keyfunc function = (*(keymaps->find(id))).second;
                                if (function != NULL) {
                                        (inst->*function)();
                                }
                        }
                        itor ++;
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
        keyhitmap::iterator itor = keys->begin();
        keyhitmap::iterator itor2 = keyslaststep->begin();
        while (itor != keys->end()) {
                (*itor2).second = (*itor).second;
                (*itor).second = false;
                itor ++;
                itor2 ++;
        }

        mouse_left_flagged_laststep = mouse_left_flagged;
        mouse_right_flagged_laststep = mouse_right_flagged;
        mouse_center_flagged_laststep = mouse_center_flagged;
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











void Engine::generateKeyMaps() {
        //keys = new keyhitmap();
        //keyslaststep = new keyhitmap();
        //keymaps = new keymap();
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_F1+200,&Object::key_F1));
        keys->insert(pair<int,bool>(GLUT_KEY_F1+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_F1+200,false));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_F2+200,&Object::key_F2));
        keys->insert(pair<int,bool>(GLUT_KEY_F2+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_F2+200,false));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_F3+200,&Object::key_F3));
        keys->insert(pair<int,bool>(GLUT_KEY_F3+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_F3+200,false));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_F4+200,&Object::key_F4));
        keys->insert(pair<int,bool>(GLUT_KEY_F4+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_F4+200,false));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_F5+200,&Object::key_F5));
        keys->insert(pair<int,bool>(GLUT_KEY_F5+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_F5+200,false));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_F6+200,&Object::key_F6));
        keys->insert(pair<int,bool>(GLUT_KEY_F6+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_F6+200,false));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_F7+200,&Object::key_F7));
        keys->insert(pair<int,bool>(GLUT_KEY_F7+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_F7+200,false));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_F8+200,&Object::key_F8));
        keys->insert(pair<int,bool>(GLUT_KEY_F8+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_F8+200,false));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_F9+200,&Object::key_F9));
        keys->insert(pair<int,bool>(GLUT_KEY_F9+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_F9+200,false));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_F10+200,&Object::key_F10));
        keys->insert(pair<int,bool>(GLUT_KEY_F10+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_F10+200,false));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_F11+200,&Object::key_F11));
        keys->insert(pair<int,bool>(GLUT_KEY_F11+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_F11+200,false));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_F12+200,&Object::key_F12));
        keys->insert(pair<int,bool>(GLUT_KEY_F12+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_F12+200,false));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_UP+200,&Object::key_up));
        keys->insert(pair<int,bool>(GLUT_KEY_UP+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_UP+200,false));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_DOWN+200,&Object::key_down));
        keys->insert(pair<int,bool>(GLUT_KEY_DOWN+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_DOWN+200,false));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_LEFT+200,&Object::key_left));
        keys->insert(pair<int,bool>(GLUT_KEY_LEFT+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_LEFT+200,false));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_RIGHT+200,&Object::key_right));
        keys->insert(pair<int,bool>(GLUT_KEY_RIGHT+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_RIGHT+200,false));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_PAGE_UP+200,&Object::key_page_up));
        keys->insert(pair<int,bool>(GLUT_KEY_PAGE_UP+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_PAGE_UP+200,false));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_PAGE_DOWN+200,&Object::key_page_down));
        keys->insert(pair<int,bool>(GLUT_KEY_PAGE_DOWN+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_PAGE_DOWN+200,false));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_HOME+200,&Object::key_home));
        keys->insert(pair<int,bool>(GLUT_KEY_HOME+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_HOME+200,false));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_END+200,&Object::key_end));
        keys->insert(pair<int,bool>(GLUT_KEY_END+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_END+200,false));
        keymaps->insert(pair<int,keyfunc>(GLUT_KEY_INSERT+200,&Object::key_insert));
        keys->insert(pair<int,bool>(GLUT_KEY_INSERT+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_INSERT+200,false));
}
