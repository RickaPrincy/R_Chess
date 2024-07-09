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
		std::for_each(m_pieces.begin(), m_pieces.end(), [](const auto piece) { piece->init_position(); });
	}

	void Board::setup_all_pieces()
	{
		m_pieces.push_back(std::make_shared<Pawn>("pawnWhiteA2", PieceColor::WHITE, 0, 6));
		m_pieces.push_back(std::make_shared<Pawn>("pawnWhiteB2", PieceColor::WHITE, 1, 6));
		m_pieces.push_back(std::make_shared<Pawn>("pawnWhiteC2", PieceColor::WHITE, 2, 6));
		m_pieces.push_back(std::make_shared<Pawn>("pawnWhiteD2", PieceColor::WHITE, 3, 6));
		m_pieces.push_back(std::make_shared<Pawn>("pawnWhiteE2", PieceColor::WHITE, 4, 6));
		m_pieces.push_back(std::make_shared<Pawn>("pawnWhiteF2", PieceColor::WHITE, 5, 6));
		m_pieces.push_back(std::make_shared<Pawn>("pawnWhiteG2", PieceColor::WHITE, 6, 6));
		m_pieces.push_back(std::make_shared<Pawn>("pawnWhiteH2", PieceColor::WHITE, 7, 6));
		m_pieces.push_back(std::make_shared<Rook>("rookWhiteA1", PieceColor::WHITE, 0, 7));
		m_pieces.push_back(std::make_shared<Knight>("knightWhiteB1", PieceColor::WHITE, 1, 7));
		m_pieces.push_back(std::make_shared<Bishop>("bishopWhiteC1", PieceColor::WHITE, 2, 7));
		m_pieces.push_back(std::make_shared<Queen>("bishopWhiteD1", PieceColor::WHITE, 3, 7));
		m_pieces.push_back(std::make_shared<King>("kingWhiteE1", PieceColor::WHITE, 4, 7));
		m_pieces.push_back(std::make_shared<Bishop>("bishopWhiteF1", PieceColor::WHITE, 5, 7));
		m_pieces.push_back(std::make_shared<Knight>("kingWhiteG1", PieceColor::WHITE, 6, 7));
		m_pieces.push_back(std::make_shared<Rook>("rookWhiteH1", PieceColor::WHITE, 7, 7));

		// blacks
		m_pieces.push_back(std::make_shared<Pawn>("pawnBlackA2", PieceColor::BLACK, 0, 1));
		m_pieces.push_back(std::make_shared<Pawn>("pawnBlackB2", PieceColor::BLACK, 1, 1));
		m_pieces.push_back(std::make_shared<Pawn>("pawnBlackC2", PieceColor::BLACK, 2, 1));
		m_pieces.push_back(std::make_shared<Pawn>("pawnBlackD2", PieceColor::BLACK, 3, 1));
		m_pieces.push_back(std::make_shared<Pawn>("pawnBlackE2", PieceColor::BLACK, 4, 1));
		m_pieces.push_back(std::make_shared<Pawn>("pawnBlackF2", PieceColor::BLACK, 5, 1));
		m_pieces.push_back(std::make_shared<Pawn>("pawnBlackG2", PieceColor::BLACK, 6, 1));
		m_pieces.push_back(std::make_shared<Pawn>("pawnBlackH2", PieceColor::BLACK, 7, 1));
		m_pieces.push_back(std::make_shared<Rook>("rookBlackA1", PieceColor::BLACK, 0, 0));
		m_pieces.push_back(std::make_shared<Knight>("knightBlackB1", PieceColor::BLACK, 1, 0));
		m_pieces.push_back(std::make_shared<Bishop>("bishopBlackC1", PieceColor::BLACK, 2, 0));
		m_pieces.push_back(std::make_shared<Queen>("bishopBlackD1", PieceColor::BLACK, 3, 0));
		m_pieces.push_back(std::make_shared<King>("kingBlackE1", PieceColor::BLACK, 4, 0));
		m_pieces.push_back(std::make_shared<Bishop>("bishopBlackF1", PieceColor::BLACK, 5, 0));
		m_pieces.push_back(std::make_shared<Knight>("kingBlackG1", PieceColor::BLACK, 6, 0));
		m_pieces.push_back(std::make_shared<Rook>("rookBlackH1", PieceColor::BLACK, 7, 0));
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
