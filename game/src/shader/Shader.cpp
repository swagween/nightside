
#include "nightside/shader/Shader.hpp"
#include "nightside/core/Finder.hpp"

#include <imgui.h>

#include <iostream>

namespace nightside {

Shader::Shader(std::string_view source, std::string_view palette_source, Finder& finder) : m_palette{palette_source, finder} {
	if (!sf::Shader::isAvailable()) { std::cout << "Shaders are not available.\n"; }
	auto vert{finder.get_resource_path() / fs::path{"shaders"} / fs::path{source.data() + std::string{".vert"}}};
	auto frag{finder.get_resource_path() / fs::path{"shaders"} / fs::path{source.data() + std::string{".frag"}}};
	if (!m_shader.loadFromFile(vert, frag)) { std::cout << "Failed to load shader " + frag.string() << ".\n"; }
	if (!m_subject.loadFromFile(finder.get_resource_path() / fs::path{"images"} / fs::path{"pioneer.png"})) { std::cout << "Failed to load image.\n"; }
}

void Shader::update(sf::RenderWindow& win, sf::Clock& clock, float key) {
	auto& io = ImGui::GetIO();
	auto pos = sf::Glsl::Vec2{io.MousePos};
	m_palette.set_position({400.f, 400.f});
	m_shader.setUniform("u_size", static_cast<float>(m_palette.get_size()));
	m_shader.setUniform("u_key", static_cast<float>(key));
	m_shader.setUniform("palette", m_palette.get_texture().getTexture());
	m_shader.setUniform("texture", m_subject);
	const auto num_verts{3};
	sf::Glsl::Vec2 verts[num_verts] = {
		{0.0f, 0.0f},
		{600.f, 0.0f},
		{0.0f, 1200.f}
	};
	for (auto i{0}; i < num_verts; ++i) { m_shader.setUniform(std::string{"u_mask_" + std::to_string(i + 1)}, verts[i] + pos); }
}

void Shader::render(sf::RenderWindow& win, sf::Vector2f offset) {
	auto palette{sf::Sprite{m_palette.get_texture().getTexture()}};
	palette.setScale({64.f, 64.f});
	auto tile{sf::Sprite{m_subject}};
	win.draw(palette);
	tile.setPosition(m_palette.get_position() - sf::Vector2f{tile.getLocalBounds().size} + offset);
	win.draw(tile, &m_shader);
	tile.setPosition(m_palette.get_position() - sf::Vector2f{tile.getLocalBounds().size});
	win.draw(tile);
}

} // namespace nightside