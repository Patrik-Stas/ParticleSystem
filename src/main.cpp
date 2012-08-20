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

	Particle particle (10, 10);
	particle.setVectorXY(1,2);
	particle.setFriction(0);

	ParticleGroup particleGroup(50, 50, 300, 300);
	particleGroup.pushSpawnparticles(200);
	particleGroup.setRandVect();
	ParticleGroupPainter particleGroupPainter(&particleGroup, &App);

	while (App.IsOpened())
	{
		particle.processData(60);
		gradient.shiftColor();
		sf::Event Event;
		while (App.GetEvent(Event))
		{
			if (Event.Type == sf::Event::Closed)
				App.Close();
		}
		App.Clear();
		App.Draw(sf::Shape::Rectangle(0, 0, 600, 350, sf::Color(gradient.red, gradient.green, gradient.blue)));
		particleGroup.processData(60);
		particleGroupPainter.paint();
		App.Display();
	}

	return EXIT_SUCCESS;
}
