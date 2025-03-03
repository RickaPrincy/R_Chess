#include <SDL2/SDL_render.h>

#include <sdlk/utils/basic_wrapper.hpp>

#include "./draw.hpp"

namespace rchess
{
	void draw::line_rect(SDL_Renderer *renderer, SDL_Rect rect, SDL_Color color, int thickness)
	{
		sdlk::throw_if_not_success(
			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a), "Cannot Set render target color");

		SDL_Rect tempRect = { rect.x, rect.y, rect.w, thickness };
		sdlk::throw_if_not_success(SDL_RenderFillRect(renderer, &tempRect), "Cannot render rect");

		tempRect = { rect.x, rect.y + rect.h - thickness, rect.w, thickness };
		sdlk::throw_if_not_success(SDL_RenderFillRect(renderer, &tempRect), "Cannot render rect");

		tempRect = { rect.x, rect.y + thickness, thickness, rect.h - thickness * 2 };
		sdlk::throw_if_not_success(SDL_RenderFillRect(renderer, &tempRect), "Cannot render rect");

		tempRect = { rect.x + rect.w - thickness, rect.y + thickness, thickness, rect.h - thickness * 2 };
		sdlk::throw_if_not_success(SDL_RenderFillRect(renderer, &tempRect), "Cannot render rect");
	}
}  // namespace rchess
