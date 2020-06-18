#pragma once
#include "spacecraft.hpp"

namespace gsi
{
	class CHostileSpacecraft
		: public CSpacecraft
	{
	public:
		using CSpacecraft::CSpacecraft;

		CHostileSpacecraft();
		virtual ~CHostileSpacecraft() = default;

		float getSwitchDistance() const;
		void setSwitchDistance(float);

		virtual void moveOverTime(float) override;

	private:
		EDirection lastDirection_;
		float switchDistance_;
		float movedDistance_;
	};
}