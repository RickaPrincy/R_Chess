#include "move.hpp"

namespace rchess
{
	bool Move::operator==(const Move& other) const
	{
		return this->m_src == other.m_src && this->m_dest == other.m_dest &&
			   this->m_piece->get_color() == other.get_piece()->get_color();
	}

	bool Move::operator!=(const Move& other) const
	{
		return !(*this == other);
	}

	Move::Move(std::shared_ptr<Piece> piece, sdlk::Position src, sdlk::Position dest)
		: m_piece(piece),
		  m_src(src),
		  m_dest(dest)
	{
	}

}  // namespace rchess
