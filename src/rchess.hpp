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
		void run();
		RChessApp();
		virtual ~RChessApp();
	};
}  // namespace rchess
