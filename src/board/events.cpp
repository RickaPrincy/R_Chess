#include "board.hpp"

namespace rchess
{
	void Board::handle_case_click(std::shared_ptr<Case> click_case)
	{
		auto current_selected_piece = this->get_selected_piece();
		auto new_selected_piece = click_case->get_piece();

		if (new_selected_piece == nullptr)
		{
			if (current_selected_piece != nullptr)
			{
				this->move_selected_piece_position(click_case);
			}
			return;
		}

		// change selected_piece if same colors
		if (this->get_turn() == new_selected_piece->get_color())
		{
			this->set_selected_piece(new_selected_piece);
		}
		// capture if piece selected exist and not same color
		else if (current_selected_piece != nullptr)
		{
			this->move_selected_piece_position(click_case);
		}
	}

	void Board::move_selected_piece_position(std::shared_ptr<Case> click_case)
	{
		if (this->m_selected_piece == nullptr)
		{
			return;
		}

		if (click_case->get_piece() != nullptr)
		{
			click_case->get_piece()->set_is_on_board(false);
			click_case->get_piece()->do_re_render();
		}

		click_case->set_piece(this->m_selected_piece);
		this->toggle_turn();
		this->m_selected_piece->do_re_render();
		this->m_selected_piece->set_position(sdlk::Position(click_case->get_x(), click_case->get_y()));
		this->set_selected_piece(nullptr);
	}
}  // namespace rchess
