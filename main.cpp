#include <iostream>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Image.h"
#include "ObjectType.h"
#include "Objects.h"
#include "Room.h"
#include <cstdio>
#include "Engine.h"
#include "Rooms.h"
#include <cstdlib>

using namespace std;

const float BOX_SIZE = 70.0f; //The length of each side of the cube
const float WINDOW_WIDTH = 800;
const float WINDOW_HEIGHT = 600;
//testobject *inst;
//int objectid;
//int instanceid;

void handleKeypress(unsigned char key, int x, int y) {
        printf("key: %d\n",key);
        (*Engine::keys->find(key)).second = true;
        //Engine::keys[key] = true;
	switch (key) {
		case 27: //Escape key
			exit(0);
	}
}


void handleMouse(int button, int state, int x, int y) {
        /*vector<Object *> instances = Engine::currentRoom->getInstances();
        unsigned int i;
        printf("%d %d\n",button,state);
        for (i=0;i<instances.size();i++) {
                Object *inst = instances[i];*/
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			Engine::mouse_left_flagged = true;
		} else if (state == GLUT_UP) {
			Engine::mouse_left_flagged = false;	
		}
	} else if (button == GLUT_RIGHT_BUTTON) {
		if (state == GLUT_DOWN) {
			Engine::mouse_right_flagged = true;
		} else if (state == GLUT_UP) {
			Engine::mouse_right_flagged = false;	
		}
	} else if (button == GLUT_MIDDLE_BUTTON) {
		if (state == GLUT_DOWN) {
			Engine::mouse_center_flagged = true;
		} else if (state == GLUT_UP) {
			Engine::mouse_center_flagged = false;	
		}
	}
	/*}*/
}

void handleSpecialKeypress(int key, int x, int y) {
        printf("key: %d\n",key);
        (*Engine::keys->find(key+200)).second = true;
        //Engine::keys[key+200] = true;
}

void initRendering() {
	//objectid = 0;
	//instanceid = 0;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	/*char *bler = (char *)malloc(sizeof(GL_UNSIGNED_BYTE)*16*16*3);

	for (int i=0;i<16*16*3;i+=1) {
		bler[i] = 0;
	}
	for (int i=0;i<16*16*3;i+=3) {
		bler[i] = 100;
	}*/
	
	//Image *image = new Image((char *)"vtr.bmp",64,64,IMAGE_FILE);
	//Image *image = new Image(bler,16,16,IMAGE_DATA);
	//ObjectType *obj = new ObjectType(objectid,"object",image);
	//objectid ++;
	//inst = new testobject(instanceid,obj,20,10);
	//instanceid ++;

        Engine::init();
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,WINDOW_WIDTH,WINDOW_HEIGHT,0,-100,1000);
}

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//inst->draw();
        Engine::currentRoom->draw();
	
	glutSwapBuffers();
}

//Called every 25 milliseconds
void update(int value) {
        // begin step
        // fire events
        Engine::handleEvents();
        // collision
        // step
        // end step
        // draw
	glutPostRedisplay();
	glutTimerFunc(1000/Engine::currentRoom->getSpeed(), update, 0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	
	glutCreateWindow("Game name!");
	initRendering();
	
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutSpecialFunc(handleSpecialKeypress);
	glutMouseFunc(handleMouse);
	glutReshapeFunc(handleResize);
	glutTimerFunc(25, update, 0);
	
	glutMainLoop();
	return 0;
}









