#ifndef ENGINE
#define ENGINE

#define noone -4

#include "Objects.h"
#include <vector>
#include "Image.h"
#include "ObjectType.h"
#include "Room.h"

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

class Engine {
public:
        static void init();
        static void fillObjects();
        static void fillImages();
        static void fillRooms();

        static void handleEvents();

        static vector<ObjectType *> objectref;
        static vector<Image *> imageref;
        static vector<Object *> instanceref;
        static vector<Room *> roomref;

        static bool keys[500];
        static bool keyslaststep[500];

        static int instanceid;
        static ObjectType *getObject(unsigned int id);
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
        
};

#endif
