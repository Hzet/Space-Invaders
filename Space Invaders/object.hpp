#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

namespace gsi
{
	enum EObjectType
	{
		TYPE_SPACECRAFT = 1,
		TYPE_BULLLET
	};

	enum EDirection
	{
		DIRECTION_INVALID = 1,
		DIRECTION_UP,
		DIRECTION_RIGHT,
		DIRECTION_DOWN,
		DIRECTION_LEFT
	};

	class IObject
		: public sf::Sprite
	{
	public:
		using sf::Sprite::Sprite;

		IObject();
		virtual ~IObject() = default;

		EDirection getDirection() const;
		void setDirection(EDirection);

		float getVelocity() const;
		void setVelocity(float);

		virtual int getType() const = 0;

		virtual void moveOverTime(float dTime)
		{
			float factor = getVelocity() * dTime;
			//std::cout << "Object: " << typeid(*this).name() << " Factor: " << factor << " Delta time:	" << dTime <<std::endl;
			switch (getDirection())
			{
			case DIRECTION_UP:
				sf::Sprite::move(0, factor * -1);
				break;
			case DIRECTION_RIGHT:
				sf::Sprite::move(factor, 0);
				break;
			case DIRECTION_DOWN:
				sf::Sprite::move(0, factor);
				break;
			case DIRECTION_LEFT:
				sf::Sprite::move(factor * -1, 0);
				break;
			default:
				break;
			}
		}

	private:
		EDirection direction_;
		float velocity_;
	};
}