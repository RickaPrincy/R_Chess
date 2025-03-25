#include "board.hpp"

#include <algorithm>
#include <sdlk/core/events/event_listener.hpp>
#include <sdlk/core/events/types.hpp>

#include "../case/case.hpp"
#include "../constant.hpp"
#include "../pieces/pieces.hpp"

namespace rchess
{
	using namespace constant;

	Board::Board(sdlk::EventListener *event_listener) : sdlk::Observer()
	{
		this->instanciate_cases_and_pieces();
		this->re_calc_move_valid();
		this->p_event_listener = event_listener;
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

	std::array<std::array<std::shared_ptr<Case>, ROW_COUNT>, COLUMN_COUNT> Board::get_cases()
	{
		return this->m_cases;
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
		if (piece != nullptr)
		{
			piece->set_is_selected(true);
			piece->do_re_render();
		}
		this->update_valid_moves();
	}

	void Board::re_calc_move_valid()
	{
		for (int x = 0; x < ROW_COUNT; x++)
		{
			for (int y = 0; y < COLUMN_COUNT; y++)
			{
				m_cases[x][y]->reset_attackers();
				m_cases[x][y]->set_is_valid(false);
			}
		}

		std::for_each(this->m_pieces.begin(),
			this->m_pieces.end(),
			[&](std::shared_ptr<Piece> &piece) { piece->calc_possible_moves(this); });
	}

	void Board::update_valid_moves()
	{
		for (int x = 0; x < ROW_COUNT; x++)
		{
			for (int y = 0; y < COLUMN_COUNT; y++)
			{
				const auto &current_case = m_cases[x][y];
				if (m_selected_piece == nullptr)
				{
					current_case->set_is_valid(false);
					continue;
				}

				const auto piece_on_case = current_case->get_piece();
				if (piece_on_case != nullptr && piece_on_case->get_color() == m_selected_piece->get_color())
				{
					current_case->set_is_valid(false);
					continue;
				}
				const auto is_attacker = current_case->is_attacker(m_selected_piece);
				// TODO: check (+)
				current_case->set_is_valid(is_attacker);
			}
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
}  // namespace rchess
