#include "EventHandler.h"

#include <iostream>

EventHandler* EventHandler::s_Instance = nullptr;

EventHandler::EventHandler()
{
	if (s_Instance)
	{
		std::cout << "EventHandler already exists" << std::endl;
		return;
	}

	s_Instance = this;
}

EventHandler::~EventHandler()
{
	s_Instance = nullptr;
}

const void EventHandler::TriggerEventListeners(const EventType& eventType, const Event& event)
{
	for (EventListener* eventListener : s_Instance->m_EventListeners)
	{
		if (eventType == eventListener->GetEventType())
		{
			eventListener->TriggerEventCallback(event);
		}
	}
}

void EventHandler::AddEventListener(EventListener* eventListener)
{
	s_Instance->m_EventListeners.push_back(eventListener);
}

void EventHandler::RemoveEventListener(EventListener* eventListener)
{
	auto iterator = std::find(s_Instance->m_EventListeners.begin(), s_Instance->m_EventListeners.end(), eventListener);
	if (iterator != s_Instance->m_EventListeners.end())
	{
		delete* iterator;
		s_Instance->m_EventListeners.erase(iterator);
	}
}

void EventHandler::RemoveEventListenerAt(uint32_t index)
{
	if (index >= s_Instance->m_EventListeners.size())
		return;

	delete s_Instance->m_EventListeners[index];
	s_Instance->m_EventListeners.erase(s_Instance->m_EventListeners.begin() + index);
}

void EventHandler::ClearEventListeners()
{
	for (EventListener* eventListener : s_Instance->m_EventListeners)
	{
		delete eventListener;
	}
	s_Instance->m_EventListeners.clear();
}
