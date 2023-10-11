#pragma once

#include "Event.h"
#include "EventType.h"

class EventListener
{
public:
	EventListener(const EventType& eventType) 
		: m_EventType(eventType) 
	{}
	
	virtual void TriggerEventCallback(const Event& event) = 0;
	const EventType& GetEventType() const { return m_EventType; }
protected:
	EventType m_EventType;
};
