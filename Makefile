OBJ=src/game.o src/hud.o src/image.o src/main.o src/map.o src/sound.o src/actor.o src/font.o src/world.o
CFLAGS=$(shell sdl2-config --cflags)
CXXFLAGS=$(shell sdl2-config --cflags) -I/opt/local/include -I/opt/local/include/ -g
LIBS=$(shell sdl2-config --libs) -lSDL2_image -lSDL2_mixer -lSDL2_ttf -g

trumpjump: $(OBJ)
	g++ -Wall -o trumpjump $(OBJ) $(LIBS)

clean:
	-rm src/*.o

