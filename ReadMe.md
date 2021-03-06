# WASM

`Patterns for creating WASM in a single HTML snippet, using SDL2 and C++`

See this WASM Demo running in the browser https://yatter.itch.io/sdl2wasm

- Also, for those wishing to contribute a Pull-Request, please see the community request at https://stackoverflow.com/questions/69918876/patterns-for-creating-wasm-in-a-single-html-snippet-using-sdl2-and-c
- We have created three platform ReadMe stubs to cater for community pull-requests (see the tree below).

## Introduction

We wanted to animate some webpage banners, similar to how we used to do it in Flash, which is no longer supported.

The solution, of course, is WASM - WebAssembly - which is not just supported by all the major browsers, but by iOS and Android mobile-app browsers.

This repo is a work in progress, however you can see it working at the above link.

It was written in C++ using SDL2 and compiled using emscripten.

_It also runs on the desktop as an application!_

Deployment to the above link was easy, we just went `make wasm`, and that produced four files, `hello.html`, `hello.js`, `hello.wasm`, and `hello.data`, we then renamed the hello.html file to index.html, zipped them all up, and uploaded the zip file to our itch.io account!

- we are on the pathway of formalising `Patterns for creating WASM in a single HTML snippet, using SDL2 and C++`
- to get there, please see the StackOverflow link, above
- we are trying to create a simple set of rules for creating WASM Banner Advertisements, using SDL2 and C++, in all of the standard industry sizes that are outlined at https://www.match2one.com/blog/standard-banner-sizes/
- That link refers to the industry standards for banner advertising, vis-a-vis "[The Interactive Advertising Bureau (IAB)](https://www.iab.com/guidelines/iab-new-ad-portfolio/) has created standardized guidelines on banner sizes, which work across all advertising networks, including the Google Display Network (GDN)". You do have to create a free account to get access to their abundant range of banner specifications in PDF, but not only is it scintillating reading, once we get WASM-div patterns sorted out, we'll create a SDK for each of the standard sizes.
- The IAB documents are quite significant because they also specify Banner Ad 'K-Weight' (kilobyte size) for each standard banner size, and although they are difficult to achieve using WASM, we suspect that the advent of 5G will afford some flexibilty on this, as well as giving us some optimisation targets.

## Setup

The following is our own MacOS aide memoire to ourselves so that we can remember what we did, we have, however, created three platform ReadMes in the Platforms folder.

- At the moment we need community Pull-Requests for the Linux and Windows ReadMe files and Makefiles.

You'll notice in the resources folder that there are both .bmp files and .png files. The reason for this is that the library setup for .png files for SDL2 can be tricky, yet BMPs run out of the box. There's a note about this at the bottom of this page.

Similarly, you will see that the load font method is commented out - although we could compile them for an app, we couldn't get the compiler paths right for the WASM build, so we just loaded the text as an image instead. Yup, a pretty good hack for the moment.

Hopefully there are enough tips below to get a running start!

## Platform

The following setup is for MacOS, which we use for outputting to Mac, iOS, and Android. As WASM is platform independant, WASM produced on MacOS is also suitable for Windows and Linux deployments. We don't currently have any guides for building SDL2 and creating WASM from it, using Linux and Windows, and we welcome any contributions to assist this. The endpoint goal is an Open-Source SDK that caters for MacOS, Linux, and Windows, catering for all the banner ad sizes specified by the IAB (see above).

- Contributors are sought for the ReadMe and Makefiles in the Platform folders.

### Important Platform Note

- If you have missed the subtlety, one of the IAB standard banner ad sizes is full page - so this is the pathway towards creating full-blown WASM applications in a WASM-div snippet! We're starting at 320 x 100, fleshing it out, accomodating all of the other IAB sizes, then going for multiple WASM-divs in a single HTML page where each can talk to each other, with the capability of each size (no matter how small or big) being capable of transforming to full-screen, as well as being reactive to the platform that they are rendered on, Desktop or Mobile.

## Makefile Aide Memoire

- `make wasm` builds the WASM in build/debug and outputs `hello.html`, `hello.js`, `hello.wasm`, and `hello.data`
- `make wasmrun` runs up a server in the current directory, go to `localhost:8000` in a browser, click on build, then hello.html
- `make app` builds the app in build/debug and outputs an executable called `application`
- `make apprun` runs up the application at `build/debug/application` and which should appear in it's own window
- `make tree` outputs your directory tree, useful for finding out how the includes and libs are symlinked.
- `make clean` cleans the build/debug folder of any WASM or App files that were generated using the commands above.

