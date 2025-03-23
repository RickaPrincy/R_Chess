#include "pieces.hpp"

#include <SDL2/SDL_render.h>

#include <sdlk/utils/basic_wrapper.hpp>

#include "../case/case.hpp"
#include "../constant.hpp"
#include "../ui/draw.hpp"

using namespace rchess::constant;
constexpr const int THICKNESS_RECT_SELECTED_PIECE = 3;

namespace rchess
{
	static sdlk::Image *p_background = nullptr;
	static SDL_Texture *all_image_texture = nullptr;

	Piece::Piece(PieceType type, PieceColor color, int x, int y)
		: sdlk::Component(p_background, sdlk::Size(UI_PIECE_SIZE), sdlk::Position(x, y)),
		  m_type(type),
		  m_color(color)
	{
		m_src_rect = { static_cast<int>(m_type) * UI_PIECE_SIZE,
			static_cast<int>(m_color) * UI_PIECE_SIZE,
			UI_PIECE_SIZE,
			UI_PIECE_SIZE };
	}

	void Piece::render(SDL_Renderer *renderer)
	{
		if (!this->m_is_on_board)
		{
			return;
		}

		SDL_Rect dest_rect = { this->get_x() * UI_CASE_SIZE + UI_BORDER_SIZE + UI_PADDING_SIZE / 2,
			this->get_y() * UI_CASE_SIZE + UI_BORDER_SIZE + UI_PADDING_SIZE / 2,
			this->get_width(),
			this->get_height() };

		if (this->m_is_selected)
		{
			draw::line_rect(renderer,
				{ dest_rect.x - UI_PADDING_SIZE / 2, dest_rect.y - UI_PADDING_SIZE / 2, UI_CASE_SIZE, UI_CASE_SIZE },
				{ 255, 242, 0, 255 },
				THICKNESS_RECT_SELECTED_PIECE);
		}

		sdlk::throw_if_not_success(
			SDL_RenderCopy(renderer, all_image_texture, &m_src_rect, &dest_rect), "Cannot copy Pieces texture");
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

	bool Piece::is_valid_position(int x, int y)
	{
		return x >= 0 && x < ROW_COUNT && y >= 0 && y < COLUMN_COUNT;
	}

	void Piece::explore_direction(int dx,
		int dy,
		std::array<std::array<std::shared_ptr<Case>, ROW_COUNT>, COLUMN_COUNT> &cases)
	{
		int current_x = this->get_x() + dx;
		int current_y = this->get_y() + dy;

		while (is_valid_position(current_x, current_y))
		{
			auto &current_case = cases[current_x][current_y];
			current_case->add_piece_attacker(this);

			if (current_case->get_piece() != nullptr)
			{
				break;
			}
			current_x += dx;
			current_y += dy;
		}
	}
}  // namespace rchess
