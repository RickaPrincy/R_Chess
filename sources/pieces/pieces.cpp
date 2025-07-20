#include "pieces.hpp"

#include "../board.hpp"
#include "../constant.hpp"

using namespace sdlk;
using namespace constant;

piece::piece(piece_type type, piece_color color, int x, int y, std::shared_ptr<texture> texture, std::vector<point> uv)
	: textured_shape(std::move(polygon(std::move(quad::make(piece_size, piece_size)))),
		  std::move(uv),
		  std::move(texture)),
	  m_type(std::move(type)),
	  m_color(std::move(color))
{
	this->set_position(std::move(x), std::move(y));
}

// unified function for exploring all possible moves (for both bishop and rook and queen)
auto piece::explore_direction(int dx, int dy, board *board) -> void
{
	int current_x = this->get_x() + dx;
	int current_y = this->get_y() + dy;

	while (is_valid_position(current_x, current_y))
	{
		auto squares = board->get_squares();
		auto &current_square = squares[current_x][current_y];

		current_square->add_piece_attacker(this);
		if (current_square->has_piece())
		{
			break;
		}
		current_x += dx;
		current_y += dy;
	}
}

// unified function for exploring all possible moves (for both king and knight)
auto piece::explore_moves(const std::vector<std::array<int, 2>> &move_patterns, board *board) -> void
{
	auto squares = board->get_squares();
	for (const auto &move : move_patterns)
	{
		int new_x = this->get_x() + move[0];
		int new_y = this->get_y() + move[1];

		if (is_valid_position(new_x, new_y))
		{
			auto &target_square = squares[new_x][new_y];
			target_square->add_piece_attacker(this);
		}
	}
}

auto piece::get_x() -> int
{
	return this->m_x;
}

auto piece::get_y() -> int
{
	return this->m_y;
}

auto piece::get_type() -> piece_type
{
	return this->m_type;
}

auto piece::get_color() -> piece_color
{
	return this->m_color;
}

auto piece::get_is_selected() -> bool
{
	return this->m_is_selected;
}

auto piece::set_is_on_board(bool is_on_board) -> void
{
	this->m_is_on_board = std::move(is_on_board);
}

auto piece::set_is_selected(bool is_selected) -> void
{
	this->m_is_selected = std::move(is_selected);
}

auto piece::set_position(int x, int y) -> void
{
	this->m_x = x;
	this->m_y = y;
	this->translate(
		{ x * square_size + border_size + padding_size / 2, y * square_size + border_size + padding_size / 2 });
}

auto piece::get_is_on_board() -> bool
{
	return this->m_is_on_board;
}

auto piece::is_valid_position(const int &x, const int &y) -> bool
{
	return x >= 0 && x < row_count && y >= 0 && y < column_count;
}

auto piece::calc_uv(piece_type type, piece_color color) -> std::vector<sdlk::point>
{
	auto start_x = static_cast<float>(type) * piece_size;
	auto start_y = static_cast<float>(color) * piece_size;

	return {
		{ start_x, start_y },
		{ start_x + piece_size, start_y },
		{ start_x + piece_size, start_y + piece_size },
		{ start_x, start_y + piece_size },
	};
}
