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
keymap *Engine::keydownmaps;
keymap *Engine::keyupmaps;
objfunc Engine::beginStepEvent;
objfunc Engine::stepEvent;
objfunc Engine::endStepEvent;
instancemap *Engine::instances;
collidemap *Engine::collisionmap;

void Engine::init() {
        //refs = (references *)malloc(sizeof(struct references));
        instanceref = *(new vector<Object *>());
        objectref = *(new vector<ObjectType *>());
        imageref = *(new vector<Image *>());
        roomref = *(new vector<Room *>());

        instances = new instancemap();
        instances->insert(pair<int,objlist *>(0,new objlist()));
        instances->insert(pair<int,objlist *>(0,new objlist()));

        fillObjects();
        fillImages();
        fillRooms();

        collisionmap = new collidemap();

        registerCollisions();

        mouse_left_flagged = false;
        mouse_left_flagged_laststep = false;
        mouse_right_flagged = false;
        mouse_right_flagged_laststep = false;
        mouse_center_flagged = false;
        mouse_center_flagged_laststep = false;

        keys = new keyhitmap();
        keyslaststep = new keyhitmap();
        keymaps = new keymap();
        keydownmaps = new keymap();
        keyupmaps = new keymap();

        generateFunctionMaps();
}

void Engine::fillObjects() {
        objectref.push_back(new ObjectType(0,"testobject",0));
        objectref.push_back(new ObjectType(1,"obj_wall",0));
}

void Engine::fillImages() {
        imageref.push_back(new Image((char *)"vtr.bmp",64,64,IMAGE_FILE));
}

void Engine::fillRooms() {
        roomref.push_back(new testroom(0,"testroom",800,600));

        currentRoom = roomref[0];
}

void Engine::registerCollisions() {
        // collision between testobject and obj_wall;
        collisionmap->insert(pair<ObjectType *,ObjectType *>(objectref[0],objectref[1]));
}

