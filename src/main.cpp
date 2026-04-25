#include <SFML/Graphics.hpp>
#include <iostream>

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

	void update(float dt, float gravity, float windowWidth, float windowHeight) 
	{
		velocity.y += gravity * dt;
		shape.move(velocity * dt);
		bounce(windowWidth, windowHeight);
	}

	void draw(sf::RenderWindow& window)
	{
		window.draw(shape);
	}

	void bounce(float windowWidth, float windowHeight)
	{
		sf::Vector2f pos = shape.getPosition();
		float diameter = shape.getRadius() * 2;

		float ballRightEdge = pos.x + diameter;
		float ballBottomEdge = pos.y + diameter;

		if (ballRightEdge >= windowWidth) 
		{
			shape.setPosition({ windowWidth - diameter, pos.y });
			velocity.x = -velocity.x;
		}
		else if (pos.x <= 0) 
		{
			shape.setPosition({ 0, pos.y });
			velocity.x = -velocity.x;
			
		}
		if (ballBottomEdge >= windowHeight) 
		{
			shape.setPosition({ pos.x, windowHeight - diameter });
			velocity.y = -velocity.y;
		}
		else if (pos.y <= 0)
		{
			shape.setPosition({ pos.x, 0 });
			velocity.y = -velocity.y;
		}
	}
};


int main()
{
	// "Initialization" phase: create the window, set up resources, etc.
	sf::ContextSettings settings;
	settings.antiAliasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode({800, 600}), "moving-ball-simulation", sf::Style::Default, sf::State::Windowed, settings);
	
	sf::Clock clock;

	Ball ball(80.f, { 300.f, 250.f }, { 500.f, -10.f }); // radius, start position, start velocity

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
		ball.update(dt, gravity, window.getSize().x, window.getSize().y);
		std::cout << "Ball position: " << ball.shape.getPosition().x << ", " << ball.shape.getPosition().y << std::endl;
		

		// "Render" phase: clear the window, draw everything, display the result on screen, etc.
		window.clear();
		ball.draw(window);
		window.display();
	}

    return 0;
}