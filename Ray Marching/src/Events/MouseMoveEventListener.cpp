#include "MouseMoveEventListener.h"

void MouseMoveEventListener::TriggerEventCallback(const Event& event)
{
	m_EventCallback(MouseMoveEvent(event.mousePositionX, event.mousePositionY));
}
