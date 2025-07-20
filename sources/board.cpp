#include "board.hpp"

#include <SDL2/SDL_events.h>

#include <algorithm>
#include <sdlk/core/types.hpp>

using namespace sdlk;

static point get_square_position_from_mouse_position(const SDL_MouseMotionEvent &event);

board::board(app *rchess) : observer(rchess->get_event_listener())
{
	this->m_piece_texture = texture::from_file("./resources/images/pieces.png");
	this->m_background = std::make_shared<image_shape>("./resources/images/background.jpg", window_size, window_size);
	this->instanciate_squares_and_pieces();
	this->calc_square_attackers();

	rchess->add_renderable(m_background.get());
	for (auto &piece : this->m_pieces)
	{
		rchess->add_renderable(piece.get());
	}

	for (int x = 0; x < row_count; x++)
	{
		for (int y = 0; y < column_count; y++)
		{
			rchess->add_renderable(this->get_square(x, y).get());
		}
	}

	this->add_event_listener(event_type::MOUSE_BUTTON_DOWN,
		[&](const SDL_Event &event)
		{
			auto square_position = get_square_position_from_mouse_position(event.motion);

			if (square_position[0] == -1)
			{
				return;
			}

			this->handle_square_click((int)square_position[0], (int)square_position[1]);
		});
}

auto board::update_selected_piece_possible_moves() -> void
{
	// update ui of the selected piece
	for (int x = 0; x < row_count; x++)
	{
		for (int y = 0; y < column_count; y++)
		{
			const auto &current_square = this->m_squares[x][y];
			if (this->m_selected_piece == nullptr)
			{
				current_square->set_is_valid(false);
				continue;
			}

			const auto piece_on_square = current_square->get_piece();
			if (piece_on_square != nullptr && piece_on_square->get_color() == m_selected_piece->get_color())
			{
				current_square->set_is_valid(false);
				continue;
			}
			current_square->set_is_valid(current_square->is_attacker(this->m_selected_piece.get()));
		}
	}
}

auto board::set_selected_piece(std::shared_ptr<piece> piece) -> void
{
	if (this->m_selected_piece != nullptr)
	{
		this->m_selected_piece->set_is_selected(false);
	}

	this->m_selected_piece = piece;
	if (piece != nullptr)
	{
		piece->set_is_selected(true);
	}

	this->update_selected_piece_possible_moves();
}

auto board::toggle_turn() -> void
{
	auto last_turn = this->get_turn();
	this->m_turn = last_turn == piece_color::black ? piece_color::white : piece_color::black;
}

auto board::get_turn() const -> piece_color
{
	return this->m_turn;
}

auto board::get_selected_piece() const -> std::shared_ptr<piece>
{
	return this->m_selected_piece;
}

auto board::get_pieces() const -> std::array<std::shared_ptr<piece>, pieces_count>
{
	return this->m_pieces;
}

auto board::get_squares() const -> std::array<std::array<std::shared_ptr<square>, column_count>, row_count>
{
	return this->m_squares;
}

