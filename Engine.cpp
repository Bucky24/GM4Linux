#include "Engine.h"
#include <cstdlib>
#include "Rooms.h"
#include "sprites.h"

//vector<ObjectType *> Engine::objectref;
vector<Image *> Engine::imageref;
vector<Object *> Engine::instanceref;
vector<Room *> Engine::roomref;
vector< Font *> Engine::fonts;
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
float Engine::mousex;
float Engine::mousey;
double Engine::r;
double Engine::g;
double Engine::b;
Font *Engine::currentFont;
arraymap *Engine::vecList;
vector<fstream *> *Engine::filePtrRead;
vector<fstream *> *Engine::filePtrWrite;
map<string,Variable *> *Engine::globalVars;
vector<vector<Variable *> *> *Engine::vectors;
Variable *Engine::keyboardString;

void Engine::init() {

	Engine::keyboardString = new Variable("");

	cout << "engine.cpp init begin initialization" << endl;
	Engine::currentRoom = NULL;

	Engine::globalVars = new map<string,Variable *>();

	cout << "engine.cpp init creating reference vectors" << endl;
        Engine::instanceref = *(new vector<Object *>());
        //Engine::objectref = *(new vector<ObjectType *>());
        Engine::imageref = *(new vector<Image *>());
        Engine::roomref = *(new vector<Room *>());
	Engine::fonts = *(new vector<Font *>());

	Engine::vecList = new vector<map<int, Variable *> *>();
	Engine::vectors = new vector<vector<Variable *> *>();

	Engine::filePtrRead = new vector<fstream *>();
	Engine::filePtrWrite = new vector<fstream *>();

	cout << "engine.cpp init creating instance maps" << endl;
        Engine::instances = new instancemap();
	/* -- INSTANCE MAP -- */

	cout << "engine.cpp init creating objects/rooms/images" << endl;

        fillImages();
        fillObjects();
        fillRooms();
	cout << "engine.cpp completed creation of rooms " << endl;
	fillFonts();

        collisionmap = new collidemap();

	cout << "engine.cpp init registering collisions" << endl;

        registerCollisions();

        Engine::mouse_left_flagged = false;
        Engine::mouse_left_flagged_laststep = false;
        Engine::mouse_right_flagged = false;
        Engine::mouse_right_flagged_laststep = false;
        Engine::mouse_center_flagged = false;
        Engine::mouse_center_flagged_laststep = false;

	cout << "engine.cpp init creating keymaps" << endl;

        Engine::keys = new keyhitmap();
        Engine::keyslaststep = new keyhitmap();
        Engine::keymaps = new keymap();
        Engine::keydownmaps = new keymap();
        Engine::keyupmaps = new keymap();

	cout << "engine.cpp init creating function maps " << endl;

        generateFunctionMaps();

	Engine::r = 0;
	Engine::g = 0;
	Engine::b = 0;

	cout << "engine.cpp init initialization complete " << endl;
}

void Engine::fillObjects() {
	/* -- CREATE OBJECT TYPES -- */
}

void Engine::fillImages() {
	initSprites();
	/* -- CREATE IMAGES -- */
}

void Engine::fillRooms() {
	/* -- CREATE ROOMS -- */

	cout << "engine.cpp fillRooms there are " << Engine::roomref.size() << " rooms" << endl;
	if (Engine::roomref.size() > 0) {	
        	Engine::currentRoom = roomref[0];
		cout << "engine.cpp fillRooms current room creation code " << endl;
		Engine::currentRoom->initInstances();
		Engine::currentRoom->create();
		cout << "engine.cpp fillRooms reshaping window to " << Engine::currentRoom->width << "," << Engine::currentRoom->height << endl;
		// forcing a reshape will cause main program to change to current room size
		glutReshapeWindow(Engine::currentRoom->width,Engine::currentRoom->height);
		cout << "engine.cpp window reshaped " << endl;
	}
}

