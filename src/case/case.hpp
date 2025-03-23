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
		std::vector<std::shared_ptr<Piece>> m_white_attackers{};
		std::vector<std::shared_ptr<Piece>> m_black_attackers{};
		std::shared_ptr<Piece> m_piece{};

	public:
		Case(int x, int y);
		Case(int x, int y, std::shared_ptr<Piece> piece);
		GETTER(int, x);
		GETTER(int, y);
		GETTER(std::vector<std::shared_ptr<Piece>>, white_attackers);
		GETTER(std::vector<std::shared_ptr<Piece>>, black_attackers);
		GETTER(std::shared_ptr<Piece>, piece);
		SETTER(std::shared_ptr<Piece>, piece);

		void add_piece_attacker(std::shared_ptr<Piece> piece);
		bool has_piece();
		void reset();
	};
}  // namespace rchess
