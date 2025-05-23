#include "move_histories_ui.hpp"

#include <sdlk/components/text.hpp>
#include <sdlk/core/textured_component.hpp>
#include <sdlk/utils/basic_wrapper.hpp>
#include <stdexcept>

#include "../constant.hpp"
#include "../fonts//font.hpp"

namespace rchess
{
	using namespace constant;
	using Position = sdlk::Position;

	MoveHistoriesUi::MoveHistoriesUi(sdlk::Window *window)
		: sdlk::TexturedComponent(window,
			  sdlk::Size(UI_WINDOW_WIDTH - UI_BOARD_SIZE, UI_WINDOW_HEIGHT),
			  Position(UI_BOARD_SIZE, 0))
	{
		this->p_window = window;
		this->p_move_title = new sdlk::Text(this, "Moves", { 255, 255, 212, 255 }, Font::get("arial", 20), Position(5));
	}

	void MoveHistoriesUi::re_create_texture(SDL_Renderer *renderer)
	{
		this->p_sdl_texture = SDL_CreateTexture(renderer,
			SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET,
			this->m_size.get_width(),
			this->m_size.get_height());

		if (sdlk::check::is_null(this->p_sdl_texture))
		{
			throw std::runtime_error("Cannot create move_histories_ui texture");
		}
	}

	MoveHistoriesUi::~MoveHistoriesUi()
	{
		delete this->p_move_title;
	}
}  // namespace rchess
