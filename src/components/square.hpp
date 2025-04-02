#pragma once

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>

#include <sdlk/core/component.hpp>
#include <sdlk/core/preprocessor/getter_setter.hpp>
#include <sdlk/core/textured_component.hpp>

namespace rchess
{
	class Square : public sdlk::TexturedComponent
	{
	private:
		SDL_Color m_color{};

	public:
		GETTER(SDL_Color, color)
		SETTER(SDL_Color, color)
		Square(sdlk::Component *parent,
			sdlk::Size size,
			sdlk::Position position,
			SDL_Color color = { 255, 255, 255, 255 });
		virtual void re_create_texture(SDL_Renderer *renderer) override;
	};
}  // namespace rchess
