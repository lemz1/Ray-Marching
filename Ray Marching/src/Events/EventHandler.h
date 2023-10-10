#pragma once

#include <vector>

#include "Event.h"
#include "EventListener.h"
#include "EventType.h"

class EventHandler
{
public:
	const void TriggerEventListeners(const EventType& eventType, const Event& event) const;
	void AddEventListener(EventListener* eventListener);
	void RemoveEventListener(EventListener* eventListener);
	void RemoveEventListenerAt(uint32_t index);
	void ClearEventListeners();
private:
	std::vector<EventListener*> m_EventListeners;
};