# Minesweeper
Simple minesweeper clone

## Build and run
The project contains prebuilt binaries for Windows 10 and Archlinux, try running them, otherwise build the source code as instructed.
### Linux
Run cmake and bild with make
```bash
cd linux-build
cmake ..
make
```
### Windows
Try using cmake with the config file provided
```cmd
cd windows-build
cmake ..
make
```
If cmake can't find the SDL2 package, try compiling with the Makefile provided, but first make sure the library paths are set correctly
```Makefile
EXTERNLIBPATH		="C:/Program Files/SDL2-2.0.22/x86_64-w64-mingw32"
SDL2_IMAGE_PATH		="C:/Program Files/SDL2_image"
```
once paths are set, run make
```cmd
cd windows-build
make
```

## Tips
The file ```states.xml``` found under ```linux-build/assets/XML/states.xml``` or ```windows-build``` contains settings for the game. Find the commented section and feel free to play around with the values (grid size and number of mines). Tweaking these doesn't require recompiling as the file is read at runtime.

## Disclaimer
- Contains a couple of bugs (glitchy buttons)
- the graphical design could be better
- game over / win animations make the program unresponsive until done
- window not resizable
- currently, the first hit can be a mine (not preferred), mine generation has to be improved
- ```assets``` folder is stored separately under ```windows/linux``` build folders + another copy at project root. Needed restructuring
