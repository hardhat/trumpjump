OBJ=src/falling.o src/game.o src/hud.o src/image.o src/main.o src/map.o src/sprite.o
CFLAGS=$(shell sdl-config --cflags)
CXXFLAGS=$(shell sdl-config --cflags) -I/opt/local/include -I/opt/local/include/
LIBS=$(shell sdl-config --libs) -lSDL_image -lSDL_mixer

trumpjump: $(OBJ)
	g++ -o trumpjump $(OBJ) $(LIBS)

clean:
	-rm src/*.o

