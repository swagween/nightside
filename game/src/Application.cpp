
#include "nightside/Application.hpp"
#include "nightside/core/Finder.hpp"
#include "nightside/shader/Shader.hpp"

#include <imgui.h>
#include <imgui-SFML.h>

#include <iostream>
#include <string>

namespace nightside {

Application::Application() {
	window.setFramerateLimit(144);
	auto dimensions{sf::Vector2u{1280, 720}};
	auto mode{sf::VideoMode(dimensions)};
	auto title{"Nightside Projects"};
	window.create(mode, title, sf::Style::Default & ~sf::Style::Resize);
	if (!ImGui::SFML::Init(window)) { std::cout << "Failed to initialize window.\n"; }
}

void Application::run() {
	constexpr static float size_v{64.f};
	constexpr static sf::Vector2<float> dimensions_v{size_v, size_v};
	static auto f_window_size_v{sf::Vector2f{window.getSize()}};
	static auto f_center_v{sf::Vector2f{window.getSize() / 2u}};
	static auto clock{sf::Clock()};
	clock.start();

	// game variables
	Finder finder{};
	Shader darken{"lighten", "pioneer", finder};
	Shader point_light{"point_light", "pioneer", finder};
	Shader point_light_2{"point_light", "pioneer", finder};

	while (window.isOpen()) {
		while (std::optional const event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) { window.close(); }
			ImGui::SFML::ProcessEvent(window, *event);
		}

		// update
		ImGui::SFML::Update(window, clock.getElapsedTime());
		auto& io = ImGui::GetIO();
		auto pos = sf::Glsl::Vec2{io.MousePos.x, window.getSize().y - io.MousePos.y};
		darken.update(window, clock, -5.f, {});
		point_light_2.update(window, clock, 0.f, {200.f, 300.f});
		point_light.update(window, clock, 0.f, pos);

		// render
		window.clear();

		sf::RectangleShape backdrop{};
		backdrop.setFillColor(sf::Color{16, 8, 28});
		backdrop.setSize(f_window_size_v);
		backdrop.setOrigin(f_window_size_v / 2.f);
		backdrop.setPosition(f_center_v);
		window.draw(backdrop);

		darken.render(window, sf::Vector2f{0.f, 0.f});
		point_light_2.render(window, sf::Vector2f{0.f, 0.f});
		point_light.render(window, sf::Vector2f{0.f, 0.f});

		ImGui::SFML::Render(window);
		window.display();
	}
	shutdown();
}

void Application::shutdown() { ImGui::SFML::Shutdown(); }

} // namespace nightside