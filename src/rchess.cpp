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
		Piece test(PieceType::PAWN, PieceColor::WHITE, 2, 3);
		Piece rook(PieceType::ROOK, PieceColor::BLACK, 0, 3);
		sdlk::App::run();
	}

	RChessApp::~RChessApp()
	{
		clean_resources(p_background);
	}
}  // namespace rchess
