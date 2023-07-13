#pragma once
#include "level-basic.hpp"

namespace gsi
{
	class Level1
		: public IBasicLevel
	{
		virtual void init() override
		{
			sf::Texture spaceTexture;
			spaceTexture.loadFromFile("PlayerSpacecraft.png");

			IGameObject::saveTexture("PlayerSpacecraft.png", spaceTexture);
			spacecraft_.setTexture(IGameObject::loadTexture("PlayerSpacecraft.png"));
		}
	};
}