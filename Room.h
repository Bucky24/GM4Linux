#ifndef ROOMH
#define ROOMH

#include <vector>
#include <string>

using namespace std;

#include "Objects.h"

class Room {
public:
	Room(int i, string t, int w, int h, int sp = 30);
        virtual void initInstances();
	virtual void create();
	void draw();

	string getTitle() {return title;}
	int getId() {return id;}
        int getWidth() {return width;}
        int getheight() {return height;}
        vector<Object *> getInstances() {return instances;}
        int getSpeed() {return speed;}
protected:
	int id;
	string title;
        int width;
        int height;
        vector<Object *> instances;
        int speed;
};

#endif