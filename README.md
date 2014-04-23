Agent_GUI_R3a
=============

Multiplatform version of the Tsung-Che Chiang's Agent_GUI_R3a Vacuum Cleaner

Este código está basado en el del profesor Tsung-Che Chiang de la NTNU (Norwegian University of Science and Technology, Taiwan).

http://web.ntnu.edu.tw/~tcchiang/ai/Vacuum%20Cleaner%20World.htm

Los cambios han sido realizados por Ernesto Serrano <info@ernesto.es>

------------------------------------------------------------------------------

Esta variación de Agent-GUI permite su uso en Windows, Mac y Linux

Se incluye el código fuente de la librería GLUI a la que ha habido que hacer ajustes para solucionar errores en plataformas de 64bits


Para cada una de las plataformas existe un makefile que genera el ejecutable

Windows:
============
Se debe compilar con Mingw32, así que el directorio bin de Ming32 debe estar en el path

Mingw32-make -f Makefile.win

Linux:
==========
Para Linux hay que instalar la libería freeglut: 

sudo apt-get install freeglut3-dev

make -f Makefile.linux

MacOSX:
=============
Para MacOSX se utlizan los framework de OpenGL y GLUT del sistema, por lo que lo único que 
hay que hacer es compilar (en este caso si se compila GLUI desde include)

make -f Makefile.mac
