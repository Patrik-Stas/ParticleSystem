/*
 * SfguiController.cpp
 *
 *  Created on: Sep 5, 2012
 *      Author: stashell
 */

#include "ControlPanel.h"
#include "ParticleSystem.h"
#include "Misc.h"
#include <iostream>

using std::cout;
using std::endl;
using std::cerr;

ControlPanel::ControlPanel(ParticleSystem* p_particleSystem, sfg::Box::Orientation p_orientation, float p_spacing) :
		particleSystem(p_particleSystem)
{
	// GRAVITY
	panelBox = sfg::Box::Create(p_orientation, p_spacing);
	panelBox->Pack(sfg::Label::Create("--- Gravitation settings ---"));
	panelBox->Pack(gravity_label = sfg::Label::Create());
	panelBox->Pack(gravityScrollbar = getScrollbar(0, 50.f, 0.2f, 5.f, &ControlPanel::gravityGuiChange, this));

	// GRAVITY POINT WEIGHT
	panelBox->Pack(gravityPointWeightLabel = sfg::Label::Create());
	panelBox->Pack(
			gravityPointWeightScrollbar = getScrollbar(0, 200000.f, 10000.f, 30000.f,
					&ControlPanel::gravityPointWeightGuiChange, this));

	// SIDE GRAVITY
	sideGravity = sfg::CheckButton::Create("Planetary gravity");
	sideGravity->GetSignal(sfg::ToggleButton::OnToggle).Connect(&ControlPanel::sideGravityGuiChange, this);
	panelBox->Pack(sideGravity);

	// BOUND ACTION
	stop = sfg::RadioButton::Create("Stop");
	respawn = sfg::RadioButton::Create("Respawn", stop->GetGroup());
	mirrorPort = sfg::RadioButton::Create("Mirror", stop->GetGroup());
	kill = sfg::RadioButton::Create("Kill", stop->GetGroup());
	stop->GetSignal(sfg::ToggleButton::OnToggle).Connect(&ControlPanel::boundaryActionGuiChange, this);
	respawn->GetSignal(sfg::ToggleButton::OnToggle).Connect(&ControlPanel::boundaryActionGuiChange, this);
	mirrorPort->GetSignal(sfg::ToggleButton::OnToggle).Connect(&ControlPanel::boundaryActionGuiChange, this);
	kill->GetSignal(sfg::ToggleButton::OnToggle).Connect(&ControlPanel::boundaryActionGuiChange, this);
	panelBox->Pack(sfg::Label::Create("--- Particle boundary action ---"));
	panelBox->Pack(stop);
	panelBox->Pack(respawn);
	panelBox->Pack(mirrorPort);
	panelBox->Pack(kill);

	// PARTICLE SIZE
	panelBox->Pack(particleSizeLabel = sfg::Label::Create("Particle size :"));
	panelBox->Pack(
			particleSizeScrollbar = getScrollbar(0.01, 1.f, 0.01f, 0.025f, &ControlPanel::particleSizeGuiChange, this));

	// PARTICLE COUNT
	panelBox->Pack(particleCountLabel = sfg::Label::Create("Particle count :"));
	panelBox->Pack(
			particleCountScrollbar = getScrollbar(1, 60000, 2000, 5000, &ControlPanel::particleCountGuiChange, this));
	panelBox->Pack(particleAlphaLabel = sfg::Label::Create("Particle opacity : "));
	panelBox->Pack(
			particleAlphaScrollbar = getScrollbar(0, 255.f, 2.f, 8.f, &ControlPanel::particleAlphaGuiChange, this));

	// COLOR CHANGE BUTTON
	changeColorSchemeButton = sfg::Button::Create("Change color scheme");
	changeColorSchemeButton->GetSignal(sfg::Widget::OnLeftClick).Connect(&ControlPanel::changeColorScheme, this);
	panelBox->Pack(changeColorSchemeButton);

	// COLOR AUTOCHNAGE SWITCH BUTTON
	autoColorSchemeToggleButton = sfg::ToggleButton::Create("Change color scheme automatically");
	autoColorSchemeToggleButton->GetSignal(sfg::Widget::OnLeftClick).Connect(&ControlPanel::autoColorSchemeGuiChange,
			this);
	panelBox->Pack(autoColorSchemeToggleButton);

	// DRAW MODE
	dotDrawMode = sfg::RadioButton::Create("DotDrawMode");
	paintDrawMode = sfg::RadioButton::Create("PaintDrawMode", dotDrawMode->GetGroup());
	dotDrawMode->GetSignal(sfg::ToggleButton::OnToggle).Connect(&ControlPanel::drawModeGuiChange, this);
	paintDrawMode->GetSignal(sfg::ToggleButton::OnToggle).Connect(&ControlPanel::drawModeGuiChange, this);
	panelBox->Pack(dotDrawMode);
	panelBox->Pack(paintDrawMode);

	mouseGravityPoint = sfg::RadioButton::Create("Mouse gravityPoint mode");
	autoGravityPoint = sfg::RadioButton::Create("Auto gravityPoint mode", mouseGravityPoint->GetGroup());
	mouseGravityPoint->GetSignal(sfg::ToggleButton::OnToggle).Connect(&ControlPanel::gravityPointModeGuiChange, this);
	autoGravityPoint->GetSignal(sfg::ToggleButton::OnToggle).Connect(&ControlPanel::gravityPointModeGuiChange, this);
	panelBox->Pack(mouseGravityPoint);
	panelBox->Pack(autoGravityPoint);

}

