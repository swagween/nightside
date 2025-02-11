
#include "nightside/shader/Shader.hpp"
#include "nightside/core/Finder.hpp"

#include <imgui.h>

#include <iostream>

namespace nightside {

Shader::Shader(std::string_view source, std::string_view palette_source, Finder& finder) : m_palette{palette_source, finder} {
	if (!sf::Shader::isAvailable()) { std::cout << "Shaders are not available.\n"; }
	auto vert{finder.get_resource_path() / fs::path{"shaders"} / fs::path{source.data() + std::string{".vert"}}};
	auto frag{finder.get_resource_path() / fs::path{"shaders"} / fs::path{source.data() + std::string{".frag"}}};
	if (!m_shader.loadFromFile(vert, frag)) { std::cout << "Failed to load shader " + frag.string() << "\n"; }
}

void Shader::update(sf::RenderWindow& win, sf::Clock& clock) {
	auto& io = ImGui::GetIO();
	m_palette.set_position(io.MousePos);
	m_shader.setUniform("textureSampler", m_palette.get_texture().getTexture());
}

void Shader::render(sf::RenderWindow& win) {
	auto sprite{sf::Sprite{m_palette.get_texture().getTexture()}};
	sprite.setPosition(m_palette.get_position());
	win.draw(sprite, &m_shader);
}

} // namespace nightside