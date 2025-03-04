#pragma once

#include <SDL2/SDL_events.h>

#include <memory>
#include <sdlk/core/events/observer.hpp>
#include <sdlk/core/preprocessor/getter_setter.hpp>
#include <sdlk/core/properties/position.hpp>

#include "../case/case.hpp"
#include "../pieces/pieces.hpp"

namespace rchess
{
	class Board : public sdlk::Observer
	{
	private:
		PieceColor m_turn{ PieceColor::WHITE };
		std::shared_ptr<Piece> m_selected_piece = nullptr;
		std::vector<std::shared_ptr<Piece>> m_pieces{};
		std::vector<ValidCase> m_valid_cases{};

		void setup_all_pieces();

	public:
		Board();
		GETTER(PieceColor, turn);
		SETTER(PieceColor, turn);
		GETTER(std::vector<ValidCase>, valid_cases);
		GETTER(std::vector<std::shared_ptr<Piece>>, pieces);
		GETTER(std::shared_ptr<Piece>, selected_piece);

		void calc_valid_case();
		void init_new_game();
		void toggle_turn();
		void append_or_update_case_valid(Piece *piece, int x, int y);
		void set_selected_piece(std::shared_ptr<Piece> piece);
		bool has_piece_on_position(int x, int y);
		bool is_empty_case(int x, int y);
		Piece *get_piece_on_position(int x, int y);

		static sdlk::Position get_case_position_from_mouse_position(const SDL_MouseMotionEvent &mouse_motion);
		static void setup(sdlk::EventListener *event_listener);
		friend class RChessApp;
	};
}  // namespace rchess
