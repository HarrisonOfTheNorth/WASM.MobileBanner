#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "MobileBanner/Entity.hpp"

namespace MobileBanner
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