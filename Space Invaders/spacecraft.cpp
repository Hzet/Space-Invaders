#include "spacecraft.hpp"

namespace gsi
{
	float CSpacecraft::UpperBulletBoundary = -20.f;
	float CSpacecraft::LowerBulletBoundary = 1050.f;

	CSpacecraft::CSpacecraft()
		: cooldown_(0.f), cooldownState_(0.f), isGunReady_(true)
	{
	}

	void CSpacecraft::shoot()
	{
		if (isGunReady())
		{
			CBullet bullet = bulletTemplate_;
			bullet.setPosition(getPosition().x + getGlobalBounds().width / 2.f, getPosition().y);
			bullets_.push_back(bullet);
			isGunReady_ = false;
		}
	}

	void CSpacecraft::updateBullets(float dTime)
	{
		if (!isGunReady_)
		{
			cooldownState_ += dTime;
			if (cooldownState_ >= getCooldown())
			{
				cooldownState_ = 0.f;
				isGunReady_ = true;
			}
		}

		auto end = bullets_.end();
		for (auto it = bullets_.begin(); it != end; ++it)
			if (it->getPosition().y < UpperBulletBoundary || it->getPosition().y > LowerBulletBoundary)
			{
				bullets_.erase(it);
				if (bullets_.empty())
					break;
				it = bullets_.begin();
				end = bullets_.end();
			}
	}

	std::vector<CBullet>& CSpacecraft::getBullets()
	{
		return bullets_;
	}

	const CBullet& CSpacecraft::getBullet() const
	{
		return bulletTemplate_;
	}

	void CSpacecraft::setBullet(const CBullet &bulletTemplate)
	{
		bulletTemplate_ = bulletTemplate;
	}

	bool CSpacecraft::isGunReady()
	{
		return isGunReady_;
	}

	float CSpacecraft::getCooldown() const
	{
		return cooldown_;
	}

	void CSpacecraft::setCooldown(float cooldown)
	{
		if (cooldown_ == 0.f)
		{
			if (cooldown < 0.f)
				cooldown = 0.f;
			cooldown_ = cooldown;
		}
	}

	int CSpacecraft::getType() const
	{
		return TYPE_SPACECRAFT;
	}

	void CSpacecraft::moveOverTime(float dTime)
	{
		IObject::moveOverTime(dTime);
		for (auto &v : bullets_)
			v.moveOverTime(dTime);
	}
}