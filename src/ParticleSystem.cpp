/*
 * ParticleSystem.cpp
 *
 *  Created on: Aug 23, 2012
 *      Author: stashell
 */

#include "ParticleSystem.h"
#include "ShapeCircle.h"
#include "Misc.h"
#include <ctime>
#include "Constants.h"

using std::cout;
using std::endl;
using std::cerr;
using std::string;

sf::Texture particleTexture;

sf::Sprite getDefaultParticleSprite()
{

	particleTexture.loadFromFile("media/particleSharp2.tga");
	sf::Sprite sprite(particleTexture);
	return sprite;
}

const int ParticleSystem::SCREEN_WIDTH = 1276;
const int ParticleSystem::SCREEN_HEIGHT = 758;
const float ParticleSystem::PDEFAULT_GRAVITYPOINT_WEIGHT = 10000;

const sf::Keyboard::Key ParticleSystem::KEY_SHOW_HIDE_MENU = sf::Keyboard::Q;
const sf::Keyboard::Key ParticleSystem::KEY_PAUSE_CONTINUE = sf::Keyboard::P;
const sf::Keyboard::Key ParticleSystem::KEY_SCREENSHOT = sf::Keyboard::W;
const sf::Keyboard::Key ParticleSystem::KEY_SWITCH_COLOR = sf::Keyboard::A;
const sf::Keyboard::Key ParticleSystem::KEY_DUMP_COLOR = sf::Keyboard::L;
const sf::Keyboard::Key ParticleSystem::KEY_GP_WEIGHT_UP = sf::Keyboard::S;
const sf::Keyboard::Key ParticleSystem::KEY_GP_WEIGHT_DOWN = sf::Keyboard::X;
const sf::Keyboard::Key ParticleSystem::KEY_GRAVITY_UP = sf::Keyboard::D;
const sf::Keyboard::Key ParticleSystem::KEY_GRAVITY_DOWN = sf::Keyboard::C;
const sf::Keyboard::Key ParticleSystem::KEY_PARTICLE_SIZE_UP = sf::Keyboard::K;
const sf::Keyboard::Key ParticleSystem::KEY_PARTICLE_SIZE_DOWN = sf::Keyboard::M;
const sf::Keyboard::Key ParticleSystem::KEY_PARTICLE_ALPHA_UP = sf::Keyboard::J;
const sf::Keyboard::Key ParticleSystem::KEY_PARTICLE_ALPHA_DOWN = sf::Keyboard::N;
const sf::Keyboard::Key ParticleSystem::KEY_GP_AUTOFORCE_SWITCH = sf::Keyboard::Space;
const sf::Keyboard::Key ParticleSystem::KEY_PARTICLE_COLORTRANS_LENGTHPLUS = sf::Keyboard::R;
const sf::Keyboard::Key ParticleSystem::KEY_PARTICLE_COLORTRANS_LENGTHMINUS = sf::Keyboard::E;
const sf::Keyboard::Key ParticleSystem::KEY_PARTICLE_COUNT_UP = sf::Keyboard::H;
const sf::Keyboard::Key ParticleSystem::KEY_PARTICLE_COUNT_DOWN = sf::Keyboard::B;
const sf::Keyboard::Key ParticleSystem::KEY_DRAWMODE_SWITCH = sf::Keyboard::L;

const Color ParticleSystem::DEFAULT_GRAVITYPOINT_COLOR = Color(0, 255, 255, 200);
const PARTICLE_ACTION ParticleSystem::DEFAULT_BOUND_ACTION = STOP;
sf::RenderWindow ParticleSystem::appWindow(sf::VideoMode(ParticleSystem::SCREEN_WIDTH, ParticleSystem::SCREEN_HEIGHT),
		"SFML Shapes");
sf::Sprite ParticleSystem::DEFAULT_PARTICLE_SPRITE = getDefaultParticleSprite();

ShapeCircle circle(Point(200, 200), 60);
Emitter ParticleSystem::circleEmitter = Emitter(&circle);

