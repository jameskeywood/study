PKGFLAGS := $(shell pkg-config --cflags --libs sdl2 SDL2_ttf)

all: study

study: main.o graphics.o utility.o
	gcc main.o graphics.o utility.o -o study $(PKGFLAGS)

main.o: main.c graphics.h utility.h
	gcc -c main.c $(PKGFLAGS)

graphics.o: graphics.c graphics.h
	gcc -c graphics.c $(PKGFLAGS)

utility.o: utility.c utility.h
	gcc -c utility.c

clean:
	rm -f *.o study
