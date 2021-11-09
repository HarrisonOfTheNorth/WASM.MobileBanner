#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "MobileBanner/Maths.hpp"

namespace MobileBanner
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