ParticleSystem::ParticleSystem() :
		moveableArea(Point(0, 0), SCREEN_WIDTH-400, SCREEN_HEIGHT - 180)
{
	srand(time(NULL));

	automatedMovingObject.setMoveableArea(&moveableArea);
	automatedGravityPoint.setAutomatedMovingObject(&automatedMovingObject);
	mouseControllGravityPoint.setMouseVariables(&c_mouseX, &c_mouseY, &c_rightButtonClicked);

	//gravityPoint = &mouseControllGravityPoint;

	showMenu = true;
	automaticColorSchemeChange = false;

	particlePhysics.setGravitation(1.0f);
	particlePhysics.setDownForce(false);

	particleGroup.setMoveableArea(&moveableArea);
	particleGroup.setBoundAction(DEFAULT_BOUND_ACTION);
	particleGroup.setEmitter(&circleEmitter);
	particleGroup.setDefaultWeight(1.0f);
	particleGroup.setDefaultScaledSize(1.0f);
	particleGroup.setParticleSprite(DEFAULT_PARTICLE_SPRITE);

	appWindow.resetGLStates();
	mainFont = loadMainFont();

	sfguiWindow = sfg::Window::Create();

	panelBox = ControlPanel::getControlPanel(this, sfg::Box::VERTICAL, 0.1f);
	sfguiWindow->Add(panelBox->getBox());
	sfguiWindow->SetPosition(sf::Vector2f(SCREEN_WIDTH - sfguiWindow->GetRequisition().x, 0));

	setParticleBoundaryAction(RESPAWN);
	setGravitation(5);
	setParticleSize(0.1);
	setParticleCount(20000);
	setMouseGravityPointMode(true);
	setGravityPointWeigth(100000);
	setDotMode(true);


	automaticMovingObject.setMoveableArea(&moveableArea);
	applicationPaused = false;

}

