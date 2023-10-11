#pragma once

#include <cstdint>

struct Event
{
	uint32_t windowWidth, windowHeight;

	int key, keyAction;

	double mousePositionX, mousePositionY;
	int mouseButton, mouseAction;
};