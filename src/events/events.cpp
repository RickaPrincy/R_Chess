#include "./events.hpp"

#include <algorithm>

namespace rchess
{
	void handle_case_click(Board *board, int x, int y)
	{
		const auto current_selected_piece = board->get_selected_piece();
		const auto pieces = board->get_pieces();
		auto new_selected_piece = std::find_if(pieces.begin(),
			pieces.end(),
			[&](const std::shared_ptr<Piece> piece)
			{ return piece->get_x() == x && piece->get_y() == y && piece->get_is_on_board(); });

		if (new_selected_piece == pieces.end())
		{
			if (current_selected_piece != nullptr)
			{
				move_piece_position(board, current_selected_piece, x, y);
			}
			return;
		}

		// change selected_piece if same colors
		if (board->get_turn() == new_selected_piece->get()->get_color())
		{
			board->set_selected_piece(*new_selected_piece);
		}
		// capture if piece selected exist and not same color
		else if (current_selected_piece != nullptr)
		{
			do_capture(board, *new_selected_piece);
		}
	}

	void do_capture(Board *board, std::shared_ptr<Piece> captured_piece)
	{
		captured_piece->set_is_on_board(false);
		move_piece_position(board, board->get_selected_piece(), captured_piece->get_x(), captured_piece->get_y());
	}

	void reset_selected_piece(Board *board)
	{
		board->set_selected_piece(nullptr);
	}

	void move_piece_position(Board *board, std::shared_ptr<Piece> piece, int x, int y)
	{
		piece->set_position(sdlk::Position(x, y));
		piece->do_re_render();
		board->toggle_turn();
		reset_selected_piece(board);
	}
}  // namespace rchess
