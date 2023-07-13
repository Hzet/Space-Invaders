#pragma once
#include <iostream>

namespace gsi
{
	class CHealth
	{
	public:
		CHealth();
		virtual ~CHealth() = default;

		void setHealth(float);
		float getHealth() const;

		void setMaxHealth(float);
		float getMaxHealth() const;

	private:
		float maxHealth_;
		float health_;
	};
}