void Engine::fillFonts() {
	/* -- CREATE FONTS -- */

	cout << "engine.cpp fillFonts there are " << Engine::fonts.size() << " fonts" << endl;
	if (Engine::fonts.size() > 0) {
		Engine::currentFont = fonts[0];
	}
}

void Engine::registerCollisions() {
	/* -- REGISTER COLLISIONS -- */
}

void Engine::handleEvents() {
        vector<Object *> instances = Engine::currentRoom->getInstances();
        unsigned int i;
        //int j;
        keyhitmap::iterator itor = keys->begin();
        while (itor != keys->end()) {
                bool val = (*itor).second;
                int id = (*itor).first;
                if (val == true) {
                        objfunc function = (*(keymaps->find(id))).second;
                        if (function != NULL) {
                                for (i=0;i<instances.size();i++) {
                                        Object *inst = instances[i];
					if (inst != NULL) {
                                        	(inst->*function)();
					}
                                }
                        }
			if (id >= 32 && id < 127) {
				string str = Engine::keyboardString->getS();
				str += (char)id;
				*(Engine::keyboardString) = str;
			} else if (id == 8) {
				string str = Engine::keyboardString->getS();
				str = str.substr(0,str.size()-1);
				*(Engine::keyboardString) = str;
			}
                }
                itor ++;
        }

	// left button
	if (mouse_left_flagged && !mouse_left_flagged_laststep) {
		cout << "engine.cpp handleEvents mouse left click at " << Engine::mousex << "," << Engine::mousey << " " << instances.size() << endl;
		for (i=0;i<instances.size();i++) {
			Object *inst = instances[i];
			if (inst != NULL) {
				if (inst->pointInside(Engine::mousex,Engine::mousey)) {
	                		inst->mousepressed_left();
				}
				inst->globalmousepressed_left();
			}
                }
	}
	if (mouse_left_flagged) {
		for (i=0;i<instances.size();i++) {
                	Object *inst = instances[i];
			if (inst != NULL) {
			}
                }
	}
	if (!mouse_left_flagged && mouse_left_flagged_laststep) {
		for (i=0;i<instances.size();i++) {
                	Object *inst = instances[i];
			if (inst != NULL) {
				inst->globalmousereleased_left();
			}
                }
	}

	// right button
	if (mouse_right_flagged && !mouse_right_flagged_laststep) {
		for (i=0;i<instances.size();i++) {
                	Object *inst = instances[i];
			if (inst != NULL) {
				if (inst->pointInside(Engine::mousex,Engine::mousey)) {
                        		inst->mousepressed_right();
				}
				inst->globalmousepressed_right();
			}
                }
	}
	if (mouse_right_flagged) {
		for (i=0;i<instances.size();i++) {
                	Object *inst = instances[i];
			if (inst != NULL) {
                        	//inst->mouseclicked_right();
			}
                }
	}
	if (!mouse_right_flagged && mouse_right_flagged_laststep) {
		for (i=0;i<instances.size();i++) {
                	Object *inst = instances[i];
			if (inst != NULL) {
                        	//inst->mousereleased_right();
				inst->globalmousereleased_right();
			}
                }
	}

	// middle button
	if (mouse_center_flagged && !mouse_center_flagged_laststep) {
		for (i=0;i<instances.size();i++) {
                	Object *inst = instances[i];
			if (inst != NULL) {
				if (inst->pointInside(Engine::mousex,Engine::mousey)) {
                        		inst->mousepressed_middle();
				}
				inst->globalmousepressed_middle();
			}
                }
	}
	if (mouse_center_flagged) {
		for (i=0;i<instances.size();i++) {
                	Object *inst = instances[i];
			if (inst != NULL) {
                        	//inst->mouseclicked_middle();
			}
                }
	}
	if (!mouse_center_flagged && mouse_center_flagged_laststep) {
		for (i=0;i<instances.size();i++) {
                	Object *inst = instances[i];
			if (inst != NULL) {
                        	//inst->mousereleased_middle();
				inst->globalmousereleased_middle();
			}
                }
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
        for (i=0;i<instances.size();i++) {
                Object *inst = instances[i];
		if (inst != NULL) {
                	inst->step_begin();
		}
        }
}

void Engine::step() {
        vector<Object *> instances = Engine::currentRoom->getInstances();
        unsigned int i;
        for (i=0;i<instances.size();i++) {
                Object *inst = instances[i];
		if (inst != NULL) {
                	inst->step();
		}
        }
}

void Engine::endStep() {
        vector<Object *> instances = Engine::currentRoom->getInstances();
        unsigned int i;
        for (i=0;i<instances.size();i++) {
                Object *inst = instances[i];
		if (inst != NULL) {
                	inst->step_end();
		}
	}
	
	updateObjects();
}

void Engine::checkCollisions() {
        collidemap::iterator it;
        unsigned int i,j;
        for (it=collisionmap->begin();it!=collisionmap->end();it++) {
                objlist *list = Engine::instances->find(it->first)->second;
                objlist *list2 = Engine::instances->find(it->second)->second;
                for (i=0;i<list->size();i++) {
			for (j=0;j<list2->size();j++) {
                        	if (list->at(i)->check_collision_with_object(list2->at(j))) {
                        	        list->at(i)->collide_with(list2->at(i)->getId());
                        	        list2->at(j)->collide_with(list->at(i)->getId());
                        	}
			}
                }
        }
}

/*ObjectType *Engine::getObject(unsigned int id) {
        if (id >= objectref.size()) {
                return NULL;
        }
        return objectref[id];
}*/

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

void Engine::setMouse(int x, int y) {
	Engine::mousex = x;
	Engine::mousey = y;
}

void Engine::setColors(double r, double g, double b) {
	Engine::r = r;
	Engine::g = g;
	Engine::b = b;
}

void Engine::updateObjects() {
	vector<Object *> instances = Engine::currentRoom->getInstances();
        unsigned int i;
        for (i=0;i<instances.size();i++) {
                Object *inst = instances[i];
		if (inst != NULL) {
                	

			// do various things to move objects, etc

			inst->variables["x"] = inst->x;
			inst->variables["y"] = inst->y;
		}
	}
}










void Engine::generateFunctionMaps() {
        //keys = new keyhitmap();
        //keyslaststep = new keyhitmap();
        //keymaps = new keymap();
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_F1+200,&Object::key_F1));
        keyupmaps->insert(pair<int,objfunc>(GLUT_KEY_F1+200,&Object::keyup_F1));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_F1+200,&Object::keydown_F1));
        keys->insert(pair<int,bool>(GLUT_KEY_F1+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_F1+200,false));
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_F2+200,&Object::key_F2));
        keyupmaps->insert(pair<int,objfunc>(GLUT_KEY_F2+200,&Object::keyup_F2));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_F2+200,&Object::keydown_F2));
        keys->insert(pair<int,bool>(GLUT_KEY_F2+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_F2+200,false));
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_F3+200,&Object::key_F3));
        keyupmaps->insert(pair<int,objfunc>(GLUT_KEY_F3+200,&Object::keyup_F3));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_F3+200,&Object::keydown_F3));
        keys->insert(pair<int,bool>(GLUT_KEY_F3+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_F3+200,false));
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_F4+200,&Object::key_F4));
        keyupmaps->insert(pair<int,objfunc>(GLUT_KEY_F4+200,&Object::keyup_F4));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_F4+200,&Object::keydown_F4));
        keys->insert(pair<int,bool>(GLUT_KEY_F4+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_F4+200,false));
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_F5+200,&Object::key_F5));
        keyupmaps->insert(pair<int,objfunc>(GLUT_KEY_F5+200,&Object::keyup_F5));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_F5+200,&Object::keydown_F5));
        keys->insert(pair<int,bool>(GLUT_KEY_F5+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_F5+200,false));
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_F6+200,&Object::key_F6));
        keyupmaps->insert(pair<int,objfunc>(GLUT_KEY_F6+200,&Object::keyup_F6));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_F6+200,&Object::keydown_F6));
        keys->insert(pair<int,bool>(GLUT_KEY_F6+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_F6+200,false));
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_F7+200,&Object::key_F7));
        keyupmaps->insert(pair<int,objfunc>(GLUT_KEY_F7+200,&Object::keyup_F7));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_F7+200,&Object::keydown_F7));
        keys->insert(pair<int,bool>(GLUT_KEY_F7+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_F7+200,false));
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_F8+200,&Object::key_F8));
        keyupmaps->insert(pair<int,objfunc>(GLUT_KEY_F8+200,&Object::keyup_F8));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_F8+200,&Object::keydown_F8));
        keys->insert(pair<int,bool>(GLUT_KEY_F8+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_F8+200,false));
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_F9+200,&Object::key_F9));
        keyupmaps->insert(pair<int,objfunc>(GLUT_KEY_F9+200,&Object::keyup_F9));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_F9+200,&Object::keydown_F9));
        keys->insert(pair<int,bool>(GLUT_KEY_F9+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_F9+200,false));
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_F10+200,&Object::key_F10));
        keyupmaps->insert(pair<int,objfunc>(GLUT_KEY_F10+200,&Object::keyup_F10));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_F10+200,&Object::keydown_F10));
        keys->insert(pair<int,bool>(GLUT_KEY_F10+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_F10+200,false));
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_F11+200,&Object::key_F11));
        keyupmaps->insert(pair<int,objfunc>(GLUT_KEY_F11+200,&Object::keyup_F11));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_F11+200,&Object::keydown_F11));
        keys->insert(pair<int,bool>(GLUT_KEY_F11+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_F11+200,false));
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_F12+200,&Object::key_F12));
        keyupmaps->insert(pair<int,objfunc>(GLUT_KEY_F12+200,&Object::keyup_F12));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_F12+200,&Object::keydown_F12));
        keys->insert(pair<int,bool>(GLUT_KEY_F12+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_F12+200,false));
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_UP+200,&Object::key_up));
        keyupmaps->insert(pair<int,objfunc>(GLUT_KEY_UP+200,&Object::keyup_up));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_UP+200,&Object::keydown_up));
        keys->insert(pair<int,bool>(GLUT_KEY_UP+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_UP+200,false));
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_DOWN+200,&Object::key_down));
        keyupmaps->insert(pair<int,objfunc>(GLUT_KEY_DOWN+200,&Object::keyup_down));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_DOWN+200,&Object::keydown_down));
        keys->insert(pair<int,bool>(GLUT_KEY_DOWN+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_DOWN+200,false));
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_LEFT+200,&Object::key_left));
        keyupmaps->insert(pair<int,objfunc>(GLUT_KEY_LEFT+200,&Object::keyup_left));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_LEFT+200,&Object::keydown_left));
        keys->insert(pair<int,bool>(GLUT_KEY_LEFT+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_LEFT+200,false));
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_RIGHT+200,&Object::key_right));
        keyupmaps->insert(pair<int,objfunc>(GLUT_KEY_RIGHT+200,&Object::keyup_right));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_RIGHT+200,&Object::keydown_right));
        keys->insert(pair<int,bool>(GLUT_KEY_RIGHT+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_RIGHT+200,false));
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_PAGE_UP+200,&Object::key_page_up));
        keyupmaps->insert(pair<int,objfunc>(GLUT_KEY_PAGE_UP+200,&Object::keyup_page_up));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_PAGE_UP+200,&Object::keydown_page_up));
        keys->insert(pair<int,bool>(GLUT_KEY_PAGE_UP+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_PAGE_UP+200,false));
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_PAGE_DOWN+200,&Object::key_page_down));
        keyupmaps->insert(pair<int,objfunc>(GLUT_KEY_PAGE_DOWN+200,&Object::keyup_page_down));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_PAGE_DOWN+200,&Object::keydown_page_down));
        keys->insert(pair<int,bool>(GLUT_KEY_PAGE_DOWN+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_PAGE_DOWN+200,false));
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_HOME+200,&Object::key_home));
        keyupmaps->insert(pair<int,objfunc>(GLUT_KEY_HOME+200,&Object::keyup_home));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_HOME+200,&Object::keydown_home));
        keys->insert(pair<int,bool>(GLUT_KEY_HOME+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_HOME+200,false));
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_END+200,&Object::key_end));
        keyupmaps->insert(pair<int,objfunc>(GLUT_KEY_END+200,&Object::keyup_end));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_END+200,&Object::keydown_end));
        keys->insert(pair<int,bool>(GLUT_KEY_END+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_END+200,false));
        keymaps->insert(pair<int,objfunc>(GLUT_KEY_INSERT+200,&Object::key_insert));
        keyupmaps->insert(pair<int,objfunc>(GLUT_KEY_INSERT+200,&Object::keyup_insert));
        keydownmaps->insert(pair<int,objfunc>(GLUT_KEY_INSERT+200,&Object::keydown_insert));
        keys->insert(pair<int,bool>(GLUT_KEY_INSERT+200,false));
        keyslaststep->insert(pair<int,bool>(GLUT_KEY_INSERT+200,false));
        keys->insert(pair<int,bool>(8,false));
        keyslaststep->insert(pair<int,bool>(8,false));

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
        keys->insert(pair<int,bool>(' ',false));
        keyslaststep->insert(pair<int,bool>(' ',false));
        keys->insert(pair<int,bool>('1',false));
        keyslaststep->insert(pair<int,bool>('1',false));
        keys->insert(pair<int,bool>('2',false));
        keyslaststep->insert(pair<int,bool>('2',false));
        keys->insert(pair<int,bool>('3',false));
        keyslaststep->insert(pair<int,bool>('3',false));
        keys->insert(pair<int,bool>('4',false));
        keyslaststep->insert(pair<int,bool>('4',false));
        keys->insert(pair<int,bool>('5',false));
        keyslaststep->insert(pair<int,bool>('5',false));
        keys->insert(pair<int,bool>('6',false));
        keyslaststep->insert(pair<int,bool>('6',false));
        keys->insert(pair<int,bool>('7',false));
        keyslaststep->insert(pair<int,bool>('7',false));
        keys->insert(pair<int,bool>('8',false));
        keyslaststep->insert(pair<int,bool>('8',false));
        keys->insert(pair<int,bool>('9',false));
        keyslaststep->insert(pair<int,bool>('9',false));
        keys->insert(pair<int,bool>('0',false));
        keyslaststep->insert(pair<int,bool>('0',false));

        keys->insert(pair<int,bool>('[',false));
        keyslaststep->insert(pair<int,bool>('[',false));
        keys->insert(pair<int,bool>(']',false));
        keyslaststep->insert(pair<int,bool>(']',false));
        keys->insert(pair<int,bool>('/',false));
        keyslaststep->insert(pair<int,bool>('/',false));
        keys->insert(pair<int,bool>('-',false));
        keyslaststep->insert(pair<int,bool>('-',false));
        keys->insert(pair<int,bool>('+',false));
        keyslaststep->insert(pair<int,bool>('+',false));
        keys->insert(pair<int,bool>('=',false));
        keyslaststep->insert(pair<int,bool>('=',false));
        keys->insert(pair<int,bool>('(',false));
        keyslaststep->insert(pair<int,bool>('(',false));
        keys->insert(pair<int,bool>(')',false));
        keyslaststep->insert(pair<int,bool>(')',false));
        keys->insert(pair<int,bool>(',',false));
        keyslaststep->insert(pair<int,bool>(',',false));
        keys->insert(pair<int,bool>('.',false));
        keyslaststep->insert(pair<int,bool>('.',false));
        keys->insert(pair<int,bool>(';',false));
        keyslaststep->insert(pair<int,bool>(';',false));
        keys->insert(pair<int,bool>('*',false));
        keyslaststep->insert(pair<int,bool>('*',false));

        beginStepEvent = &Object::step_begin;
        stepEvent = &Object::step;
        endStepEvent = &Object::step_end;
}
