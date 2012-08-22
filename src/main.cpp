#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>

#include "Gradient.h"
#include "Particle.h"
#include "ParticleSfmlPrimitive.h"
#include "ParticleGroup.h"
#include "ParticleGroupPainter.h"
#include "ParticlePhysics.h"

using std::cout;
using std::endl;
using std::cerr;

int TAcolorBounds();
int testvis_push(float speed);


int main(int argc, char *argv[])
{
	if (argc>2)
	{
		cerr << "Invalid parameters" << endl;
		return -1;
	}
	TAcolorBounds();
	return testvis_push(atof(argv[1]));
}


int TAcolorBounds()
{
	Color c1 = Color(255,0,0);
	Color c2 = Color(2004, -23, 0);
	if ( c1 != c2 ) cerr << "fail ... Color1: "<< c1 << "  color2:" << c2 << endl;
	return -1;
}


int testvis_push(float p_speed)
{
    sf::RenderWindow App(sf::VideoMode(800, 600), "SFML Shapes");

	sf::Image Image;
	if (!Image.LoadFromFile("particle.tga"))
	{
	    cerr << "failed loading image" << endl;
	    abort();
	}

    App.ShowMouseCursor(false); // Hide cursor
    // Load image and create sprite

	sf::Sprite particleSprite;
	particleSprite.SetImage(Image);
	particleSprite.SetScale(0.3f, 0.3f);
	Gradient gradient(0, 0, 255);
	gradient.setSpeed(p_speed);
	gradient.colors.push_back(Color(255,0,0));
	gradient.colors.push_back(Color(0,0,255));

	ParticleGroup particleGroup(ShapeRectangle(50,50,50,50), 1, particleSprite );
	particleGroup.pushSpawnparticles(2500);
	ParticleGroupPainter particleGroupPainter(&particleGroup, &App);
	ParticlePhysics particlePhysics(1, ShapeRectangle(10, 10, 240, 250));

	int gravityPointWeight = 10000;
	Color gravityPointColor =  Color(0,255,0,255);
	ParticleSfmlPrimitive gravityPoint(0,0, gravityPointWeight, gravityPointColor);

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
		particlePhysics.apply(&particleGroup, gravityPoint);
		particleGroup.processData(framerate);
		particleGroupPainter.paint();
		gravityPoint.paint(&App);
		App.Display();
	}

	return EXIT_SUCCESS;
}
