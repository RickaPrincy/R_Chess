#include "pieces.hpp"

#include <SDL2/SDL_render.h>

#include <sdlk/utils/basic_wrapper.hpp>

#include "../config/config.hpp"

using namespace rchess::config;

namespace rchess
{
	static sdlk::Image *p_background = nullptr;
	static SDL_Texture *all_image_texture = nullptr;

	Piece::Piece(std::string name, PieceType type, PieceColor color, int x, int y)
		: sdlk::Component(p_background, sdlk::Size(PIECE_SIZE), sdlk::Position(x, y)),
		  m_name(name),
		  m_type(type),
		  m_color(color),
		  m_initial_position(sdlk::Position(x, y))
	{
		m_src_rect = {
			static_cast<int>(m_type) * PIECE_SIZE, static_cast<int>(m_color) * PIECE_SIZE, PIECE_SIZE, PIECE_SIZE
		};
	}
	void Piece::init_position()
	{
		this->set_position(m_initial_position);
		this->do_re_render();
	}

	void Piece::render(SDL_Renderer *renderer)
	{
		SDL_Rect dest_rect = { this->get_x() * CASE_SIZE + BORDER_SIZE + PADDING_SIZE,
			this->get_y() * CASE_SIZE + BORDER_SIZE + PADDING_SIZE,
			this->get_width(),
			this->get_height() };
		sdlk::throw_if_not_success(
			SDL_RenderCopy(renderer, all_image_texture, &m_src_rect, &dest_rect), "Cannot copy Pieces texture");

		if (this->m_is_on_board && this->m_is_selected)
		{
			// render square
		}
	}

	void Piece::setup(sdlk::Image *background, SDL_Renderer *renderer, const std::string &path)
	{
		all_image_texture = sdlk::load_image(renderer, path);
		p_background = background;
	}

	void Piece::clean_up()
	{
		if (!sdlk::check::is_null(all_image_texture))
		{
			SDL_DestroyTexture(all_image_texture);
		}
	}
}  // namespace rchess