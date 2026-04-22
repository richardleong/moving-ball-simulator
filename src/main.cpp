#include <SFML/Graphics.hpp>

int main()
{
	// "Initialization" phase: create the window, set up resources, etc.
	sf::ContextSettings settings;
	settings.antiAliasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode({800, 600}), "moving-ball-simulation", sf::Style::Default, sf::State::Windowed, settings);
	sf::CircleShape ball(100.f);
	ball.setFillColor(sf::Color::Green);
	ball.setPosition({300.f, 250.f});
	ball.setOutlineThickness(5.f);
	ball.setOutlineColor(sf::Color::Red);

	while (window.isOpen()) 
	{
		// "Update" phase: handle events, update the state of the simulation, etc.
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}

		// "Render" phase: clear the window, draw everything, display the result on screen, etc.
		window.clear();
		window.draw(ball);
		window.display();
	}

    return 0;
}