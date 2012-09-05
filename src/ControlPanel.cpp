/*
 * SfguiController.cpp
 *
 *  Created on: Sep 5, 2012
 *      Author: stashell
 */

#include "ControlPanel.h"

namespace sfg
{
ControlPanel::ControlPanel(ParticleSystem* p_particleSystem, sfg::Box::Orientation p_orientation, float p_spacing)
				: Box (p_orientation, p_spacing),
				  particleSystem(p_particleSystem)
{

	this->Pack(sfg::Label::Create("--- Gravitation settings ---"));
	this->Pack(gravity_label = sfg::Label::Create());
	this->Pack(gravityScrollbar = getScrollbar(0, 50.f, 0.2f, 5.f, &ControlPanel::gravityChange, this));
}

ControlPanel::Ptr ControlPanel::Create(ParticleSystem* p_particleSystem, sfg::Box::Orientation p_orientation, float p_spacing)
{
	ControlPanel::Ptr ptr( new ControlPanel( p_particleSystem, p_orientation, p_spacing ) );
	return ptr;
}

ControlPanel::~ControlPanel()
{
	// TODO Auto-generated destructor stub
}

void ControlPanel::gravityChange()
{
	float gravitation = gravityScrollbar->GetAdjustment()->GetValue();
	particleSystem->setGravitation(gravitation);
	gravity_label->SetText("Gravity : " + getString(gravitation));
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
}
