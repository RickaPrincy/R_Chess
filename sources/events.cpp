#include <algorithm>

#include "board.hpp"

using namespace sdlk;

auto board::handle_square_click(int x, int y) -> void
{
	auto clicked_square = this->get_square(x, y);
	auto current_selected_piece = this->get_selected_piece();

	auto raw_clicked_piece = clicked_square->get_piece();
	auto it_clicked_piece = std::find_if(this->m_pieces.begin(),
		this->m_pieces.end(),
		[&](std::shared_ptr<piece> piece)
		{
			if (raw_clicked_piece == nullptr)
			{
				return false;
			}

			return piece->get_is_on_board() && piece->get_x() == raw_clicked_piece->get_x() &&
				   raw_clicked_piece->get_y() == piece->get_y();
		});

	auto clicked_piece = it_clicked_piece == this->m_pieces.end() ? nullptr : *it_clicked_piece;

	// If no piece is selected and no piece on clicked square -> do nothing
	if (current_selected_piece == nullptr && clicked_piece == nullptr)
	{
		return;
	}

	// If clicked square is invalid move destination
	if (!clicked_square->get_is_valid())
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
			// //TODO: reset squares valid
		}
		return;
	}

	// If clicked square is valid for movement
	if (current_selected_piece != nullptr)
	{
		// Move or capture
		this->move_selected_piece_position(clicked_square);
	}
}

auto board::move_selected_piece_position(std::shared_ptr<square> target_square) -> void
{
	auto target_piece = target_square->get_piece();
	if (target_piece != nullptr)
	{
		target_piece->set_is_on_board(false);
	}

	// Remove piece from old position
	this->get_square(m_selected_piece->get_x(), m_selected_piece->get_y())->set_piece(nullptr);

	// Place selected piece on the target square
	target_square->set_piece(m_selected_piece.get());

	// Update piece position
	m_selected_piece->set_position(target_square->get_x(), target_square->get_y());

	this->toggle_turn();
	this->set_selected_piece(nullptr);
	this->calc_square_attackers();
}
