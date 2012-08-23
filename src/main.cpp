#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
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

void init(tgui::Window& window)
{
    // Create the picture.
    // As you can see you will receive a pointer to the picture.
    // This pointer may go out of scope, the real object is stored inside the window.
    // The load function for a picture points to a file, unlike the load function from other objects.
    tgui::Picture* picture = window.add<tgui::Picture>();
    picture->load("ThinkLinux.jpg");
    picture->setSize(800, 600);

    // Create the button.
    // This time the load function contains a pathname. The folder were it points to must
    // constain an info.txt file and the necessary images. The info.txt file is very complex
    // so it won't be discussed here (See the 'read me' file inside the objects folder).
    tgui::Button* button = window.add<tgui::Button>();
    button->load("../objects/Button/Black");
    button->setText("Button 1");
    button->setSize(160, 40);
    button->setPosition(20, 4);

    // Create the checkbox.
    // This time we pass a parameter to the add function.
    // Outside the init function, our pointer will be gone, but of course you might
    // still need to access the object. You will need the string to do that.
    tgui::Checkbox* checkbox = window.add<tgui::Checkbox>("CHECK");
    checkbox->load("../objects/Checkbox/Black");
    checkbox->setText("Checkbox");
    checkbox->setPosition(20, 50);

    // Create the first radio button.
    // Only one radio button can be checked at a time, unless they have different parents.
    // In this example all radio buttons are added to the same parent, the window.
    // You can use panels to make multiple radio button groups.
    tgui::RadioButton* radioButton1 = window.add<tgui::RadioButton>();
    radioButton1->load("../objects/RadioButton/Black");
    radioButton1->setText("Radio button 1");
    radioButton1->setPosition(20, 100);

    // Create the second radio button.
    // It is loaded with the same path as the previous radio button.
    // The images won't be loaded again, they will simply be reused.
    tgui::RadioButton* radioButton2 = window.add<tgui::RadioButton>();
    radioButton2->load("../objects/RadioButton/Black");
    radioButton2->setText("Radio button 2");
    radioButton2->setPosition(20, 150);

    // Create an edit box.
    // The borders can be changed with the setBorders function.
    // You can call setTextSize to change the size of the text. If you do not do this and leave it 0,
    // like in this example, the text will be auto scaled and fit perfectly within those borders.
    tgui::EditBox* editBox = window.add<tgui::EditBox>();
    editBox->load("../objects/EditBox/Black");
    editBox->setBorders(6, 4, 6, 4);
    editBox->setText("This text no longer fits inside the EditBox.");
    editBox->setPosition(20, 300);
    editBox->setSize(360, 40);

    // Create the slider.
    // We want the slider to lie horizontal, so we set vertical scroll to false.
    tgui::Slider* slider = window.add<tgui::Slider>();
    slider->load("../objects/Slider/Black");
    //                                        slider->setVerticalScroll(false);
    slider->setPosition(30, 360);

    // Create the loading bar.
    // The maximum is changed, so the loading bar goes from 0 to 500 (instead of 0 to 100).
    // Note that we change callbackID here. This ID is used to receive callbacks.
    // The ID is 0 by default which means that no callback is sent.
    tgui::LoadingBar* loadingBar = window.add<tgui::LoadingBar>("LOAD");
    loadingBar->load("../objects/LoadingBar/Black");
    loadingBar->setPosition(20, 400);
    loadingBar->setMaximum(500);
    loadingBar->callbackID = 1;

    // Create a scrollbar.
    // You can call the setLowValue function to change when the scrollbar should be visible.
    // The number is 1 by default and the scrollbar is only visible when the maximum is higher.
    // Here we set the maximum to 5.
    tgui::Scrollbar* scroll = window.add<tgui::Scrollbar>();
    scroll->load("../objects/Scrollbar/Black");
    scroll->setLowValue(4);
    scroll->setMaximum(5);
    //								scroll->setVerticalScroll(false);
    scroll->setPosition(30, 480);


    // All the objects until now were loaded at the same way.
    // Although I'd rather don't have them, there are some exceptions.
    // The objects that are going to be created now have different parameters for the load function.
    // The explanation and the names of the parameters to pass should be clear enough though.

    // Create the listbox.
    // You must pass the width and height to the load function. The next parameter is the path to
    // the scrollbar. This path works like that from all the other objects.
    // The last parameter is the height of one item (if not provided this is a tenth of the height).
    // Again you can set the borders with the setBorders function.
    tgui::Listbox* listbox = window.add<tgui::Listbox>();
    listbox->load(260, 200, "../objects/Scrollbar/Black", 30);
    listbox->setBorders(4, 4, 4, 4);
    listbox->setPosition(300, 20);
    listbox->addItem("Item 1");
    listbox->addItem("Item 2");
    listbox->addItem("Item 3");
    listbox->addItem("Item 4 is too long to fit inside the listbox and will be cropped.");
    listbox->addItem("Item 5");
    listbox->addItem("Item 6");
    listbox->addItem("Item 7");
    listbox->addItem("Item 8");
    listbox->addItem("Item 9");
    listbox->addItem("Item 10");

    // Create the combo box.
    // The first parameter of the load function is normal. It is the path were the arrow image can
    // be found. The second and third parameters change the width and height of the combo box.
    // The next parameter would choose the amount of items in the list. If there is no scrollbar then
    // this will also be the maximum items to select from (this parameter is 10 by default).
    // If there is a scrollbar then it will become visible when you have more items than this number.
    // The last parameter would be the path to the scrollbar.
    tgui::ComboBox* comboBox = window.add<tgui::ComboBox>();
    comboBox->load("../objects/ComboBox/Black", 200, 40);
    comboBox->setBorders(4, 4, 4, 4);
    comboBox->setPosition(500, 330);
    comboBox->addItem("Item 1 is too long");
    comboBox->addItem("Item 2");
    comboBox->addItem("Item 3");
    comboBox->setSelectedItem(2); // "Item 2" will now be selected

    // In this case I am not happy with the default colors.
    // The listbox and combo box don't fit next to our other objects.
    listbox->changeColors(sf::Color( 50,  50,  50),  // Background color
                          sf::Color(200, 200, 200),  // Text color
                          sf::Color( 10, 110, 255),  // Background color of the selected item.
                          sf::Color(255, 255, 255)); // Text color of the selected item
                          // The next pareter would change the border color (black by default)

    // We can do exactly the same with our combo box (same function, same parameters).
    comboBox->changeColors(sf::Color( 50,  50,  50), sf::Color(200, 200, 200),
                           sf::Color( 10, 110, 255), sf::Color(255, 255, 255));


    // There are still a lot of objects missing in this example code.
}
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

