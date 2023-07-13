#include "game-execution.hpp"


namespace gsi
{
	int CGame::getScore() const
	{
		return score_;
	}

	void CGame::setPlayerLives(int playerLives)
	{
		playerLives_ = playerLives;
	}

	void CGame::execute()
	{
		levels_.push_back(new Level1());

		sf::Clock frameTime;
		frameTime.restart();

		while (getHostileHitsTotal() < playerLives_ && window_.isOpen())
		{
			setFrameTime(frameTime.getElapsedTime().asMilliseconds());
			frameTime.restart();

			pollEvents();

			executeFrame();

			window_.clear(sf::Color::Black);
			levels_[currentLevel_]->drawElements(window_);
			window_.display();
		}
	}
}