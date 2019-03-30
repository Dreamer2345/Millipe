#pragma once

//
// MIT License
//
// Copyright (c) 2018-2019 Thomas Buckland (@Dreamer2345)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

//
// Reformatted by Pharap
//

#include <stddef.h>
#include <stdint.h>

#include "Direction.h"

class CentipedeSegment
{
private:
	uint8_t x;
	uint8_t y;
	uint8_t parent = 0;
	bool head;
	bool active;
	Direction direction;

public:
	void set(uint8_t x, uint8_t y, uint8_t parent, bool head)
	{
		this->x = x;
		this->y = y;
		this->parent = parent;
		this->head = head;
		this->active = true;
		this->direction = Direction::South;
	}

	bool isActive() const
	{
		return this->active;
	}

	bool isHead() const
	{
		return this->head;
	}

	Direction getDirection() const
	{
		return this->direction;
	}

	uint8_t getX() const
	{
		return x;
	}

	uint8_t getY() const
	{
		return y;
	}

	void setHead(bool head)
	{
		this->head = head;
	}

	void setDirection(Direction direction)
	{
		this->direction = direction;
	}

	void toggleDirection()
	{
		this->direction = getOtherDirection(this->direction);
	}

	void kill()
	{
		this->active = false;
	}

	void draw();

	void damage();

	void update();
};