int main(int argc, char *argv[])
{
	{
		std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();

		tgui::Window window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML Shapes");
		//init(window);
		window.loadObjectsFromFile("TGUI/form.txt");


		sf::Font MyFont;
		if (!MyFont.loadFromFile("media/DejaVuSans.ttf"))
		{
			std::cerr << "cant load font" << std::endl;
			abort();
		}

		sf::Text Text("Text", MyFont, 30);
		Text.setPosition(300, 100);

	//	window.setMouseCursorVisible(false); // Hide cursor
		// Load image and create sprite

		sf::Texture particleTexture;
		particleTexture.loadFromFile("media/particleSharp2.tga");
		sf::Sprite particleSprite(particleTexture);
		particleSprite.setScale(0.2f, 0.2f);

		/*Gradient gradient(0, 0, 255);
		 gradient.setSpeed(p_speed);
		 gradient.colors.push_back(Color(255,0,0));
		 gradient.colors.push_back(Color(0,0,255));*/

		ShapeRectangle spawnArea(300, 50, 180, 180);
		ShapeRectangle moveableArea(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

		ParticleGroup particleGroup(spawnArea, moveableArea, 1, particleSprite);
		particleGroup.pushSpawnparticles(10200);
		ParticleGroupPainter particleGroupPainter(&particleGroup, &window);

		int gravityPointWeight = 1000000;
		Color gravityPointColor = Color(0, 255, 0, 255);
		ParticleSfmlPrimitive gravityPoint(0, 0, gravityPointWeight, gravityPointColor);

		const float gravitation = 0.1;

		sf::Clock clock;
		clock.restart();

		sf::Event event;
		sf::Time lastTime = clock.getElapsedTime();
		float framerate;

		while (window.isOpen())
		{
			//	gradient.shiftColor();
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				if (event.type == sf::Event::MouseMoved || event.type == sf::Event::MouseEntered)
				{
					gravityPoint.setPosition(event.mouseMove.x, event.mouseMove.y);
				}
			}

			tgui::Callback callback;
			while (window.getCallback(callback))
			{
				// Here you can handle the callback.
				// In this example we will check if the value of the loading bar has changed.
				// First we check the ID. This ID 1 was given to the object inside the init function.
				if (callback.callbackID == 1)
				{
					// Now check if the loading bar is full. If it is then close the window.
					// You only had a pointer to the loading bar inside the init function.
					// To get it back you must use the get function.
					// The "LOAD" name was chosen inside the init function.
					if (callback.value == window.get<tgui::LoadingBar>("LOAD")->getMaximum())
						window.close();
				}
			}

			framerate = 1 / (clock.getElapsedTime() - lastTime).asSeconds();
			lastTime = clock.getElapsedTime();
			std::cout << "fps: " << framerate << std::endl;
			//window.draw(sf::RectangleShape(0, 0, 5, 350, sf::Color(gradient.red, gradient.green, gradient.blue)));
			particleGroup.applyPhysics(gravitation, gravityPoint);
			particleGroup.processData(60);
			particleGroupPainter.paint();
			gravityPoint.paint(&window);
			Text.setString(boost::lexical_cast<string>(particleGroup.getParticleCount()));
			window.draw(Text);
			window.drawGUI();
			window.display();

		}
		//window.removeAllObjects();
		return EXIT_SUCCESS;
	}
}

