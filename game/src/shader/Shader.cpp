
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

void Shader::update(sf::RenderWindow& win, sf::Clock& clock, float key, sf::Vector2f position) {
	static sf::Glsl::Vec2 lights[16]{};
	lights[0] = sf::Glsl::Vec2{position};
	// lights[1] = sf::Glsl::Vec2{200.f, 320.f};
	m_palette.set_position({400.f, 400.f});
	m_shader.setUniform("u_size", static_cast<float>(m_palette.get_size()));
	m_shader.setUniform("u_key", static_cast<float>(key));
	m_shader.setUniform("palette", m_palette.get_texture().getTexture());
	m_shader.setUniform("texture", m_subject);
	m_shader.setUniform("u_radius", 16.f + 0.2f * sin(16.f * clock.getElapsedTime().asSeconds()));
	m_shader.setUniform("u_luminosity", 4.f);
	m_shader.setUniform("u_position", position);
	m_shader.setUniformArray("u_lights", lights, 16);
	auto const num_verts{4};
	sf::Glsl::Vec2 verts[num_verts] = {{0.0f, 0.0f}, {1200.f, 0.0f}, {0.0f, 1200.f}, {1200.0f, 1200.f}};
	auto movement = sf::Vector2f{8.f * sin(clock.getElapsedTime().asSeconds()), 0.f};
	for (auto i{0}; i < num_verts; ++i) { m_shader.setUniform(std::string{"u_mask_" + std::to_string(i + 1)}, verts[i] + movement); }
}

void Shader::render(sf::RenderWindow& win, sf::Vector2f offset) {
	auto palette{sf::Sprite{m_palette.get_texture().getTexture()}};
	palette.setScale({64.f, 64.f});
	auto tile{sf::Sprite{m_subject}};
	win.draw(palette);
	tile.setPosition(m_palette.get_position() - sf::Vector2f{tile.getLocalBounds().size} + offset);
	win.draw(tile, &m_shader);
}

} // namespace nightside