sf::Font ParticleSystem::loadMainFont()
{
	sf::Font myFont;
	if (!myFont.loadFromFile("media/DejaVuSans.ttf"))
	{
		std::cerr << "can't load font" << std::endl;
		abort();
	}
	return myFont;
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

void ParticleSystem::setGravitation(float p_gravitation)
{
	particlePhysics.setGravitation(trimValue(p_gravitation, MIN_GRAVITY, MAX_GRAVITY));
}
float ParticleSystem::getGravitation()
{
	return particlePhysics.getGravitation();
}
void ParticleSystem::setGravitationUp()
{
	setGravitation(particlePhysics.getGravitation() + 2);
}
void ParticleSystem::setGravitationDown()
{
	setGravitation(particlePhysics.getGravitation() - 2);
}
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void ParticleSystem::setGravityPointWeigth(float p_weight)
{
	p_weight = trimValue(p_weight, MIN_GRAVITYPOINT_WEIGHT, MAX_GRAVITYPOINT_WEIGHT);
	mouseControllGravityPoint.setWeight(p_weight);
	automatedGravityPoint.setWeight(p_weight);
}
float ParticleSystem::getGravityPointWeigth()
{
	return gravityPoint->getWeight();
}
void ParticleSystem::setGravityPointWeigthUp()
{
	setGravityPointWeigth(gravityPoint->getWeight() + 1000);
}
void ParticleSystem::setGravityPointWeigthDown()
{
	setGravityPointWeigth(gravityPoint->getWeight() - 1000);
}
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void ParticleSystem::setSideGravity(bool p_sideGravity)
{
	 particlePhysics.setDownForce(p_sideGravity);
}
bool ParticleSystem::isSideGravity()
{
	return particlePhysics.isDownForce();
}
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
PARTICLE_ACTION ParticleSystem::getParticleBoundaryAction()
{
	return boundaryParticleAction;
}
void ParticleSystem::setParticleBoundaryAction(PARTICLE_ACTION p_action)
{
	particleGroup.setBoundAction(p_action);
}
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void ParticleSystem::setParticleSize(float p_size)
{
	particleGroup.setScaledSize(trimValue(p_size, MIN_PARTICLE_SIZE, MAX_PARTICLE_SIZE));
}
float ParticleSystem::getParticleSize()
{
	return particleGroup.getScaledSize();
}
void ParticleSystem::setParticleSizeUp()
{
	setParticleSize(getParticleSize()+0.025);
}
void ParticleSystem::setParticleSizeDown()
{
	setParticleSize(getParticleSize()-0.025);
}
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void ParticleSystem::setParticleCount(int p_count)
{
	particleGroup.setParticlesCount(trimValue(p_count, MIN_PARTICLE_COUNT, MAX_PARTICLE_COUNT));
}
int ParticleSystem::getParticleCount()
{
	return particleGroup.getParticleCount();
}
void ParticleSystem::setParticleCountUp()
{
	setParticleCount(getParticleCount()+1000);
}
void ParticleSystem::setParticleCountDown()
{
	setParticleCount(getParticleCount()-1000);
}
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

void ParticleSystem::setColorTransientLength(float p_length)
{
	particleColorManager.setTrasitionLength(trimValue(p_length, MIN_TRANSATION_LENGTH, MAX_TRANSATION_LENGTH));
}
float ParticleSystem::getColorTransientLength()
{
	return particleColorManager.getTrasitionLength();
}
void ParticleSystem::setColorTransientLengthUp()
{
	setColorTransientLength(getColorTransientLength() + 0.5f);
}
void ParticleSystem::setColorTransientLengthDown()
{
	setColorTransientLength(getColorTransientLength() - 0.5f);
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void ParticleSystem::setParticleAlpha(float p_alpha)
{
	particleGroup.setAlpha(trimValue(p_alpha, MIN_PARTICLE_ALPHA, MAX_PARTICLE_ALPHA));
}
float ParticleSystem::getParticleAlpha()
{
	return particleGroup.getAlpha();
}
void ParticleSystem::setParticleAlphaUp()
{
	setParticleAlpha(getParticleAlpha()+2);
}
void ParticleSystem::setParticleAlphaDown()
{
	setParticleAlpha(getParticleAlpha()-2);
}
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void ParticleSystem::changeColorScheme()
{
	particleColorManager.changeColorScheme();
}
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

void ParticleSystem::setAutoColorScheme(bool p_autoColorSchemeChange)
{
	automaticColorSchemeChange = p_autoColorSchemeChange;
}
bool ParticleSystem::isAutoColorScheme()
{
	return automaticColorSchemeChange;
}
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void ParticleSystem::setDotMode(bool p_dotMode)
{
	dotMode = p_dotMode;
}
bool ParticleSystem::isDotMode()
{
	return dotMode;
}
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void ParticleSystem::setMouseGravityPointMode(bool p_mouseGravityPointMode)
{
	if (p_mouseGravityPointMode)
		gravityPoint = &mouseControllGravityPoint;
	else
		gravityPoint = &automatedGravityPoint;
}
bool ParticleSystem::isMouseGravityPointMode()
{
	return (gravityPoint == &mouseControllGravityPoint);
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void ParticleSystem::buttonActionTakeScreenshot()
{
	toTakePicture = true;
}
void ParticleSystem::takeScreenshot()
{
	sf::Image Screenshot;
	Screenshot = appWindow.capture();
	string actualTime = getActualTime();
	Screenshot.saveToFile("screenshots/screenshot" + actualTime + ".png");
	toTakePicture = false;
}
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

void ParticleSystem::switchGravityPointForceActive()
{
	if (gravityPoint->isForceActive())
		gravityPoint->setForceActive(false);
	else
		gravityPoint->setForceActive(true);
}

int ParticleSystem::run()
{
	// window.setMouseCursorVisible(false); // Hide cursor
	sf::Event event;
	sf::Clock clock;
	sf::Clock pauseClocks;
	sf::Time pauseTime;
	clock.restart();
	sf::Time lastTime = clock.getElapsedTime();
	float framerate;

	sf::Clock clockGui;
	clockGui.restart();
	while (appWindow.isOpen())
	{
		while (appWindow.pollEvent(event))
		{
			sfguiWindow->HandleEvent(event);

			if (event.type == sf::Event::Closed)
				appWindow.close();
			if (event.type == sf::Event::MouseMoved || event.type == sf::Event::MouseEntered)
			{
				c_mouseX = event.mouseMove.x;
				c_mouseY = event.mouseMove.y;
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == KEY_SHOW_HIDE_MENU)
					showMenu = (showMenu) ? false : true;
				if (event.key.code == KEY_PAUSE_CONTINUE)
				{
					if (applicationPaused)
						lastTime += pauseClocks.getElapsedTime();
					else
						pauseClocks.restart();
					applicationPaused = (applicationPaused) ? false : true;
				}
				if (event.key.code == KEY_SCREENSHOT)
					takeScreenshot();
				if (event.key.code == KEY_SWITCH_COLOR)
					changeColorScheme();
				if (event.key.code == KEY_GP_WEIGHT_UP)
					setGravityPointWeigthUp();
				if (event.key.code == KEY_GP_WEIGHT_DOWN)
					setGravityPointWeigthDown();
				if (event.key.code == KEY_GRAVITY_UP)
					setGravitationUp();
				if (event.key.code == KEY_GRAVITY_DOWN)
					setGravitationDown();
				if (event.key.code == KEY_PARTICLE_COLORTRANS_LENGTHPLUS)
					setColorTransientLengthUp();
				if (event.key.code == KEY_PARTICLE_COLORTRANS_LENGTHMINUS)
					setColorTransientLengthDown();
				if (event.key.code == KEY_PARTICLE_SIZE_UP)
					setParticleSizeUp();
				if (event.key.code == KEY_PARTICLE_SIZE_DOWN)
					setParticleSizeDown();
				if (event.key.code == KEY_PARTICLE_ALPHA_UP)
					setParticleAlphaUp();
				if (event.key.code == KEY_PARTICLE_ALPHA_DOWN)
					setParticleAlphaDown();
				if (event.key.code == KEY_GP_AUTOFORCE_SWITCH)
					switchGravityPointForceActive();
				if (event.key.code == KEY_DRAWMODE_SWITCH)
					(isDotMode()) ? setDotMode(false) : setDotMode(true);
				if (event.key.code == KEY_PARTICLE_COUNT_UP)
					setParticleCountUp();
				if (event.key.code == KEY_PARTICLE_COUNT_DOWN)
					setParticleCountDown();
			}
		}

		c_rightButtonClicked = (sf::Mouse::isButtonPressed(sf::Mouse::Right)) ? true : false;
		if (!applicationPaused)
		{
			if (automaticColorSchemeChange && rand() % 100 == 10)
			{
				changeColorScheme();
				cout << "scheme changed" << std::endl;
			}

			framerate = 1 / (clock.getElapsedTime() - lastTime).asSeconds();

			lastTime = clock.getElapsedTime();

			particleGroup.applyPhysics(&particlePhysics, gravityPoint);
			particleGroup.processData(framerate);
			particleGroup.checkBounds();
			gravityPoint->calcNextPosition(framerate);
			particleColorManager.updateColors(&particleGroup, framerate);
			circleEmitter.setEmitLocation(gravityPoint->getPosition());
			if (dotMode)
				appWindow.clear(sf::Color::Black);
			particleGroup.paint(&appWindow);
			if (clockGui.getElapsedTime().asMicroseconds() >= 5000)
			{
				sfguiWindow->Update(static_cast<float>(clockGui.getElapsedTime().asMicroseconds()) / 1000000.f);
				panelBox->updateGuiByValues();
				clockGui.restart();
			}

			if (toTakePicture)
				takeScreenshot();
			if (showMenu)
				sfgui.Display(appWindow);
			appWindow.display();
		}
		else
			(usleep(100000));
	}
	return 0;
}

ParticleSystem::~ParticleSystem()
{
	// TODO Auto-generated destructor stub
}

