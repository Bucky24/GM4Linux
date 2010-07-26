CC = g++
CFLAGS = -Wall -g



ifeq ($(shell uname),Darwin)
	LIBS = -framework OpenGL -framework GLUT
else
	LIBS = -lglut
endif

all:
	$(CC) $(CFLAGS) -o builder builder.cpp files.h files.cpp

clean:
	rm -f builder
	rm -f *~
