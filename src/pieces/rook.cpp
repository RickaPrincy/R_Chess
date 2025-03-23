#include "../board/board.hpp"
#include "../constant.hpp"
#include "pieces.hpp"

namespace rchess
{
	using namespace constant;
	Rook::Rook(PieceColor color, int x, int y) : Piece(PieceType::ROOK, color, x, y)
	{
	}

	bool Rook::add_attacker_and_should_stop(int &current_x,
		int &current_y,
		std::array<std::array<std::shared_ptr<Case>, ROW_COUNT>, COLUMN_COUNT> &cases)
	{
		std::shared_ptr<Piece> piece = cases[current_x][current_y]->get_piece();
		cases[current_x][current_y]->add_piece_attacker(this);

		if (piece != nullptr)
		{
			return true;
		}
		return false;
	}

	void Rook::calc_possible_moves(Board *board)
	{
		int start_x = this->get_x();
		int start_y = this->get_y();
		auto cases = board->get_cases();

		int current_x = start_x + 1;
		int current_y = start_y;

		// x++
		while (current_x < ROW_COUNT)
		{
			if (this->add_attacker_and_should_stop(current_x, current_y, cases))
			{
				break;
			}
			current_x++;
		}

		current_x = start_x;
		current_y = start_y;
		// x--
		while (current_x >= 0)
		{
			if (this->add_attacker_and_should_stop(current_x, current_y, cases))
			{
				break;
			}
			current_x--;
		}

		current_x = start_x;
		current_y = start_y;
		// y++
		while (current_y < COLUMN_COUNT)
		{
			if (this->add_attacker_and_should_stop(current_x, current_y, cases))
			{
				break;
			}
			current_y++;
		}

		current_x = start_x;
		current_y = start_y;
		// y--
		while (current_y >= 0)
		{
			if (this->add_attacker_and_should_stop(current_x, current_y, cases))
			{
				break;
			}
			current_y--;
		}
	}
}  // namespace rchess
