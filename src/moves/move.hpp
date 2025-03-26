#pragma once

#include <memory>
#include <sdlk/core/preprocessor/getter_setter.hpp>

#include "../pieces/pieces.hpp"
namespace rchess
{
	class Move
	{
	private:
		std::shared_ptr<Piece> m_piece;
		sdlk::Position m_src{}, m_dest{};

	public:
		GETTER(std::shared_ptr<Piece>, piece)
		GETTER(sdlk::Position, src)
		GETTER(sdlk::Position, dest)

		Move(std::shared_ptr<Piece> piece, sdlk::Position src, sdlk::Position dest);

		bool operator==(const Move& other) const;
		bool operator!=(const Move& other) const;
	};
}  // namespace rchess
