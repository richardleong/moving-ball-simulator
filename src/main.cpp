#include <SFML/Graphics.hpp>

class Ball 
{
public:
	sf::CircleShape shape;
	sf::Vector2f velocity;

	Ball(float radius, sf::Vector2f startPos, sf::Vector2f startVelocity)
	{
		shape.setFillColor(sf::Color::Green);
		shape.setOutlineThickness(5.f);
		shape.setOutlineColor(sf::Color::Red);

		shape.setRadius(radius);
		shape.setPosition(startPos);
		velocity = startVelocity;
	}

	void update(float dt, float gravity) 
	{
		velocity.y += gravity * dt;
		shape.move(velocity * dt);
	}

	void draw(sf::RenderWindow& window)
	{
		window.draw(shape);
	}
};


int main()
{
	// "Initialization" phase: create the window, set up resources, etc.
	sf::ContextSettings settings;
	settings.antiAliasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode({800, 600}), "moving-ball-simulation", sf::Style::Default, sf::State::Windowed, settings);
	
	sf::Clock clock;

	Ball ball(80.f, { 300.f, 250.f }, { 100.f, 0.f });

	const float gravity = 500.f;

	while (window.isOpen()) 
	{
		float dt = clock.restart().asSeconds();
		
		// Event Handling: check for events (like key presses, mouse clicks, etc.)
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}

		// "Update" phase
		ball.update(dt, gravity);

		// "Render" phase: clear the window, draw everything, display the result on screen, etc.
		window.clear();
		ball.draw(window);
		window.display();
	}

    return 0;
}