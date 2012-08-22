#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <boost/lexical_cast.hpp>
#include <string>

#include "Gradient.h"
#include "Particle.h"
#include "ParticleSfmlPrimitive.h"
#include "ParticleGroup.h"
#include "ParticleGroupPainter.h"

using std::cout;
using std::endl;
using std::cerr;
using std::string;

int testvis_push(float speed);


int main(int argc, char *argv[])
{
	if (argc>2)
	{
		cerr << "Invalid parameters" << endl;
		return -1;
	}
	return testvis_push(atof(argv[1]));
}

int testvis_push(float p_speed)
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Shapes");

	sf::Font MyFont;
	if (!MyFont.loadFromFile("media/DejaVuSans.ttf"))
	{
		std::cerr << "cant load font" << std::endl;
	    abort();
	}
	sf::Text Text("Text", MyFont, 30);
	Text.setPosition(300,100);

    window.setMouseCursorVisible(false); // Hide cursor
    // Load image and create sprite

    sf::Texture particleTexture;
    particleTexture.loadFromFile ("media/particle.tga");
	sf::Sprite particleSprite(particleTexture);
	particleSprite.setScale(0.5f, 0.5f);
	Gradient gradient(0, 0, 255);
	gradient.setSpeed(p_speed);
	gradient.colors.push_back(Color(255,0,0));
	gradient.colors.push_back(Color(0,0,255));

	ShapeRectangle spawnArea(300,50,140,140);
	ShapeRectangle moveableArea(50, 10, 500, 500);

	ParticleGroup particleGroup(spawnArea, moveableArea, 1, particleSprite );
	particleGroup.pushSpawnparticles(10200);
	ParticleGroupPainter particleGroupPainter(&particleGroup, &window);

	int gravityPointWeight = 1000000;
	Color gravityPointColor =  Color(0,255,0,255);
	ParticleSfmlPrimitive gravityPoint(0,0, gravityPointWeight, gravityPointColor);

	const float gravitation = 0.1;

    sf::Clock clock;
    clock.restart();

    sf::Event event;
    sf::Time lastTime = clock.getElapsedTime();
    float framerate;

	while (window.isOpen())
	{
		gradient.shiftColor();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseMoved || event.type == sf::Event::MouseEntered )
			{
				gravityPoint.setPosition(event.mouseMove.x, event.mouseMove.y);
			}
		}
		window.clear();


        framerate = 1 / (clock.getElapsedTime() - lastTime).asSeconds();
        lastTime = clock.getElapsedTime();
        std::cout << "fps: " << framerate << std::endl;
		//window.draw(sf::RectangleShape(0, 0, 5, 350, sf::Color(gradient.red, gradient.green, gradient.blue)));
		particleGroup.applyPhysics(gravitation, gravityPoint);
		particleGroup.processData(60);
		particleGroupPainter.paint();
		gravityPoint.paint(&window);
		Text.setString(boost::lexical_cast<string>( particleGroup.getParticleCount() ));
		window.draw(Text);
		window.display();

	}

	return EXIT_SUCCESS;
}
