#pragma once
#include "game-mechanics.hpp"
#include "Levels.hpp"

namespace gsi
{
	class CGame
		: protected CGameMechanics
	{
	public:
		using CGameMechanics::CGameMechanics;

		int getScore() const;
		void setPlayerLives(int);

		void execute();

	private:
		int score_;
		int playerLives_;
		float time_;
	};
}