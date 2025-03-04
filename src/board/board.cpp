#include "board.hpp"

#include <algorithm>
#include <sdlk/core/events/types.hpp>

#include "../config/config.hpp"
#include "../events/events.hpp"
#include "../pieces/pieces.hpp"

namespace rchess
{
	static sdlk::EventListener *p_main_event_listener = nullptr;

	Board::Board() : sdlk::Observer()
	{
		this->setup_all_pieces();
		this->p_event_listener = p_main_event_listener;
		this->add_event_listener(sdlk::EventType::MOUSE_BUTTON_DOWN,
			[&](const SDL_Event &event)
			{
				auto case_position = get_case_position_from_mouse_position(event.motion);
				if (case_position.get_x() == -1)
					return;

				rchess::handle_case_click(this, case_position.get_x(), case_position.get_y());
			});
	}

	void Board::init_new_game()
	{
		std::for_each(m_pieces.begin(), m_pieces.end(), [](const auto piece) { piece->init_position(); });
	}

	void Board::setup_all_pieces()
	{
		// whites
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
		m_pieces.push_back(std::make_shared<Pawn>("pawnBlackA7", PieceColor::BLACK, 0, 1));
		m_pieces.push_back(std::make_shared<Pawn>("pawnBlackB7", PieceColor::BLACK, 1, 1));
		m_pieces.push_back(std::make_shared<Pawn>("pawnBlackC7", PieceColor::BLACK, 2, 1));
		m_pieces.push_back(std::make_shared<Pawn>("pawnBlackD7", PieceColor::BLACK, 3, 1));
		m_pieces.push_back(std::make_shared<Pawn>("pawnBlackE7", PieceColor::BLACK, 4, 1));
		m_pieces.push_back(std::make_shared<Pawn>("pawnBlackF7", PieceColor::BLACK, 5, 1));
		m_pieces.push_back(std::make_shared<Pawn>("pawnBlackG7", PieceColor::BLACK, 6, 1));
		m_pieces.push_back(std::make_shared<Pawn>("pawnBlackH7", PieceColor::BLACK, 7, 1));
		m_pieces.push_back(std::make_shared<Rook>("rookBlackA8", PieceColor::BLACK, 0, 0));
		m_pieces.push_back(std::make_shared<Knight>("knightBlackB8", PieceColor::BLACK, 1, 0));
		m_pieces.push_back(std::make_shared<Bishop>("bishopBlackC8", PieceColor::BLACK, 2, 0));
		m_pieces.push_back(std::make_shared<Queen>("bishopBlackD8", PieceColor::BLACK, 3, 0));
		m_pieces.push_back(std::make_shared<King>("kingBlackE8", PieceColor::BLACK, 4, 0));
		m_pieces.push_back(std::make_shared<Bishop>("bishopBlackF8", PieceColor::BLACK, 5, 0));
		m_pieces.push_back(std::make_shared<Knight>("kingBlackG8", PieceColor::BLACK, 6, 0));
		m_pieces.push_back(std::make_shared<Rook>("rookBlackH8", PieceColor::BLACK, 7, 0));
	}

	sdlk::Position Board::get_case_position_from_mouse_position(const SDL_MouseMotionEvent &event)
	{
		if (!config::is_on_board(event))
		{
			return sdlk::Position(-1, -1);
		}

		// to know the x and y case[x][y] clicked
		int x_case = (event.x - config::BORDER_SIZE) / config::CASE_SIZE;
		int y_case = (event.y - config::BORDER_SIZE) / config::CASE_SIZE;
		return sdlk::Position(x_case, y_case);
	}

	void Board::setup(sdlk::EventListener *event_listener)
	{
		p_main_event_listener = event_listener;
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

	void Board::toggle_turn()
	{
		auto last_turn = this->get_turn();
		this->set_turn(last_turn == rchess::PieceColor::BLACK ? rchess::PieceColor::WHITE : rchess::PieceColor::BLACK);
	}

	bool Board::has_piece_on_position(int x, int y)
	{
		return this->get_piece_on_position(x, y) != nullptr;
	}

	Piece *Board::get_piece_on_position(int x, int y)
	{
		const auto pieces = this->get_pieces();
		auto piece_on_position = std::find_if(pieces.begin(),
			pieces.end(),
			[&](const std::shared_ptr<Piece> piece)
			{ return piece->get_x() == x && piece->get_y() == y && piece->get_is_on_board(); });

		if (piece_on_position == pieces.end())
		{
			return nullptr;
		}

		return piece_on_position->get();
	}

	bool Board::is_empty_case(int x, int y)
	{
		return !this->has_piece_on_position(x, y);
	}

	void Board::calc_valid_case()
	{
		auto selected_piece = this->get_selected_piece();
		if (selected_piece == nullptr)
		{
			return;
		}
		selected_piece->calc_possible_moves(*this);
	}

	void Board::append_or_update_case_valid(Piece *piece, int x, int y)
	{
		auto valid_cases = this->get_valid_cases();
		auto select_valid_case = std::find_if(valid_cases.begin(),
			valid_cases.end(),
			[&](ValidCase &valid_case) { return valid_case.get_x() == x && valid_case.get_y() == y; });

		if (select_valid_case == valid_cases.end())
		{
			ValidCase new_valid_case(x, y);
			new_valid_case.append_piece_attack(piece);
			this->m_valid_cases.push_back(new_valid_case);
		}
		else
		{
			select_valid_case->append_piece_attack(piece);
		}
	}
}  // namespace rchess
