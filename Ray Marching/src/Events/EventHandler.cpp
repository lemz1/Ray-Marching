#include "EventHandler.h"

const void EventHandler::TriggerEventListeners(const EventType& eventType, const Event& event) const
{
	for (EventListener* eventListener : m_EventListeners)
	{
		if (eventType == eventListener->GetEventType())
		{
			eventListener->TriggerEventCallback(event);
		}
	}
}

void EventHandler::AddEventListener(EventListener* eventListener)
{
	m_EventListeners.push_back(eventListener);
}

void EventHandler::RemoveEventListener(EventListener* eventListener)
{
	auto iterator = std::find(m_EventListeners.begin(), m_EventListeners.end(), eventListener);
	if (iterator != m_EventListeners.end())
	{
		delete* iterator;
		m_EventListeners.erase(iterator);
	}
}

void EventHandler::RemoveEventListenerAt(uint32_t index)
{
	if (index >= m_EventListeners.size())
		return;

	delete m_EventListeners[index];
	m_EventListeners.erase(m_EventListeners.begin() + index);
}

void EventHandler::ClearEventListeners()
{
	for (EventListener* eventListener : m_EventListeners)
	{
		delete eventListener;
	}
	m_EventListeners.clear();
}
