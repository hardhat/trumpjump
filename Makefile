OBJ=src/game.o src/hud.o src/image.o src/main.o src/map.o src/sound.o src/actor.o src/font.o
CFLAGS=$(shell sdl2-config --cflags)
CXXFLAGS=$(shell sdl2-config --cflags) -I/opt/local/include -I/opt/local/include/
LIBS=$(shell sdl2-config --libs) -lSDL_image -lSDL_mixer -lSDL_ttf

trumpjump: $(OBJ)
	g++ -o trumpjump $(OBJ) $(LIBS)

clean:
	-rm src/*.o

