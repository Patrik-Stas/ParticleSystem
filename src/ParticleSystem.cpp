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

const float ParticleSystem::DEFAULT_GRAVITY = 4.5;
const float ParticleSystem::DEFAULT_GRAVITYPOINT_WEIGHT = 50000;
const float ParticleSystem::DEFAULT_PARTICLE_WEIGHT = 1;
const float ParticleSystem::DEFAULT_PARTICLE_SCALEDSIZE = 0.04;
const float ParticleSystem::DEFAULT_PARTICLE_ALPHA = 100;
const float ParticleSystem::DEFAULT_PARTICLES_COUNT = 24000;
const float ParticleSystem::DEFAULT_TRANSIENT_LENGTH = 0.3;
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
const sf::Keyboard::Key ParticleSystem::KEY_PARTICLE_ALPHA_UP =  sf::Keyboard::J;
const sf::Keyboard::Key ParticleSystem::KEY_PARTICLE_ALPHA_DOWN =  sf::Keyboard::N;
const sf::Keyboard::Key ParticleSystem::KEY_GP_AUTOFORCE_SWITCH = sf::Keyboard::Space;
const sf::Keyboard::Key ParticleSystem::KEY_PARTICLE_COLORTRANS_LENGTHPLUS = sf::Keyboard::R;
const sf::Keyboard::Key ParticleSystem::KEY_PARTICLE_COLORTRANS_LENGTHMINUS = sf::Keyboard::E;
const sf::Keyboard::Key ParticleSystem::KEY_DRAWMODE_SWITCH = sf::Keyboard::L;

const Color ParticleSystem::DEFAULT_GRAVITYPOINT_COLOR = Color(0, 255, 255, 200);
const BOUND_ACTION ParticleSystem::DEFAULT_BOUND_ACTION = bound_stop;
sf::RenderWindow ParticleSystem::appWindow(sf::VideoMode(ParticleSystem::SCREEN_WIDTH, ParticleSystem::SCREEN_HEIGHT),
		"SFML Shapes");
sf::Sprite ParticleSystem::DEFAULT_PARTICLE_SPRITE = getDefaultParticleSprite();

ShapeCircle circle(Point(200, 200), 60);
Emitter ParticleSystem::circleEmitter = Emitter(&circle);

