CFLAGS=-Wall -Wextra -std=c++1y
INCLUDE_PATHS = -I/Users/sillypog/OpenGL/glfw/include -I/Users/sillypog/OpenGL/glew/glew-1.10.0-built/include -I/Users/sillypog/OpenGL/glm
LIBRARY_PATHS = -L/Users/sillypog/OpenGL/glfw/build/src -L/Users/sillypog/OpenGL/glew/glew-1.10.0-built/lib
LINKER_FLAGS = -lglew -lglfw3 -lpng -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
#DEFINES = -DGLM_MESSAGES

all: bin/spinning-boxes.app bin/assets

bin/spinning-boxes.app: obj/main.o obj/window.o obj/framecounter.o obj/renderer.o obj/shader.o obj/shader_program.o obj/entity.o obj/square.o obj/cube.o obj/tlcube.o obj/brcube.o obj/scene.o
	g++ -v $(LIBRARY_PATHS) $(LINKER_FLAGS) obj/main.o obj/window.o obj/framecounter.o obj/renderer.o obj/shader.o obj/shader_program.o obj/entity.o obj/square.o obj/cube.o obj/tlcube.o obj/brcube.o obj/scene.o -o bin/spinning-boxes.app

obj/main.o: obj src/main.cpp src/renderer/window.h src/util/framecounter.h
	g++ -c -v $(CFLAGS) $(INCLUDE_PATHS) src/main.cpp -o obj/main.o

obj/window.o: obj src/renderer/window.h src/renderer/window.cpp
	g++ -c -v $(CFLAGS) $(INCLUDE_PATHS) src/renderer/window.cpp -o obj/window.o

obj/framecounter.o: obj src/util/framecounter.h src/util/framecounter.cpp
	g++ -c -v $(CFLAGS) $(INCLUDE_PATHS) src/util/framecounter.cpp -o obj/framecounter.o

obj/renderer.o: obj src/renderer/renderer.h src/renderer/renderer.cpp
	g++ -c -v $(CFLAGS) $(INCLUDE_PATHS) src/renderer/renderer.cpp -o obj/renderer.o

obj/shader.o: obj src/renderer/shader.h src/renderer/shader.cpp
	g++ -c -v $(CFLAGS) $(INCLUDE_PATHS) src/renderer/shader.cpp -o obj/shader.o

obj/shader_program.o: obj src/renderer/shader_program.h src/renderer/shader_program.cpp
	g++ -c -v $(CFLAGS) $(INCLUDE_PATHS) src/renderer/shader_program.cpp -o obj/shader_program.o

obj/entity.o: obj src/model/entity.h src/model/entity.cpp
	g++ -c -v $(CFLAGS) $(INCLUDE_PATHS) src/model/entity.cpp -o obj/entity.o

obj/square.o: obj src/model/square.h src/model/square.cpp
	g++ -c -v $(CFLAGS) $(INCLUDE_PATHS) src/model/square.cpp -o obj/square.o

obj/cube.o: obj src/model/cube.h src/model/cube.cpp
	g++ -c -v $(CFLAGS) $(INCLUDE_PATHS) src/model/cube.cpp -o obj/cube.o

obj/tlcube.o: obj src/model/tlcube.h src/model/tlcube.cpp
	g++ -c -v $(CFLAGS) $(INCLUDE_PATHS) src/model/tlcube.cpp -o obj/tlcube.o

obj/brcube.o: obj src/model/brcube.h src/model/brcube.cpp
	g++ -c -v $(CFLAGS) $(INCLUDE_PATHS) src/model/brcube.cpp -o obj/brcube.o

obj/scene.o: obj src/model/scene.h src/model/scene.cpp
	g++ -c -v $(CFLAGS) $(INCLUDE_PATHS) src/model/scene.cpp -o obj/scene.o

bin/assets: bin assets
	cp -r assets bin

bin:
	mkdir bin

obj:
	mkdir obj

.PHONY: clean

clean:
	rm -r bin/* obj/*
