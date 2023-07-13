#include "movable.hpp"

namespace gsi
{
	void IMovable::setVelocity(float velocity)
	{
		if (velocity < 0.f)
			velocity = 0.f;
		velocity_ = velocity;
	}

	float IMovable::getVelocity() const
	{
		return velocity_;
	}

	void IMovable::setDirection(EDirections direction)
	{
		direction_ = direction;
	}

	EDirections IMovable::getDirection() const
	{
		return direction_;
	}
}