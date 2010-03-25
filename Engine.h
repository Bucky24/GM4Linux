#ifndef ENGINE
#define ENGINE

#define noone -4

#include "Objects.h"
#include <vector>
#include "Image.h"
#include "ObjectType.h"
#include "Room.h"

using namespace std;

typedef struct references references;

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

        static int instanceid;
        static ObjectType *getObject(unsigned int id);
        static Object *getInstance(unsigned int id);
        static Image *getSprite(unsigned int id);
        static Room *getRoom(unsigned int id);
        static Room *currentRoom;
};

#endif
