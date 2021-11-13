#pragma region license
/*
	main.cpp
	+-------------------------------------------------------------+
	|                      y@R BannerEngine                       |
	|  "We host, you boast!" - Anthony Harrison                   |
	+-------------------------------------------------------------+

MIT License

Copyright (c) 2021 Count Anthony Harrison

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#pragma endregion

#pragma region Custom BannerEngine Implementation
/*
	main.cpp
	+-------------------------------------------------------------+
	|                      y@R BannerEngine                       |
	|  Custom BannerEngine Implementation                         |
	+-------------------------------------------------------------+
*/

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_ttf.h>
#include <vector>

#if defined(__EMSCRIPTEN__)
#include <emscripten/emscripten.h>
#endif

#include "Banner.h"

class BannerAd320x100 : public Banner::BannerEngine
{
public:
	BannerAd320x100()
	{
		Initialize();
	}

	void Resize(int width, int height) override
	{
		resizedScale = false; // force re-scale)
		CreateFixedEntities();		
		SDL_SetWindowSize(GetWindow(), width, height);
	}

	Banner::ReturnCode LoadMedia() override
	{
		Banner::ReturnCode response = Banner::ReturnCode::OK;

		SDL_Surface *image = SDL_LoadBMP("resources/square_white_32x32.bmp");
		tex_square_white_32x32 = SDL_CreateTextureFromSurface(GetRenderer(), image);
		if (tex_square_white_32x32 == NULL)
		{
			printf("Failed to load texture image 1!\n");
			response = Banner::ReturnCode::FAIL;
		}

		image = SDL_LoadBMP("resources/square_yellow_32x32.bmp");
		tex_square_black_32x32 = SDL_CreateTextureFromSurface(GetRenderer(), image);
		if (tex_square_black_32x32 == NULL)
		{
			printf("Failed to load texture image 2!\n");
			response = Banner::ReturnCode::FAIL;
		}

		image = SDL_LoadBMP("resources/logo512x512.bmp");
		tex_logo_512x512 = SDL_CreateTextureFromSurface(GetRenderer(), image);
		if (tex_logo_512x512 == NULL)
		{
			printf("Failed to load texture image 3!\n");
			response = Banner::ReturnCode::FAIL;
		}

		image = SDL_LoadBMP("resources/advertisementballoon512x512.bmp");
		tex_advertisementballoon_512x512 = SDL_CreateTextureFromSurface(GetRenderer(), image);
		if (tex_advertisementballoon_512x512 == NULL)
		{
			printf("Failed to load texture image 4!\n");
			response = Banner::ReturnCode::FAIL;
		}

		image = SDL_LoadBMP("resources/qrcodeballoon512x512.bmp");
		tex_qrcodeballoon_512x512 = SDL_CreateTextureFromSurface(GetRenderer(), image);
		if (tex_qrcodeballoon_512x512 == NULL)
		{
			printf("Failed to load texture image 5!\n");
			response = Banner::ReturnCode::FAIL;
		}

		image = SDL_LoadBMP("resources/youataresource463x62.bmp");
		tex_youataresource_463x62 = SDL_CreateTextureFromSurface(GetRenderer(), image);
		if (tex_youataresource_463x62 == NULL)
		{
			printf("Failed to load texture image 6!\n");
			response = Banner::ReturnCode::FAIL;
		}

		return response;
	}

	void CreateFixedEntities() override
	{
		std::vector<Banner::Entity> fixedEntities = GetFixedEntities();

		// White Background
		Banner::Entity background(Banner::Vector2f(0, 0, GetScreenWidth(), GetScreenHeight()), tex_square_white_32x32);
		fixedEntities.push_back(background);
		// top border entities
		for (int x = 0; x < GetScreenWidth() / defaultTileWidth; x++)
		{
			{
				Banner::Entity tile(Banner::Vector2f(x * defaultTileWidth, 0, defaultTileWidth, defaultTileWidth), tex_square_black_32x32);
				fixedEntities.push_back(tile);
			}
		}

		// left border entities
		for (int x = 0; x < GetScreenWidth() / defaultTileWidth; x++)
		{
			{
				Banner::Entity tile(Banner::Vector2f(0, x * defaultTileWidth, defaultTileWidth, defaultTileWidth), tex_square_black_32x32);
				fixedEntities.push_back(tile);
			}
		}

		// bottom border entities
		for (int x = 0; x < GetScreenWidth() / defaultTileWidth; x++)
		{
			{
				Banner::Entity tile(Banner::Vector2f(x * defaultTileWidth, GetScreenHeight() - defaultTileWidth, defaultTileWidth, defaultTileWidth), tex_square_black_32x32);
				fixedEntities.push_back(tile);
			}
		}

		// right border entities
		for (int x = 0; x < GetScreenWidth() / defaultTileWidth; x++)
		{
			{
				Banner::Entity tile(Banner::Vector2f(GetScreenWidth() - defaultTileWidth, x * defaultTileWidth, defaultTileWidth, defaultTileWidth), tex_square_black_32x32);
				fixedEntities.push_back(tile);
			}
		}	

		SetFixedEntities(fixedEntities);

		std::cout << "Fixed Entities loaded: " << fixedEntities.size() << std::endl;	
	}

