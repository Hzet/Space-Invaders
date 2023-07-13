#pragma once
#include "game-object.hpp"

namespace gsi
{
	enum EDirections
	{
		MOVE_INVALID = -1,
		MOVE_UP,
		MOVE_RIGHT,
		MOVE_DOWN,
		MOVE_LEFT
	};

	class IMovable
		: public IGameObject
	{
	public:
		using IGameObject::IGameObject;

		void setVelocity(float);
		float getVelocity() const;

		void setDirection(EDirections);
		EDirections getDirection() const;

		virtual void move(double time)
		{
			double factor = (double)velocity_ * time;
			switch (direction_)
			{
			case MOVE_UP:
				sf::Sprite::move(0, factor * -1);
				break;
			case MOVE_RIGHT:
				sf::Sprite::move(factor, 0);
				break;
			case MOVE_DOWN:
				sf::Sprite::move(0, factor);
				break;
			case MOVE_LEFT:
				sf::Sprite::move(factor * -1, 0);
				break;
			default:
				break;
			}
		}

	private:
		EDirections direction_;
		float velocity_;
	};
}