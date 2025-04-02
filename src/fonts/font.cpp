#include "font.hpp"

#include <SDL2/SDL_log.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <unordered_map>

namespace rchess
{
	std::unordered_map<std::string, TTF_Font*> Font::m_fonts;

	TTF_Font* Font::get(const std::string& font_name, int size)
	{
		std::string key = font_name + "_" + std::to_string(size);

		if (m_fonts.find(key) != m_fonts.end())
		{
			return m_fonts[key];
		}

		TTF_Font* font = TTF_OpenFont(get_path(font_name).c_str(), size);
		if (!font)
		{
			SDL_Log("TTF_OpenFont Error: %s", TTF_GetError());
			return nullptr;
		}

		m_fonts[key] = font;
		return font;
	}

	std::string Font::get_path(std::string font)
	{
		// TODO: sdlk: use resource like qt
		return "../assets/fonts/" + font + ".ttf";
	}
}  // namespace rchess
