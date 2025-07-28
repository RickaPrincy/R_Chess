#pragma once

#include <glad/glad.h>

#include <cstdint>
#include <sdlk/core/shape.hpp>
#include <sdlk/core/types.hpp>
#include <vector>

#include "../constant.hpp"

class board;
class square;
using namespace constant;

enum class piece_type : std::uint8_t
{
	rook,  // based on pieces graphics order
	knight,
	bishop,
	queen,
	king,
	pawn
};

enum class piece_color
{
	white = 0,	// based on pieces graphics order
	black
};

class piece : public sdlk::textured_shape
{
protected:
	int m_x{ 0 };
	int m_y{ 0 };

	bool m_is_selected{ false };
	bool m_is_on_board{ true };

	piece_type m_type{ piece_type::pawn };
	piece_color m_color{ piece_color::black };

	auto explore_direction(int dx, int dy, board *board) -> void;
	auto explore_moves(const std::vector<std::array<int, 2>> &move_patterns, board *board) -> void;

	piece(piece_type type,
		piece_color color,
		int x,
		int y,
		std::shared_ptr<sdlk::texture> texture,
		std::vector<sdlk::point> uv);

	static auto is_valid_position(const int &x, const int &y) -> bool;
	static auto calc_uv(piece_type type, piece_color color) -> std::vector<sdlk::point>;

public:
	[[nodiscard]] auto get_x() -> int;
	[[nodiscard]] auto get_y() -> int;

	[[nodiscard]] auto get_type() -> piece_type;
	[[nodiscard]] auto get_color() -> piece_color;

	[[nodiscard]] auto get_is_selected() -> bool;
	[[nodiscard]] auto get_is_on_board() -> bool;

	auto set_is_on_board(bool is_on_board) -> void;
	auto set_is_selected(bool is_selected) -> void;
	auto set_position(int x, int y) -> void;
	virtual auto calc_possible_moves(board *board) -> void = 0;
	virtual auto render(GLuint *program) -> void override;

	static auto setup() -> void;
};

class rook : public piece
{
public:
	virtual auto calc_possible_moves(board *board) -> void override;
	rook(piece_color color, int x, int y, std::shared_ptr<sdlk::texture> texture);
};

class knight : public piece
{
public:
	virtual auto calc_possible_moves(board *board) -> void override;
	knight(piece_color color, int x, int y, std::shared_ptr<sdlk::texture> texture);
};

class bishop : public piece
{
public:
	virtual auto calc_possible_moves(board *board) -> void override;
	bishop(piece_color color, int x, int y, std::shared_ptr<sdlk::texture> texture);
};

class queen : public piece
{
public:
	virtual auto calc_possible_moves(board *board) -> void override;
	queen(piece_color color, int x, int y, std::shared_ptr<sdlk::texture> texture);
};

class king : public piece
{
public:
	virtual auto calc_possible_moves(board *board) -> void override;
	king(piece_color color, int x, int y, std::shared_ptr<sdlk::texture> texture);
};

class pawn : public piece
{
private:
	short m_increment_value{ 0 };

public:
	virtual auto calc_possible_moves(board *board) -> void override;
	pawn(piece_color color, int x, int y, std::shared_ptr<sdlk::texture> texture);
};
