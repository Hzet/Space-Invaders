#include "bullet.hpp"

namespace gsi
{
	int CBullet::getType() const
	{
		return TYPE_BULLLET;
	}

	void CBullet::moveOverTime(float dTime)
	{
		float factor = getVelocity() * dTime;
		switch (getDirection())
		{
		case DIRECTION_UP:
			sf::Sprite::move(0, factor * -1);
			break;
		case DIRECTION_DOWN:
			sf::Sprite::move(0, factor);
			break;
		default:
			break;
		}
	}
}