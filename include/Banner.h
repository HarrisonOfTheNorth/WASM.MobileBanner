#pragma region license, copyright, and trademarks
/*
	Banner.h
	+-------------------------------------------------------------+
	|                      y@R BannerEngine                       |
	|                                                             |
	|  "We host, you boast!" - Anthony Harrison                   |
	|                                                             |
	|                     You-At-A-Resource                       |
	+-------------------------------------------------------------+

Trademarks

y@R and You-At-A-Service are trademarks of Count Anthony Harrison, 
operating out of Cumberland in the UK

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

#pragma region version_history
/*
	Banner.h
	+-------------------------------------------------------------+
	|                      y@R BannerEngine                       |
	|  Version History                                            |
	+-------------------------------------------------------------+

	0.0.1: Moved classes to Banner.h, renamed namespace from MobileBanner to Banner.

*/
#pragma endregion

#pragma region Example Implementation
/*
	Banner.h
	+-------------------------------------------------------------+
	|                      y@R BannerEngine                       |
	|  Example Implementation                                     |
	+-------------------------------------------------------------+

*/
#pragma endregion

#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

#if defined(__EMSCRIPTEN__)
#include <emscripten/emscripten.h>
#endif

#pragma region 

// A copy of the SDL_ version, but without the prefix - the advantage being 
// that you don't need to include the SDL references in main.cpp unless
// you otherwise need them.
typedef enum
{
    WINDOW_FULLSCREEN = 0x00000001,         /**< fullscreen window */
    WINDOW_OPENGL = 0x00000002,             /**< window usable with OpenGL context */
    WINDOW_SHOWN = 0x00000004,              /**< window is visible */
    WINDOW_HIDDEN = 0x00000008,             /**< window is not visible */
    WINDOW_BORDERLESS = 0x00000010,         /**< no window decoration */
    WINDOW_RESIZABLE = 0x00000020,          /**< window can be resized */
    WINDOW_MINIMIZED = 0x00000040,          /**< window is minimized */
    WINDOW_MAXIMIZED = 0x00000080,          /**< window is maximized */
    WINDOW_MOUSE_GRABBED = 0x00000100,      /**< window has grabbed mouse input */
    WINDOW_INPUT_FOCUS = 0x00000200,        /**< window has input focus */
    WINDOW_MOUSE_FOCUS = 0x00000400,        /**< window has mouse focus */
    WINDOW_FULLSCREEN_DESKTOP = ( WINDOW_FULLSCREEN | 0x00001000 ),
    WINDOW_FOREIGN = 0x00000800,            /**< window not created by SDL */
    WINDOW_ALLOW_HIGHDPI = 0x00002000,      /**< window should be created in high-DPI mode if supported.
                                                     On macOS NSHighResolutionCapable must be set true in the
                                                     application's Info.plist for this to have any effect. */
    WINDOW_MOUSE_CAPTURE    = 0x00004000,   /**< window has mouse captured (unrelated to MOUSE_GRABBED) */
    WINDOW_ALWAYS_ON_TOP    = 0x00008000,   /**< window should always be above others */
    WINDOW_SKIP_TASKBAR     = 0x00010000,   /**< window should not be added to the taskbar */
    WINDOW_UTILITY          = 0x00020000,   /**< window should be treated as a utility window */
    WINDOW_TOOLTIP          = 0x00040000,   /**< window should be treated as a tooltip */
    WINDOW_POPUP_MENU       = 0x00080000,   /**< window should be treated as a popup menu */
    WINDOW_KEYBOARD_GRABBED = 0x00100000,   /**< window has grabbed keyboard input */
    WINDOW_VULKAN           = 0x10000000,   /**< window usable for Vulkan surface */
    WINDOW_METAL            = 0x20000000,   /**< window usable for Metal view */

    WINDOW_INPUT_GRABBED = WINDOW_MOUSE_GRABBED /**< equivalent to SDL_WINDOW_MOUSE_GRABBED for compatibility */
} WindowFlags;

#pragma endregion

