
#include "nightside/shader/Shader.hpp"
#include "nightside/core/Finder.hpp"

#include <imgui.h>

namespace nightside {

Shader::Shader(std::string_view source, Finder& finder) : m_palette{source, finder} {}

void Shader::update() {
	auto& io = ImGui::GetIO();
	m_palette.set_position(io.MousePos);
}

void nightside::Shader::render(sf::RenderWindow& win) { m_palette.render(win); }

} // namespace nightside