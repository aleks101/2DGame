# 2DGame

- SDL2 version 2.26.5 or above - https://github.com/libsdl-org/SDL/releases/tag/release-2.28.5
- SDL2_image version 2.6.3 or above - https://www.libsdl.org/projects/SDL_image/release/?C=M;O=D
- SDL2_mixer version 2.6.3 or above - https://www.libsdl.org/projects/SDL_mixer/release/?C=M;O=D
- SDL2_ttf version 2.20.1 or above - https://github.com/libsdl-org/SDL_ttf/releases
- libnoise library - https://libnoise.sourceforge.net/downloads/index.html

Make sure your path to SDL2 directory on your computer is as follows(extract the libraries in the SDL folder):
- SDL2:       C:\SDL\SDL2-2.26.5
- SDL2_image: C:\SDL\SDL2_image-2.6.3
- SDL2_ttf:   C:\SDL\SDL2_ttf-2.20.2
- SDL2_mixer: C:\SDL\SDL2_mixer-2.6.3

Make sure your path to the libnoise directory on your computer is as follows(extract the library in the libnoise folder):
- libnoise: C:\libnoise\Header

Libnoise library works only for 32bit system, so make sure you switch to 32bit configuration in visual studio.

Don't forget to copy the DLL files from the SDL2 and libnoise directories to the Release/Debug folder after building the solution.
