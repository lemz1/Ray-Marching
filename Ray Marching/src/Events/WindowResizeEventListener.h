#pragma once

#include <functional>

#include "../Core/EventListener.h"
#include "WindowResizeEvent.h"

class WindowResizeEventListener : public EventListener
{
public:
	WindowResizeEventListener(std::function<void(const WindowResizeEvent&)> eventCallback)
		: EventListener(EventType::WindowResize), m_EventCallback(eventCallback)
	{}
	
	void TriggerEventCallback(const Event& event) override;
private:
	std::function<void(const WindowResizeEvent&)> m_EventCallback;
};