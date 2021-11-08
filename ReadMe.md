# WASM

## Command Lines

- `emcc main.cpp -std=c++17 -lSDL2 -O3 -s WASM=1 -O3 -o hello.html --shell-file template.html --preload-file ./resources`
- `python3 -m http.server`
- `pkg-config --libs sdl2`
- `source ./emsdk_env.sh`

## Checklist:

- pkg-config --libs zlib
- pkg-config --libs libpng
- pkg-config --libs sdl2
- pkg-config --libs sdl2_image

## Links

- https://emscripten.org/docs/index.html
- https://emscripten.org/docs/getting_started/downloads.html
- https://lazyfoo.net/tutorials/SDL/index.php
- https://github.com/OneLoneCoder/olcPixelGameEngine
- This link https://github.com/emscripten-ports/SDL2_image says: JPEG support requires the JPEG library: http://www.ijg.org/ and PNG support requires the PNG library: http://www.libpng.org/pub/png/libpng.html and the Zlib library: http://www.gzip.org/zlib/ and TIFF support requires the TIFF library: ftp://ftp.sgi.com/graphics/tiff/
- libpng http://www.libpng.org/pub/png/libpng.html
- zlib https://zlib.net/

## Videos

- https://www.youtube.com/watch?v=VeyMi337AwA&t=96s
- https://www.youtube.com/watch?v=MrI5kkVY6zk&t=637s
- https://www.youtube.com/watch?v=KsG6dJlLBDw&list=PL2RPjWnJduNmXHRYwdtublIPdlqocBoLS
- https://www.youtube.com/watch?v=Dyz9O7s7B8w&t=983s

Notes.

WASM? --use-preload-plugins