#pragma region Vector2f_Declaration
/*
	Banner.h
	+-------------------------------------------------------------+
	|                      y@R BannerEngine                       |
	|  Vector2f Declaration                                       |
	+-------------------------------------------------------------+
*/
namespace Banner
{
	// A struct that represents an object's x, y, w, h, and scale. Defaults to 0.0f, 0.0f, 32.0f, 32.0f, and 1, respectively, unless overloaded.
	struct Vector2f
	{
		Vector2f()
		    : x(0.0f), y(0.0f)
		{
			w = 32;
			h = 32;
			scale = 1;
		}

		Vector2f(float p_scale)
		    : x(0.0f), y(0.0f), scale(p_scale)
		{
			w = 32;
			h = 32;
		}

		Vector2f(float p_x, float p_y)
		    : x(p_x), y(p_y)
		{
			w = 32;
			h = 32;
			scale = 1;
		}

		Vector2f(float p_x, float p_y, float p_scale)
		    : x(p_x), y(p_y), scale(p_scale)
		{
			w = 32;
			h = 32;
		}

		Vector2f(float p_x, float p_y, float p_w, float p_h)
		    : x(p_x), y(p_y), w(p_w), h(p_h)
		{
			scale = 1;
		}

		Vector2f(float p_x, float p_y, float p_w, float p_h, float p_scale)
		    : x(p_x), y(p_y), w(p_w), h(p_h), scale(p_scale)
		{
		}

		void print()
		{
			std::cout << x << ", " << y << ", " << w << ", " << h << std::endl;
		}

		float x, y, w, h, scale;
	};

}
#pragma endregion 


#pragma region Entity_Declaration
/*
	Banner.h
	+-------------------------------------------------------------+
	|                      y@R BannerEngine                       |
	|  Entity Declaration                                         |
	+-------------------------------------------------------------+
*/
namespace Banner
{
	// An item that is rendered on the canvas as an SDL_Texture
	class Entity
	{
	public:
		Entity(Vector2f p_pos, SDL_Texture *p_tex);
		Vector2f &GetPos()
		{
			return pos;
		}
		SDL_Texture *GetTex();
		SDL_Rect GetCurrentFrame();

	private:
		Vector2f pos;
		SDL_Rect currentFrame;
		SDL_Texture *tex;
	};

}
#pragma endregion

#pragma region BannerEngine_Implementation
/*
	Banner.h
	+-------------------------------------------------------------+
	|                      y@R BannerEngine                       |
	|  BannerEngine Declaration                                   |
	+-------------------------------------------------------------+
*/

namespace Banner
{
	enum ReturnCode { FAIL = 0, OK = 1 };

	// The BannerEngine itself, which your banner must inherit
	class BannerEngine
	{
		public:
			BannerEngine();

		public:
			char* ApplicationName;

		public: // overrides
			virtual Banner::ReturnCode LoadMedia();
			virtual void CreateFixedEntities();
			virtual void Loop();
			virtual void Resize(int width, int height);
			virtual ~BannerEngine();

		public: // lifecycle, Start calls LoadMedia, CreateFixedEntities, Loop, in that order
			Banner::ReturnCode Construct(int32_t screen_w, int32_t screen_h, int flags);
			Banner::ReturnCode Start();
			void Quit();

		public: // cancellation
			void SetIsRunning(bool app_isRunning);
			bool GetIsRunning();
			
		public: // entities
			void SetFixedEntities(std::vector<Banner::Entity> fixedEntities);
			std::vector<Banner::Entity> GetFixedEntities();
			void RenderEntity(Banner::Entity &p_entity);
			
		public:	// screen metadata
			int32_t GetScreenWidth();
			int32_t GetScreenHeight();

		public: // lowlevel SDL objects
			SDL_Window *GetWindow();
			SDL_Renderer *GetRenderer();	
			SDL_Surface *GetScreenSurface();
			SDL_Event GetEvent();
	
