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
#include "Util.h"
#include "Rooms.h"

using namespace std;

const float BOX_SIZE = 70.0f; //The length of each side of the cube
const float WINDOW_WIDTH = 800;
const float WINDOW_HEIGHT = 600;
//testobject *inst;
//int objectid;
//int instanceid;

void handleKeypress(unsigned char key, int x, int y) {
        printf("key: %d\n",key);
	switch (key) {
		case 27: //Escape key
			exit(0);
	}
}

void handleSpecialKeypress(int key, int x, int y) {
        printf("key: %d\n",key);
        vector<Object *> instances = Util::currentRoom->getInstances();
        unsigned int i;
        for (i=0;i<instances.size();i++) {
                Object *inst = instances[i];
	        switch (key) {
	                case GLUT_KEY_F1:
                                break;
                        case GLUT_KEY_F2:
                                break;
                        case GLUT_KEY_F3:
                                break;
                        case GLUT_KEY_F4:
                                break;
                        case GLUT_KEY_F5:
                                break;
                        case GLUT_KEY_F6:
                                break;
                        case GLUT_KEY_F7:
                                break;
                        case GLUT_KEY_F8:
                                break;
                        case GLUT_KEY_F9:
                                break;
                        case GLUT_KEY_F10:
                                break;
                        case GLUT_KEY_F11:
                                break;
                        case GLUT_KEY_F12:
                                break;
                        case GLUT_KEY_LEFT:
                                break;
                        case GLUT_KEY_UP:
                                inst->key_up();
                                break;
                        case GLUT_KEY_RIGHT:
                                break;
                        case GLUT_KEY_DOWN:
                                break;
                        case GLUT_KEY_PAGE_UP:
                                break;
                        case GLUT_KEY_PAGE_DOWN:
                                break;
                        case GLUT_KEY_HOME:
                                break;
                        case GLUT_KEY_END:
                                break;
                        case GLUT_KEY_INSERT:
                                break;
                }
        }
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

        Util::init();
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
        Util::currentRoom->draw();
	
	glutSwapBuffers();
}

//Called every 25 milliseconds
void update(int value) {
        // begin step
        // collision
        // step
        // end step
        // draw
	glutPostRedisplay();
	glutTimerFunc(1000/Util::currentRoom->getSpeed(), update, 0);
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
	glutReshapeFunc(handleResize);
	glutTimerFunc(25, update, 0);
	
	glutMainLoop();
	return 0;
}








