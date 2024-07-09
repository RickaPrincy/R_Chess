#include "board.hpp"

#include <algorithm>

#include "../config/config.hpp"
#include "../pieces/pieces.hpp"

namespace rchess
{
	Board::Board()
	{
		this->setup_all_pieces();
	}

	void Board::init_new_game()
	{
		std::for_each(m_pieces.begin(), m_pieces.end(), [](Piece &piece) { piece.init_position(); });
	}

    Pawn test("pawnWhiteA2", PieceColor::WHITE, 0, 1);
	void Board::setup_all_pieces()
	{
		// whites
		m_pieces.push_back(test);
		// m_pieces.push_back(Pawn("pawnWhiteB2", PieceColor::WHITE, 1, 1));
		// m_pieces.push_back(Pawn("pawnWhiteC2", PieceColor::WHITE, 2, 1));
		// m_pieces.push_back(Pawn("pawnWhiteD2", PieceColor::WHITE, 3, 1));
		// m_pieces.push_back(Pawn("pawnWhiteE2", PieceColor::WHITE, 4, 1));
		// m_pieces.push_back(Pawn("pawnWhiteF2", PieceColor::WHITE, 5, 1));
		// m_pieces.push_back(Pawn("pawnWhiteH2", PieceColor::WHITE, 6, 1));
		// m_pieces.push_back(Rook("rookWhiteA1", PieceColor::WHITE, 0, 0));
		// m_pieces.push_back(Knight("knightWhiteB1", PieceColor::WHITE, 1, 0));
		// m_pieces.push_back(Bishop("bishopWhiteC1", PieceColor::WHITE, 2, 0));
		// m_pieces.push_back(Queen("bishopWhiteD1", PieceColor::WHITE, 3, 0));
		// m_pieces.push_back(King("kingWhiteE1", PieceColor::WHITE, 4, 0));
		// m_pieces.push_back(Bishop("bishopWhiteF1", PieceColor::WHITE, 5, 0));
		// m_pieces.push_back(Knight("kingWhiteG1", PieceColor::WHITE, 6, 0));
		// m_pieces.push_back(Rook("rookWhiteH1", PieceColor::WHITE, 7, 0));

		// blacks
		// TODO
	}

	sdlk::Position Board::get_case_position_from_mouse_position(const SDL_MouseMotionEvent &event)
	{
		if (!config::is_on_board(event))
		{
			return sdlk::Position(-1, -1);
		}
		// TODO
		return sdlk::Position();
	}
}  // namespace rchess