## Tree

Depending upon your symlinks, it should look something like the following:

```
.
????????? Makefile
????????? Platforms
???   ????????? Linux
???   ???   ????????? Makefile
???   ???   ????????? ReadMe.md
???   ????????? MacOS
???   ???   ????????? Makefile
???   ???   ????????? ReadMe.md
???   ????????? Windows
???       ????????? Makefile
???       ????????? ReadMe.md
????????? ReadMe.md
????????? build
???   ????????? debug
????????? include
???   ????????? MobileBanner
???   ???   ????????? Entity.hpp
???   ???   ????????? Maths.hpp
???   ????????? SDL2 -> /opt/homebrew/Cellar/sdl2/2.0.16/include/SDL2
???   ????????? SDL_image -> /opt/homebrew/Cellar/sdl2_image/2.0.5/include/SDL2
???   ????????? SDL_ttf -> /opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2
????????? lib
???   ????????? SDL2_ttf -> /opt/homebrew/Cellar/sdl2_ttf/2.0.15/lib
????????? resources
???   ????????? Roboto-Bold.ttf
???   ????????? advertisementballoon512x512.bmp
???   ????????? advertisementballoon512x512.png
???   ????????? logo512x512.bmp
???   ????????? logo512x512.png
???   ????????? qrcodeballoon512x512.bmp
???   ????????? qrcodeballoon512x512.png
???   ????????? square_black_32x32.bmp
???   ????????? square_black_32x32.png
???   ????????? square_white_32x32.bmp
???   ????????? square_white_32x32.png
???   ????????? square_yellow_32x32.bmp
???   ????????? square_yellow_32x32.png
???   ????????? youataresource463x62.bmp
???   ????????? youataresource463x62.png
????????? src
???   ????????? Entity.cpp
???   ????????? main.cpp
????????? template.html
```

Please see the note at the bottom, outlining why .png files are temporarily duplicated as .bmp files.

## Command Lines Aide Memoire

Don't be daunted by these command lines, the first three are automatically generated by the Makefile. They are, however, interesting to look at!

The bottom three, however, you will use, the first of them to install tree, if you don't already have it; the seecond of them to find the paths of already installed packages; and the third of them to look at your tree.

- `em++ src/Entity.cpp src/main.cpp -std=c++17 -O3 -s WASM=1 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_LIBPNG=1 -lsdl2 -lsdl2_image -lz -Iinclude -I/opt/homebrew/Cellar/sdl2_image/2.0.5/include -I/opt/homebrew/Cellar/sdl2/2.0.16/include/SDL2 -I/opt/homebrew/Cellar/zlib/1.2.11/include -I/opt/homebrew/Cellar/libpng/1.6.37/include -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 -Llib -o build/debug/hello.html --shell-file template.html --preload-file ./resources` - the current make wasm command line
- `g++ src/Entity.cpp src/main.cpp -std=c++11 -Wall -O0 -g -lsdl2 -lsdl2_image -lSDL2_ttf -Iinclude -I/opt/homebrew/Cellar/sdl2_image/2.0.5/include -I/opt/homebrew/Cellar/sdl2/2.0.16/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 -Llib -L/opt/homebrew/lib -o build/debug/application` - the current make app command line
- `python3 -m http.server` - kicks up an HTTP Server on port 8000 in the current directory, `make wasmrun` calls this! If this does not work, try `brew install python3`.
- `brew install tree` to get the tree command line.
- `pkg-config --libs sdl2` - this is used to find where the includes and libraries are for a particular library, this example shows SDL2
- `source ./emsdk_env.sh` - this is used to put the emscripten environmental variables in the path of the current terminal, just navigate tot where Emscriptem is installed, enter this command, and return to this project directory, and for example, run make.

## Checklist:

### zlib (needed for libpng, only needed for the WASM build)

- Check: `pkg-config --libs zlib`
- Example: `-L/opt/homebrew/Cellar/zlib/1.2.11/lib -lz`
- Install: `brew install zlib`
- Reinstall `brew reinstall zlib`
- Upgrade: `brew upgrade zlib`
- Locate the include folder: To find the include, try going to the L directory above, and look for an include folder in the next higher directory.

### libpng (needed for SDL2_image WASM build)

