#include "game-mechanics.hpp"

namespace gsi
{
	CGameMechanics::CGameMechanics(sf::RenderWindow &window)
		: frameTime_(0.f), playerHits_(0), hostileHits_(0), currentLevel_(0), window_(window)
	{}

	CGameMechanics::~CGameMechanics()
	{
		for (auto &v : levels_)
		{
			delete v;
			v = NULL;
		}
	}

	void CGameMechanics::setFrameTime(float frameTime)
	{
		if (frameTime < 0.f)
			frameTime = 0.f;
		frameTime_ = frameTime_;
	}

	float CGameMechanics::getFrameTime() const
	{
		return frameTime_;
	}

	int CGameMechanics::getPlayerHitsTotal() const
	{
		return playerHits_;
	}

	int CGameMechanics::getHostileHitsTotal() const
	{
		return hostileHits_;
	}

	void CGameMechanics::executeFrame()
	{
		moveObjects(getFrameTime());
		hostileHits_ += detectHostileHits();
		playerHits_ += detectPlayerHits();
		checkSpacecraftCollision(); 
	}

	void CGameMechanics::pollEvents()
	{
		sf::Event event;
		while (window_.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window_.close();
			else if (event.type == sf::Event::KeyPressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					levels_[currentLevel_]->spacecraft_.setDirection(gsi::EDirections::MOVE_LEFT);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					levels_[currentLevel_]->spacecraft_.setDirection(gsi::EDirections::MOVE_RIGHT);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					levels_[currentLevel_]->spacecraft_.setDirection(gsi::EDirections::MOVE_UP);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					levels_[currentLevel_]->spacecraft_.setDirection(gsi::EDirections::MOVE_DOWN);
				}
				else
				{
					levels_[currentLevel_]->spacecraft_.setDirection(gsi::EDirections::MOVE_INVALID);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					levels_[currentLevel_]->spacecraft_.shoot();
				}
			}
		}
	}

	bool CGameMechanics::checkSpacecraftCollision() const
	{
		for (const auto &v : levels_[currentLevel_]->levelObjects_)
			if (v->getType() == OBJECT_TYPE_SPACECRAFT)
				if (levels_[currentLevel_]->spacecraft_.getGlobalBounds().intersects(v->getGlobalBounds()))
					return false;
		return true;
	}

	int CGameMechanics::detectHostileHits() 
	{
		int result = 0;
		for(const auto &v : levels_[currentLevel_]->levelObjects_)
			if (v->getType() == OBJECT_TYPE_SPACECRAFT)
				for (const auto &vbullet :dynamic_cast<CSpacecraft*>(v)->getBulletsShoot())
					if(levels_[currentLevel_]->spacecraft_.getGlobalBounds().intersects(vbullet.getGlobalBounds()))
						result++;
		return result;
	}

	int CGameMechanics::detectPlayerHits()
	{

		int result = 0;
		for(auto it = levels_[currentLevel_]->spacecraft_.getBulletsShoot().begin(); it != levels_[currentLevel_]->spacecraft_.getBulletsShoot().end(); ++it)
			for(auto spaceIt = levels_[currentLevel_]->levelObjects_.begin(); spaceIt != levels_[currentLevel_]->levelObjects_.end(); ++spaceIt)
				if (it->getGlobalBounds().intersects((*spaceIt)->getGlobalBounds()))
				{
					levels_[currentLevel_]->spacecraft_.bulletsShoot_.erase(it);
					levels_[currentLevel_]->levelObjects_.erase(spaceIt);
					result++;
				}
		return result;
	}

	void CGameMechanics::moveObjects(float milliseconds)
	{
		levels_[currentLevel_]->spacecraft_.move(milliseconds);
		for (auto &v : levels_[currentLevel_]->levelObjects_)
			v->move(milliseconds);
	}
}