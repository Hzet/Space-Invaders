#pragma once
#include "level-basic.hpp"

namespace gsi
{
	class CGameMechanics
	{
	public:
		CGameMechanics(sf::RenderWindow&);
		virtual ~CGameMechanics();

		int getPlayerHitsTotal() const; // return total count of accurate player's shots
		int getHostileHitsTotal() const; // return total count of accurate hostile spacecrafts' shots
		
	protected:
		void setFrameTime(float);
		float getFrameTime() const;

		void executeFrame();
		void pollEvents();

		sf::RenderWindow &window_;
		size_t currentLevel_;
		std::vector<IBasicLevel*> levels_;

	private:
		bool checkSpacecraftCollision() const; //true if any hostile spacecraft colllides with player's spacecraft
		int detectHostileHits(); // count how many bullets did hostile spacecrafts hit
		int detectPlayerHits(); // count how many bullets did player hit
		void moveObjects(float);  // move objects according to their implementation

		int hostileHits_;
		int playerHits_;
		float frameTime_;
	};
}