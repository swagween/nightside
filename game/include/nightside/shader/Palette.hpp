
#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <string_view>

namespace nightside {

constexpr static auto f_swatch_dimensions_v{sf::Vector2f{64.f, 64.f}};

class Finder;

class Palette {
  public:
	Palette(std::string_view source, Finder& finder, sf::Vector2f dimensions = {f_swatch_dimensions_v});
	void render(sf::RenderWindow& win);
	void set_position(sf::Vector2f to_position);

  private:
	std::vector<sf::Color> m_swatches{};
	sf::Vector2f m_dimensions{};
	sf::Vector2f m_position{};
};

} // namespace nightside