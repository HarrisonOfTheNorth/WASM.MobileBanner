#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_ttf.h>
#include <vector>

#if defined(__EMSCRIPTEN__)
#include <emscripten/emscripten.h>
#endif

#include "Banner.h"


int screenWidth = 320;
int screenHeight = 100;

bool isRunning = true;
SDL_Event event;

SDL_Window *window = NULL;

SDL_Surface *screenSurface = NULL;
SDL_Renderer *renderer = NULL;

// image textures
SDL_Texture *tex_logo_512x512 = NULL;
SDL_Texture *tex_advertisementballoon_512x512 = NULL;
SDL_Texture *tex_qrcodeballoon_512x512 = NULL;
SDL_Texture *tex_square_black_32x32 = NULL;
SDL_Texture *tex_square_white_32x32 = NULL;
SDL_Texture *tex_youataresource_463x62 = NULL;

// text textures
SDL_Texture *tex_youataresource = NULL;

std::vector<Banner::Entity> fixedEntities{
    
};

float defaultTileWidth = 16; // renders the borders at 16 instead of 32 (tex_square_black_32x32)

// balloon variables
float x = screenWidth * 0.1; // balloon tex x
float y = screenHeight / 5;  // balloon tex y
float scale = 0.25;	     // balloon rendering scale
bool resizedScale = true; 
bool forwards = true;	     // is balloon moving to the right?
bool growing = true;	     // is balloon growing in size?
bool downwards = true;	     // is balloon moving downwards?

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

	SDL_Surface *image = SDL_LoadBMP("resources/square_white_32x32.bmp");
	tex_square_white_32x32 = SDL_CreateTextureFromSurface(renderer, image);
	if (tex_square_white_32x32 == NULL)
	{
		printf("Failed to load texture image 1!\n");
		success = false;
	}

	image = SDL_LoadBMP("resources/square_yellow_32x32.bmp");
	tex_square_black_32x32 = SDL_CreateTextureFromSurface(renderer, image);
	if (tex_square_black_32x32 == NULL)
	{
		printf("Failed to load texture image 2!\n");
		success = false;
	}

	image = SDL_LoadBMP("resources/logo512x512.bmp");
	tex_logo_512x512 = SDL_CreateTextureFromSurface(renderer, image);
	if (tex_logo_512x512 == NULL)
	{
		printf("Failed to load texture image 3!\n");
		success = false;
	}

	image = SDL_LoadBMP("resources/advertisementballoon512x512.bmp");
	tex_advertisementballoon_512x512 = SDL_CreateTextureFromSurface(renderer, image);
	if (tex_advertisementballoon_512x512 == NULL)
	{
		printf("Failed to load texture image 4!\n");
		success = false;
	}

	image = SDL_LoadBMP("resources/qrcodeballoon512x512.bmp");
	tex_qrcodeballoon_512x512 = SDL_CreateTextureFromSurface(renderer, image);
	if (tex_qrcodeballoon_512x512 == NULL)
	{
		printf("Failed to load texture image 5!\n");
		success = false;
	}

	image = SDL_LoadBMP("resources/youataresource463x62.bmp");
	tex_youataresource_463x62 = SDL_CreateTextureFromSurface(renderer, image);
	if (tex_youataresource_463x62 == NULL)
	{
		printf("Failed to load texture image 6!\n");
		success = false;
	}

	return success;
}

void CreateEntities()
{
	fixedEntities.clear();
	// White Background
	Banner::Entity background(Banner::Vector2f(0, 0, screenWidth, screenHeight), tex_square_white_32x32);
	fixedEntities.push_back(background);
	// top border entities
	for (int x = 0; x < screenWidth / defaultTileWidth; x++)
	{
		{
			Banner::Entity tile(Banner::Vector2f(x * defaultTileWidth, 0, defaultTileWidth, defaultTileWidth), tex_square_black_32x32);
			fixedEntities.push_back(tile);
		}
	}

	// left border entities
	for (int x = 0; x < screenWidth / defaultTileWidth; x++)
	{
		{
			Banner::Entity tile(Banner::Vector2f(0, x * defaultTileWidth, defaultTileWidth, defaultTileWidth), tex_square_black_32x32);
			fixedEntities.push_back(tile);
		}
	}

	// bottom border entities
	for (int x = 0; x < screenWidth / defaultTileWidth; x++)
	{
		{
			Banner::Entity tile(Banner::Vector2f(x * defaultTileWidth, screenHeight - defaultTileWidth, defaultTileWidth, defaultTileWidth), tex_square_black_32x32);
			fixedEntities.push_back(tile);
		}
	}

	// right border entities
	for (int x = 0; x < screenWidth / defaultTileWidth; x++)
	{
		{
			Banner::Entity tile(Banner::Vector2f(screenWidth - defaultTileWidth, x * defaultTileWidth, defaultTileWidth, defaultTileWidth), tex_square_black_32x32);
			fixedEntities.push_back(tile);
		}
	}
}

