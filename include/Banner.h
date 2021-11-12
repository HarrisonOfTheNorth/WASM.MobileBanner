#pragma region license
/*
	MIT License
*/
#pragma endregion

#pragma region version_history
/*
	0.0.1: Moved classes to Banner.h, renamed namespace from MobileBanner to Banner.

*/
#pragma endregion

#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

#pragma region Vector2f_Declaration
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
namespace Banner
{
	// An item that is rendered as an SDL_Texture
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

#pragma region Entity_Implementation
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