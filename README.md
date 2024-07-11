# 3DViewer_v2.0

3DViewer is a program for reading and visualizing .obj files.

The program structure is made in accordance with the MVC design pattern and Google Style requirements.

## Requirements:
- Ubuntu or MacOS operating system;
- Qt version 6+ (e.g. qt-6-base-dev for Ubuntu);
- OpenGL libraries;
- Cmake for compiling;

## Basic properties:
- The program is provide the ability to:
    - Load a wireframe model from an .obj file (vertices and surfaces list support only);
    - Translate the model by a given distance in relation to the X, Y, Z axes;
    - Rotate the model by a given angle in relation to its X, Y, Z axes;
    - Scale the model by a given value;
- The program is allow customizing the type of projection (parallel and central);
- The program is allow setting up the type (solid, dashed), color and thickness of the edges, display method (none, circle, square), color and size of the vertices;
- The program is allow choosing the background color;
- Settings are saved between program restarts.
- The program is allow saving the captured (rendered) images as bmp and jpeg files;
- The program is allow recording small screencasts - the current custom affine transformation of the loaded object into gif-animation (640x480, 10fps, 5s) by a special button.
      
## Compilation:

Use "make" command:
```
make install
```
The command installs the program to "3D_Viewer_v2.0" directory.

(for Ubuntu) If your system does not have qt ver.6+ or OpenGL libraries installed:
```
make libs_install
```
or manually run the command:
```
sudo apt-get install qt6-base-dev libglu1-mesa-dev freeglut3-dev mesa-common-dev
```
## Uninstall:
```
make uninstall
```
Or delete app's directory.

## Run:
```
make run
```
Or manually open "3D_Viewer" file.

## Zip compiled program:
```
make dist
```
It makes "dist_3DViewer.tar.gz" file.

## Compile and open readme.dvi:
```
make dvi
```
If you have not installed "latex" command:
```
make latex_install
```
