#include "health.hpp"

namespace gsi
{
	CHealth::CHealth()
		: health_(0.f), maxHealth_(0.f)
	{}

	void CHealth::setHealth(float health)
	{
		if (health < 0.f)
			health = 0.f;
		else if (health > maxHealth_)
			health = maxHealth_;
		health_ = health;
	}

	float CHealth::getHealth() const
	{
		return health_;
	}

	void CHealth::setMaxHealth(float maxHealth)
	{
		if (maxHealth_ == 0.f)
		{
			if (maxHealth < 0.f)
				maxHealth = 0.f;
			maxHealth_ = maxHealth;
			setHealth(maxHealth_);
		}
	}

	float CHealth::getMaxHealth() const
	{
		return maxHealth_;
	}
}