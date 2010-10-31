CC = g++
CFLAGS = -Wall -g
PROG = game
CORE_FILES = Engine.cpp Engine.h Image.cpp Image.h Object.cpp Object.h Objects.h Room.cpp Room.h Rooms.h common.cpp common.h main.cpp Variable.h Variable.cpp Font.h Font.cpp sprites.h sprites.cpp specialDefs.h specialDefs.cpp
EXTRA_FILES = 


ifeq ($(shell uname),Darwin)
	LIBS = -framework OpenGL -framework GLUT
else
	LIBS = -lglut
endif

all:
	$(CC) $(LIBS) $(CFLAGS) -o $(PROG) $(CORE_FILES) $(EXTRA_FILES)

clean:
	rm -f *.o *.gch

cleancode:
	rm -f $(CORE_FILES) $(EXTRA_FILES) *.o *.gch

cleanall:
	rm -f $(CORE_FILES) $(EXTRA_FILES) $(PROG) Makefile *.o *.gch

