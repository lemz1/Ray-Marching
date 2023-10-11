#pragma once

#include <functional>

#include "../Core/EventListener.h"
#include "MouseMoveEvent.h"

class MouseMoveEventListener : public EventListener
{
public:
	MouseMoveEventListener(std::function<void(const MouseMoveEvent&)> eventCallback)
		: EventListener(EventType::MouseMove), m_EventCallback(eventCallback)
	{}

	void TriggerEventCallback(const Event& event) override;
private:
	std::function<void(const MouseMoveEvent&)> m_EventCallback;
};