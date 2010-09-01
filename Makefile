CC = g++
CFLAGS = -Wall -g
PROG = game
CORE_FILES = Engine.cpp Engine.h Image.cpp Image.h ObjectType.cpp ObjectType.h Object.cpp Object.h Objects.h Room.cpp Room.h Rooms.h common.cpp common.h main.cpp Variable.h Variable.cpp Font.h Font.cpp
EXTRA_FILES = 


ifeq ($(shell uname),Darwin)
	LIBS = -framework OpenGL -framework GLUT
else
	LIBS = -lglut
endif

all:
	$(CC) $(LIBS) $(CFLAGS) -o $(PROG) $(CORE_FILES) $(EXTRA_FILES)

clean:
	rm -f *.o

cleancode:
	rm -f $(CORE_FILES) $(EXTRA_FILES)

cleanall:
	rm -f $(CORE_FILES) $(EXTRA_FILES) $(PROG) Makefile

