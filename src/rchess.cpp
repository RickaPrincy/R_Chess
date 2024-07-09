#include "rchess.hpp"

#include <cstdlib>
#include <sdlk/components/image.hpp>
#include <sdlk/sdlk.hpp>
#include <stdexcept>

#include "config/config.hpp"
#include "pieces/pieces.hpp"

namespace rchess
{
	static void clean_resources(sdlk::Image *backround)
	{
		Piece::clean_up();
		delete backround;
	}

	RChessApp::RChessApp() : sdlk::App("R_Chess", sdlk::Size(config::WINDOW_SIZE))
	{
		try
		{
			p_background =
				new sdlk::Image(this->get_window(), "../graphics/background.jpg", sdlk::Size(config::WINDOW_SIZE));
			Piece::setup(this->get_window(), "../graphics/pieces.png");
		}
		catch (const std::runtime_error &error)
		{
			clean_resources(p_background);
			exit(EXIT_FAILURE);
		}
	}

	void RChessApp::run()
	{
		Piece rook(PieceType::ROOK, PieceColor::BLACK, 0, 3);

		rook.add_event_listener(sdlk::EventType::MOUSE_MOTION,
			[&](const SDL_Event &event)
			{
				rook.set_x(event.motion.x);
				rook.set_y(event.motion.x);
				rook.do_re_render();
			});

		sdlk::App::run();
	}

	RChessApp::~RChessApp()
	{
		clean_resources(p_background);
	}
}  // namespace rchess
