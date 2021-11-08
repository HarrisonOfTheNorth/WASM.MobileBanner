#pragma once

#include <iostream>

namespace MobileBanner
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