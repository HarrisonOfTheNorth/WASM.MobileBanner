SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
BUILD_DIR = build/debug

CC = g++
EC = em++

APP_INCLUDES = -Iinclude -I/opt/homebrew/Cellar/sdl2_image/2.0.5/include -I/opt/homebrew/Cellar/sdl2/2.0.16/include/SDL2
APP_LIBS = -Llib -L/opt/homebrew/lib
APP_COMPILERFLAGS = -std=c++11 -Wall -O0 -g
APP_LINKERFLAGS = -lsdl2 -lsdl2_image
APP_OUTPUT = -o build/debug/application

WASM_INCLUDES = -Iinclude -I/opt/homebrew/Cellar/sdl2_image/2.0.5/include -I/opt/homebrew/Cellar/sdl2/2.0.16/include/SDL2
WASM_LIBS = -Llib 
WASM_COMPILERFLAGS = -std=c++17 -O3 -s WASM=1 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_LIBPNG=1 
WASM_LINKERFLAGS = -lsdl2 -lsdl2_image
WASM_PRELOAD = --preload-file ./resources 
WASM_SHELLFILETEMPLATE = --shell-file template.html
WASM_OUTPUT = -o $(BUILD_DIR)/hello.html

app:
	rm -rf $(BUILD_DIR)/*.js
	rm -rf $(BUILD_DIR)/*.wasm
	rm -rf $(BUILD_DIR)/hel*
	rm -rf $(BUILD_DIR)/app*
	$(CC) $(SRC_FILES) $(APP_COMPILERFLAGS) $(APP_LINKERFLAGS) $(APP_INCLUDES) $(APP_LIBS) $(APP_OUTPUT)

runapp:
	./build/debug/application

wasm:
	rm -rf $(BUILD_DIR)/*.js
	rm -rf $(BUILD_DIR)/*.wasm
	rm -rf $(BUILD_DIR)/hel*
	rm -rf $(BUILD_DIR)/app*
	$(EC) $(SRC_FILES) $(WASM_COMPILERFLAGS) $(WASM_LINKERFLAGS) $(WASM_INCLUDES) $(WASM_LIBS) $(WASM_OUTPUT) $(WASM_SHELLFILETEMPLATE) $(WASM_PRELOAD)

runwasm: 
	python3 -m http.server 

clean:
	rm -rf $(BUILD_DIR)/*.js
	rm -rf $(BUILD_DIR)/*.wasm
	rm -rf $(BUILD_DIR)/hel*
	rm -rf $(BUILD_DIR)/app*
