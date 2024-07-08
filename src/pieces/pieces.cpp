#include "pieces.hpp"

#include <SDL2/SDL_render.h>

#include <sdlk/utils/basic_wrapper.hpp>
#include <stdexcept>

#include "../config/config.hpp"

using namespace rchess::config;

namespace rchess
{
	static sdlk::Window *p_main_window = nullptr;
	static SDL_Texture *all_image_texture = nullptr;

	Piece::Piece(PieceType type, PieceColor color, int x, int y)
		: sdlk::Component(p_main_window, sdlk::Size(PIECE_SIZE), sdlk::Position(x, y)),
		  m_type(type),
		  m_color(color)
	{
		m_src_rect = {
			static_cast<int>(m_type) * PIECE_SIZE, static_cast<int>(m_color) * PIECE_SIZE, PIECE_SIZE, PIECE_SIZE
		};

		if (sdlk::check::is_null(p_main_window))
		{
			throw std::runtime_error("Piece was not setting up");
		}
		p_main_window->append_child(this);
	}

	void Piece::render(SDL_Renderer *renderer)
	{
		SDL_Rect dest_rect = { this->get_x() * CASE_SIZE + BORDER_SIZE + PADDING_SIZE,
			this->get_y() * CASE_SIZE + BORDER_SIZE + PADDING_SIZE,
			this->get_width(),
			this->get_height() };
		sdlk::throw_if_not_success(
			SDL_RenderCopy(renderer, all_image_texture, &m_src_rect, &dest_rect), "Cannot copy Pieces texture");
	}

	void Piece::setup(sdlk::Window *window, const std::string &path)
	{
		all_image_texture = sdlk::load_image(window->get_sdl_renderer(), path);
		p_main_window = window;
	}

	void Piece::clean_up()
	{
		if (!sdlk::check::is_null(all_image_texture))
		{
			SDL_DestroyTexture(all_image_texture);
		}
	}
}  // namespace rchess
