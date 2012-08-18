#include <SFML/Graphics.hpp>
#include <iostream>
#include "Gradient.h"

using std::cout;
using std::endl;

int main()
{
    sf::RenderWindow App(sf::VideoMode(800, 600), "SFML Shapes");
    Gradient transCol(0,0,255);


    while (App.IsOpened())
    {
        transCol.shiftColor();
        sf::Event Event;
        while (App.GetEvent(Event))
        {
            if (Event.Type == sf::Event::Closed)
                App.Close();
        }
        App.Clear();
        App.Draw(sf::Shape::Rectangle(0, 0, 600, 350,  sf::Color(transCol.red, transCol.green, transCol.blue)));
        App.Display();
      //cout << transCol << endl;
      ///  sleep(1);
    }

    return EXIT_SUCCESS;
}
