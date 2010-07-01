CC = g++
CFLAGS = -Wall -g
PROG = game



ifeq ($(shell uname),Darwin)
	LIBS = -framework OpenGL -framework GLUT
else
	LIBS = -lglut
endif

all:
	$(CC) $(LIBS) $(CFLAGS) -o $(PROG) *.cpp *.h

clean:
	rm -f $(PROG)
	rm -f *~
