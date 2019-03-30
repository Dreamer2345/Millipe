#include "Player.h"

#include <Arduboy2.h>

#include "Constants.h"
#include "Globals.h"
#include "Bullet.h"

void Player::move()
{
	if (arduboy.pressed(UP_BUTTON))
	{
		if (this->x > 0)
		{
			this->x -= 1;
		}
	}

	if (arduboy.pressed(DOWN_BUTTON))
	{
		if (this->x + 8 < 64)
		{
			this->x += 1;
		}
	}

	if (arduboy.justPressed(RIGHT_BUTTON) || arduboy.justPressed(A_BUTTON))
	{
		for (uint8_t i = 0; i < maxbullets; ++i)
		{
			if (!bullets[i].isActive())
			{
				bullets[i].set(0, x);

				sound.noTone();
				sound.tone(NOTE_D2, 50);
				break;
			}
		}
	}
}