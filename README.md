### Description###
This windows application is the generator of three-dimensional landscapes with fractal trees.

# See demonstration video:
# Part I
 [![IMAGE ALT TEXT HERE](http://img.youtube.com/vi/5is1VMlSnUQ/0.jpg)](https://www.youtube.com/watch?v=5is1VMlSnUQ)
# Part II
 [![IMAGE ALT TEXT HERE](http://img.youtube.com/vi/nT-fF0_rEm4/0.jpg)](https://www.youtube.com/watch?v=nT-fF0_rEm4)


### Used technologies and tools###
* Basic: C++, WinAPI/MFC, Visual Studio 2013
* Graphics: OpenGL + shaders

### Requires###
* MFC framework
* opengl: "glut, glaux, glew" libs

### Possible problems###
* If you get the next error: "fatal error LNK1281: .... SAFESEH." we recommend that you do the following: Open project properties/Linker/Additional/(set NO:SAFESEH.)
* If we run project and get "can not find glew32.dll", copy glew32.dll and glut32.dll libraries to folder "Release[or Debug]"
