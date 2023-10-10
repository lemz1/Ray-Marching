#include "KeyboardEventListener.h"

void KeyboardEventListener::TriggerEventCallback(const Event& event)
{
	m_EventCallback(KeyboardEvent(event.key, event.keyAction));
}
