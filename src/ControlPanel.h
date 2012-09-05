/*
 * SfguiController.h
 *
 *  Created on: Sep 5, 2012
 *      Author: stashell
 */

#ifndef SFGUICONTROLLER_H_
#define SFGUICONTROLLER_H_

#include <SFGUI/SFGUI.hpp>

class ParticleSystem;

namespace sfg
{
class ControlPanel : public sfg::Box
{
public:

	typedef SharedPtr<ControlPanel> Ptr;
	typedef SharedPtr<const ControlPanel> PtrConst;

	ControlPanel(ParticleSystem* particleSystem, sfg::Box::Orientation p_orientation, float p_spacing);
	virtual ~ControlPanel();
	static ControlPanel::Ptr Create(ParticleSystem* particleSystem, sfg::Box::Orientation p_orientation, float p_spacing);

	static sfg::Scrollbar::Ptr getScrollbar(float lowerValue, float upperValue, float minorStep, float majorStep,
			void (ControlPanel::*function)(), ControlPanel* object);

	sfg::Scrollbar::Ptr gravityScrollbar;
	sfg::Label::Ptr gravity_label;
	void gravityChange();

	ParticleSystem* particleSystem;
};
}

#endif /* SFGUICONTROLLER_H_ */
