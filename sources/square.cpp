#include "square.hpp"

#include <algorithm>
#include <sdlk/core/quad.hpp>
#include <vector>

#include "constant.hpp"

using namespace constant;
using namespace sdlk;

static auto calc_position(int x, int y) -> std::vector<point>;

square::square(int x, int y)
	: colored_shape(std::move(polygon(quad::make(square_size, square_size))),
		  { 255, 255, 0, 255 },
		  std::move(quad::indices())),
	  m_x(std::move(x)),
	  m_y(std::move(y))
{
	this->translate({
		square_size * this->m_x + border_size,
		square_size * this->m_y + border_size,
	});
}

auto square::reset() -> void
{
	this->m_is_valid = false;
	this->m_black_attackers.clear();
	this->m_white_attackers.clear();
}

auto square::is_attacker(piece *candidate_piece) -> bool
{
	std::vector<piece *> attackers{ candidate_piece->get_color() == piece_color::black ? this->m_black_attackers
																					   : this->m_white_attackers };

	return std::find_if(attackers.begin(),
			   attackers.end(),
			   [&candidate_piece](piece *subject_piece)
			   {
				   return candidate_piece->get_x() == subject_piece->get_x() &&
						  candidate_piece->get_y() == subject_piece->get_y();
			   }) != attackers.end();
}

auto square::has_piece() -> bool
{
	return this->m_piece != nullptr;
}

auto square::add_piece_attacker(piece *piece_attacker) -> void
{
	if (piece_attacker->get_color() == piece_color::black)
	{
		this->m_black_attackers.push_back(piece_attacker);
		return;
	}

	this->m_white_attackers.push_back(piece_attacker);
}

auto square::set_piece(piece *piece) -> void
{
	this->m_piece = piece;
}

auto square::get_piece() -> piece *
{
	return this->m_piece;
}

auto square::get_is_valid() -> bool
{
	return this->m_is_valid;
}

auto square::get_x() -> int
{
	return this->m_x;
}

auto square::get_y() -> int
{
	return this->m_y;
}

auto square::set_is_valid(bool is_valid) -> void
{
	this->m_is_valid = std::move(is_valid);
}

auto square::render(GLuint *program) -> void
{
	if (!this->get_is_valid())
	{
		return;
	}

	colored_shape::render(program);
}
