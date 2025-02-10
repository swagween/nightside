
#include "nightside/Application.hpp"
#include "nightside/core/Finder.hpp"
#include "nightside/shader/Shader.hpp"

#include <imgui-SFML.h>
#include <imgui.h>

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
	Shader shader{"lighten", "gameboy", finder};

	while (window.isOpen()) {
		while (std::optional const event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) { window.close(); }
			ImGui::SFML::ProcessEvent(window, *event);
		}

		// update
		ImGui::SFML::Update(window, clock.getElapsedTime());
		shader.update(window, clock);

		// render
		window.clear();

		sf::RectangleShape backdrop{};
		backdrop.setFillColor(sf::Color{12, 12, 20});
		backdrop.setSize(f_window_size_v);
		backdrop.setOrigin(f_window_size_v / 2.f);
		backdrop.setPosition(f_center_v);
		window.draw(backdrop);

		shader.render(window);

		ImGui::SFML::Render(window);
		window.display();
	}
	shutdown();
}

void Application::shutdown() { ImGui::SFML::Shutdown(); }

} // namespace nightside