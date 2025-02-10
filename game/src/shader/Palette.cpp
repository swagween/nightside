
#include "nightside/shader/Palette.hpp"
#include "nightside/core/Finder.hpp"

#include <djson/json.hpp>

#include <cassert>
#include <iostream>

namespace nightside {

Palette::Palette(std::string_view source, Finder& finder, sf::Vector2f dimensions) : m_dimensions(dimensions) {
	auto dir{(finder.get_resource_path() / fs::path{"palettes"} / fs::path{source.data() + std::string{".json"}}).string()};
	auto in_swatches = dj::Json::from_file(dir.c_str());
	assert(!in_swatches.is_null());
	sf::RectangleShape swatch_box{};
	auto offset{sf::Vector2f{}};
	m_texture.clear(sf::Color::Transparent);
	if (!m_texture.resize(sf::Vector2u{static_cast<unsigned int>(m_dimensions.x * static_cast<float>(in_swatches["swatches"].array_view().size())), static_cast<unsigned int>(m_dimensions.y)})) {
		std::cout << "Failed to resize palette texture.\n";
	}
	for (auto& entry : in_swatches["swatches"].array_view()) {
		m_swatches.push_back(sf::Color{entry[0].as<uint8_t>(), entry[1].as<uint8_t>(), entry[2].as<uint8_t>()});
		swatch_box.setSize(m_dimensions);
		swatch_box.setFillColor(m_swatches.back());
		swatch_box.setPosition(m_position + offset);
		m_texture.draw(swatch_box);
		m_texture.display();
		offset.x += m_dimensions.x;
	}
}

void Palette::render(sf::RenderWindow& win) {
	auto sprite{sf::Sprite{m_texture.getTexture()}};
	sprite.setPosition(m_position);
	win.draw(sprite);
}

void Palette::set_position(sf::Vector2f to_position) { m_position = to_position; }

sf::RenderTexture& Palette::get_texture() { return m_texture; }

} // namespace nightside