		private: // secret squirrel
			SDL_Window *window;
			SDL_Renderer *renderer;
			SDL_Surface *screenSurface;
			SDL_Event event;
			int32_t width, height;
			bool isRunning;
			std::vector<Banner::Entity> fixedEntities{ };
			void LoopInternal()
			{
				while (SDL_PollEvent(&event))
				{

					if (event.type == SDL_QUIT)
					{
						SetIsRunning(false);
					}
					if (event.type == SDL_WINDOWEVENT) {
						switch (event.window.event) {
						case SDL_WINDOWEVENT_SHOWN:
						SDL_Log("Window %d shown", event.window.windowID);
						break;
						case SDL_WINDOWEVENT_HIDDEN:
						SDL_Log("Window %d hidden", event.window.windowID);
						break;
						case SDL_WINDOWEVENT_EXPOSED:
						SDL_Log("Window %d exposed", event.window.windowID);
						break;
						case SDL_WINDOWEVENT_MOVED:
						SDL_Log("Window %d moved to %d,%d",
							event.window.windowID, event.window.data1,
							event.window.data2);
						break;
						case SDL_WINDOWEVENT_RESIZED:
						SDL_Log("Window %d resized to %dx%d",
							event.window.windowID, event.window.data1,
							event.window.data2);
							//Resize(event.window.data1, event.window.data2);
						break;
						case SDL_WINDOWEVENT_SIZE_CHANGED:
						SDL_Log("Window %d size changed to %dx%d",
							event.window.windowID, event.window.data1,
							event.window.data2);
							//Resize(event.window.data1, event.window.data2);
						break;
						case SDL_WINDOWEVENT_MINIMIZED:
						SDL_Log("Window %d minimized", event.window.windowID);
						break;
						case SDL_WINDOWEVENT_MAXIMIZED:
						SDL_Log("Window %d maximized", event.window.windowID);
						break;
						case SDL_WINDOWEVENT_RESTORED:
						SDL_Log("Window %d restored", event.window.windowID);
						break;
						case SDL_WINDOWEVENT_ENTER:
						SDL_Log("Mouse entered window %d",
							event.window.windowID);
						break;
						case SDL_WINDOWEVENT_LEAVE:
						SDL_Log("Mouse left window %d", event.window.windowID);
						break;
						case SDL_WINDOWEVENT_FOCUS_GAINED:
						SDL_Log("Window %d gained keyboard focus",
							event.window.windowID);
						break;
						case SDL_WINDOWEVENT_FOCUS_LOST:
						SDL_Log("Window %d lost keyboard focus",
							event.window.windowID);
						break;
						case SDL_WINDOWEVENT_CLOSE:
						SDL_Log("Window %d closed", event.window.windowID);
						break;
					#if SDL_VERSION_ATLEAST(2, 0, 5)
						case SDL_WINDOWEVENT_TAKE_FOCUS:
						SDL_Log("Window %d is offered a focus", event.window.windowID);
						break;
						case SDL_WINDOWEVENT_HIT_TEST:
						SDL_Log("Window %d has a special hit test", event.window.windowID);
						break;
					#endif
						default:
						SDL_Log("Window %d got unknown event %d",
							event.window.windowID, event.window.event);
						break;
						}	
					}				
				}

				SDL_RenderClear(renderer);
				Loop();
			}
	};
}

#pragma endregion

#pragma region Entity_Implementation
/*
	Banner.h
	+-------------------------------------------------------------+
	|                      y@R BannerEngine                       |
	|  Entity Implementation                                      |
	+-------------------------------------------------------------+
*/
namespace Banner
{
	Entity::Entity(Vector2f p_pos, SDL_Texture *p_tex)
	    : pos(p_pos), tex(p_tex)
	{
		currentFrame.x = 0;
		currentFrame.y = 0;
		currentFrame.w = p_pos.w;
		currentFrame.h = p_pos.h;
	}

	SDL_Texture *Entity::GetTex()
	{
		return tex;
	}

	SDL_Rect Entity::GetCurrentFrame()
	{
		return currentFrame;
	}

}
#pragma endregion

