
#include "nightside/shader/Shader.hpp"
#include "nightside/core/Finder.hpp"

#include <imgui.h>

#include <iostream>

namespace nightside {

Shader::Shader(std::string_view source, std::string_view palette_source, Finder& finder) : m_palette{palette_source, finder} {
	if (!sf::Shader::isAvailable()) { std::cout << "Shaders are not available.\n"; }
	auto frag{finder.get_resource_path() / fs::path{"shaders"} / fs::path{source.data() + std::string{".frag"}}};
	if (!m_shader.loadFromFile(frag, sf::Shader::Type::Fragment)) { std::cout << "Failed to load shader " + frag.string() << "\n"; }
}

void Shader::update(sf::RenderWindow& win, sf::Clock& clock) {
	auto& io = ImGui::GetIO();
	m_palette.set_position(io.MousePos);
	m_box.setSize(sf::Vector2f{win.getSize() / 2u});
	m_shader.setUniform("u_texture", sf::Shader::CurrentTexture);
	m_shader.setUniform("u_tex_coord", sf::Glsl::Vec2{0.f, 0.f});
}

void Shader::render(sf::RenderWindow& win) {
	m_palette.render(win);
	auto sprite{sf::Sprite{m_palette.get_texture().getTexture()}};
	sprite.setPosition(m_palette.get_position());
	win.draw(sprite, &m_shader);
}

} // namespace nightside