void WindowClear()
{
	SDL_RenderClear(renderer);
}

void RenderEntity(Banner::Entity &p_entity)
{
	SDL_Rect src;
	src.x = p_entity.GetCurrentFrame().x;
	src.y = p_entity.GetCurrentFrame().y;
	src.w = p_entity.GetCurrentFrame().w;
	src.h = p_entity.GetCurrentFrame().h;

	SDL_Rect dst;
	dst.x = p_entity.GetPos().x;
	dst.y = p_entity.GetPos().y;
	dst.w = p_entity.GetCurrentFrame().w * p_entity.GetPos().scale;
	dst.h = p_entity.GetCurrentFrame().h * p_entity.GetPos().scale;

	SDL_RenderCopy(renderer, p_entity.GetTex(), &src, &dst);
}

void RenderWhiteBackground()
{
	// Example of rendering a texture without abstracting dimensions to Entity class:
	// Compare this to generic RenderEntity method above.
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = 32;
	src.h = 32;

	SDL_Rect dst;
	dst.x = 0;
	dst.y = 0;
	dst.w = screenWidth;
	dst.h = screenHeight;

	SDL_RenderCopy(renderer, tex_square_white_32x32, &src, &dst);
}

void RenderBorders()
{
	for (Banner::Entity &entity : fixedEntities)
	{
		RenderEntity(entity);
	}
}

void RenderLogo()
{
	float logoScale = (screenHeight - (2.0f * defaultTileWidth)) / 512.0f;

	Banner::Entity yatrlogo(Banner::Vector2f(defaultTileWidth, defaultTileWidth, 512, 512, logoScale), tex_logo_512x512);
	RenderEntity(yatrlogo);

	if(screenWidth < 321.0f && screenHeight < 101.0f)
	{
		Banner::Entity text(Banner::Vector2f(screenWidth / 3.68, 40, 463, 62, 0.45), tex_youataresource_463x62);
		RenderEntity(text);
	}
}

void RenderText()
{
	/*
	if (tex_youataresource == NULL)
	{
		TTF_Font *font = TTF_OpenFont("resources/roboto-bold.ttf", 16);

		SDL_Color color = {8, 64, 136};
		SDL_Surface *surface = TTF_RenderText_Solid(font,
							    "You-At-A-Resource, y@R", color);
		tex_youataresource = SDL_CreateTextureFromSurface(renderer, surface);

		SDL_FreeSurface(surface);

		if (tex_youataresource == NULL)
		{
			std::cout << "Failed to create text text 1." << std::endl;
		}
	}

	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(tex_youataresource, NULL, NULL, &texW, &texH);
	SDL_Rect dst = {100, 45, texW, texH};

	SDL_RenderCopy(renderer, tex_youataresource, NULL, &dst);
	*/
}

void RenderBalloon()
{
	{
		Banner::Entity red(Banner::Vector2f(x, y, 512, 512, scale), tex_advertisementballoon_512x512);
		Banner::Entity blue(Banner::Vector2f(x, y, 512, 512, scale), tex_qrcodeballoon_512x512);
		if (x > screenWidth / 3)
		{
			RenderEntity(red);
		}
		else
		{
			RenderEntity(blue);
		}
	}
}

