#pragma once

#include <array>
#include <sdlk/core/app.hpp>
#include <sdlk/core/texture.hpp>

#include "constant.hpp"
#include "pieces/pieces.hpp"
#include "square.hpp"

using namespace constant;

class board : sdlk::observer
{
private:
	std::shared_ptr<sdlk::image_shape> m_background = nullptr;
	std::shared_ptr<sdlk::texture> m_piece_texture = nullptr;

	piece_color m_turn{ piece_color::white };
	std::shared_ptr<piece> m_selected_piece = nullptr;
	std::array<std::shared_ptr<piece>, pieces_count> m_pieces{};
	std::array<std::array<std::shared_ptr<square>, column_count>, row_count> m_squares{};

	auto toggle_turn() -> void;
	auto instanciate_cases_and_pieces() -> void;
	auto set_selected_piece(std::shared_ptr<piece> piece) -> void;

public:
	board(sdlk::app *app);

	[[nodiscard]] auto get_turn() const -> piece_color;
	[[nodiscard]] auto get_selected_piece() const -> std::shared_ptr<piece>;
	[[nodiscard]] auto get_pieces() const -> std::array<std::shared_ptr<piece>, pieces_count>;
	[[nodiscard]] auto get_squares() const -> std::array<std::array<std::shared_ptr<square>, column_count>, row_count>;
};
