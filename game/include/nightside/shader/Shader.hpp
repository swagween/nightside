
#pragma once

#include "nightside/shader/Palette.hpp"

#include <SFML/Graphics.hpp>

namespace nightside {
class Finder;
class Shader {
  public:
	Shader(std::string_view source, std::string_view palette_source, Finder& finder);
	void update(sf::RenderWindow& win, sf::Clock& clock, float key, sf::Vector2f position);
	void render(sf::RenderWindow& win, sf::Vector2f offset);

  private:
	Palette m_palette;
	sf::Texture m_subject{};
	sf::Shader m_shader{};
	sf::VertexArray m_mask{};
};

} // namespace nightside