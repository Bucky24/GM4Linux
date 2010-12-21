#include "common.h"

void draw_character(char letter, float x, float y) {
	if (x == 0) x++;
	if (y == 0) y++;
	
	int i,j;
	bool found = false;

	for (i=0;i<(signed int)Engine::currentFont->chars->size();i++) {
		if (Engine::currentFont->chars->at(i) == letter) {
			found = true;
			break;
		}
	}

	if (!found) {
		return;
	}

	Image *let = Engine::currentFont->letters->find(letter)->second;
	if (let == NULL) {
		return;
	}

	//let->draw(x,y);
	glColor3f(0,0,0);

	glBegin(GL_POINTS);
	for (i=0;i<let->height;i++) {
		for (j=0;j<let->width;j++) {
			int index = (i*let->width+j)*3;
			if (let->pixels[index] != -1 || let->pixels[index+1] != -1 || let->pixels[index+2] != -1) {
				double r = (unsigned char)let->pixels[index];
				double g = (unsigned char)let->pixels[index+1];
				double b = (unsigned char)let->pixels[index+2];
				glColor3d(r/255,g/255,b/255);
				glVertex2f(j+x,y+(let->height-i));
			}
		}
	}
	glEnd();
	glColor3d(Engine::r,Engine::g,Engine::b);

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
	Engine::r = ((double)r)/255;
	Engine::g = ((double)g)/255;
	Engine::b = ((double)b)/255;
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
		x += Engine::currentFont->widthOf(let)+2;
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
	fstream *file = new fstream();
	file->open(filename.c_str(),ios::out);
	if (!file->is_open()) {
		cout << "common.cpp file_text_open_write cannot open " << filename << endl;
		return -4;
	}
	
	unsigned int i;
	for (i=0;i<Engine::filePtrWrite->size();i++) {
		if (Engine::filePtrWrite->at(i) == NULL) {
			Engine::filePtrWrite->at(i) = file;
			return i;
		}
	}

	Engine::filePtrWrite->push_back(file);
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
	if (handle < 0) return;
	if (Engine::filePtrWrite->size() > (unsigned int)handle) {
		fstream *file = Engine::filePtrWrite->at(handle);
		if (file != NULL) {
			if (file->is_open()) {
				file->write(data.c_str(),data.length());
			}
		}
	}
}

int ds_list_create() {	
	vector<Variable *> *vec = new vector<Variable *>();
	Engine::vectors->push_back(vec);
	return Engine::vectors->size()-1;
}

void ds_list_add(Variable &id2, Variable &value) {
	int id = id2.getI();
	if ((signed int)Engine::vectors->size() <= id) {
		return;
	}
	if (Engine::vectors->at(id) == NULL) {
		return;
	}
	Variable *var = new Variable(value.getS());
	Engine::vectors->at(id)->push_back(var);
}

void ds_list_add(Variable &id2, const char *value) {
	int id = id2.getI();
	if ((signed int)Engine::vectors->size() <= id) {
		return;
	}
	if (Engine::vectors->at(id) == NULL) {
		return;
	}
	Variable *var = new Variable(value);
	Engine::vectors->at(id)->push_back(var);
}

void ds_list_add(Variable &id2, int value) {
	int id = id2.getI();
	if ((signed int)Engine::vectors->size() <= id) {
		return;
	}
	if (Engine::vectors->at(id) == NULL) {
		return;
	}
	Variable *var = new Variable(value);
	Engine::vectors->at(id)->push_back(var);
}

Variable &ds_list_find_value(int id, int pos) {
	if ((signed int)Engine::vectors->size() <= id) {
		return *(new Variable(-4));
	}
	if (Engine::vectors->at(id) == NULL) {
		return *(new Variable(-4));
	}
	if ((signed int)Engine::vectors->at(id)->size() <= pos) {
		return *(new Variable(-4));
	}
	return *(Engine::vectors->at(id)->at(pos));
}

int ds_list_size(int id) {
	if ((signed int)Engine::vectors->size() <= id) {
		return -4;
	}
	return Engine::vectors->at(id)->size();
}


int round(Variable *data) {
	return (int)data->getI();
}

Variable &string_char_at(Variable &str, unsigned int pos) {
	if (str.getType() != 2 || pos > str.getS().length()) {
		return *(new Variable(""));
	}
	string s = "";
	s.push_back(str.getS().at(pos));
	return *(new Variable(s));
}

Variable &string_length(Variable &str) {
	if (str.getType() != 2) {
		return *(new Variable(0));
	}
	return *(new Variable(str.getS().size()));
}
