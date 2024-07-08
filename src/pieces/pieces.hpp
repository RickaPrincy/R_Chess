#pragma once

#include <SDL2/SDL_render.h>

#include <sdlk/core/component.hpp>
#include <sdlk/core/preprocessor/getter_setter.hpp>
#include <sdlk/core/properties/position.hpp>
#include <sdlk/core/window.hpp>
#include <string>

namespace rchess
{
	enum class PieceType
	{
		ROOK = 0,  // based on pieces graphics order
		KNIGHT,
		BISHOP,
		QUEEN,
		KING,
		PAWN
	};

	enum class PieceColor
	{
		WHITE = 0,	// based on pieces graphics order
		BLACK
	};

	class Piece : public sdlk::Component
	{
	protected:
		bool m_is_selected{ false }, m_is_on_board{ true };
		PieceType m_type{ PieceType::PAWN };
		PieceColor m_color{ PieceColor::BLACK };

		virtual void render(SDL_Renderer *renderer) override;

	public:
		GETTER(PieceType, type);
		GETTER(PieceColor, color);

		Piece(PieceType type, PieceColor color, int x, int y);

		static void setup(sdlk::Window *background, const std::string &path);
		static void clean_up();
	};
}  // namespace rchess
