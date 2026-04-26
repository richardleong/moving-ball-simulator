#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

class Ball 
{
public:
	sf::CircleShape shape;
	sf::Vector2f velocity;
	float restitution;

	Ball(float radius, sf::Vector2f startPos, sf::Vector2f startVelocity)
	{
		shape.setFillColor(sf::Color::Magenta);
		// shape.setOutlineThickness(5.f);
		// shape.setOutlineColor(sf::Color::Red);

		shape.setRadius(radius);
		shape.setPosition(startPos);
		velocity = startVelocity;
		// restitution between 0.5 and 0.9 based on radius (bigger balls are bouncier)
		// formula = min + (input - inputMin) / inputRange * outputRange
		restitution = 0.5f + (radius - 20.f) / (50.f - 20.f) * (0.9f - 0.5f); 
	}

	void update(float dt, float gravity, float windowWidth, float windowHeight) 
	{
		float drag = 0.1f; // simple drag factor to slow down the ball over time
		velocity.y += gravity * dt;
		velocity -= velocity * drag * dt;
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
			velocity.x = -velocity.x * restitution;
		}
		else if (pos.x <= 0) 
		{
			shape.setPosition({ 0, pos.y });
			velocity.x = -velocity.x * restitution;
			
		}
		if (ballBottomEdge >= windowHeight) 
		{
			shape.setPosition({ pos.x, windowHeight - diameter });
			velocity.y = -velocity.y * restitution;
		}
		else if (pos.y <= 0)
		{
			shape.setPosition({ pos.x, 0 });
			velocity.y = -velocity.y * restitution;
		}
	}
};

// Utility functions for random number generation
std::mt19937& prng()
{
	static std::random_device rd; // "random device" to obtain a seed value from hardware
	static std::mt19937 gen(rd()); // Mersenne Twister generator

	return gen;
}

float randomFloat(float min, float max)
{
	std::uniform_real_distribution<float> dist(min, max); // distribution that produces random floats in the range [min, max]

	return dist(prng());
}

int randomInt(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max); // distribution that produces random integers in the range [min, max]
	
	return dist(prng());
}

int main()
{
	// "Initialization" phase: create the window, set up resources, etc.
	sf::ContextSettings settings;
	settings.antiAliasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode({800, 600}), "moving-ball-simulation", sf::Style::Default, sf::State::Windowed, settings);
	sf::Clock clock;

	int numBalls = randomInt(1, 10);
	std::vector<Ball> balls;

	for (int i = 0; i < numBalls; ++i)
	{
		float radius = randomFloat(20.f, 50.f);
		sf::Vector2f startPos = { randomFloat(0.f, 800.f - radius * 2), randomFloat(0.f, 600.f - radius * 2) };
		sf::Vector2f startVel = { randomFloat(-400.f, 400.f), randomFloat(-400.f, 400.f) };
		balls.push_back(Ball(radius, startPos, startVel));
	}

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
		for (auto& ball : balls) // Range-based for loop to update each ball in the vector
		{
			ball.update(dt, gravity, window.getSize().x, window.getSize().y);
			// std::cout << "Ball position: " << ball.shape.getPosition().x << ", " << ball.shape.getPosition().y << std::endl;
		}

		// "Render" phase: clear the window, draw everything, display the result on screen, etc.
		window.clear();
		for (auto& ball : balls)
		{
			ball.draw(window);
		}
		window.display();
	}

    return 0;
}