- Check: `pkg-config --libs libpng`
- Example: `-L/opt/homebrew/Cellar/libpng/1.6.37/lib -lpng16 -lz`
- Install: `brew install libpng`
- Reinstall: `brew reinstall libpng`
- Upgrade: `brew upgrade libpng`
- Locate the include folder: To find the include, try going to the L directory above, and look for an include folder in the next higher directory.

### SDL2_image

- Check: `pkg-config --libs sdl2`
- Example: `-L/opt/homebrew/lib -lSDL2`
- Install: `brew install sdl2_image`
- Reinstall: `brew reinstall sdl2_image`
- Upgrade: `brew upgrade sdl2_image`
- Locate the include folder: Best bet is doing a reinstall and finding the path from the output.
- Tree: run `tree` to see if it is linked to in the current folder.
- include Symlink example: `ln -s /opt/homebrew/Cellar/sdl2_image/2.0.5/include/SDL2 include/SDL_image`

### SDL2

- Check: `pkg-config --libs sdl2`
- Example: `-L/opt/homebrew/lib -lSDL2`
- Install: `brew install sdl2`
- Reinstall: `brew reinstall sdl2`
- Upgrade: `brew upgrade sdl2`
- Locate the include folder: Best bet is doing a reinstall and finding the path from the output.
- Tree: run `tree` to see if it is linked to in the current folder.
- include Symlink example: `ln -s /opt/homebrew/Cellar/sdl2/2.0.16/include/SDL2 include/SDL2`

### SDL_tff

- Check: `pkg-config --libs sdl2_ttf`
- Example: `-L/opt/homebrew/lib -lSDL2_ttf -lSDL2`
- Install: `brew install sdl2_ttf`
- Reinstall: `brew reinstall sdl2_ttf`
- Upgrade: `brew upgrade sdl2_ttf`
- Locate the include folder: Best bet is doing a reinstall and finding the path from the output, in our case it said `/opt/homebrew/Cellar/sdl2_ttf/2.0.15`, so we looked in the folders downstream of this path (`ls /opt/homebrew/Cellar/sdl2_ttf/2.0.15`)
- include Symlink Example: `ln -s /opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 include/SDL_ttf`
- lib Symlink Example: `ln -s /opt/homebrew/Cellar/sdl2_ttf/2.0.15/lib lib/SDL2_ttf`
- Tree: run `tree` to see if it is linked to in the current folder.

## Links

- https://emscripten.org/docs/index.html
- https://emscripten.org/docs/getting_started/downloads.html
- https://lazyfoo.net/tutorials/SDL/index.php
- https://github.com/OneLoneCoder/olcPixelGameEngine
- This link https://github.com/emscripten-ports/SDL2_image says: JPEG support requires the JPEG library: http://www.ijg.org/ and PNG support requires the PNG library: http://www.libpng.org/pub/png/libpng.html and the Zlib library: http://www.gzip.org/zlib/ and TIFF support requires the TIFF library: ftp://ftp.sgi.com/graphics/tiff/
- libpng http://www.libpng.org/pub/png/libpng.html
- zlib https://zlib.net/

## Videos

- https://www.youtube.com/watch?v=MrI5kkVY6zk&t=637s
- https://www.youtube.com/watch?v=KsG6dJlLBDw&list=PL2RPjWnJduNmXHRYwdtublIPdlqocBoLS
- https://www.youtube.com/watch?v=Dyz9O7s7B8w&t=983s
- https://www.youtube.com/watch?v=VeyMi337AwA&t=96s
- Cmake https://www.youtube.com/watch?v=nlKcXPUJGwA&list=PLalVdRk2RC6o5GHu618ARWh0VO0bFlif4
- Advanced Makefile https://www.youtube.com/watch?v=_r7i5X0rXJk

Notes.

I'd agree that the tree for the reources dirctory looks awkward, the reason for both .bmp and .png files is because we have had difficulty getting .png images to run both as an app and as wasm. This has something to do with Emscripten having it's own SDL2 support, so although we've generally got the command line right for g++, we're not doing so well with the separate em++ command line. So as an app, we are finding it quite easy, but as wasm - well not at all so far, but at least our hack produces the same visual rendering in both the app and wasm demos. So after a day of tinkering with include and lib paths for the .png assets in WASM mode, I fell back into MVP mode and added the .bmp files as a fall-back. A full solution will resolve this and incorporate the .png files, which is why both are there.
