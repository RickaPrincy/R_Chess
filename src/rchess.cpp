#include "rchess.hpp"

#include <cstdlib>
#include <iostream>
#include <sdlk/components/image.hpp>
#include <sdlk/sdlk.hpp>
#include <stdexcept>

#include "board/board.hpp"
#include "constant.hpp"
#include "pieces/pieces.hpp"

namespace rchess
{
	using namespace constant;
	static void clean_resources(sdlk::Image *background)
	{
		Piece::clean_up();
		delete background;
	}

	RChessApp::RChessApp() : sdlk::App("R_Chess", sdlk::Size(UI_WINDOW_SIZE))
	{
		try
		{
			p_background =
				new sdlk::Image(this->get_window(), "../graphics/background.jpg", sdlk::Size(UI_WINDOW_SIZE));
			Piece::setup(p_background, this->get_window()->get_sdl_renderer(), "../graphics/pieces.png");
			Board::setup_observer(&this->m_event_listener);
		}
		catch (const std::runtime_error &error)
		{
			rchess::clean_resources(p_background);
			exit(EXIT_FAILURE);
		}
	}

	int RChessApp::run(int argc, char *argv[])
	{
		Board rchess_board;
		try
		{
			sdlk::App::run();
			return 0;
		}
		catch (...)
		{
			std::cerr << "[ERROR]" << std::endl;
			return -1;
		}
	}

	RChessApp::~RChessApp()
	{
		rchess::clean_resources(p_background);
	}
}  // namespace rchess