auto board::instanciate_squares_and_pieces() -> void
{
	for (int x = 0; x < row_count; x++)
	{
		for (int y = 0; y < column_count; y++)
		{
			m_squares[x][y] = std::make_shared<square>(x, y);
		}
	}

	m_pieces[0] = std::make_shared<pawn>(piece_color::white, 0, 6, this->m_piece_texture);
	m_pieces[1] = std::make_shared<pawn>(piece_color::white, 1, 6, this->m_piece_texture);
	m_pieces[2] = std::make_shared<pawn>(piece_color::white, 2, 6, this->m_piece_texture);
	m_pieces[3] = std::make_shared<pawn>(piece_color::white, 3, 6, this->m_piece_texture);
	m_pieces[4] = std::make_shared<pawn>(piece_color::white, 4, 6, this->m_piece_texture);
	m_pieces[5] = std::make_shared<pawn>(piece_color::white, 5, 6, this->m_piece_texture);
	m_pieces[6] = std::make_shared<pawn>(piece_color::white, 6, 6, this->m_piece_texture);
	m_pieces[7] = std::make_shared<pawn>(piece_color::white, 7, 6, this->m_piece_texture);
	m_pieces[8] = std::make_shared<rook>(piece_color::white, 0, 7, this->m_piece_texture);
	m_pieces[9] = std::make_shared<knight>(piece_color::white, 1, 7, this->m_piece_texture);
	m_pieces[10] = std::make_shared<bishop>(piece_color::white, 2, 7, this->m_piece_texture);
	m_pieces[11] = std::make_shared<queen>(piece_color::white, 3, 7, this->m_piece_texture);
	m_pieces[12] = std::make_shared<king>(piece_color::white, 4, 7, this->m_piece_texture);
	m_pieces[13] = std::make_shared<bishop>(piece_color::white, 5, 7, this->m_piece_texture);
	m_pieces[14] = std::make_shared<knight>(piece_color::white, 6, 7, this->m_piece_texture);
	m_pieces[15] = std::make_shared<rook>(piece_color::white, 7, 7, this->m_piece_texture);

	// blacks
	m_pieces[16] = std::make_shared<pawn>(piece_color::black, 0, 1, this->m_piece_texture);
	m_pieces[17] = std::make_shared<pawn>(piece_color::black, 1, 1, this->m_piece_texture);
	m_pieces[18] = std::make_shared<pawn>(piece_color::black, 2, 1, this->m_piece_texture);
	m_pieces[19] = std::make_shared<pawn>(piece_color::black, 3, 1, this->m_piece_texture);
	m_pieces[20] = std::make_shared<pawn>(piece_color::black, 4, 1, this->m_piece_texture);
	m_pieces[21] = std::make_shared<pawn>(piece_color::black, 5, 1, this->m_piece_texture);
	m_pieces[22] = std::make_shared<pawn>(piece_color::black, 6, 1, this->m_piece_texture);
	m_pieces[23] = std::make_shared<pawn>(piece_color::black, 7, 1, this->m_piece_texture);
	m_pieces[24] = std::make_shared<rook>(piece_color::black, 0, 0, this->m_piece_texture);
	m_pieces[25] = std::make_shared<knight>(piece_color::black, 1, 0, this->m_piece_texture);
	m_pieces[26] = std::make_shared<bishop>(piece_color::black, 2, 0, this->m_piece_texture);
	m_pieces[27] = std::make_shared<queen>(piece_color::black, 3, 0, this->m_piece_texture);
	m_pieces[28] = std::make_shared<king>(piece_color::black, 4, 0, this->m_piece_texture);
	m_pieces[29] = std::make_shared<bishop>(piece_color::black, 5, 0, this->m_piece_texture);
	m_pieces[30] = std::make_shared<knight>(piece_color::black, 6, 0, this->m_piece_texture);
	m_pieces[31] = std::make_shared<rook>(piece_color::black, 7, 0, this->m_piece_texture);

	for (auto &piece : m_pieces)
	{
		this->get_square(piece->get_x(), piece->get_y())->set_piece(piece.get());
	}
}

auto board::get_square(int x, int y) const -> std::shared_ptr<square>
{
	return this->m_squares[x][y];
}

auto board::calc_square_attackers() -> void
{
	for (int x = 0; x < row_count; x++)
	{
		for (int y = 0; y < column_count; y++)
		{
			this->m_squares[x][y]->reset();
			this->m_squares[x][y]->set_is_valid(false);
		}
	}

	std::for_each(this->m_pieces.begin(),
		this->m_pieces.end(),
		[&](std::shared_ptr<piece> piece) { piece->calc_possible_moves(this); });
}

static auto get_square_position_from_mouse_position(const SDL_MouseMotionEvent &event) -> point
{
	auto is_on_board = event.x < max_coord_on_board && event.y < max_coord_on_board && event.x > min_coord_on_board &&
					   event.y > min_coord_on_board;

	if (!is_on_board)
	{
		return { -1.0f, -1.0f };
	}

	// to know the x and y square[x][y] clicked
	int x_square = (event.x - border_size) / square_size;
	int y_square = (event.y - border_size) / square_size;

	return { (float)x_square, (float)y_square };
}
