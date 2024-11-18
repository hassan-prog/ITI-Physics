#include <SFML/Graphics.hpp>
//#include <iostream>

#include "Particle.h"
#include "PhysicsWorld.h"
#include "Renderer.h"
#include "Vector2d.h"
#include "Collider.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 400), "SFML works!");
	sf::CircleShape shape(15.f);
	sf::CircleShape otherShape(15.f);

	shape.setPosition(15.f, 15.f);
	shape.setPosition(300.f, 300.f);

	shape.setFillColor(sf::Color::Green);
	//shape.setOrigin(15.f, 15.f);

	otherShape.setFillColor(sf::Color::Red);
	//otherShape.setOrigin(15.f, 15.f);

	Renderer renderer;
	renderer.AddDrawable(&shape);
	renderer.AddDrawable(&otherShape);

	PhysicsWorld physicsWorld;

	// SAT Collider
	sf::RectangleShape rectShape(Vector2f(40.f, 40.f));
	sf::RectangleShape rectOtherShape(Vector2f(40.f, 40.f));

	rectShape.setPosition(550.f, 350.f);
	rectOtherShape.setPosition(550.f, 50.f);

	rectShape.setFillColor(sf::Color::Yellow);
	rectOtherShape.setFillColor(sf::Color::Blue);

	renderer.AddDrawable(&rectShape);
	renderer.AddDrawable(&rectOtherShape);

	Particle shapeParticle(Vector2d(15, 15), 1.f, 10.f, "circle");
	Particle otherShapeParticle(Vector2d(300, 300), 1.f, 10.f, "circle");
	Particle rectShapeParticle(Vector2d(550.f, 350.f), 1.f, 10.f, "square");
	Particle rectOtherShapeParticle(Vector2d(550.f, 50.f), 1.f, 10.f, "square");

	physicsWorld.addParticle(&shapeParticle);
	physicsWorld.addParticle(&otherShapeParticle);
	physicsWorld.addParticle(&rectShapeParticle);
	physicsWorld.addParticle(&rectOtherShapeParticle);

	Clock clock;
	float deltaTime = 0;
	float time = 0;
	bool circlesCollided = false;
	bool squareCollided = false;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//shapeParticle.addDrag(35);
		deltaTime = clock.getElapsedTime().asSeconds() - time;
		time += deltaTime;

		physicsWorld.Update(deltaTime, circlesCollided, squareCollided);

		if (!circlesCollided) {
			shapeParticle.addForce(Vector2d(80, 80));
			otherShapeParticle.addForce(Vector2d(-40, -40));
		}

		if (!squareCollided) {
			rectShapeParticle.addForce(Vector2d(0.f, -80.f));
			rectOtherShapeParticle.addForce(Vector2d(0.f, 80.f));
		}


		shape.setPosition(shapeParticle.position.x, shapeParticle.position.y);
		otherShape.setPosition(otherShapeParticle.position.x, otherShapeParticle.position.y);
		rectShape.setPosition(rectShapeParticle.position.x, rectShapeParticle.position.y);
		rectOtherShape.setPosition(rectOtherShapeParticle.position.x, rectOtherShapeParticle.position.y);

		renderer.Render(&window);
	}

	return 0;
}