#pragma region license
/*
	main.cpp
	+-------------------------------------------------------------+
	|                      y@R BannerEngine                       |
	|                                                             |
	|  "We host, you boast!" - Anthony Harrison                   |
	|                                                             |
	|                     You-At-A-Resource                       |
	+-------------------------------------------------------------+

Trademarks

y@R and You-At-A-Resource are trademarks of Count Anthony Harrison, 
operating out of Cumberland in the UK.

y@R is pronounced Yatter.

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
	|  Example BannerEngine Implementation, 'ExampleBannerAd'     |
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

class ExampleBannerAd : public Banner::BannerEngine
{
public:
	ExampleBannerAd()
	{
		Initialize();
	}

	/*
		Five overrides to write your code:

		- LoadMedia
		- CreateFixedEntities
		- Loop
		- Resize
		- ~[Destructor]

		With all of the following accessible as well:
		
		- Start();
		- SetIsRunning(bool app_isRunning);
		- GetIsRunning();
		- void SetFixedEntities(std::vector<Banner::Entity> fixedEntities);
		- std::vector<Banner::Entity> GetFixedEntities();
		- void RenderEntity(Banner::Entity &p_entity);
		- int32_t GetScreenWidth();
		- int32_t GetScreenHeight();
		- void Quit();

		As well as access to the low-level SDL2 objects:

		- SDL_Window *GetWindow();
		- SDL_Renderer *GetRenderer();	
		- SDL_Surface *GetScreenSurface();
		- SDL_Event GetEvent();

		Called in Main as follows (example):

		  Banner::BannerEngine* banner310x100 = new ExampleBannerAd();

		  int applicationFlags = WINDOW_SHOWN | WINDOW_ALWAYS_ON_TOP;
		  int wasmFlags = WINDOW_SHOWN;

		  banner310x100->Construct(320,100,applicationFlags); 
		  banner310x100->Start();
		  banner310x100->Quit();

	*/

	void SetBalloonPresets(
				float preset_scaleMinimum,
				float preset_scaleMaximum,
				float preset_xForwards,
				float preset_forwardsLeft,
				float preset_forwardsRight, 
				float preset_yDownwards,
				float preset_downwardsTop,
				float preset_downwardsBottom,
				float preset_scaleGrowing
	)
	{
		scaleMinimum = preset_scaleMinimum;
		scaleMaximum = preset_scaleMaximum;
		xForwards = preset_xForwards;
		forwardsLeft = preset_forwardsLeft;
		forwardsRight = preset_forwardsRight;
		yDownwards = preset_yDownwards;
		downwardsTop = preset_downwardsTop;
		downwardsBottom = preset_downwardsBottom;
		scaleGrowing = preset_scaleGrowing;
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
		for (Banner::Entity &entity : GetFixedEntities()) // Render all the fixed entities
		{
			RenderEntity(entity);
		}

		float logoScale = (GetScreenHeight() - (2.0f * defaultTileWidth)) / 512.0f; // Ours is a square logo of 512.0f wide
		// and we want to fit it between both borders but allow the canvas to resize, hence the logo needs to be able to scale

		Banner::Entity yatrlogo(Banner::Vector2f(defaultTileWidth, defaultTileWidth, 512, 512, logoScale), tex_logo_512x512);
		RenderEntity(yatrlogo);

		if(GetScreenWidth() < 321.0f && GetScreenHeight() < 101.0f) // this is the trademark text, arbitrarily positioned
		{
			Banner::Entity text(Banner::Vector2f(GetScreenWidth() / 3.68, 40, 463, 62, 0.45), tex_youataresource_463x62);
			RenderEntity(text);
		}

		{
			// two balloons, but only one is rendered.
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

		// the black art of plugging in various values for each screen-width until the balloon moved with grace,
		// appropriate sizing, and appropriate growth and shrinking within appropriate boundaries.
		if(GetScreenWidth() < 400)
		{
			if(!resizedScale) scale = 0.2f; resizedScale = true; // must be between scaleMinimum and scaleMaximum
			SetBalloonPresets(0.1f, 0.5f, 0.4f, 0.0f, 1.0f, 0.4f, 0.00f, 1.0f, 0.002f);
		}
		else if(GetScreenWidth() < 800)
		{
			if(!resizedScale) scale = 0.4f; resizedScale = true; // must be between scaleMinimum and scaleMaximum
			SetBalloonPresets(0.3f, 1.0f, 0.6f, 0.0f, 1.0f, 0.6f, 0.0f, 1.0f, 0.002f);
		}
		else if(GetScreenWidth() < 1200)
		{
			if(!resizedScale) scale = 0.8f; resizedScale = true; // must be between scaleMinimum and scaleMaximum
			SetBalloonPresets(0.7f, 1.5f, 0.8f, 0.0f, 0.9f, 0.8f, 0.0f, 0.8f,0.002f);
		}
		else
		{
			if(!resizedScale) scale = 0.8f; resizedScale = true; // must be between scaleMinimum and scaleMaximum
			SetBalloonPresets(0.7f, 1.5f, 1.0f, 0.0f, 0.9f, 1.0f, 0.0f, 0.8f, 0.002f);
		}

		// Balloon position-change logic
		if (forwards){x+=xForwards;}else{x-=xForwards;}
		if (downwards){y+=yDownwards;}else{y-=yDownwards;}
		if (growing){scale+=scaleGrowing;}else{scale-=scaleGrowing;}
		if (x<(GetScreenWidth()*forwardsLeft)||x>(GetScreenWidth()*forwardsRight)){forwards=!forwards;}
		if (y<(GetScreenHeight()*downwardsTop)||y>(GetScreenHeight()* downwardsBottom)){downwards=!downwards;}
		if (scale<scaleMinimum||scale>scaleMaximum){growing=!growing;}

		// Mandatory
		SDL_RenderPresent(GetRenderer());
		SDL_UpdateWindowSurface(GetWindow());
	}

	void Resize(int width, int height) override
	{
		resizedScale = false; // force re-scale)
		CreateFixedEntities();		
		SDL_SetWindowSize(GetWindow(), width, height);
	}

	~ExampleBannerAd() override
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

	private: // Variables that affect Balloon delta changes per frame
		float scaleMinimum; // how small will the balloon shrink?
		float scaleMaximum; // how big will the balloon grow?
		float xForwards; // how far will x advance when moving forwards
		float forwardsLeft; // minimum forwards flip-flop
		float forwardsRight; // maximum forwards flip-flop
		float yDownwards; // how far will y advance when moving downwards
		float downwardsTop; // minimum downwards flip-flop
		float downwardsBottom; // maximum downwards flip-flop
		float scaleGrowing; // growth increment


		void Initialize()
		{
			ApplicationName = (char*)"Example 310x100"; // in the base class

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
Banner::BannerEngine* banner310x100 = new ExampleBannerAd();

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

	int applicationFlags = WINDOW_SHOWN | WINDOW_ALWAYS_ON_TOP;
	int wasmFlags = WINDOW_SHOWN;

	banner310x100->Construct(320,100,applicationFlags); 
	banner310x100->Start();
	banner310x100->Quit();

	return EXIT_SUCCESS;
}
#pragma endregion