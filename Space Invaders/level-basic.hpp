#pragma once
#include <vector>
#include "spacecraft.hpp"

namespace gsi
{
	class IBasicLevel
	{
	public:
		virtual ~IBasicLevel();

		virtual void init() = 0;

		void scaleLevel(float,float);

		void setPlayerSpacecraft(const CSpacecraft&);
		const CSpacecraft& getPlayerSpacecraft() const;

		void drawElements(sf::RenderWindow&) const;

	protected:
		friend class CGameMechanics;

		CSpacecraft spacecraft_;
		std::vector<IMovable*> levelObjects_;
	};
}