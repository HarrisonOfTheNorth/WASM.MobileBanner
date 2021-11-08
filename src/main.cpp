#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#if defined(__EMSCRIPTEN__)
#include <emscripten/emscripten.h>
#endif

const int SCREENWIDTH = 320;
const int SCREENHEIGHT = 100;

bool isRunning = true;
SDL_Event event;

SDL_Window *window = NULL;
SDL_Surface *screenSurface = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *tex_square_white_32x32 = NULL;

void Dispose()
{
	SDL_DestroyTexture(tex_square_white_32x32);
	tex_square_white_32x32 = NULL;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;
}

SDL_Texture *LoadTexture(const char *path)
{
	SDL_Texture *newTexture = NULL;
	newTexture = IMG_LoadTexture(renderer, path);

	if (newTexture == NULL)
	{
		printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
	}

	return newTexture;
}

bool LoadMedia()
{
	bool success = true;

	tex_square_white_32x32 = LoadTexture("resources/square_white_32x32.png");
	if (tex_square_white_32x32 == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	return success;
}

int x = 0;

void MainLoop()
{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			isRunning = false;
		}
	}
	x++;
	//std::cout << "looping" << x << std::endl;

	SDL_RenderClear(renderer);

	//Render texture to screen

	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = 32;
	src.h = 32;

	SDL_Rect dst;
	dst.x = 0;
	dst.y = 0;
	dst.w = SCREENWIDTH;
	dst.h = SCREENHEIGHT;

	SDL_RenderCopy(renderer, tex_square_white_32x32, &src, &dst);

	//Update screen
	SDL_RenderPresent(renderer);

	SDL_UpdateWindowSurface(window);
}

int main()
{

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

#if defined(__EMSCRIPTEN__)
	screenSurface = SDL_GetWindowSurface(window);

	if (screenSurface == NULL)
	{
	}
#endif

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (renderer == NULL)
	{
	}

	LoadMedia();

	//SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0x00, 0x00));

#if defined(__EMSCRIPTEN__)
	emscripten_set_main_loop(MainLoop, -1, 1);
#else
	while (isRunning)
	{
		Uint64 start = SDL_GetPerformanceCounter();

		MainLoop();

		Uint64 end = SDL_GetPerformanceCounter();

		float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

		//std::cout << floor(16.666f - elapsedMS) << std::endl; // 16.666 is 1/60th of a second

		SDL_Delay(floor(16.666f - elapsedMS)); // delay so that the complete frame time is 1/60th of a second.
	}
#endif

	Dispose();

	IMG_Quit();
	SDL_Quit();

	return EXIT_SUCCESS;
}