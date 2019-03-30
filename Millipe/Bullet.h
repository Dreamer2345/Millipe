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

#include "Constants.h"
#include "Bitmaps.h"

class Bullet
{
private:
	bool active = false;
	uint8_t x;
	uint8_t y;

public:
	void set(uint8_t x, uint8_t y)
	{
		this->x = x;
		this->y = y;
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

	void update()
	{
		if ((x + 8) < 127)
			this->x += 1;
		else
			this->active = false;
	}

	void draw()
	{
		Sprites::drawSelfMasked(x, y, Tiles, 6);
	}

	void kill()
	{
		this->active = false;
	}
};