
#pragma once

#include "nightside/shader/Palette.hpp"

#include <SFML/Graphics.hpp>

namespace nightside {
class Finder;
class Shader {
  public:
	Shader(std::string_view source, std::string_view palette_source, Finder& finder);
	void update(sf::RenderWindow& win, sf::Clock& clock);
	void render(sf::RenderWindow& win);

  private:
	Palette m_palette;
	sf::Shader m_shader{};
};

} // namespace nightside