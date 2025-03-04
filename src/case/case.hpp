#pragma once

#include <sdlk/core/preprocessor/getter_setter.hpp>

#include "../pieces/pieces.hpp"

namespace rchess
{
	class ValidCase
	{
	private:
		int m_x{ 0 }, m_y{ 0 };
		int m_white_attacks{ 0 };
		int m_black_attacks{ 0 };

	public:
		ValidCase(int x, int y);
		GETTER(int, x);
		GETTER(int, y);
		GETTER(int, white_attacks);
		GETTER(int, black_attacks);
		void append_piece_attack(Piece *piece);
	};
}  // namespace rchess
