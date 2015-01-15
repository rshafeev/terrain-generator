###Description###
This application is the generator of three-dimensional landscapes with fractal trees.

### Control keys ###
* keyboard arrows - moving on.
* Home/End - increase/decrease height.
* F1 - exit full screen mode
* F2 - return to full-screen mode 
* Esc - exit

###Used technologies and tools###
* Basic: C++, WinAPI/MFC, Visual Studio 2013
* Graphics: OpenGL + shaders

###Requires###
* MFC framework
* opengl: "glut, glaux, glew" libs

###Possible problems###
* If you get the next error: "fatal error LNK1281: .... SAFESEH." we recommend that you do the following: Open project properties/Linker/Additional/(set NO:SAFESEH.)
* If we run project and get "can not find glew32.dll", copy glew32.dll and glut32.dll libraries to folder "Release[or Debug]"