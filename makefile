CFLAGS:=-Wall -Wextra -std=c++1y
# VERBOSE_FLAG:=-v # Comment out for clearer compile messages
INCLUDE_PATHS:= -I/Users/sillypog/OpenGL/glfw/include -I/Users/sillypog/OpenGL/glew/glew-1.10.0-built/include -I/Users/sillypog/OpenGL/glm
LIBRARY_PATHS:= -L/Users/sillypog/OpenGL/glfw/build/src -L/Users/sillypog/OpenGL/glew/glew-1.10.0-built/lib
LINKER_FLAGS:= -lglew -lglfw3 -lpng -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
#DEFINES:= -DGLM_MESSAGES
DEPS=-MMD -MF deps/$(basename $(@F)).d

all: obj deps bin bin/spinning-boxes.app bin/assets

bin/spinning-boxes.app: obj/main.o obj/window.o obj/framecounter.o obj/renderer.o obj/shader.o obj/shader_program.o obj/texture.o obj/entity.o obj/square.o obj/cube.o obj/tlcube.o obj/brcube.o obj/scene.o obj/texture_manager.o
	g++ $(VERBOSE_FLAG) $(LIBRARY_PATHS) $(LINKER_FLAGS) $^ -o $@

obj/main.o: src/main.cpp
	g++ -c $(VERBOSE_FLAG) $(CFLAGS) $(INCLUDE_PATHS) $(DEPS) $< -o $@
-include deps/main.d

obj/window.o: src/renderer/window.cpp
	g++ -c $(VERBOSE_FLAG) $(CFLAGS) $(INCLUDE_PATHS) $(DEPS) $< -o $@
-include deps/window.d

obj/framecounter.o: src/util/framecounter.cpp
	g++ -c $(VERBOSE_FLAG) $(CFLAGS) $(INCLUDE_PATHS) $(DEPS) $< -o $@
-include deps/framecounter.d

obj/renderer.o: src/renderer/renderer.cpp
	g++ -c $(VERBOSE_FLAG) $(CFLAGS) $(INCLUDE_PATHS) $(DEPS) $< -o $@
-include deps/renderer.d

obj/shader.o: src/renderer/shader.cpp
	g++ -c $(VERBOSE_FLAG) $(CFLAGS) $(INCLUDE_PATHS) $(DEPS) $< -o $@
-include deps/shader.d

obj/shader_program.o: src/renderer/shader_program.cpp
	g++ -c $(VERBOSE_FLAG) $(CFLAGS) $(INCLUDE_PATHS) $(DEPS) $< -o $@
-include deps/shader_program.d

obj/texture.o: src/renderer/texture.cpp
	g++ -c $(VERBOSE_FLAG) $(CFLAGS) $(INCLUDE_PATHS) $(DEPS) $< -o $@
-include deps/texture.d

obj/entity.o: src/model/entity.cpp
	g++ -c $(VERBOSE_FLAG) $(CFLAGS) $(INCLUDE_PATHS) $(DEPS) $< -o $@
-include deps/entity.d

obj/square.o: src/model/square.cpp
	g++ -c $(VERBOSE_FLAG) $(CFLAGS) $(INCLUDE_PATHS) $(DEPS) $< -o $@
-include deps/square.d

obj/cube.o: src/model/cube.cpp
	g++ -c $(VERBOSE_FLAG) $(CFLAGS) $(INCLUDE_PATHS) $(DEPS) $< -o $@
-include deps/cube.d

obj/tlcube.o: src/model/tlcube.cpp
	g++ -c $(VERBOSE_FLAG) $(CFLAGS) $(INCLUDE_PATHS) $(DEPS) $< -o $@
-include deps/tlcube.d

obj/brcube.o: src/model/brcube.cpp
	g++ -c $(VERBOSE_FLAG) $(CFLAGS) $(INCLUDE_PATHS) $(DEPS) $< -o $@
-include deps/brcube.d

obj/scene.o: src/model/scene.cpp
	g++ -c $(VERBOSE_FLAG) $(CFLAGS) $(INCLUDE_PATHS) $(DEPS) $< -o $@
-include deps/scene.d

obj/texture_manager.o: src/renderer/texture_manager.cpp
	g++ -c $(VERBOSE_FLAG) $(CFLAGS) $(INCLUDE_PATHS) $(DEPS) $< -o $@
-include deps/texture_manager.d

bin/assets: bin assets
	cp -r assets bin

bin:
	mkdir bin

deps:
	mkdir deps

obj:
	mkdir obj

.PHONY: clean

clean:
	-rm -r bin/* deps/* obj/*
