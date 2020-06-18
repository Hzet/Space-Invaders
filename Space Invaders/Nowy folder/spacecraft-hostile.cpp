#include "spacecraft-hostile.hpp"

namespace gsi
{
	CHostileSpacecraft::CHostileSpacecraft()
		: movedDistance_(0.f), switchDistance_(0.f), lastDirection_(DIRECTION_LEFT)
	{
		setDirection(DIRECTION_DOWN);
	}

	float CHostileSpacecraft::getSwitchDistance() const
	{
		return switchDistance_;
	}

	void CHostileSpacecraft::setSwitchDistance(float switchTime)
	{
		if (switchTime < 0.f)
			switchTime = 0.f;
		switchDistance_ = switchTime;
	}

	void CHostileSpacecraft::moveOverTime(float dTime)
	{
		movedDistance_ += getVelocity() * dTime;
		if (movedDistance_ >= getSwitchDistance())
		{
			movedDistance_ = 0.f;
			if (getDirection() == DIRECTION_DOWN)
			{
				if (lastDirection_ == DIRECTION_LEFT)
				{
					setDirection(DIRECTION_RIGHT);
					lastDirection_ = DIRECTION_RIGHT;
				}
				else
				{
					setDirection(DIRECTION_LEFT);
					lastDirection_ = DIRECTION_LEFT;
				}
			}
			else if (getDirection() == DIRECTION_LEFT || getDirection() == DIRECTION_RIGHT)
				setDirection(DIRECTION_DOWN);
		}

		// move bullets before messing with dTime
		for (auto &v : bullets_)
			v.moveOverTime(dTime);

		if (movedDistance_ > getSwitchDistance())
		{
			// calculate amount of redundant distance, convert it into time and subtract it from the original dTime
			// time = s / v 
			dTime -= (movedDistance_ - getSwitchDistance()) / getVelocity();
		}

		IObject::moveOverTime(dTime);
	}
}