#pragma once

#include <sdlk/components/image.hpp>
#include <sdlk/core/app.hpp>

namespace rchess
{
	class RChessApp : public sdlk::App
	{
	protected:
		sdlk::Image *p_background = nullptr;

	public:
		int run(int argc, char *argv[]);
		RChessApp();
		virtual ~RChessApp();
	};
}  // namespace rchess
