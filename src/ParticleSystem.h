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
//class sfg::ControlPanel;

enum PARTICLE_ACTION
{
	STOP, RESPAWN, MIRROR_PORT
};

class ParticleSystem
{
public:
	ParticleSystem();
	int run();
	virtual ~ParticleSystem();
private:
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
	static const BOUND_ACTION DEFAULT_BOUND_ACTION;

	sfg::Scrollbar::Ptr getScrollbar(float lowerValue, float upperValue, float minorStep, float majorStep,
			void (ParticleSystem::*function)(), ParticleSystem* object);

	sf::Font mainFont;
	sf::Font loadMainFont();

	bool showMenu;

	int particleAlpha;
	sfg::Scrollbar::Ptr particleAlphaScrollbar;
	sfg::Label::Ptr particleAlphaLabel;
	void particleAlphaChange();
	void particleAlphaUp();
	void particleAlphaDown();

	sf::Texture particleTexture;
	sfg::Scrollbar::Ptr particleSizeScrollbar;
	sfg::Label::Ptr particleSizeLabel;
	void particleSizeChange();
	void particleSizeUp();
	void particleSizeDown();

	sf::Text fpsText;

	sfg::Scrollbar::Ptr gravityScrollbar;
	sfg::Label::Ptr gravity_label;
	void setGravitationUp();
	void setGravitationDown();
	void setGravitation(float p_gravitation);

	GravityPoint* gravityPoint;
	AutomatedGravityPoint automatedGravityPoint;
	AutomatedMovingObject automatedMovingObject;
	MouseControllGravityPoint mouseControllGravityPoint;

	sfg::Scrollbar::Ptr gravityPointWeightScrollbar;
	sfg::Label::Ptr gravityPointWeightLabel;
	void gravityPointWeightChange();
	void gravityPointWeightUp();
	void gravityPointWeightDown();

	sfg::CheckButton::Ptr planetaryGravity;
	void SwitchDownForce();

	sfg::Scrollbar::Ptr particleCountScrollbar;
	sfg::Label::Ptr particleCountLabel;
	void particleCountChange();
	void particleCountUp();
	void particleCountDown();

	sfg::Scrollbar::Ptr colorTransientLengthScrollbar;
	sfg::Label::Ptr colorTransientLengthLabel;
	void colorTransientLengthChange();
	void colorTransientLengthUp();
	void colorTransientLengthDown();

	PARTICLE_ACTION boundaryParticleAction;
	sfg::RadioButton::Ptr stop;
	sfg::RadioButton::Ptr respawn;
	sfg::RadioButton::Ptr mirrorPort;
	sfg::RadioButton::Ptr kill;
	void ParticleBoundaryAction();

	sfg::Button::Ptr switchColorScheme;
	void changeColorScheme();

	bool automaticColorSchemeChange;
	sfg::ToggleButton::Ptr autoColorSchemeToggleButton;
	void autoColorSchemeChangeToggleButtonAction();

	bool toTakePicture;
	void takeScreenshot();
	void buttonActionTakeScreenshot();
	sfg::Button::Ptr takePictureButton;

	void drawModeChangeAction();
	void switchDrawMode();
	bool dotMode;
	sfg::RadioButton::Ptr dotDrawMode;
	sfg::RadioButton::Ptr paintDrawMode;

	void changeGravityPointMode();
	sfg::RadioButton::Ptr automaticGravityPointMode;
	sfg::RadioButton::Ptr manualGravityPointMode;

	void switchGravityPointForceActive();
	sfg::Box::Ptr main_box;
	sfg::ControlPanel::Ptr controlPanel;

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
