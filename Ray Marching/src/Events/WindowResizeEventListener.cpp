#include "WindowResizeEventListener.h"

void WindowResizeEventListener::TriggerEventCallback(const Event& event)
{
	m_EventCallback(WindowResizeEvent(event.windowWidth, event.windowHeight));
}
