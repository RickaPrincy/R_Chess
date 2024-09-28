#include <SDL2/SDL_render.h>

#include <sdlk/utils/basic_wrapper.hpp>

#include "./draw.hpp"

namespace rchess
{
	void draw::line_rect(SDL_Renderer *renderer, SDL_Rect rect, SDL_Color color)
	{
		sdlk::throw_if_not_success(
			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a), "Cannot Set render target color");
		sdlk::throw_if_not_success(SDL_RenderDrawRect(renderer, &rect), "Cannot render rect");
	}
}  // namespace rchess
