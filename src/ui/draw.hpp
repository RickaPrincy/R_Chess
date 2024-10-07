#pragma once

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

namespace rchess
{
	namespace draw
	{
		void line_rect(SDL_Renderer *renderer, SDL_Rect rect, SDL_Color color, int thickness);
	}  // namespace draw
}  // namespace rchess
