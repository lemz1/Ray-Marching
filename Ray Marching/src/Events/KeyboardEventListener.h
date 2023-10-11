#pragma once

#include <functional>

#include "../Core/EventListener.h"
#include "KeyboardEvent.h"

class KeyboardEventListener : public EventListener
{
public:
	KeyboardEventListener(std::function<void(const KeyboardEvent&)> eventCallback)
		: EventListener(EventType::Keyboard), m_EventCallback(eventCallback)
	{}

	void TriggerEventCallback(const Event& event) override;
private:
	std::function<void(const KeyboardEvent&)> m_EventCallback;
};