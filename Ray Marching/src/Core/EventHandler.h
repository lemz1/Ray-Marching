#pragma once

#include <vector>

#include "Event.h"
#include "EventListener.h"
#include "EventType.h"

class EventHandler
{
public:
	EventHandler();
	~EventHandler();

	static const void TriggerEventListeners(const EventType& eventType, const Event& event);
	static void AddEventListener(EventListener* eventListener);
	static void RemoveEventListener(EventListener* eventListener);
	static void RemoveEventListenerAt(uint32_t index);
	static void ClearEventListeners();
private:
	static EventHandler* s_Instance;
	
	std::vector<EventListener*> m_EventListeners;
};