CC = g++
CFLAGS = -Wall -g
PROG = compiler



ifeq ($(shell uname),Darwin)
	LIBS = -framework OpenGL -framework GLUT
else
	LIBS = -lglut
endif

all:
	$(CC) $(LIBS) $(CFLAGS) -o $(PROG) compiler.cpp
	$(CC) $(CFLAGS) -o builder builder.cpp

clean:
	rm -f $(PROG)
	rm -f builder
	rm -f *~
