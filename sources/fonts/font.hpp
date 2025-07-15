#pragma once

#include <SDL2/SDL_ttf.h>

#include <string>
#include <unordered_map>

namespace rchess
{
	class Font
	{
	private:
		static std::unordered_map<std::string, TTF_Font*> m_fonts;
		static std::string get_path(std::string key);

	public:
		static TTF_Font* get(const std::string& font_name, int size);
	};
}  // namespace rchess
