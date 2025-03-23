#pragma once

#include <memory>
#include <sdlk/core/preprocessor/getter_setter.hpp>
#include <vector>

#include "../pieces/pieces.hpp"

namespace rchess
{
	class Case
	{
	private:
		int m_x{ 0 }, m_y{ 0 };
		bool m_is_valid{ false };
		std::vector<Piece *> m_white_attackers{};
		std::vector<Piece *> m_black_attackers{};
		std::shared_ptr<Piece> m_piece{};

	public:
		Case(int x, int y);
		Case(int x, int y, Piece *piece);
		GETTER(int, x);
		GETTER(int, y);
		GETTER(bool, is_valid);
		SETTER(bool, is_valid);
		GETTER(std::vector<Piece *>, white_attackers);
		GETTER(std::vector<Piece *>, black_attackers);
		GETTER(std::shared_ptr<Piece>, piece);
		SETTER(std::shared_ptr<Piece>, piece);

		void add_piece_attacker(Piece *piece);
		void reset_attackers();
		bool has_piece();
		bool is_attacker(std::shared_ptr<Piece> piece);
	};
}  // namespace rchess
