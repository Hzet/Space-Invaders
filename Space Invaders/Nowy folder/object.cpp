#include "object.hpp"

namespace gsi
{
	IObject::IObject()
		: direction_(DIRECTION_INVALID), velocity_(0.f)
	{}

	EDirection IObject::getDirection() const
	{
		return direction_;
	}

	void IObject::setDirection(EDirection direction)
	{
		direction_ = direction;
	}

	float IObject::getVelocity() const
	{
		return velocity_;
	}

	void IObject::setVelocity(float velocity)
	{
		if (velocity < 0.f)
			velocity = 0.f;
		velocity_ = velocity;
	}
}