#pragma once

#include <memory>
#include <sdlk/core/preprocessor/getter_setter.hpp>
#include <vector>

#include "move.hpp"

namespace rchess
{
	class MoveNode
	{
	private:
		Move m_move;
		std::vector<std::shared_ptr<MoveNode>> m_childs{};
		std::shared_ptr<MoveNode> m_parent;

	public:
		MoveNode(std::shared_ptr<MoveNode> m_parent, Move move);
		GETTER(std::shared_ptr<MoveNode>, parent)
		GETTER(std::vector<std::shared_ptr<MoveNode>>, childs)

		void add_child(std::shared_ptr<MoveNode> new_child);
	};
}  // namespace rchess
