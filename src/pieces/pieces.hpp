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
		std::string m_name{};
		PieceType m_type{ PieceType::PAWN };
		PieceColor m_color{ PieceColor::BLACK };
		sdlk::Position m_initial_position;

		virtual void render(SDL_Renderer *renderer) override;

	public:
		GETTER(PieceType, type);
		GETTER(PieceColor, color);
		SETTER(bool, is_selected);

		Piece(std::string name, PieceType type, PieceColor color, int x, int y);
		virtual void calc_possible_moves() = 0;
		void init_position();

		static void setup(sdlk::Image *background, SDL_Renderer *renderer, const std::string &path);
		static void clean_up();
	};

	class Rook : public Piece
	{
	public:
		virtual void calc_possible_moves() override;
		Rook(std::string name, PieceColor color, int x, int y);
	};

	class Knight : public Piece
	{
	public:
		virtual void calc_possible_moves() override;
		Knight(std::string name, PieceColor color, int x, int y);
	};

	class Bishop : public Piece
	{
	public:
		virtual void calc_possible_moves() override;
		Bishop(std::string name, PieceColor color, int x, int y);
	};

	class Queen : public Piece
	{
	public:
		virtual void calc_possible_moves() override;
		Queen(std::string name, PieceColor color, int x, int y);
	};

	class King : public Piece
	{
	public:
		virtual void calc_possible_moves() override;
		King(std::string name, PieceColor color, int x, int y);
	};

	class Pawn : public Piece
	{
	public:
		virtual void calc_possible_moves() override;
		Pawn(std::string name, PieceColor color, int x, int y);
	};
}  // namespace rchess
