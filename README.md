Goals for this project:

Create a C++ class based system for working with the technology shown in the open.gl tutorials.

- Render multiple spinning cubes.
- Cubes should have multiple textures.
- User should be able to move camera with keys and mouse.

- Nothing in bin directory should be under version control.
- Textures and shaders should get copied to the bin directory.
- Paths in makefile should use environment variable to work on other macs.


I am generating .o objects for each of my files, but unless I use headers to include those in main.cpp, there's not going to be any savings when compiling that file. Also need to work out where to put the GLEW defines - might need to put these in a header file so they can be referenced wherever GLEW is referenced. I nthat case I probably need include guards so things aren't defined twice.
