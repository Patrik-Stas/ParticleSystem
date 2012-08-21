#include <SFML/Graphics.hpp>
#include <iostream>
#include "Gradient.h"
#include "Particle.h"
#include "ParticleGroup.h"
#include "ParticleGroupPainter.h"


#include <stdlib.h>

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
	Gradient gradient(0, 0, 255);
	gradient.setSpeed(p_speed);
	gradient.colors.push_back(Color(255,0,0));
	gradient.colors.push_back(Color(0,0,255));
	/*gradient.colors.push_back(Color(0,0,0));
	gradient.colors.push_back(Color(244,244,112));
	gradient.colors.push_back(Color(0,0,244));
	gradient.colors.push_back(Color(1,255,1));*/

	ParticleGroup particleGroup(ShapeRectangle(10,10,10,500));
	particleGroup.pushSpawnparticles(1000);
	ParticleGroupPainter particleGroupPainter(&particleGroup, &App);

	Point mouse(0,0);

	sf::Image Image;
	if (!Image.LoadFromFile("particle.tga"))
	{
	    cerr << "failed loading image" << endl;
	    abort();
	}


	while (App.IsOpened())
	{
		gradient.shiftColor();
		sf::Event Event;
		while (App.GetEvent(Event))
		{
			if (Event.Type == sf::Event::Closed)
				App.Close();
			if (Event.Type == sf::Event::MouseMoved || Event.Type == sf::Event::MouseEntered )
				mouse = Point(Event.MouseMove.X, Event.MouseMove.Y);
		}
		App.Clear();
		App.Draw(sf::Shape::Rectangle(0, 0, 600, 350, sf::Color(gradient.red, gradient.green, gradient.blue)));
		particleGroup.processData(60, mouse);
		particleGroupPainter.paint();
		App.Display();
	}

	return EXIT_SUCCESS;
}