#pragma region BannerEngine_Implementation
/*
	Banner.h
	+-------------------------------------------------------------+
	|                      y@R BannerEngine                       |
	|  BannerEngine Implementation                                |
	+-------------------------------------------------------------+
*/

namespace Banner
{
	BannerEngine::BannerEngine() {}
	BannerEngine::~BannerEngine() 
	{
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		window = NULL;
		renderer = NULL;		
	}

	Banner::ReturnCode BannerEngine::Construct(int32_t screen_w, int32_t screen_h, int flags)
	{
		width = screen_w;
		height = screen_h;

		ReturnCode response = ReturnCode::OK;

		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			std::cout << "SDL_Init failed." << SDL_GetError() << std::endl;
			return ReturnCode::FAIL;
		}

		TTF_Init();

		window = SDL_CreateWindow(
			(char*)ApplicationName,
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			width,
			height,
			flags);

		if (window == NULL)
		{
			std::cout << "SDL_CreateWindow failed." << SDL_GetError() << std::endl;
			return ReturnCode::FAIL;			
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		if (renderer == NULL)
		{
			std::cout << "SDL_CreateRenderer failed." << SDL_GetError() << std::endl;
			return ReturnCode::FAIL;			
		}

#if defined(__EMSCRIPTEN__)
		screenSurface = SDL_GetWindowSurface(window);

		if (screenSurface == NULL)
		{
			std::cout << "SDL_GetWindowSurface failed." << SDL_GetError() << std::endl;
			return ReturnCode::FAIL;			
		}
#endif		

		return response;
	}

	void BannerEngine::RenderEntity(Banner::Entity &p_entity)
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

	Banner::ReturnCode BannerEngine::LoadMedia()
	{
		return Banner::ReturnCode::OK;
	}

	SDL_Window *BannerEngine::GetWindow()
	{
		return window;
	}

	SDL_Renderer * BannerEngine::GetRenderer()
	{
		return renderer;
	}

	SDL_Surface * BannerEngine::GetScreenSurface()
	{
		return screenSurface;
	}

	SDL_Event BannerEngine::GetEvent()
	{
		return event;
	}

	std::vector<Banner::Entity> BannerEngine::GetFixedEntities()
	{
		return fixedEntities;
	}

	void BannerEngine::SetFixedEntities(std::vector<Banner::Entity> entities)
	{
		fixedEntities = entities;
	}

	void BannerEngine::CreateFixedEntities() {}

	bool BannerEngine::GetIsRunning()
	{
		return isRunning;
	}

	void BannerEngine::SetIsRunning(bool app_isRunning)
	{
		isRunning = app_isRunning;
	}

	Banner::ReturnCode BannerEngine::Start()
	{
		LoadMedia();
		CreateFixedEntities();
		SetIsRunning(true);

	#if defined(__EMSCRIPTEN__)
		emscripten_set_main_loop(LoopInternal, -1, 1);
	#else
		while (isRunning)
		{
			Uint64 start = SDL_GetPerformanceCounter();

			LoopInternal();

			Uint64 end = SDL_GetPerformanceCounter();

			float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

			//std::cout << floor(16.666f - elapsedMS) << std::endl; // 16.666 is 1/60th of a second

			SDL_Delay(floor(16.666f - elapsedMS)); // delay so that the complete frame time is 1/60th of a second.
		}
	#endif
		return Banner::ReturnCode::OK;
	}

	void BannerEngine::Resize(int32_t w, int32_t h)
	{

		if(w!=width&&h!=height)
		{
			SDL_Log("Window Resized %d, %d", w, h);
			SDL_SetWindowSize(window, w, h);
			width = w;
			height = h;
		}
	}

	void BannerEngine::Loop() {}

	int32_t BannerEngine::GetScreenWidth()
	{
		return width;
	}

	int32_t BannerEngine::GetScreenHeight()
	{
		return height;
	}

	void BannerEngine::Quit()
	{
		IMG_Quit();
		SDL_Quit();
	}
}
#pragma endregion
