
#pragma once

#include "nightside/shader/Palette.hpp"

#include <SFML/Graphics.hpp>

namespace nightside {
class Finder;
class Shader {
  public:
	Shader(std::string_view source, Finder& finder);
	void update();
	void render(sf::RenderWindow& win);

  private:
	Palette m_palette;
	sf::Shader m_shader{};
};

} // namespace nightside