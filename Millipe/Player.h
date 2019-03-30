#pragma once

#include <stddef.h>
#include <stdint.h>

class Player
{
public:
	uint8_t x;
	uint8_t h;

public:
	void move();
};