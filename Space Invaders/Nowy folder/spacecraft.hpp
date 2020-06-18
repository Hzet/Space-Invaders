#pragma once
#include "bullet.hpp"

namespace gsi
{
	class CSpacecraft
		: public IObject
	{
	public:
		static float UpperBulletBoundary;
		static float LowerBulletBoundary;

		using IObject::IObject;

		CSpacecraft();
		virtual ~CSpacecraft() = default;

		void shoot();
		void updateBullets(float);

		std::vector<CBullet>& getBullets();
		const CBullet& getBullet() const;
		void setBullet(const CBullet&);

		bool isGunReady();
		float getCooldown() const;
		void setCooldown(float);

		virtual int getType() const override;
		virtual void moveOverTime(float) override;

	protected:
		bool isGunReady_;
		float cooldown_;
		float cooldownState_;
		CBullet bulletTemplate_;
		std::vector<CBullet> bullets_;
	};
}