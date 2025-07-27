#include "square.hpp"

#include <algorithm>
#include <sdlk/core/quad.hpp>
#include <vector>

#include "constant.hpp"

using namespace constant;
using namespace sdlk;

static auto calc_position(int x, int y) -> std::vector<point>;

static SDL_Color color_valid_without_piece = { 255, 255, 0, 255 };
static SDL_Color color_valid_with_piece = { 255, 0, 0, 255 };
static SDL_Color color_valid_with_checked = { 128, 0, 128, 255 };

square::square(int x, int y)
	: colored_shape(std::move(polygon(quad::make(square_size, square_size))),
		  { 255, 255, 0, 255 },
		  std::move(quad::indices()),
		  false),
	  m_x(std::move(x)),
	  m_y(std::move(y))
{
	this->update_ui();
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
	this->update_ui();
}

auto square::update_ui() -> void
{
	auto has_piece = this->has_piece();
	glm::vec2 normal_translation = { square_size * this->m_x + border_size, square_size * this->m_y + border_size };

	if (has_piece)
	{
		this->scale(1.0);

		this->translate(normal_translation);

		this->set_color(
			this->m_piece->get_type() == piece_type::king ? color_valid_with_checked : color_valid_with_piece);
	}
	else
	{
		float scale_factor = 0.4f;
		this->scale(scale_factor);

		float offset = (1.0f - scale_factor) * 0.5f * square_size;
		this->translate(normal_translation + glm::vec2{ offset, offset });

		this->set_color(color_valid_without_piece);
	}
}

auto square::render(GLuint *program) -> void
{
	if (!this->get_is_valid())
	{
		return;
	}

	colored_shape::render(program);
}
