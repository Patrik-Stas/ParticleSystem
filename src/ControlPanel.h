/*
 * SfguiController.h
 *
 *  Created on: Sep 5, 2012
 *      Author: stashell
 */

#ifndef SFGUICONTROLLER_H_
#define SFGUICONTROLLER_H_

#include <SFGUI/SFGUI.hpp>
#include "ParticleActionEnum.h"

class ParticleSystem;

class ControlPanel
{
public:

	static ControlPanel* getControlPanel(ParticleSystem* particleSystem, sfg::Box::Orientation p_orientation, float p_spacing);
	sfg::Box::Ptr getBox();
	void updateGuiByValues();

private:



	ControlPanel(ParticleSystem* particleSystem, sfg::Box::Orientation p_orientation, float p_spacing);

	ParticleSystem* particleSystem;


	// GRAVITY
	sfg::Scrollbar::Ptr gravityScrollbar;
	sfg::Label::Ptr gravity_label;
	void gravityGuiChange();
	void gravitySliderGuiUpdate();
	sfg::Box::Ptr panelBox;

	// GP WEIGHT
	sfg::Scrollbar::Ptr gravityPointWeightScrollbar;
	sfg::Label::Ptr gravityPointWeightLabel;
	void gravityPointWeightGuiChange();
	void gravityPointSliderGuiUpdate();

	sfg::CheckButton::Ptr sideGravity;
	void sideGravityGuiChange();
	void sideGravitySliderGuiUpdate();

	// BOUNDARY ACTION
	sfg::RadioButton::Ptr stop;
	sfg::RadioButton::Ptr respawn;
	sfg::RadioButton::Ptr mirrorPort;
	sfg::RadioButton::Ptr kill;
	void boundaryActionGuiChange();
	void boundaryActionGuiUpdate();

	// PARTICLE SIZE
	sfg::Scrollbar::Ptr particleSizeScrollbar;
	sfg::Label::Ptr particleSizeLabel;
	void particleSizeGuiChange();
	void particleSizeGuiUpdate();

	// PARTICLE COUNT
	sfg::Scrollbar::Ptr particleCountScrollbar;
	sfg::Label::Ptr particleCountLabel;
	void particleCountGuiChange();
	void particleCountGuiUpdate();

	// PARTICLE ALPHA
	sfg::Scrollbar::Ptr particleAlphaScrollbar;
	sfg::Label::Ptr particleAlphaLabel;
	void particleAlphaGuiChange();
	void particleAlphaGuiUpdate();

	// COLOR SCHEME ChANGE BUTTON
	sfg::Button::Ptr changeColorSchemeButton;
	void changeColorScheme();

	// COLOR AUTOCHNAGE SWITCH BUTTON
	sfg::ToggleButton::Ptr autoColorSchemeToggleButton;
	void autoColorSchemeGuiChange();

	// DRAW MODE
	sfg::RadioButton::Ptr dotDrawMode;
	sfg::RadioButton::Ptr paintDrawMode;
	void drawModeGuiChange();
	void drawModeGuiUpdate();

	// DRAW MODE
	sfg::RadioButton::Ptr mouseGravityPoint;
	sfg::RadioButton::Ptr autoGravityPoint;
	void gravityPointModeGuiChange();
	void gravityPointModeGuiUpdate();


	static sfg::Scrollbar::Ptr getScrollbar(float lowerValue, float upperValue, float minorStep, float majorStep,
			void (ControlPanel::*function)(), ControlPanel* object);
};

#endif /* SFGUICONTROLLER_H_ */