ControlPanel* ControlPanel::getControlPanel(ParticleSystem* p_particleSystem, sfg::Box::Orientation p_orientation,
		float p_spacing)
{
	return new ControlPanel(p_particleSystem, p_orientation, p_spacing);
}

sfg::Box::Ptr ControlPanel::getBox()
{
	return panelBox;
}

// ==================================================================
void ControlPanel::gravityGuiChange()
{
	float gravitation = gravityScrollbar->GetAdjustment()->GetValue();
	particleSystem->setGravitation(gravitation);
	gravity_label->SetText("Gravity : " + getString(gravitation));
}
void ControlPanel::gravitySliderGuiUpdate()
{
	gravityScrollbar->GetAdjustment()->SetValue(particleSystem->getGravitation());
}
// ==================================================================
void ControlPanel::gravityPointWeightGuiChange()
{
	float gpWeight = gravityPointWeightScrollbar->GetAdjustment()->GetValue();
	particleSystem->setGravityPointWeigth(gpWeight);
	gravityPointWeightLabel->SetText("GP weight : " + getString(gpWeight));
}
void ControlPanel::gravityPointSliderGuiUpdate()
{
	gravityPointWeightScrollbar->GetAdjustment()->SetValue(particleSystem->getGravityPointWeigth());
}
// ==================================================================
void ControlPanel::boundaryActionGuiChange()
{
	if (stop->IsActive())
		particleSystem->setParticleBoundaryAction(STOP);
	else if (respawn->IsActive())
		particleSystem->setParticleBoundaryAction(RESPAWN);
	else if (mirrorPort->IsActive())
		particleSystem->setParticleBoundaryAction(MIRROR_PORT);
	else if (kill->IsActive())
		particleSystem->setParticleBoundaryAction(DISAPPEAR);
}
void ControlPanel::boundaryActionGuiUpdate()
{
	//particleSystem->getParticleBoundaryAction();
	cerr << "not imeplented boundaryActionGuiUpdate" << endl;
	//abort();
}
// ==================================================================
void ControlPanel::sideGravityGuiChange()
{
	particleSystem->setSideGravity(sideGravity->IsActive());
}
void ControlPanel::sideGravitySliderGuiUpdate()
{
	sideGravity->SetActive(particleSystem->isSideGravity());
}
// ==================================================================

void ControlPanel::particleSizeGuiChange()
{
	float particleSize = particleSizeScrollbar->GetAdjustment()->GetValue();
	particleSystem->setParticleSize(particleSize);
	particleSizeLabel->SetText("Particle size : " + getString(particleSize));
}

void ControlPanel::particleSizeGuiUpdate()
{
	particleSizeScrollbar->GetAdjustment()->SetValue(particleSystem->getParticleSize());
}
// ==================================================================
void ControlPanel::particleCountGuiChange()
{
	int particlesCount = particleCountScrollbar->GetAdjustment()->GetValue();
	particleSystem->setParticleCount(particlesCount);
	particleCountLabel->SetText("Particle count : " + getString(particlesCount));
}

void ControlPanel::particleCountGuiUpdate()
{
	particleCountScrollbar->GetAdjustment()->SetValue(particleSystem->getParticleCount());
}
// ==================================================================
void ControlPanel::particleAlphaGuiChange()
{
	int alpha = particleAlphaScrollbar->GetAdjustment()->GetValue();
	particleSystem->setParticleAlpha(alpha);
	particleAlphaLabel->SetText("Particle opacity : " + getString(alpha));
}

void ControlPanel::particleAlphaGuiUpdate()
{
	particleAlphaScrollbar->GetAdjustment()->SetValue(particleSystem->getParticleAlpha());
}
// ==================================================================
void ControlPanel::changeColorScheme()
{
	particleSystem->changeColorScheme();
}
// ==================================================================
void ControlPanel::autoColorSchemeGuiChange()
{
	if (autoColorSchemeToggleButton->IsActive())
		particleSystem->setAutoColorScheme(true);
	else
		particleSystem->setAutoColorScheme(false);
}
// ==================================================================
void ControlPanel::drawModeGuiChange()
{
	if (dotDrawMode->IsActive())
		particleSystem->setDotMode(true);
	if (paintDrawMode->IsActive())
		particleSystem->setDotMode(false);
}
void ControlPanel::drawModeGuiUpdate()
{
	if (particleSystem->isDotMode())
		dotDrawMode->SetActive(true);
	else
		paintDrawMode->SetActive(true);
}
// ==================================================================
void ControlPanel::gravityPointModeGuiChange()
{
	(mouseGravityPoint->IsActive()) ?
			particleSystem->setMouseGravityPointMode(true) : particleSystem->setMouseGravityPointMode(false);
}
void ControlPanel::gravityPointModeGuiUpdate()
{
	if (particleSystem->isMouseGravityPointMode())
		mouseGravityPoint->SetActive(true);
	else
		autoGravityPoint->SetActive(true);
}

// ==================================================================
void ControlPanel::updateGuiByValues()
{
	gravitySliderGuiUpdate();
	gravityPointSliderGuiUpdate();
	sideGravitySliderGuiUpdate();
	particleSizeGuiUpdate();
	particleCountGuiUpdate();
	drawModeGuiUpdate();
	gravityPointModeGuiUpdate();
//	boundaryActionGuiUpdate();
}

sfg::Scrollbar::Ptr ControlPanel::getScrollbar(float lowerValue, float upperValue, float minorStep, float majorStep,
		void (ControlPanel::*function)(), ControlPanel* object)
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
