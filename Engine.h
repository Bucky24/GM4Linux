#ifndef ENGINE
#define ENGINE

#define noone -4

#include "Objects.h"
#include <vector>
#include "Image.h"
#include "ObjectType.h"
#include "Room.h"

using namespace std;

class Engine {
public:
        static void init();
        static void fillObjects();
        static void fillImages();
        static void fillRooms();

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

        bool mouse_left_flagged;
        bool mouse_left_flagged_laststep;
        bool mouse_right_flagged;
        bool mouse_right_flagged_laststep;
        bool mouse_center_flagged;
        bool mouse_center_flagged_laststep;
        
};

#endif
