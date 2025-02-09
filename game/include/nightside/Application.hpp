
#pragma once

#include <SFML/Graphics.hpp>

namespace nightside {

class Application {
  public:
	Application();
	void run();
	void shutdown();

  private:
	sf::RenderWindow window{};
};

} // namespace nightside