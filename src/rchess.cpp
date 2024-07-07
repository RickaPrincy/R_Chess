#include "rchess.hpp"

#include <sdlk/components/image.hpp>
#include <sdlk/sdlk.hpp>

#include "config.hpp"

namespace rchess
{
	void run()
	{
		sdlk::App rchess("R_Chess", sdlk::Size(config::WINDOW_SIZE));
		sdlk::Image background(rchess.get_window(),
			"../graphics/background.jpg",
			sdlk::Size(config::WINDOW_SIZE));
		rchess.run();
	}
}  // namespace rchess
