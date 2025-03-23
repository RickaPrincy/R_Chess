#pragma once

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>

#include <sdlk/components/image.hpp>
#include <sdlk/core/component.hpp>
#include <sdlk/core/preprocessor/getter_setter.hpp>
#include <sdlk/core/properties/position.hpp>
#include <sdlk/core/window.hpp>
#include <string>

namespace rchess
{
	class Board;
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
		GETTER(bool, is_on_board);
		SETTER(bool, is_selected);
		SETTER(bool, is_on_board);

		Piece(PieceType type, PieceColor color, int x, int y);
		virtual void calc_possible_moves(Board &board) = 0;
		static void setup(sdlk::Image *background, SDL_Renderer *renderer, const std::string &path);
		static void clean_up();
	};

	class Rook : public Piece
	{
	public:
		virtual void calc_possible_moves(Board &board) override;
		Rook(PieceColor color, int x, int y);
	};

	class Knight : public Piece
	{
	public:
		virtual void calc_possible_moves(Board &board) override;
		Knight(PieceColor color, int x, int y);
	};

	class Bishop : public Piece
	{
	public:
		virtual void calc_possible_moves(Board &board) override;
		Bishop(PieceColor color, int x, int y);
	};

	class Queen : public Piece
	{
	public:
		virtual void calc_possible_moves(Board &board) override;
		Queen(PieceColor color, int x, int y);
	};

	class King : public Piece
	{
	public:
		virtual void calc_possible_moves(Board &board) override;
		King(PieceColor color, int x, int y);
	};

	class Pawn : public Piece
	{
	private:
		short m_increment_value{ 0 };

	public:
		virtual void calc_possible_moves(Board &board) override;
		Pawn(PieceColor color, int x, int y);
	};
}  // namespace rchess
