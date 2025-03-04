#include "case.hpp"

namespace rchess
{
	ValidCase::ValidCase(int x, int y) : m_x(x), m_y(y)
	{
	}

	void ValidCase::append_piece_attack(Piece *piece)
	{
		if (piece->get_color() == PieceColor::WHITE)
		{
			this->m_white_attacks += this->m_white_attacks;
		}
		else
		{
			this->m_black_attacks += this->m_black_attacks;
		}
	}
}  // namespace rchess
