#pragma once

#include <glad/glad.h>

#include <sdlk/core/renderable.hpp>
#include <sdlk/core/shape.hpp>
#include <vector>

#include "pieces/pieces.hpp"

class square : public sdlk::colored_shape
{
private:
	int m_x{ 0 }, m_y{ 0 };
	bool m_is_valid{ false };

	piece *m_piece{ nullptr };
	std::vector<piece *> m_white_attackers{}, m_black_attackers{};

public:
	square(int x, int y);

	auto reset() -> void;
	auto has_piece() -> bool;
	auto set_piece(piece *piece) -> void;
	auto is_attacker(piece *piece) -> bool;
	auto add_piece_attacker(piece *piece) -> void;

	virtual auto render(GLuint *program) -> void override;
};