	void Loop() override
	{
		for (Banner::Entity &entity : GetFixedEntities())
		{
			RenderEntity(entity);
		}

			float logoScale = (GetScreenHeight() - (2.0f * defaultTileWidth)) / 512.0f;

		Banner::Entity yatrlogo(Banner::Vector2f(defaultTileWidth, defaultTileWidth, 512, 512, logoScale), tex_logo_512x512);
		RenderEntity(yatrlogo);

		if(GetScreenWidth() < 321.0f && GetScreenHeight() < 101.0f)
		{
			Banner::Entity text(Banner::Vector2f(GetScreenWidth() / 3.68, 40, 463, 62, 0.45), tex_youataresource_463x62);
			RenderEntity(text);
		}

		{
			Banner::Entity red(Banner::Vector2f(x, y, 512, 512, scale), tex_advertisementballoon_512x512);
			Banner::Entity blue(Banner::Vector2f(x, y, 512, 512, scale), tex_qrcodeballoon_512x512);
			if (x > GetScreenWidth() / 3)
			{
				RenderEntity(red);
			}
			else
			{
				RenderEntity(blue);
			}
		}	

		// Balloon change presets by screen width
		float scaleMinimum = 0.0f;
		float scaleMaximum = 0.0f;
		float xForwards = 0.0f;
		float forwardsLeft = 0.0f;
		float forwardsRight = 0.0f;
		float yDownwards = 0.0f;
		float downwardsTop = 0.0f;
		float downwardsBottom = 0.0f;
		float scaleGrowing = 0.0f;

		if(GetScreenWidth() < 400)
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
		else if(GetScreenWidth() < 800)
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
		else if(GetScreenWidth() < 1200)
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

		// Balloon position-change logic
		if (forwards){x+=xForwards;}else{x-=xForwards;}
		if (downwards){y+=yDownwards;}else{y-=yDownwards;}
		if (growing){scale+=scaleGrowing;}else{scale-=scaleGrowing;}
		if (x<(GetScreenWidth()*forwardsLeft)||x>(GetScreenWidth()*forwardsRight)){forwards=!forwards;}
		if (y<(GetScreenHeight()*downwardsTop)||y>(GetScreenHeight()* downwardsBottom)){downwards=!downwards;}
		if (scale<scaleMinimum||scale>scaleMaximum){growing=!growing;}

		SDL_RenderPresent(GetRenderer());
		SDL_UpdateWindowSurface(GetWindow());

	}

	~BannerAd320x100() override
	{
		SDL_DestroyTexture(tex_logo_512x512);
		SDL_DestroyTexture(tex_square_white_32x32);
		SDL_DestroyTexture(tex_square_black_32x32);
		SDL_DestroyTexture(tex_advertisementballoon_512x512);
		SDL_DestroyTexture(tex_qrcodeballoon_512x512);
		SDL_DestroyTexture(tex_youataresource_463x62);
	}

	private:
		SDL_Texture *tex_logo_512x512;
		SDL_Texture *tex_square_white_32x32;
		SDL_Texture *tex_square_black_32x32;
		SDL_Texture *tex_advertisementballoon_512x512;
		SDL_Texture *tex_qrcodeballoon_512x512;
		SDL_Texture *tex_youataresource_463x62;

	private: // Balloon variable initial values:
		float x; 		// balloon tex x
		float y;  		// balloon tex y
		float scale;	     	// balloon rendering scale
		bool resizedScale; 
		bool forwards;	     	// is balloon moving to the right?
		bool growing;	     	// is balloon growing in size?
		bool downwards;	     	// is balloon moving downwards?	
		float defaultTileWidth;

		void Initialize()
		{
			AppName = (char*)"Example 310x100"; // in the base class

			x = GetScreenWidth() * 0.1;
			y = GetScreenHeight() / 5;
			scale = 0.25;
			resizedScale = true;
			forwards = true;
			growing = true;
			downwards = true;
			defaultTileWidth = 16;
		}
};

#pragma endregion

#pragma region Main Implementaion
/*
	main.cpp
	+-------------------------------------------------------------+
	|                      y@R BannerEngine                       |
	|  Main Implementation - Entry Point - main()                 |
	+-------------------------------------------------------------+
*/
Banner::BannerEngine* banner310x100 = new BannerAd320x100();

extern "C"
{
	#if defined(__EMSCRIPTEN__)
		EMSCRIPTEN_KEEPALIVE 
	#endif
	void OnHostResize(int width, int height)
	{
		std::cout << "Resizing ..." << width << ", " << height << std::endl;

		banner310x100->Resize(width, height);
	}
}

#if defined(__EMSCRIPTEN__)
	EMSCRIPTEN_KEEPALIVE 
#endif
int main()
{

	#if defined(__EMSCRIPTEN__)
	WindowFlags flags = WINDOW_SHOWN;
	#else
	int flags = WINDOW_SHOWN | WINDOW_ALWAYS_ON_TOP;
	#endif
	banner310x100->Construct(320,100,flags); 
	banner310x100->Start();
	banner310x100->Quit();

	return EXIT_SUCCESS;
}
#pragma endregion