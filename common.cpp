#include "common.h"

void draw_character(char letter, float x, float y) {
	if (x == 0)x++;
	if (y == 0)y++;
	glColor3f(0,0,0);
	if (Engine::currentFont->letters.find(letter) == Engine::currentFont->letters.end()) {
		return;
	}
	Letter *let = Engine::currentFont->letters.find(letter)->second;
	int i,j;
	if (let == NULL) {
		return;
	}

	glBegin(GL_POINTS);
	for (i=0;i<let->height;i++) {
		for (j=0;j<let->width;j++) {
			int index = (i*let->width+j)*3;
			if (let->pixels[index] != -1 || let->pixels[index+1] != -1 || let->pixels[index+2] != -1) {
				//glColor3f((float)let->pixels[index]/255,(float)let->pixels[index+1]/255,(float)let->pixels[index+2]/255);
				glVertex2f(j+x,i+y);
			}
		}
	}
	glEnd();
	glColor3f(Engine::r,Engine::g,Engine::b);
}

int instance_create(unsigned int id, int x, int y) {
        int ret = noone;
        Object *inst = NULL;
	/* -- OBJECT CREATION -- */
	cout << "common.cpp instance_create " << id << endl;
        if (inst != NULL) {
                Engine::instanceref.push_back(inst);
                Engine::instances->find(id)->second->push_back(inst);
		if (Engine::currentRoom != NULL) {
			cout << "common.cpp instance_create room is not null" << endl;
			Engine::currentRoom->instances.push_back(inst);
		}
                ret = Engine::instanceid;
                Engine::instanceid++;
        }
        return ret;
}

void draw_sprite(unsigned int sprite, int offset, float x, float y) {
        if (sprite >= Engine::imageref.size()) {
                return;
        }
        Engine::imageref[sprite]->draw(x,y);
}

void draw_line(float x1, float y1, float x2, float y2) {
	if (x1 == 0)x1++;
	if (x2 == 0)x2++;
	if (y1 == 0)y1++;
	if (y2 == 0)y2++;
	glColor3f(Engine::r,Engine::g,Engine::b);
	glBegin(GL_LINES);
	glVertex3f(x1,y1,0);
	glVertex3f(x2,y2,0);
	glEnd();
}

void draw_line_color(float x1, float y1, float x2, float y2, float r, float g, float b) {
	if (x1 == 0)x1++;
	if (x2 == 0)x2++;
	if (y1 == 0)y1++;
	if (y2 == 0)y2++;
	glColor3f(r,g,b);
	glBegin(GL_LINES);
	glVertex3f(x1,y1,0);
	glVertex3f(x2,y2,0);
	glEnd();
	glColor3f(Engine::r,Engine::g,Engine::b);
}

int instance_number(int object) {
	instancemap::iterator itor = Engine::instances->find(object);
	if (itor == Engine::instances->end()) {
		return 0;
	}
	return itor->second->size();
}

int instance_find(int object, int number) {
	instancemap::iterator itor = Engine::instances->find(object);
	if (itor == Engine::instances->end()) {
		return 0;
	}
	objlist *list = itor->second;
	return list->at(number)->id;
}

void draw_set_color_rgb(int r, int g, int b) {
	Engine::r = ((float)r)/255;
	Engine::g = ((float)g)/255;
	Engine::b = ((float)b)/255;
}

void draw_point(float x, float y) {
	glColor3f(Engine::r,Engine::g,Engine::b);
	glBegin(GL_POINTS);
	glVertex2f(x,y);
	glEnd();
}

void draw_text(string text, float x, float y) {
	unsigned int i;
	for (i=0;i<text.size();i++) {
		char let = text.at(i);
		draw_character(let,x,y);
		x += Engine::currentFont->letters[let]->width;
	}
}

void draw_text(Variable *text, float x, float y) {
	draw_text(text->getS(),x,y);
}

void draw_rectangle(float x1, float y1, float x2, float y2) {
	if (x1 == 0)x1++;
	if (x2 == 0)x2++;
	if (y1 == 0)y1++;
	if (y2 == 0)y2++;
	glColor3f(Engine::r,Engine::g,Engine::b);
	glBegin(GL_POLYGON);
	glVertex3f(x1,y1,0);
	glVertex3f(x2,y1,0);
	glVertex3f(x2,y2,0);
	glVertex3f(x1,y2,0);
	glEnd();
}

void draw_rectangle_color(float x1, float y1, float x2, float y2, float r, float g, float b) {
	if (x1 == 0)x1++;
	if (x2 == 0)x2++;
	if (y1 == 0)y1++;
	if (y2 == 0)y2++;
	glColor3f(r,g,b);
	glBegin(GL_POLYGON);
	glVertex3f(x1,y1,0);
	glVertex3f(x2,y1,0);
	glVertex3f(x2,y2,0);
	glVertex3f(x1,y2,0);
	glEnd();
	glColor3f(Engine::r,Engine::g,Engine::b);
}

void Tokenize(const string& str,
                      vector<string>& tokens,
                      const string& delimiters = " ")
{
    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}


int file_text_open_write(string filename) {
	fstream file;
	file.open(filename.c_str(),ios::out);
	if (!file.is_open()) {
		cout << "common.cpp file_text_open_write cannot open " << filename << endl;
		return -4;
	}
	
	unsigned int i;
	for (i=0;i<Engine::filePtrWrite->size();i++) {
		if (Engine::filePtrWrite->at(i) == NULL) {
			Engine::filePtrWrite->at(i) = &file;
			return i;
		}
	}

	Engine::filePtrWrite->push_back(&file);
	return Engine::filePtrWrite->size()-1;
}

void file_text_close(int handle) {
	if (handle < 0) return;
	if (Engine::filePtrWrite->size() > (unsigned int)handle) {
		fstream *file = Engine::filePtrWrite->at(handle);
		if (file != NULL) {
			file->close();
			delete(file);
		}
		Engine::filePtrWrite->at(handle) = NULL;
	}
}

void file_text_write_string(int handle, string data) {
	
}

int ds_list_create() {	
	vector<Variable *> *vec = new vector<Variable *>();
	Engine::vectors->push_back(vec);
	return Engine::vectors->size()-1;
}

void ds_list_add(int id, Variable *value) {
	if ((signed int)Engine::vectors->size() <= id) {
		return;
	}
	if (Engine::vectors->at(id) == NULL) {
		return;
	}
	Engine::vectors->at(id)->push_back(value);
}

void ds_list_add(int id, const char *value) {
	if ((signed int)Engine::vectors->size() <= id) {
		return;
	}
	if (Engine::vectors->at(id) == NULL) {
		return;
	}
	Variable *var = new Variable(value);
	Engine::vectors->at(id)->push_back(var);
}

Variable *ds_list_find_value(int id, int pos) {
	if ((signed int)Engine::vectors->size() <= id) {
		return new Variable(-4);
	}
	if (Engine::vectors->at(id) == NULL) {
		return new Variable(-4);
	}
	if ((signed int)Engine::vectors->at(id)->size() <= pos) {
		return new Variable(-4);
	}
	return Engine::vectors->at(id)->at(pos);
}

int ds_list_size(int id) {
	if ((signed int)Engine::vectors->size() <= id) {
		return -4;
	}
	return Engine::vectors->at(id)->size();
}
