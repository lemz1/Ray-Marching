#pragma once

#include <functional>

#include "EventListener.h"
#include "MouseButtonEvent.h"

class MouseButtonEventListener : public EventListener
{
public:
	MouseButtonEventListener(std::function<void(const MouseButtonEvent&)> eventCallback)
		: EventListener(EventType::MouseButton), m_EventCallback(eventCallback)
	{}

	void TriggerEventCallback(const Event& event) override;
private:
	std::function<void(const MouseButtonEvent&)> m_EventCallback;
};