void UpdateBalloonAnimationValues()
{
	float scaleMinimum = 0.0f;
	float scaleMaximum = 0.0f;
	float xForwards = 0.0f;
	float forwardsLeft = 0.0f;
	float forwardsRight = 0.0f;
	float yDownwards = 0.0f;
	float downwardsTop = 0.0f;
	float downwardsBottom = 0.0f;
	float scaleGrowing = 0.0f;

	if(screenWidth < 400)
	{
		if(!resizedScale) scale = 0.2f; resizedScale = true; // must be between scaleMinimum and scaleMaximum
		scaleMinimum = 0.1f;
		scaleMaximum = 0.5f;
		xForwards = 0.4f;
		forwardsLeft = 0.0f;
		forwardsRight = 1.0;
		yDownwards = 0.4f;
		downwardsTop = 0.00f;
		downwardsBottom = 1.0f;
		scaleGrowing = 0.002f;
	}
	else if(screenWidth < 800)
	{
		if(!resizedScale) scale = 0.4f; resizedScale = true; // must be between scaleMinimum and scaleMaximum
		scaleMinimum = 0.3f;
		scaleMaximum = 1.0f;
		xForwards = 0.6f;
		forwardsLeft = 0.0f;
		forwardsRight = 1.0;
		yDownwards = 0.6f;
		downwardsTop = 0.0f;
		downwardsBottom = 1.0f;
		scaleGrowing = 0.002f;
	}
	else if(screenWidth < 1200)
	{
		if(!resizedScale) scale = 0.8f; resizedScale = true; // must be between scaleMinimum and scaleMaximum
		scaleMinimum = 0.7f;
		scaleMaximum = 1.5f;
		xForwards = 0.8f;
		forwardsLeft = 0.0f;
		forwardsRight = 0.9f;
		yDownwards = 0.8f;
		downwardsTop = 0.0f;
		downwardsBottom = 0.8f;
		scaleGrowing = 0.002f;
	}
	else
	{
		if(!resizedScale) scale = 0.8f; resizedScale = true; // must be between scaleMinimum and scaleMaximum
		scaleMinimum = 0.7f;
		scaleMaximum = 1.5f;
		xForwards = 1.0f;
		forwardsLeft = 0.0f;
		forwardsRight = 0.9f;
		yDownwards = 1.0f;
		downwardsTop = 0.0f;
		downwardsBottom = 0.8f;
		scaleGrowing = 0.002f;
	}

	if (forwards)
	{
		x += xForwards;
	}
	else
	{
		x -= xForwards;
	}

	if (downwards)
	{
		y += yDownwards;
	}
	else
	{
		y -= yDownwards;
	}

	if (growing)
	{
		scale += scaleGrowing;
	}
	else
	{
		scale -= scaleGrowing;
	}

	if (x < (screenWidth * forwardsLeft) || x > (screenWidth * forwardsRight))
	{
		forwards = !forwards;
	}

	if (y < (screenHeight * downwardsTop) || y > (screenHeight * downwardsBottom))
	{
		downwards = !downwards;
	}

	if (scale < scaleMinimum || scale > scaleMaximum)
	{
		growing = !growing;
	}

	// std::cout << screenWidth << ", " << screenHeight <<  ", x: " << x << ", y: " << y << ", forwardsLeft: " << (screenWidth * forwardsLeft) << ", forwardsRight: " << (screenWidth * forwardsRight) << ", downwardsTop: " << (screenHeight * downwardsTop) << ", downwardsBottom: " << (screenHeight * downwardsBottom) << std::endl; 
}

void MainLoop()
{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			isRunning = false;
		}
	}

	WindowClear();

	RenderWhiteBackground();

	RenderBorders();

	RenderLogo();

	RenderText();

	RenderBalloon();

	UpdateBalloonAnimationValues();

	//Update screen
	SDL_RenderPresent(renderer);

	SDL_UpdateWindowSurface(window);
}

void Initialize(int width, int height)
{
	window = SDL_CreateWindow(
	    "Mobile Banner 320x100",
	    SDL_WINDOWPOS_UNDEFINED,
	    SDL_WINDOWPOS_UNDEFINED,
	    width,
	    height,
	    SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

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
}

extern "C"
{
	#if defined(__EMSCRIPTEN__)
		EMSCRIPTEN_KEEPALIVE 
	#endif
	void OnHostResize(int width, int height)
	{
		std::cout << "Resizing ..." << width << ", " << height << std::endl;

		screenWidth = width;
		screenHeight = height;
		SDL_SetWindowSize(window, width, height);
		resizedScale = false; // force re-scale)
		CreateEntities();
	}
}

#if defined(__EMSCRIPTEN__)
		EMSCRIPTEN_KEEPALIVE 
#endif
int main()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
	}

	TTF_Init();

	Initialize(screenWidth, screenHeight);

	LoadMedia();

	CreateEntities();
	// An alternative way of rendering the screen backgound as white:
	// SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));

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