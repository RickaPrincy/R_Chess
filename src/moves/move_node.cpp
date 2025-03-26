#include "./move_node.hpp"

#include <memory>

namespace rchess
{
	MoveNode::MoveNode(std::shared_ptr<MoveNode> parent, Move move) : m_parent(parent), m_move(move)
	{
	}

	void MoveNode::add_child(std::shared_ptr<MoveNode> new_child)
	{
		this->m_childs.push_back(new_child);
	}
}  // namespace rchess
