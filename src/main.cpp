#include <iostream>
#include <SDL2/SDL.h>

#if defined(__EMSCRIPTEN__)
#include <emscripten/emscripten.h>
#endif

const int SCREENWIDTH = 320;
const int SCREENHEIGHT = 100;

int x = 0;

void mainloop()
{
	x++;
	std::cout << "looping" << x << std::endl;
}

int main()
{
	SDL_Window *window = NULL;
	SDL_Surface *screenSurface = NULL;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
	}

	window = SDL_CreateWindow(

	    "Mobile Banner 320x100",
	    SDL_WINDOWPOS_UNDEFINED,
	    SDL_WINDOWPOS_UNDEFINED,
	    SCREENWIDTH,
	    SCREENHEIGHT,
	    SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
	}

	screenSurface = SDL_GetWindowSurface(window);

	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0x00, 0x00));

	SDL_UpdateWindowSurface(window);

#if defined(__EMSCRIPTEN__)
	emscripten_set_main_loop(mainloop, -1, 1);
#else

#endif
}
