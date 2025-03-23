#include "case.hpp"

namespace rchess
{
	Case::Case(int x, int y) : m_x(x), m_y(y) { };
	Case::Case(int x, int y, std::shared_ptr<Piece> piece) : m_x(x), m_y(y), m_piece(piece) { };

	void Case::add_piece_attacker(std::shared_ptr<Piece> piece)
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

	void Case::reset()
	{
		this->m_white_attackers.clear();
		this->m_black_attackers.clear();
		this->m_piece = nullptr;
	}
}  // namespace rchess