ParticleSystem::ParticleSystem() :
		moveableArea(Point(0, 0), SCREEN_WIDTH, SCREEN_HEIGHT-7 )
{
	automatedMovingObject.setMoveableArea(&moveableArea);
	automatedGravityPoint.setAutomatedMovingObject(&automatedMovingObject);
	mouseControllGravityPoint.setMouseVariables(&c_mouseX, &c_mouseY, &c_rightButtonClicked);

	gravityPoint = &mouseControllGravityPoint;
	showMenu = true;
	automaticColorSchemeChange = false;

	particlePhysics.setGravityPoint(&gravityPoint);
	particlePhysics.setGravitation(1.0f);
	particlePhysics.setDownForce(false);

	particleGroup.setParticlePhysics(&particlePhysics);
	particleGroup.setMoveableArea(&moveableArea);
	particleGroup.setBoundAction(DEFAULT_BOUND_ACTION);
	particleGroup.setEmitter(&circleEmitter);
	particleGroup.setDefaultWeight(1.0f);
	particleGroup.setDefaultScaledSize(1.0f);
	particleGroup.setParticleSprite(DEFAULT_PARTICLE_SPRITE);

	appWindow.resetGLStates();
	mainFont = loadMainFont();
	fpsText.setFont(mainFont);
	fpsText.setCharacterSize(30);
	fpsText.setPosition(300, 100);

	sfguiWindow = sfg::Window::Create();
	main_box = sfg::Box::Create(sfg::Box::VERTICAL);

	main_box->Pack(sfg::Label::Create("--- Gravitation settings ---"));
	main_box->Pack(gravity_label = sfg::Label::Create());
	main_box->Pack(gravityScrollbar = getScrollbar(0, 50.f, 0.2f, 5.f, &ParticleSystem::gravityChange, this));
	main_box->Pack(gravityPointWeightLabel = sfg::Label::Create());
	main_box->Pack(gravityPointWeightScrollbar = getScrollbar(0, 200000.f, 10000.f, 30000.f, &ParticleSystem::gravityPointWeightChange,
			this));
	planetaryGravity = sfg::CheckButton::Create("Planetary gravity");
	planetaryGravity->GetSignal(sfg::ToggleButton::OnToggle).Connect(&ParticleSystem::SwitchDownForce, this);
	main_box->Pack(planetaryGravity);

	stop = sfg::RadioButton::Create("Stop");
	respawn = sfg::RadioButton::Create("Respawn", stop->GetGroup());
	mirrorPort = sfg::RadioButton::Create("Mirror", stop->GetGroup());
	kill = sfg::RadioButton::Create("Kill", stop->GetGroup());

	stop->GetSignal(sfg::ToggleButton::OnToggle).Connect(&ParticleSystem::ParticleBoundaryAction, this);
	respawn->GetSignal(sfg::ToggleButton::OnToggle).Connect(&ParticleSystem::ParticleBoundaryAction, this);
	mirrorPort->GetSignal(sfg::ToggleButton::OnToggle).Connect(&ParticleSystem::ParticleBoundaryAction, this);
	kill->GetSignal(sfg::ToggleButton::OnToggle).Connect(&ParticleSystem::ParticleBoundaryAction, this);

	main_box->Pack(sfg::Label::Create("--- Particle boundary action ---"));
	main_box->Pack(stop);
	main_box->Pack(respawn);
	main_box->Pack(mirrorPort);
	main_box->Pack(kill);
	main_box->Pack(particleSizeLabel = sfg::Label::Create("Particle size :"));
	main_box->Pack(particleSizeScrollbar = getScrollbar(0.01, 1.f, 0.01f, 0.025f, &ParticleSystem::particleSizeChange, this));
	main_box->Pack(particleCountLabel = sfg::Label::Create("Particle count :"));
	main_box->Pack(particleCountScrollbar = getScrollbar(1, 60000, 2000, 5000, &ParticleSystem::particleCountChange, this));
	main_box->Pack(particleAlphaLabel = sfg::Label::Create("Particle opacity : "));
	main_box->Pack(particleAlphaScrollbar = getScrollbar(0, 255.f, 2.f, 8.f, &ParticleSystem::particleAlphaChange, this));

	switchColorScheme = sfg::Button::Create("Change color scheme");
	switchColorScheme->GetSignal(sfg::Widget::OnLeftClick).Connect(&ParticleSystem::changeColorScheme, this);
	main_box->Pack(switchColorScheme);

	autoColorSchemeToggleButton = sfg::ToggleButton::Create("Change color scheme automatically");
	autoColorSchemeToggleButton->GetSignal(sfg::Widget::OnLeftClick).Connect(
			&ParticleSystem::autoColorSchemeChangeToggleButtonAction, this);
	main_box->Pack(autoColorSchemeToggleButton);


	main_box->Pack(colorTransientLengthLabel = sfg::Label::Create("Color transient speed (secs) : "));
	main_box->Pack(colorTransientLengthScrollbar = getScrollbar(0, 3.f, 0.3f, 1.f, &ParticleSystem::colorTransientLengthChange, this));

	takePictureButton = sfg::Button::Create("Take picture");
	takePictureButton->GetSignal(sfg::Widget::OnLeftClick).Connect(&ParticleSystem::buttonActionTakeScreenshot, this);
	main_box->Pack(takePictureButton);

	dotDrawMode = sfg::RadioButton::Create("DotDrawMode");
	paintDrawMode = sfg::RadioButton::Create("PaintDrawMode", dotDrawMode->GetGroup());
	dotDrawMode->GetSignal(sfg::ToggleButton::OnToggle).Connect(&ParticleSystem::drawModeChangeAction, this);
	paintDrawMode->GetSignal(sfg::ToggleButton::OnToggle).Connect(&ParticleSystem::drawModeChangeAction, this);
	dotDrawMode->SetActive(true);

	main_box->Pack(dotDrawMode);
	main_box->Pack(paintDrawMode);

	sfguiWindow->Add(main_box);
	sfguiWindow->SetPosition(sf::Vector2f(SCREEN_WIDTH - sfguiWindow->GetRequisition().x, 0));

	respawn->SetActive(true);
	particleAlphaScrollbar->GetAdjustment()->SetValue(DEFAULT_PARTICLE_ALPHA);
	gravityScrollbar->GetAdjustment()->SetValue(DEFAULT_GRAVITY);
	gravityPointWeightScrollbar->GetAdjustment()->SetValue(DEFAULT_GRAVITYPOINT_WEIGHT);
	particleSizeScrollbar->GetAdjustment()->SetValue(DEFAULT_PARTICLE_SCALEDSIZE);
	particleCountScrollbar->GetAdjustment()->SetValue(DEFAULT_PARTICLES_COUNT);
	colorTransientLengthScrollbar->GetAdjustment()->SetValue(DEFAULT_TRANSIENT_LENGTH);
	stop->SetActive(true);
	autoColorSchemeToggleButton->SetActive(false);

	automaticGravityPointMode = sfg::RadioButton::Create("Automatic GravityPoint mode");
	;
	manualGravityPointMode = sfg::RadioButton::Create("Manual GravityPoint mode",
			automaticGravityPointMode->GetGroup());
	automaticGravityPointMode->GetSignal(sfg::ToggleButton::OnToggle).Connect(&ParticleSystem::changeGravityPointMode,
			this);
	manualGravityPointMode->GetSignal(sfg::ToggleButton::OnToggle).Connect(&ParticleSystem::changeGravityPointMode,
			this);
	main_box->Pack(automaticGravityPointMode);
	main_box->Pack(manualGravityPointMode);

	manualGravityPointMode->SetActive(true);
	dotDrawMode->SetActive(true);
	srand(time(NULL));
	colorTransientLengthChange();
	changeColorScheme();
	drawModeChangeAction();
	ParticleBoundaryAction();
	gravityChange();
	gravityPointWeightChange();
	particleCountChange();
	particleSizeChange();
	ParticleBoundaryAction();

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
sfg::Scrollbar::Ptr ParticleSystem::getScrollbar(float lowerValue, float upperValue, float minorStep, float majorStep,
		void (ParticleSystem::*function)(), ParticleSystem* object)
{
	sfg::Scrollbar::Ptr ptr = sfg::Scrollbar::Create(sfg::Scrollbar::HORIZONTAL);
	ptr->GetAdjustment()->SetLower(lowerValue);
	ptr->GetAdjustment()->SetUpper(upperValue);
	ptr->GetAdjustment()->SetMinorStep(minorStep);
	ptr->GetAdjustment()->SetMajorStep(majorStep);
	ptr->GetAdjustment()->GetSignal(sfg::Adjustment::OnChange).Connect(function, object);
	ptr->SetRequisition(sf::Vector2f(100.f, 2.f));
	return ptr;
}
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

void ParticleSystem::particleCountChange()
{
	int particlesCount = particleCountScrollbar->GetAdjustment()->GetValue();
	particleGroup.setParticlesCount(particlesCount);
	particleCountLabel->SetText("Particle count : " + getString(particlesCount));
}
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

void ParticleSystem::particleSizeChange()
{
	float particleSize = particleSizeScrollbar->GetAdjustment()->GetValue();
	particleGroup.setScaledSize(particleSize);
	particleSizeLabel->SetText("Particle size : " + getString(particleSize));
}

void ParticleSystem::particleSizeUp()
{
	particleSizeScrollbar->GetAdjustment()->Increment();
}

void ParticleSystem::particleSizeDown()
{
	particleSizeScrollbar->GetAdjustment()->Decrement();
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void ParticleSystem::gravityChange()
{
	float gravitation = gravityScrollbar->GetAdjustment()->GetValue();
	particlePhysics.setGravitation(gravitation);
	gravity_label->SetText("Gravity : " + getString(gravitation));
}

void ParticleSystem::gravityUp()
{
	gravityScrollbar->GetAdjustment()->Increment();
}

void ParticleSystem::gravityDown()
{
	gravityScrollbar->GetAdjustment()->Decrement();
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void ParticleSystem::gravityPointWeightChange()
{
	gravityPoint->setWeight(gravityPointWeightScrollbar->GetAdjustment()->GetValue());
	gravityPointWeightLabel->SetText("GP weight : " + getString(gravityPoint->getWeight()));
}

void ParticleSystem::gravityPointWeightUp()
{
	gravityPointWeightScrollbar->GetAdjustment()->Increment();
}

void ParticleSystem::gravityPointWeightDown()
{
	gravityPointWeightScrollbar->GetAdjustment()->Decrement();
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

void ParticleSystem::colorTransientLengthChange()
{
	particleColorManager.setTrasitionLength(colorTransientLengthScrollbar->GetAdjustment()->GetValue());
	colorTransientLengthLabel->SetText("Color transient speed (secs) : " + getString(particleColorManager.getTrasitionLength()));
}

void ParticleSystem::colorTransientLengthUp()
{
	colorTransientLengthScrollbar->GetAdjustment()->Increment();
}

void ParticleSystem::colorTransientLengthDown()
{
	colorTransientLengthScrollbar->GetAdjustment()->Decrement();
}

/*
void ParticleSystem::particleSizeUp(int val)
{
	int newWeight = gravityPointWeightScrollbar->GetAdjustment()->GetValue() + val;
	gravityPointWeightScrollbar->GetAdjustment()->SetValue(newWeight);
	gravityPointWeightChange();
}

void ParticleSystem::particleSizeDown(int val)
{
	int newWeight = gravityPointWeightScrollbar->GetAdjustment()->GetValue() - val;
	gravityPointWeightScrollbar->GetAdjustment()->SetValue(newWeight);
	gravityPointWeightChange();
}


void ParticleSystem::particleAlphaUp(int val)
{
	int newWeight = gravityPointWeightScrollbar->GetAdjustment()->GetValue() + val;
	gravityPointWeightScrollbar->GetAdjustment()->SetValue(newWeight);
	gravityPointWeightChange();
}

void ParticleSystem::particleAlphaDown(int val)
{
	int newWeight = gravityPointWeightScrollbar->GetAdjustment()->GetValue() - val;
	gravityPointWeightScrollbar->GetAdjustment()->SetValue(newWeight);
	gravityPointWeightChange();
}

void ParticleSystem::colorTransientSpeedUp(int val)
{
	int newWeight = gravityPointWeightScrollbar->GetAdjustment()->GetValue() + val;
	gravityPointWeightScrollbar->GetAdjustment()->SetValue(newWeight);
	gravityPointWeightChange();
}

void ParticleSystem::colorTransientSpeedDown(int val)
{
	int newWeight = gravityPointWeightScrollbar->GetAdjustment()->GetValue() - val;
	gravityPointWeightScrollbar->GetAdjustment()->SetValue(newWeight);
	gravityPointWeightChange();
}*/
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


void ParticleSystem::particleAlphaChange()
{
	int alpha = particleAlphaScrollbar->GetAdjustment()->GetValue();
	particleGroup.setAlpha(alpha);
	particleAlphaLabel->SetText("Particle opacity : " + getString(alpha));
}

void ParticleSystem::particleAlphaUp()
{
	 particleAlphaScrollbar->GetAdjustment()->Increment();
}

void ParticleSystem::particleAlphaDown()
{
	particleAlphaScrollbar->GetAdjustment()->Decrement();
}


void ParticleSystem::SwitchDownForce()
{
	(particlePhysics.isDownForce()) ? particlePhysics.setDownForce(false) : particlePhysics.setDownForce(true);
}

void ParticleSystem::ParticleBoundaryAction()
{
	if (stop->IsActive())
		particleGroup.setBoundAction(bound_stop);
	else if (respawn->IsActive())
		particleGroup.setBoundAction(bound_respawn);
	else if (mirrorPort->IsActive())
		particleGroup.setBoundAction(bound_mirror_port);
	else if (kill->IsActive())
		particleGroup.setBoundAction(bound_kill);
}

void ParticleSystem::changeColorScheme()
{
	particleColorManager.changeColorScheme();
}

void ParticleSystem::autoColorSchemeChangeToggleButtonAction()
{
	automaticColorSchemeChange = (automaticColorSchemeChange) ? false : true;
}

void ParticleSystem::drawModeChangeAction()
{
	cout << "DRAW MODE CHANGED" << endl;
	if (dotDrawMode->IsActive())
		dotMode = true;
	if (paintDrawMode->IsActive())
		dotMode = false;
}

void ParticleSystem::switchDrawMode()
{
	if (dotMode) paintDrawMode->SetActive(true);
	else dotDrawMode->SetActive(true);
}

void ParticleSystem::buttonActionTakeScreenshot()
{
	toTakePicture = true;
}

void ParticleSystem::changeGravityPointMode()
{
	if (automaticGravityPointMode->IsActive())
		gravityPoint = &automatedGravityPoint;
	if (manualGravityPointMode->IsActive())
		gravityPoint = &mouseControllGravityPoint;
}



void ParticleSystem::takeScreenshot()
{
	sf::Image Screenshot;
	Screenshot = appWindow.capture();
	string actualTime = getActualTime();
	Screenshot.saveToFile("screenshots/screenshot" + actualTime + ".png");
	toTakePicture = false;
}

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
				if (event.key.code == KEY_DUMP_COLOR)
					particlePhysics.fileDump("Dump/ColorSchemas");
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
					gravityPointWeightUp();
				if (event.key.code == KEY_GP_WEIGHT_DOWN)
					gravityPointWeightDown();
				if (event.key.code == KEY_GRAVITY_UP)
					gravityUp();
				if (event.key.code == KEY_GRAVITY_DOWN)
					gravityDown();
				if (event.key.code == KEY_PARTICLE_COLORTRANS_LENGTHPLUS)
					colorTransientLengthUp();
				if (event.key.code == KEY_PARTICLE_COLORTRANS_LENGTHMINUS)
					colorTransientLengthDown();
				if (event.key.code == KEY_PARTICLE_SIZE_UP)
					particleSizeUp();
				if (event.key.code == KEY_PARTICLE_SIZE_DOWN)
					particleSizeDown();
				if (event.key.code == KEY_PARTICLE_ALPHA_UP)
					particleAlphaUp();
				if (event.key.code == KEY_PARTICLE_ALPHA_DOWN)
					particleAlphaDown();
				if (event.key.code == KEY_GP_AUTOFORCE_SWITCH)
					switchGravityPointForceActive();
				if (event.key.code == KEY_DRAWMODE_SWITCH)
					switchDrawMode();
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

			particleGroup.applyPhysics();
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

