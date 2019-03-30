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

#include <stdint.h>

inline bool areRangesOverlapping(uint16_t min0, uint16_t max0, uint16_t min1, uint16_t max1)
{
	return ((max0 > min1) && (min0 < max1));
}

inline bool isCollision(uint16_t x, uint16_t y, uint16_t x1, uint16_t y1)
{
	return (areRangesOverlapping(x, x + 7, x1, x1 + 7) && areRangesOverlapping(y, y + 7, y1, y1 + 7));
}