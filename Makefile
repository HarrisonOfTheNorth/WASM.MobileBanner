BUILD_DIR = build/debug

cc:


em:
	rm -rf $(BUILD_DIR)/*.js
	rm -rf $(BUILD_DIR)/*.wasm
	rm -rf $(BUILD_DIR)/hel*
	emcc main.cpp  -std=c++17 -lSDL2  -O3 -s WASM=1 -O3 -o $(BUILD_DIR)/hello.html --shell-file template.html --preload-file ./resources 

server: 
	python3 -m http.server 

clean:
	rm -rf $(BUILD_DIR)/*.js
	rm -rf $(BUILD_DIR)/*.wasm
	rm -rf $(BUILD_DIR)/hel*
