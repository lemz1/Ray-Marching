#include "MouseButtonEventListener.h"

void MouseButtonEventListener::TriggerEventCallback(const Event& event)
{
	m_EventCallback(MouseButtonEvent(event.mouseButton, event.mouseAction));
}