void Engine::handleEvents() {
        vector<Object *> instances = Engine::currentRoom->getInstances();
        unsigned int i;
        //int j;
        //printf("%d %d\n",button,state);
        keyhitmap::iterator itor = keys->begin();
        while (itor != keys->end()) {
                bool val = (*itor).second;
                int id = (*itor).first;
                if (val == true) {
                        objfunc function = (*(keymaps->find(id))).second;
                        if (function != NULL) {
                                for (i=0;i<instances.size();i++) {
                                        Object *inst = instances[i];
                                        (inst->*function)();
                                }
                        }
                }
                itor ++;
        }
        itor = keys->begin();
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

void Engine::beginStep() {
        vector<Object *> instances = Engine::currentRoom->getInstances();
        unsigned int i;
        objfunc function = beginStepEvent;
        if (function != NULL) {
                for (i=0;i<instances.size();i++) {
                        Object *inst = instances[i];
                        (inst->*function)();
                }
        }
}

void Engine::step() {
        vector<Object *> instances = currentRoom->getInstances();
        unsigned int i;
        objfunc function = stepEvent;
        if (function != NULL) {
                for (i=0;i<instances.size();i++) {
                        Object *inst = instances[i];
                        (inst->*function)();
                }
        }
}

void Engine::endStep() {
        vector<Object *> instances = currentRoom->getInstances();
        unsigned int i;
        objfunc function = endStepEvent;
        if (function != NULL) {
                for (i=0;i<instances.size();i++) {
                        Object *inst = instances[i];
                        (inst->*function)();
                }
        }
}

void Engine::checkCollisions() {
        collidemap::iterator it;
        unsigned int i;
        for (it=collisionmap->begin();it!=collisionmap->end();it++) {
                objlist *list = instances->find((*it).first->getId())->second;
                for (i=0;i<list->size();i++) {
                        if (list->at(i)->check_collision_with_object((*it).second->getId())) {
                                list->at(i)->collide_with((*it).second->getId());
                        }
                }
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











void Engine::generateFunctionMaps() {
        //keys = new keyhitmap();
        //keyslaststep = new keyhitmap();
        //keymaps = new keymap();
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_F1+200,&Object::key_F1));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_F1+200,&Object::keydown_F1));
        keys->insert(pair<int,bool>(GLUT_KEY_F1+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_F1+200,false));
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_F2+200,&Object::key_F2));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_F2+200,&Object::keydown_F2));
        keys->insert(pair<int,bool>(GLUT_KEY_F2+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_F2+200,false));
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_F3+200,&Object::key_F3));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_F3+200,&Object::keydown_F3));
        keys->insert(pair<int,bool>(GLUT_KEY_F3+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_F3+200,false));
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_F4+200,&Object::key_F4));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_F4+200,&Object::keydown_F4));
        keys->insert(pair<int,bool>(GLUT_KEY_F4+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_F4+200,false));
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_F5+200,&Object::key_F5));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_F5+200,&Object::keydown_F5));
        keys->insert(pair<int,bool>(GLUT_KEY_F5+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_F5+200,false));
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_F6+200,&Object::key_F6));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_F6+200,&Object::keydown_F6));
        keys->insert(pair<int,bool>(GLUT_KEY_F6+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_F6+200,false));
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_F7+200,&Object::key_F7));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_F7+200,&Object::keydown_F7));
        keys->insert(pair<int,bool>(GLUT_KEY_F7+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_F7+200,false));
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_F8+200,&Object::key_F8));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_F8+200,&Object::keydown_F8));
        keys->insert(pair<int,bool>(GLUT_KEY_F8+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_F8+200,false));
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_F9+200,&Object::key_F9));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_F9+200,&Object::keydown_F9));
        keys->insert(pair<int,bool>(GLUT_KEY_F9+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_F9+200,false));
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_F10+200,&Object::key_F10));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_F10+200,&Object::keydown_F10));
        keys->insert(pair<int,bool>(GLUT_KEY_F10+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_F10+200,false));
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_F11+200,&Object::key_F11));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_F11+200,&Object::keydown_F11));
        keys->insert(pair<int,bool>(GLUT_KEY_F11+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_F11+200,false));
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_F12+200,&Object::key_F12));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_F12+200,&Object::keydown_F12));
        keys->insert(pair<int,bool>(GLUT_KEY_F12+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_F12+200,false));
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_UP+200,&Object::key_up));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_UP+200,&Object::keydown_up));
        keys->insert(pair<int,bool>(GLUT_KEY_UP+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_UP+200,false));
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_DOWN+200,&Object::key_down));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_DOWN+200,&Object::keydown_down));
        keys->insert(pair<int,bool>(GLUT_KEY_DOWN+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_DOWN+200,false));
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_LEFT+200,&Object::key_left));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_LEFT+200,&Object::keydown_left));
        keys->insert(pair<int,bool>(GLUT_KEY_LEFT+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_LEFT+200,false));
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_RIGHT+200,&Object::key_right));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_RIGHT+200,&Object::keydown_right));
        keys->insert(pair<int,bool>(GLUT_KEY_RIGHT+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_RIGHT+200,false));
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_PAGE_UP+200,&Object::key_page_up));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_PAGE_UP+200,&Object::keydown_page_up));
        keys->insert(pair<int,bool>(GLUT_KEY_PAGE_UP+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_PAGE_UP+200,false));
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_PAGE_DOWN+200,&Object::key_page_down));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_PAGE_DOWN+200,&Object::keydown_page_down));
        keys->insert(pair<int,bool>(GLUT_KEY_PAGE_DOWN+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_PAGE_DOWN+200,false));
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_HOME+200,&Object::key_home));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_HOME+200,&Object::keydown_home));
        keys->insert(pair<int,bool>(GLUT_KEY_HOME+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_HOME+200,false));
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_END+200,&Object::key_end));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_END+200,&Object::keydown_end));
        keys->insert(pair<int,bool>(GLUT_KEY_END+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_END+200,false));
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_INSERT+200,&Object::key_insert));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_INSERT+200,&Object::keydown_insert));
        keys->insert(pair<int,bool>(GLUT_KEY_INSERT+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_INSERT+200,false));
        keymaps->insert(pair<int,objfunc>('a',&Object::key_a));
        keys->insert(pair<int,bool>('a',false));
        keyslaststep->insert(pair<int,bool>('a',false));
        keymaps->insert(pair<int,objfunc>('b',&Object::key_b));
        keys->insert(pair<int,bool>('b',false));
        keyslaststep->insert(pair<int,bool>('b',false));
        keymaps->insert(pair<int,objfunc>('c',&Object::key_c));
        keys->insert(pair<int,bool>('c',false));
        keyslaststep->insert(pair<int,bool>('c',false));
        keymaps->insert(pair<int,objfunc>('d',&Object::key_d));
        keys->insert(pair<int,bool>('d',false));
        keyslaststep->insert(pair<int,bool>('d',false));
        keymaps->insert(pair<int,objfunc>('e',&Object::key_e));
        keys->insert(pair<int,bool>('e',false));
        keyslaststep->insert(pair<int,bool>('e',false));
        keymaps->insert(pair<int,objfunc>('f',&Object::key_f));
        keys->insert(pair<int,bool>('f',false));
        keyslaststep->insert(pair<int,bool>('f',false));
        keymaps->insert(pair<int,objfunc>('g',&Object::key_g));
        keys->insert(pair<int,bool>('g',false));
        keyslaststep->insert(pair<int,bool>('g',false));
        keymaps->insert(pair<int,objfunc>('h',&Object::key_h));
        keys->insert(pair<int,bool>('h',false));
        keyslaststep->insert(pair<int,bool>('h',false));
        keymaps->insert(pair<int,objfunc>('i',&Object::key_i));
        keys->insert(pair<int,bool>('i',false));
        keyslaststep->insert(pair<int,bool>('i',false));
        keymaps->insert(pair<int,objfunc>('j',&Object::key_j));
        keys->insert(pair<int,bool>('j',false));
        keyslaststep->insert(pair<int,bool>('j',false));
        keymaps->insert(pair<int,objfunc>('k',&Object::key_k));
        keys->insert(pair<int,bool>('k',false));
        keyslaststep->insert(pair<int,bool>('k',false));
        keymaps->insert(pair<int,objfunc>('l',&Object::key_l));
        keys->insert(pair<int,bool>('l',false));
        keyslaststep->insert(pair<int,bool>('l',false));
        keymaps->insert(pair<int,objfunc>('m',&Object::key_m));
        keys->insert(pair<int,bool>('m',false));
        keyslaststep->insert(pair<int,bool>('m',false));
        keymaps->insert(pair<int,objfunc>('n',&Object::key_n));
        keys->insert(pair<int,bool>('n',false));
        keyslaststep->insert(pair<int,bool>('n',false));
        keymaps->insert(pair<int,objfunc>('o',&Object::key_o));
        keys->insert(pair<int,bool>('o',false));
        keyslaststep->insert(pair<int,bool>('o',false));
        keymaps->insert(pair<int,objfunc>('p',&Object::key_p));
        keys->insert(pair<int,bool>('p',false));
        keyslaststep->insert(pair<int,bool>('p',false));
        keymaps->insert(pair<int,objfunc>('q',&Object::key_q));
        keys->insert(pair<int,bool>('q',false));
        keyslaststep->insert(pair<int,bool>('q',false));
        keymaps->insert(pair<int,objfunc>('r',&Object::key_r));
        keys->insert(pair<int,bool>('r',false));
        keyslaststep->insert(pair<int,bool>('r',false));
        keymaps->insert(pair<int,objfunc>('s',&Object::key_s));
        keys->insert(pair<int,bool>('s',false));
        keyslaststep->insert(pair<int,bool>('s',false));
        keymaps->insert(pair<int,objfunc>('t',&Object::key_t));
        keys->insert(pair<int,bool>('t',false));
        keyslaststep->insert(pair<int,bool>('t',false));
        keymaps->insert(pair<int,objfunc>('u',&Object::key_u));
        keys->insert(pair<int,bool>('u',false));
        keyslaststep->insert(pair<int,bool>('u',false));
        keymaps->insert(pair<int,objfunc>('v',&Object::key_v));
        keys->insert(pair<int,bool>('v',false));
        keyslaststep->insert(pair<int,bool>('v',false));
        keymaps->insert(pair<int,objfunc>('w',&Object::key_w));
        keys->insert(pair<int,bool>('w',false));
        keyslaststep->insert(pair<int,bool>('w',false));
        keymaps->insert(pair<int,objfunc>('x',&Object::key_x));
        keys->insert(pair<int,bool>('x',false));
        keyslaststep->insert(pair<int,bool>('x',false));
        keymaps->insert(pair<int,objfunc>('y',&Object::key_y));
        keys->insert(pair<int,bool>('y',false));
        keyslaststep->insert(pair<int,bool>('y',false));
        keymaps->insert(pair<int,objfunc>('z',&Object::key_z));
        keys->insert(pair<int,bool>('z',false));
        keyslaststep->insert(pair<int,bool>('z',false));

        beginStepEvent = &Object::step_begin;
        stepEvent = &Object::step;
        endStepEvent = &Object::step_end;
}
