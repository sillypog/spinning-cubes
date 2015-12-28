Goals for this project:

Create a C++ class based system for working with the technology shown in the open.gl tutorials.

- Render multiple spinning cubes.
- Cubes should have multiple textures.
- User should be able to move camera with keys and mouse.

- Nothing in bin directory should be under version control.
- Textures and shaders should get copied to the bin directory.
- Paths in makefile should use environment variable to work on other macs.


I am generating .o objects for each of my files, but unless I use headers to include those in main.cpp, there's not going to be any savings when compiling that file. Also need to work out where to put the GLEW defines - might need to put these in a header file so they can be referenced wherever GLEW is referenced. I nthat case I probably need include guards so things aren't defined twice.


Handy C++ repl: http://ideone.com/57WVOb

Working with array of pairs:
http://stackoverflow.com/questions/6687635/problem-with-array-of-stdpair-in-c
http://stackoverflow.com/questions/26811196/initializing-an-array-of-pair-in-c
http://stackoverflow.com/questions/27669200/how-to-brace-initialize-an-array-of-pairs

Passing std::array to function:
http://stackoverflow.com/questions/17156282/passing-a-stdarray-of-unknown-size-to-a-function

std::accumulate std::pair
http://stackoverflow.com/questions/5994999/problem-using-pair-with-accumulate
http://stackoverflow.com/questions/6935118/how-to-apply-stdaccumulate-algorithm-for-associative-containers

std::accumulate with c-style array
http://en.cppreference.com/w/cpp/algorithm/accumulate
https://www.google.com/?gws_rd=ssl#q=std+accumulate+c+style+array
http://stackoverflow.com/questions/25070586/why-does-stdaccumulate-behave-like-this-with-standard-arrays
http://stackoverflow.com/questions/713309/c-stl-can-arrays-be-used-transparently-with-stl-functions

Textures on cube.
Add in a camera for 3D.
Something that updates the cube position.

Implementing texture support:
http://stackoverflow.com/questions/8866904/differences-and-relationship-between-glactivetexture-and-glbindtexture

