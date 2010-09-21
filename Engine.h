#ifndef ENGINE
#define ENGINE

#include "Objects.h"
#include <vector>
#include "Image.h"
#include "Room.h"
#include <map>
#include "Font.h"

#include <iostream>
#include <fstream>

using namespace std;

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

typedef void (Object::*objfunc)();

typedef map<int,objfunc> keymap;

typedef map<int,bool> keyhitmap;

typedef vector<Object *> objlist;

typedef map<int,objlist *> instancemap;

typedef map<int,int> collidemap;

typedef vector<map<int, Variable *> *> arraymap;

class Engine {
public:
        static void init();
        static void fillObjects();
        static void fillImages();
        static void fillRooms();
	static void fillFonts();
        static void registerCollisions();

        static void generateFunctionMaps();

        static void handleEvents();
        static void beginStep();
        static void step();
        static void endStep();
        static void checkCollisions();

        //static vector<ObjectType *> objectref;
        static vector<Image *> imageref;
        static vector<Object *> instanceref;
        static vector<Room *> roomref;

        //static bool keys[500];
        static keyhitmap *keys;
        //static bool keyslaststep[500];
        static keyhitmap *keyslaststep;
        static objfunc beginStepEvent;
        static objfunc stepEvent;
        static objfunc endStepEvent;

        static int instanceid;
        //static ObjectType *getObject(unsigned int id);
        static Object *getInstance(unsigned int id);
        static Image *getSprite(unsigned int id);
        static Room *getRoom(unsigned int id);
        static Room *currentRoom;

        static bool mouse_left_flagged;
        static bool mouse_left_flagged_laststep;
        static bool mouse_right_flagged;
        static bool mouse_right_flagged_laststep;
        static bool mouse_center_flagged;
        static bool mouse_center_flagged_laststep;

	static float mousex;
	static float mousey;

	static void setMouse(int x, int y);
        
        static keymap *keymaps;
	static keymap *keydownmaps;
        static keymap *keyupmaps;

	static float r;
	static float g;
	static float b;

	static Font *currentFont;

	static void setColors(float,float,float);

        static instancemap *instances;

        static collidemap *collisionmap;

	static void updateObjects();

	static vector<Font *> fonts;

	static arraymap *vecList;

	static vector<fstream *> *filePtrRead;
	static vector<fstream *> *filePtrWrite;

	static map<string,Variable *> *globalVars;

	static vector<vector<Variable *> *> *vectors;
};

#endif
