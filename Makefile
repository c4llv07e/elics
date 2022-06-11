
.PHONY: all clean

all: src/main.cc vao.o program.o system_layer.o
	g++ -lGL -lGLEW -lSDL2 -Isrc $^ -o main

clean:
	rm -rf *.o main

vao.o: src/opengl/vao.cc
	g++ -c -Isrc $^ -o $@

program.o: src/opengl/program.cc
	g++ -c -Isrc $^ -o $@

system_layer.o: src/system_layer/system_layer.cc
	g++ -c -Isrc $^ -o $@
