#include "board.hpp"

#include <sdlk/core/events/types.hpp>

#include "../case/case.hpp"
#include "../constant.hpp"
#include "../pieces/pieces.hpp"

namespace rchess
{
	using namespace constant;
	static sdlk::EventListener *p_main_event_listener = nullptr;

	Board::Board() : sdlk::Observer()
	{
		this->setup_pieces_and_cases();
		this->p_event_listener = p_main_event_listener;
		this->add_event_listener(sdlk::EventType::MOUSE_BUTTON_DOWN,
			[&](const SDL_Event &event)
			{
				auto case_position = Board::get_case_position_from_mouse_position(event.motion);
				if (case_position.get_x() == -1)
					return;
				this->handle_case_click(this->m_cases[case_position.get_x()][case_position.get_y()]);
			});
	}

	std::array<std::shared_ptr<Piece>, 32> Board::get_pieces()
	{
		return this->m_pieces;
	}

	void Board::toggle_turn()
	{
		auto last_turn = this->get_turn();
		this->set_turn(last_turn == rchess::PieceColor::BLACK ? rchess::PieceColor::WHITE : rchess::PieceColor::BLACK);
	}

	void Board::set_selected_piece(std::shared_ptr<Piece> piece)
	{
		if (this->m_selected_piece != nullptr)
		{
			this->m_selected_piece->set_is_selected(false);
			this->m_selected_piece->do_re_render();
		}

		this->m_selected_piece = piece;
		if (m_selected_piece != nullptr)
		{
			piece->set_is_selected(true);
			piece->do_re_render();
		}
	}

	void Board::setup_pieces_and_cases()
	{
		for (int x = 0; x < 8; x++)
		{
			for (int y = 0; y < 8; y++)
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

	// STATIC FUNCTION MEMBER
	sdlk::Position Board::get_case_position_from_mouse_position(const SDL_MouseMotionEvent &event)
	{
		const auto is_on_board = event.x < MAX_COORD_ON_BOARD && event.y < MAX_COORD_ON_BOARD &&
								 event.x > MIN_COORD_ON_BOARD && event.y > MIN_COORD_ON_BOARD;

		if (!is_on_board)
		{
			return sdlk::Position(-1, -1);
		}

		// to know the x and y case[x][y] clicked
		int x_case = (event.x - UI_BORDER_SIZE) / UI_CASE_SIZE;
		int y_case = (event.y - UI_BORDER_SIZE) / UI_CASE_SIZE;
		return sdlk::Position(x_case, y_case);
	}

	void Board::setup_observer(sdlk::EventListener *event_listener)
	{
		p_main_event_listener = event_listener;
	}
}  // namespace rchess
