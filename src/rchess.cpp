#include "rchess.hpp"

#include <cstdlib>
#include <iostream>
#include <sdlk/components/image.hpp>
#include <sdlk/components/text.hpp>
#include <sdlk/sdlk.hpp>
#include <stdexcept>

#include "board/board.hpp"
#include "components/square.hpp"
#include "constant.hpp"
#include "fonts/font.hpp"
#include "pieces/pieces.hpp"

namespace rchess
{
	using namespace constant;
	static void clean_resources(sdlk::Image *background)
	{
		Piece::clean_up();
		delete background;
	}

	RChessApp::RChessApp() : sdlk::App("R_Chess", sdlk::Size(UI_WINDOW_WIDTH, UI_WINDOW_HEIGHT))
	{
		try
		{
			p_background =
				new sdlk::Image(this->get_window(), "../assets/images/background.jpg", sdlk::Size(UI_BOARD_SIZE));
			Case::setup(p_background);
			Piece::setup(p_background, this->get_window()->get_sdl_renderer(), "../assets/images/pieces.png");
		}
		catch (const std::runtime_error &error)
		{
			rchess::clean_resources(p_background);
			exit(EXIT_FAILURE);
		}
	}

	int RChessApp::run(int argc, char *argv[])
	{
		Board rchess_board(&this->m_event_listener);
		try
		{
			Square histories_container(this->get_window(),
				sdlk::Size(UI_WINDOW_WIDTH - UI_BOARD_SIZE, UI_WINDOW_HEIGHT),
				sdlk::Position(UI_BOARD_SIZE, 0));
			sdlk::Text text(this->get_window(),
				"Moves",
				{ 255, 255, 0, 255 },
				Font::get("arial", 25),
				sdlk::Position(UI_BOARD_SIZE + 5, 0));

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
