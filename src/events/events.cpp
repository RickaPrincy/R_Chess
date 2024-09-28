#include "./events.hpp"

#include <algorithm>

namespace rchess
{
	void handle_case_click(int x, int y, Board *board)
	{
		reset_selected_piece(board);
		const auto pieces = board->get_pieces();
		auto new_selected_piece = std::find_if(pieces.begin(),
			pieces.end(),
			[&](const std::shared_ptr<Piece> piece) { return piece->get_x() == x && piece->get_y() == y; });

		if (new_selected_piece == pieces.end())
		{
			return;
		}
		board->set_selected_piece(*new_selected_piece);
		new_selected_piece->get()->do_re_render();
	}

	void reset_selected_piece(Board *board)
	{
		board->set_selected_piece(nullptr);
	}

}  // namespace rchess
