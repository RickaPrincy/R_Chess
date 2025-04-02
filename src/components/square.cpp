#include "./square.hpp"

#include <SDL2/SDL_render.h>

namespace rchess
{
	Square::Square(sdlk::Component *parent, sdlk::Size size, sdlk::Position position, SDL_Color color)
		: m_color(color),
		  sdlk::TexturedComponent(parent, size, position)
	{
	}

	void Square::re_create_texture(SDL_Renderer *renderer)
	{
		p_sdl_texture = SDL_CreateTexture(
			renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, this->get_width(), this->get_height());

		SDL_SetRenderTarget(renderer, p_sdl_texture);
		SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, m_color.a);
		SDL_RenderClear(renderer);
		SDL_SetRenderTarget(renderer, nullptr);
	}
}  // namespace rchess
