
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
	for (auto& entry : in_swatches["swatches"].array_view()) { m_swatches.push_back(sf::Color{entry[0].as<uint8_t>(), entry[1].as<uint8_t>(), entry[2].as<uint8_t>()}); }
}

void Palette::render(sf::RenderWindow& win) {
	sf::RectangleShape swatch_box{};
	auto offset{sf::Vector2f{}};
	swatch_box.setSize(m_dimensions);
	for (auto& swatch : m_swatches) {
		swatch_box.setFillColor(swatch);
		swatch_box.setPosition(m_position + offset);
		win.draw(swatch_box);
		offset.x += m_dimensions.x;
	}
}

void Palette::set_position(sf::Vector2f to_position) { m_position = to_position; }

} // namespace nightside