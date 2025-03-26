#include <memory>

#include "board.hpp"

namespace rchess
{
	void Board::update_current_move(std::shared_ptr<Case> target_case)
	{
		Move new_move(this->m_selected_piece,
			sdlk::Position(this->m_selected_piece->get_x(), this->m_selected_piece->get_y()),
			sdlk::Position(target_case->get_x(), target_case->get_y()));

		auto new_move_node = std::make_shared<MoveNode>(this->m_current_move, new_move);

		if (this->m_current_move != nullptr)
		{
			this->m_current_move->add_child(new_move_node);
		}

		this->m_current_move = new_move_node;
	}
}  // namespace rchess
