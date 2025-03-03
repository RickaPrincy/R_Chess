#include "rchess.hpp"

#include <cstdlib>
#include <sdlk/components/image.hpp>
#include <sdlk/sdlk.hpp>
#include <stdexcept>

#include "board/board.hpp"
#include "config/config.hpp"
#include "pieces/pieces.hpp"

namespace rchess
{
	static void clean_resources(sdlk::Image *background)
	{
		Piece::clean_up();
		delete background;
	}

	RChessApp::RChessApp() : sdlk::App("R_Chess", sdlk::Size(config::WINDOW_SIZE))
	{
		try
		{
			p_background =
				new sdlk::Image(this->get_window(), "../graphics/background.jpg", sdlk::Size(config::WINDOW_SIZE));
			Piece::setup(p_background, this->get_window()->get_sdl_renderer(), "../graphics/pieces.png");
			Board::setup(&this->m_event_listener);
		}
		catch (const std::runtime_error &error)
		{
			rchess::clean_resources(p_background);
			exit(EXIT_FAILURE);
		}
	}

	void RChessApp::run()
	{
		Board rchess_board;
		sdlk::App::run();
	}

	RChessApp::~RChessApp()
	{
		rchess::clean_resources(p_background);
	}
}  // namespace rchess
