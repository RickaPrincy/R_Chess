#include <memory>

#include "board.hpp"

namespace rchess
{
	void Board::handle_case_click(std::shared_ptr<Case> click_case)
	{
		auto current_selected_piece = this->get_selected_piece();
		auto clicked_piece = click_case->get_piece();

		// If no piece is selected and no piece on clicked square -> do nothing
		if (current_selected_piece == nullptr && clicked_piece == nullptr)
		{
			return;
		}

		// If clicked square is invalid move destination
		if (!click_case->get_is_valid())
		{
			// Select piece if clicking on a piece of the current turn
			if (clicked_piece != nullptr && clicked_piece->get_color() == this->get_turn())
			{
				this->set_selected_piece(clicked_piece);
			}
			else
			{
				// Clear current selection
				// this->set_selected_piece(nullptr);
				// //TODO: reset cases valid
			}
			return;
		}

		// If clicked case is valid for movement
		if (current_selected_piece != nullptr)
		{
			// Move or capture
			this->move_selected_piece_position(click_case);
		}
	}

	void Board::move_selected_piece_position(std::shared_ptr<Case> target_case)
	{
		auto target_piece = target_case->get_piece();
		if (target_piece != nullptr)
		{
			target_piece->set_is_on_board(false);
			target_piece->do_re_render();
		}

		// Remove piece from old position
		m_cases[m_selected_piece->get_x()][m_selected_piece->get_y()]->set_piece(nullptr);

		// Place selected piece on the target case
		target_case->set_piece(m_selected_piece);

		// Append move in move_node_tree
		this->update_current_move(target_case);

		// Update piece position and re-render
		m_selected_piece->set_position(sdlk::Position(target_case->get_x(), target_case->get_y()));
		m_selected_piece->do_re_render();

		toggle_turn();
		set_selected_piece(nullptr);
		re_calc_move_valid();
	}
}  // namespace rchess
