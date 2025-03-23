#pragma once

#include <SDL2/SDL_events.h>

#include <array>
#include <memory>
#include <sdlk/core/events/observer.hpp>
#include <sdlk/core/preprocessor/getter_setter.hpp>
#include <sdlk/core/properties/position.hpp>

#include "../case/case.hpp"
#include "../constant.hpp"
#include "../pieces/pieces.hpp"

namespace rchess
{
	using namespace constant;
	class Board : public sdlk::Observer
	{
	private:
		PieceColor m_turn{ PieceColor::WHITE };
		std::array<std::array<std::shared_ptr<Case>, ROW_COUNT>, COLUMN_COUNT> m_cases{};
		std::array<std::shared_ptr<Piece>, PIECES_COUNT> m_pieces{};
		std::shared_ptr<Piece> m_selected_piece = nullptr;

		SETTER(PieceColor, turn);

		void toggle_turn();
		void setup_pieces_and_cases();
		void set_selected_piece(std::shared_ptr<Piece> piece);
		void handle_case_click(std::shared_ptr<Case> click_case);
		void move_selected_piece_position(std::shared_ptr<Case> selected_case);
		void re_calc_move_valid();

	public:
		Board();
		GETTER(PieceColor, turn);
		GETTER(std::shared_ptr<Piece>, selected_piece);
		std::array<std::shared_ptr<Piece>, PIECES_COUNT> get_pieces();
		std::array<std::array<std::shared_ptr<Case>, ROW_COUNT>, COLUMN_COUNT> get_cases();

		static sdlk::Position get_case_position_from_mouse_position(const SDL_MouseMotionEvent &mouse_motion);
		static void setup_observer(sdlk::EventListener *event_listener);
		friend class RChessApp;
	};
}  // namespace rchess
