#pragma once

#include <SDL2/SDL_render.h>

#include <sdlk/components/text.hpp>
#include <sdlk/core/textured_component.hpp>
#include <sdlk/core/window.hpp>

namespace rchess
{
	class MoveHistoriesUi : public sdlk::TexturedComponent
	{
	private:
		sdlk::Window *p_window = nullptr;
		sdlk::Text *p_move_title = nullptr;

	protected:
		void re_create_texture(SDL_Renderer *renderer) override;

	public:
		MoveHistoriesUi(sdlk::Window *window);

		virtual ~MoveHistoriesUi();
	};
}  // namespace rchess
