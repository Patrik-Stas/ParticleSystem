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
    sf::RenderWindow App(sf::VideoMode(800, 600), "SFML Shapes");

	sf::Image Image;
	if (!Image.LoadFromFile("media/particle.tga"))
	{
	    cerr << "failed loading image" << endl;
	    abort();
	}

	sf::Font MyFont;
	if (!MyFont.LoadFromFile("media/DejaVuSans.ttf"))
	{
		std::cerr << "cant load font" << std::endl;
	    abort();
	}
	sf::String Text("Hello", MyFont, 10);
	Text.SetPosition(300,100);

    App.ShowMouseCursor(false); // Hide cursor
    // Load image and create sprite

	sf::Sprite particleSprite;
	particleSprite.SetImage(Image);
	particleSprite.SetScale(0.5f, 0.5f);
	Gradient gradient(0, 0, 255);
	gradient.setSpeed(p_speed);
	gradient.colors.push_back(Color(255,0,0));
	gradient.colors.push_back(Color(0,0,255));

	ShapeRectangle spawnArea(50,50,80,80);
	ShapeRectangle moveableArea(10, 10, 400, 400);

	ParticleGroup particleGroup(spawnArea, moveableArea, 1, particleSprite );
	particleGroup.pushSpawnparticles(2200);
	ParticleGroupPainter particleGroupPainter(&particleGroup, &App);

	int gravityPointWeight = 10000;
	Color gravityPointColor =  Color(0,255,0,255);
	ParticleSfmlPrimitive gravityPoint(0,0, gravityPointWeight, gravityPointColor);

	const int gravitation = 1;

    sf::Clock Clock;
    Clock.Reset();
	while (App.IsOpened())
	{
		gradient.shiftColor();
		sf::Event Event;
		while (App.GetEvent(Event))
		{
			if (Event.Type == sf::Event::Closed)
				App.Close();
			if (Event.Type == sf::Event::MouseMoved || Event.Type == sf::Event::MouseEntered )
			{
				gravityPoint.setPosition(Event.MouseMove.X, Event.MouseMove.Y);
			}
		}
		App.Clear();

        float framerate=1/App.GetFrameTime();
        std::cout << "fps: " << framerate << std::endl;
		App.Draw(sf::Shape::Rectangle(0, 0, 5, 350, sf::Color(gradient.red, gradient.green, gradient.blue)));
		particleGroup.applyPhysics(gravitation, gravityPoint);
		particleGroup.processData(framerate);
		particleGroupPainter.paint();
		gravityPoint.paint(&App);
		Text.SetText(boost::lexical_cast<string>( particleGroup.getParticleCount() ));
		App.Draw(Text);
		App.Display();

	}

	return EXIT_SUCCESS;
}
