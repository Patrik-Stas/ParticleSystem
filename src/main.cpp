#include <SFML/Graphics.hpp>
#include <iostream>
#include "Gradient.h"

using std::cout;
using std::endl;

int testvis_push();


int main()
{
	return testvis_push();
}



int testvis_push()
{
    sf::RenderWindow App(sf::VideoMode(800, 600), "SFML Shapes");
	Gradient gradient(0, 0, 255);
	gradient.colors.push_back(Color(123,0,112));
	gradient.colors.push_back(Color(0,0,0));
	gradient.colors.push_back(Color(244,244,112));
	gradient.colors.push_back(Color(0,0,244));
	gradient.colors.push_back(Color(1,255,1));

	while (App.IsOpened())
	{
		gradient.shiftColor();
		sf::Event Event;
		while (App.GetEvent(Event))
		{
			if (Event.Type == sf::Event::Closed)
				App.Close();
		}
		App.Clear();
		App.Draw(sf::Shape::Rectangle(0, 0, 600, 350, sf::Color(gradient.red, gradient.green, gradient.blue)));
		App.Display();
	}

	return EXIT_SUCCESS;
}
