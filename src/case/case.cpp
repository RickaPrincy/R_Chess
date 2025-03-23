#include "case.hpp"

#include <algorithm>

namespace rchess
{
	Case::Case(int x, int y) : m_x(x), m_y(y) { };
	Case::Case(int x, int y, Piece *piece) : m_x(x), m_y(y), m_piece(piece) { };

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
		auto from_black_attacker = std::find_if(this->m_black_attackers.begin(),
			this->m_black_attackers.end(),
			[&](Piece *black_attacker)
			{ return black_attacker->get_x() == piece->get_x() && black_attacker->get_y() == piece->get_y(); });

		auto from_white_attacker = std::find_if(this->m_white_attackers.begin(),
			this->m_white_attackers.end(),
			[&](Piece *white_attacker)
			{ return white_attacker->get_x() == piece->get_x() && white_attacker->get_y() == piece->get_y(); });

		return from_black_attacker != this->m_black_attackers.end() ||
			   from_white_attacker != this->m_white_attackers.end();
	}
}  // namespace rchess
