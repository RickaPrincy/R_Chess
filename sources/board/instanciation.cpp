#include "board.hpp"

namespace rchess
{
	void Board::instanciate_cases_and_pieces()
	{
		for (int x = 0; x < ROW_COUNT; x++)
		{
			for (int y = 0; y < COLUMN_COUNT; y++)
			{
				m_cases[x][y] = std::make_shared<Case>(x, y);
			}
		}

		m_pieces[0] = std::make_shared<Pawn>(PieceColor::WHITE, 0, 6);
		m_pieces[1] = std::make_shared<Pawn>(PieceColor::WHITE, 1, 6);
		m_pieces[2] = std::make_shared<Pawn>(PieceColor::WHITE, 2, 6);
		m_pieces[3] = std::make_shared<Pawn>(PieceColor::WHITE, 3, 6);
		m_pieces[4] = std::make_shared<Pawn>(PieceColor::WHITE, 4, 6);
		m_pieces[5] = std::make_shared<Pawn>(PieceColor::WHITE, 5, 6);
		m_pieces[6] = std::make_shared<Pawn>(PieceColor::WHITE, 6, 6);
		m_pieces[7] = std::make_shared<Pawn>(PieceColor::WHITE, 7, 6);
		m_pieces[8] = std::make_shared<Rook>(PieceColor::WHITE, 0, 7);
		m_pieces[9] = std::make_shared<Knight>(PieceColor::WHITE, 1, 7);
		m_pieces[10] = std::make_shared<Bishop>(PieceColor::WHITE, 2, 7);
		m_pieces[11] = std::make_shared<Queen>(PieceColor::WHITE, 3, 7);
		m_pieces[12] = std::make_shared<King>(PieceColor::WHITE, 4, 7);
		m_pieces[13] = std::make_shared<Bishop>(PieceColor::WHITE, 5, 7);
		m_pieces[14] = std::make_shared<Knight>(PieceColor::WHITE, 6, 7);
		m_pieces[15] = std::make_shared<Rook>(PieceColor::WHITE, 7, 7);

		// blacks
		m_pieces[16] = std::make_shared<Pawn>(PieceColor::BLACK, 0, 1);
		m_pieces[17] = std::make_shared<Pawn>(PieceColor::BLACK, 1, 1);
		m_pieces[18] = std::make_shared<Pawn>(PieceColor::BLACK, 2, 1);
		m_pieces[19] = std::make_shared<Pawn>(PieceColor::BLACK, 3, 1);
		m_pieces[20] = std::make_shared<Pawn>(PieceColor::BLACK, 4, 1);
		m_pieces[21] = std::make_shared<Pawn>(PieceColor::BLACK, 5, 1);
		m_pieces[22] = std::make_shared<Pawn>(PieceColor::BLACK, 6, 1);
		m_pieces[23] = std::make_shared<Pawn>(PieceColor::BLACK, 7, 1);
		m_pieces[24] = std::make_shared<Rook>(PieceColor::BLACK, 0, 0);
		m_pieces[25] = std::make_shared<Knight>(PieceColor::BLACK, 1, 0);
		m_pieces[26] = std::make_shared<Bishop>(PieceColor::BLACK, 2, 0);
		m_pieces[27] = std::make_shared<Queen>(PieceColor::BLACK, 3, 0);
		m_pieces[28] = std::make_shared<King>(PieceColor::BLACK, 4, 0);
		m_pieces[29] = std::make_shared<Bishop>(PieceColor::BLACK, 5, 0);
		m_pieces[30] = std::make_shared<Knight>(PieceColor::BLACK, 6, 0);
		m_pieces[31] = std::make_shared<Rook>(PieceColor::BLACK, 7, 0);

		for (auto &piece : m_pieces)
		{
			m_cases[piece->get_x()][piece->get_y()].get()->set_piece(piece);
		}
	}

}  // namespace rchess
