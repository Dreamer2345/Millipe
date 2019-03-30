#pragma once

#include <stddef.h>
#include <stdint.h>

#include "Constants.h"

class Mushroom
{
private:
	uint8_t x;
	uint8_t y;
	uint8_t h = 2;
	bool active = false;

public:
	void set(uint8_t x, uint8_t y)
	{
		this->x = x;
		this->y = y;
		this->h = 2;
		this->active = true;
	}

	bool isActive() const
	{
		return this->active;
	}

	uint8_t getX() const
	{
		return this->x;
	}

	uint8_t getY() const
	{
		return this->y;
	}

	void draw();

	void damage();
};