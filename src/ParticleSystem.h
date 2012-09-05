/*
 * ParticleSystem.h
 *
 *  Created on: Aug 23, 2012
 *      Author: stashell
 */

#ifndef PARTICLESYSTEM_H_
#define PARTICLESYSTEM_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <boost/lexical_cast.hpp>
#include <string>
#include <SFGUI/SFGUI.hpp>

#include "Gradient.h"
#include "Particle.h"
#include "ParticleSfmlPrimitive.h"
#include "ParticleGroup.h"
#include "ParticlePhysics.h"
#include "Emitter.h"
#include "MovingObject.h"
#include "AutomatedMovingObject.h"
#include "GravityPoint.h"
#include "AutomatedGravityPoint.h"
#include "MouseControllGravityPoint.h"
#include "ParticleColorManager.h"
#include "ControlPanel.h"
#include "ParticleActionEnum.h"

class ControlPanel;


class ParticleSystem
{
public:
	ParticleSystem();
	int run();
	virtual ~ParticleSystem();

	int c_mouseX;
	int c_mouseY;
	bool c_rightButtonClicked;

	static const int SCREEN_WIDTH;
	static const int SCREEN_HEIGHT;
	static const float DEFAULT_GRAVITY;
	static const float DEFAULT_GRAVITYPOINT_WEIGHT;
	static const float DEFAULT_PARTICLE_WEIGHT;
	static const float DEFAULT_PARTICLE_SCALEDSIZE;
	static const float DEFAULT_PARTICLES_COUNT;
	static const float DEFAULT_PARTICLE_ALPHA;
	static const float DEFAULT_COLORSCHEME_CHANGE_FREQUNCY;
	static const float DEFAULT_TRANSIENT_LENGTH;

	static const sf::Keyboard::Key KEY_SHOW_HIDE_MENU;
	static const sf::Keyboard::Key KEY_PAUSE_CONTINUE;
	static const sf::Keyboard::Key KEY_SCREENSHOT;
	static const sf::Keyboard::Key KEY_SWITCH_COLOR;
	static const sf::Keyboard::Key KEY_GP_AUTOFORCE_SWITCH;
	static const sf::Keyboard::Key KEY_DUMP_COLOR;
	static const sf::Keyboard::Key KEY_GP_WEIGHT_UP;
	static const sf::Keyboard::Key KEY_GP_WEIGHT_DOWN;
	static const sf::Keyboard::Key KEY_GRAVITY_UP;
	static const sf::Keyboard::Key KEY_GRAVITY_DOWN;
	static const sf::Keyboard::Key KEY_PARTICLE_COLORTRANS_LENGTHPLUS;
	static const sf::Keyboard::Key KEY_PARTICLE_COLORTRANS_LENGTHMINUS;
	static const sf::Keyboard::Key KEY_PARTICLE_COUNT_UP;
	static const sf::Keyboard::Key KEY_PARTICLE_COUNT_DOWN;
	static const sf::Keyboard::Key KEY_PARTICLE_SIZE_UP;
	static const sf::Keyboard::Key KEY_PARTICLE_SIZE_DOWN;
	static const sf::Keyboard::Key KEY_PARTICLE_ALPHA_UP;
	static const sf::Keyboard::Key KEY_PARTICLE_ALPHA_DOWN;
	static const sf::Keyboard::Key KEY_DRAWMODE_SWITCH;

	static const float PDEFAULT_GRAVITYPOINT_WEIGHT;
	static const Color DEFAULT_GRAVITYPOINT_COLOR;
	static sf::Sprite DEFAULT_PARTICLE_SPRITE;
	static sf::RenderWindow appWindow;
	static Emitter circleEmitter;
	static const PARTICLE_ACTION DEFAULT_BOUND_ACTION;

	sfg::Scrollbar::Ptr getScrollbar(float lowerValue, float upperValue, float minorStep, float majorStep,
			void (ParticleSystem::*function)(), ParticleSystem* object);

	sf::Font mainFont;
	sf::Font loadMainFont();

	bool showMenu;

	sf::Texture particleTexture;

	void setParticleSize(float p_size);
	float getParticleSize();
	void setParticleSizeUp();
	void setParticleSizeDown();

	void setGravitation(float p_gravitation);
	float getGravitation();
	void setGravitationUp();
	void setGravitationDown();

	void setGravityPointWeigth(float p_weight);
	float getGravityPointWeigth();
	void setGravityPointWeigthUp();
	void setGravityPointWeigthDown();

	bool sideGravity;
	void setSideGravity(bool p_sideGravity);
	bool isSideGravity();

	PARTICLE_ACTION getParticleBoundaryAction();
	void setParticleBoundaryAction(PARTICLE_ACTION action);
	PARTICLE_ACTION boundaryParticleAction;

	GravityPoint* gravityPoint;
	AutomatedGravityPoint automatedGravityPoint;
	AutomatedMovingObject automatedMovingObject;
	MouseControllGravityPoint mouseControllGravityPoint;


	void setParticleCount(int p_count);
	int getParticleCount();
	void setParticleCountUp();
	void setParticleCountDown();


	void setParticleAlpha(float p_alpha);
	float getParticleAlpha();
	void setParticleAlphaUp();
	void setParticleAlphaDown();

	void setColorTransientLength(float p_length);
	float getColorTransientLength();
	void setColorTransientLengthUp();
	void setColorTransientLengthDown();

	void changeColorScheme();

	bool automaticColorSchemeChange;
	void setAutoColorScheme(bool p_autoColorSchemeChange);
	bool isAutoColorScheme();

	bool toTakePicture;
	void takeScreenshot();
	void buttonActionTakeScreenshot();

	void setDotMode(bool p_dotMode);
	bool isDotMode();
	bool dotMode;

	void setMouseGravityPointMode(bool p_mouseGravityPointMode);
	bool isMouseGravityPointMode();

	void switchGravityPointForceActive();
	ControlPanel* panelBox;

	sfg::Window::Ptr sfguiWindow;
	sfg::SFGUI sfgui;

	void initializeGUI();

	ParticlePhysics particlePhysics;
	ParticleColorManager particleColorManager;
	ShapeRectangle moveableArea;
	ParticleGroup particleGroup;

	AutomatedMovingObject automaticMovingObject;

	bool applicationPaused;
};

#endif /* PARTICLESYSTEM_H_ */
