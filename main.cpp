#include <iostream>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Image.h"
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
        (*Engine::keys->find(key)).second = true;
        (*Engine::keys2->find(key)).second = true;
}

void handleKeyrelease(unsigned char key, int x, int y) {
        (*Engine::keys->find(key)).second = false;
        //(*Engine::keys2->find(key)).second = false;
	switch (key) {
		case 27: //Escape key
			exit(0);
	}
}


void handleMouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			cout << "main.cpp handleMouse" << endl;
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
	Engine::setMouse(x,y);
}

void handleMouseMotion(int x, int y) {
	Engine::setMouse(x,y);
}

void handleSpecialKeypress(int key, int x, int y) {
        (*Engine::keys->find(key+200)).second = true;
}

void handleSpecialKeyrelease(int key, int x, int y) {
        (*Engine::keys->find(key+200)).second = false;
}

void initRendering() {

	/*glEnable(GL_DEPTH_TEST);*/
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_CULL_FACE);

	cout << "main.cpp initRendering initializing engine" << endl;
        Engine::init();
}

void handleResize(int w, int h) {
	cout << "main.cpp handleResize begin" << endl;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,w,h,0,-100,1000);
	Engine::currentRoom->width = w;
	Engine::currentRoom->height = h;
	cout << "main.cpp handleResize completed " << endl;
}

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(Engine::currentRoom->r, Engine::currentRoom->g, Engine::currentRoom->b,0);

        Engine::currentRoom->draw();
	
	glutSwapBuffers();
}

void update(int value) {
        // begin step
        Engine::beginStep();
        // fire events
        Engine::handleEvents();
        // collision
        Engine::checkCollisions();
        // step
        Engine::step();
        // end step
        Engine::endStep();
        // draw
	glutPostRedisplay();
	glutTimerFunc(1000/Engine::currentRoom->getSpeed(), update, 0);
}

void doKeys(int value) {
	Engine::handleKeyboard();
	glutTimerFunc(300,doKeys,0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	cout << "main.cpp main program entered" << endl;	

	glutCreateWindow("Game name!");
	initRendering();

        if (Engine::currentRoom == NULL) {
                cout << "No rooms defined." << endl;
                exit(1);
        }
	
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutKeyboardUpFunc(handleKeyrelease);
	glutSpecialFunc(handleSpecialKeypress);
	glutSpecialUpFunc(handleSpecialKeyrelease);
	glutMouseFunc(handleMouse);
	glutMotionFunc(handleMouseMotion);
	glutPassiveMotionFunc(handleMouseMotion);
	glutReshapeFunc(handleResize);
	glutTimerFunc(1, update, 0);
	glutTimerFunc(300,doKeys, 0);
	
	glutMainLoop();
	return 0;
}









