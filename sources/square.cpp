#include "square.hpp"

#include <algorithm>
#include <sdlk/core/quad.hpp>
#include <vector>

#include "constant.hpp"

using namespace constant;
using namespace sdlk;

square::square(int x, int y)
	: colored_shape(std::move(polygon(quad::make(case_size, case_size))),
		  { 255, 255, 0, 255 },
		  std::move(quad::indices())),
	  m_x(std::move(x)),
	  m_y(std::move(y))
{
}

auto square::reset() -> void
{
	this->m_piece = nullptr;
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

auto square::render(GLuint *program) -> void
{
}
