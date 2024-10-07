#pragma once

#include <SDL2/SDL_events.h>

#include <memory>
#include <sdlk/core/events/observer.hpp>
#include <sdlk/core/preprocessor/getter_setter.hpp>
#include <sdlk/core/properties/position.hpp>

#include "../pieces/pieces.hpp"
namespace rchess
{
	class Board : public sdlk::Observer
	{
	private:
		PieceColor m_turn{ PieceColor::WHITE };
		std::shared_ptr<Piece> m_selected_pieces = nullptr;
		std::vector<std::shared_ptr<Piece>> m_pieces{};
		void setup_all_pieces();

	public:
		Board();
		GETTER(PieceColor, turn);
		GETTER(std::vector<std::shared_ptr<Piece>>, pieces);

		void init_new_game();
		void set_selected_piece(std::shared_ptr<Piece> piece);

		static sdlk::Position get_case_position_from_mouse_position(const SDL_MouseMotionEvent &mouse_motion);
		static void setup(sdlk::EventListener *event_listener);
		friend class RChessApp;
	};
}  // namespace rchess
