#include "case.hpp"

#include <algorithm>
#include <sdlk/components/image.hpp>

#include "../ui/draw.hpp"

namespace rchess
{
	using namespace constant;
	static sdlk::Image *p_background = nullptr;

	Case::Case(int x, int y)
		: sdlk::Component(p_background, sdlk::Size(UI_CASE_SIZE), sdlk::Position(x, y)),
		  m_x(x),
		  m_y(y) { };

	void Case::add_piece_attacker(Piece *piece)
	{
		if (piece->get_color() == PieceColor::WHITE)
		{
			this->m_white_attackers.push_back(piece);
		}
		else
		{
			this->m_white_attackers.push_back(piece);
		}
	}

	bool Case::has_piece()
	{
		return this->m_piece != nullptr;
	}

	void Case::reset_attackers()
	{
		this->m_white_attackers.clear();
		this->m_black_attackers.clear();
	}

	bool Case::is_attacker(std::shared_ptr<Piece> piece)
	{
		auto matches_piece = [&](Piece *attacker)
		{ return attacker->get_x() == piece->get_x() && attacker->get_y() == piece->get_y(); };

		return std::any_of(m_black_attackers.begin(), m_black_attackers.end(), matches_piece) ||
			   std::any_of(m_white_attackers.begin(), m_white_attackers.end(), matches_piece);
	}

	void Case::setup(sdlk::Image *background)
	{
		p_background = background;
	}

	void Case::render(SDL_Renderer *renderer)
	{
		if (!m_is_valid)
			return;

		SDL_Rect rect = {
			get_x() * UI_CASE_SIZE + UI_BORDER_SIZE, get_y() * UI_CASE_SIZE + UI_BORDER_SIZE, UI_CASE_SIZE, UI_CASE_SIZE
		};

		if (m_piece != nullptr)
		{
			draw::fill_rect(renderer, rect, { 255, 0, 0, 255 });
			return;
		}

		int center_x = rect.x + (UI_CASE_SIZE / 2) - (UI_CASE_SIZE / 8);
		int center_y = rect.y + (UI_CASE_SIZE / 2) - (UI_CASE_SIZE / 8);
		int size = UI_CASE_SIZE / 4;

		SDL_Rect small_rect = { center_x, center_y, size, size };
		draw::fill_rect(renderer, small_rect, { 255, 255, 0, 255 });
	}
}  // namespace rchess
