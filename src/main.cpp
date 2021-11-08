#include <iostream>
#include <SDL2/SDL.h>

#if defined(__EMSCRIPTEN__)
#include <emscripten/emscripten.h>
#endif

const int SCREENWIDTH = 320;
const int SCREENHEIGHT = 100;

bool isRunning = true;
SDL_Event event;

int x = 0;

void MainLoop()
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
	emscripten_set_main_loop(MainLoop, -1, 1);
#else
	while (isRunning)
	{
		Uint64 start = SDL_GetPerformanceCounter();

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				isRunning = false;
			}
		}

		MainLoop();

		Uint64 end = SDL_GetPerformanceCounter();

		float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

		std::cout << floor(16.666f - elapsedMS) << std::endl; // 16.666 is 1/60th of a second

		SDL_Delay(floor(16.666f - elapsedMS)); // delay so that the complete frame time is 1/60th of a second.
	}
#endif

	SDL_Quit();

	return EXIT_SUCCESS;
}
